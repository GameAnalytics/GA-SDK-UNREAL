#include "GameAnalyticsProvider.h"
#include "GameAnalyticsModule.h"
#include "Misc/ConfigCacheIni.h"
#include "Interfaces/IAnalyticsProvider.h"
#include "GameAnalytics.h"

#if PLATFORM_WINDOWS
    #include "Windows/AllowWindowsPlatformTypes.h"
#endif

static const TMap<FString, EGAProgressionStatus> kProgressionStrings =
{
    {TEXT("start"),    EGAProgressionStatus::start},
    {TEXT("complete"), EGAProgressionStatus::complete},
    {TEXT("fail"),     EGAProgressionStatus::fail}
};

static const TMap<FString, EGAErrorSeverity> kSeverityStrings =
{
    {TEXT("debug"),    EGAErrorSeverity::debug},
    {TEXT("info"),     EGAErrorSeverity::info},
    {TEXT("warning"),  EGAErrorSeverity::warning},
    {TEXT("error"),    EGAErrorSeverity::error},
    {TEXT("critical"), EGAErrorSeverity::critical}
};

static const TMap<FString, EGAResourceFlowType> kFlowTypes =
{
    {TEXT("sink"),   EGAResourceFlowType::sink},
    {TEXT("source"), EGAResourceFlowType::source},
};

void GAPrintUsageWarning(const char* func)
{
    auto constexpr DOCS_LINK = TEXT("https://docs.gameanalytics.com/integrations/sdk/unreal");
    UE_LOG(LogGameAnalytics, Warning, TEXT("%hs(): wrong usage, for correct usage see: %s/event-tracking"), func, DOCS_LINK);
}

#define GA_USAGE_WARNING() GAPrintUsageWarning(__FUNCTION__)

#if PLATFORM_IOS
    #define GA_GAME_KEY_NAME    TEXT("ios_gameKey")
    #define GA_SECRET_KEY_NAME  TEXT("ios_secretKey")
#elif PLATFORM_ANDROID
    #define GA_GAME_KEY_NAME    TEXT("android_gameKey")
    #define GA_SECRET_KEY_NAME  TEXT("android_secretKey")
#elif PLATFORM_MAC
    #define GA_GAME_KEY_NAME    TEXT("mac_gameKey")
    #define GA_SECRET_KEY_NAME  TEXT("mac_secretKey")
#elif PLATFORM_WINDOWS
    #define GA_GAME_KEY_NAME    TEXT("windows_gameKey")
    #define GA_SECRET_KEY_NAME  TEXT("windows_secretKey")
#elif PLATFORM_LINUX
    #define GA_GAME_KEY_NAME    TEXT("linux_gameKey")
    #define GA_SECRET_KEY_NAME  TEXT("linux_secretKey")
#else
    #define GA_GAME_KEY_NAME    TEXT("")
    #define GA_SECRET_KEY_NAME  TEXT("")
#endif

FString FGameAnalyticsProvider::GenerateUserId() const
{
    #if (ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 15) || (ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 0)
        return FPlatformMisc::GetDeviceId();
    #else
        return FPlatformMisc::GetUniqueDeviceId();
    #endif
}

FString FGameAnalyticsProvider::GetAnalyticsPath() const
{
    #if (ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18) || (ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 0)
        return FPaths::ProjectSavedDir();
    #else
        return FPaths::GameSavedDir();
    #endif
}

#if !UE_BUILD_SHIPPING
    /**
    * Verifies that the event name matches GameAnalytics's 32 char limit and warns if it doesn't
    */
    inline void CheckEventNameLen(const FString& EventName)
    {
        constexpr int32 kMaxLength = 32;
        
        const int32 Length = EventName.Len();
        if (Length > kMaxLength)
        {
            UE_LOG(LogGameAnalytics, Warning, TEXT("GameAnalytics event name is too long: %s and will be truncated by GameAnalytics. %i characters max limit."), *EventName, kMaxLength);
        }
        else if (Length == 0)
        {
            UE_LOG(LogGameAnalytics, Warning, TEXT("GameAnalytics event name is empty!"));
        }
    }

    #define WarnIfEventNameIsWrongLength(x) CheckEventNameLen(x)

#else
    // Have these compile out
    #define WarnIfEventNameIsWrongLength(x)
#endif

// Provider
FGameAnalyticsProvider::FGameAnalyticsProvider(UGameAnalytics* GameAnalytics) :
    bHasSessionStarted(false),
    bHasWrittenFirstEvent(false),
    Age(0),
    GameAnalytics(GameAnalytics)
{
    AnalyticsFilePath = GetAnalyticsPath() + TEXT("Analytics/");
}

FGameAnalyticsProvider::~FGameAnalyticsProvider()
{
    UE_LOG(LogGameAnalytics, Display, TEXT("FGameAnalyticsModule ~FGameAnalyticsProvider"));
}

void FGameAnalyticsProvider::SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&& Attributes)
{
    (void)Attributes;
}

TArray<FAnalyticsEventAttribute> FGameAnalyticsProvider::GetDefaultEventAttributesSafe() const
{
    return {};
}

int32 FGameAnalyticsProvider::GetDefaultEventAttributeCount() const
{
    return 0;
} 

FAnalyticsEventAttribute FGameAnalyticsProvider::GetDefaultEventAttribute(int AttributeIndex) const
{
    (void)AttributeIndex;
    return FAnalyticsEventAttribute();
}

void FGameAnalyticsProvider::OnQuit()
{
    GameAnalytics->OnQuit();
}

bool FGameAnalyticsProvider::StartSession(const TArray<FAnalyticsEventAttribute>& Attributes)
{
    if(!bHasSessionStarted)
    {
        ProjectSettings = FGameAnalyticsModule::LoadProjectSettings();
        
        auto PlatformInfo = ProjectSettings.GetActivePlatform();
        
        GameAnalytics->SetWritablePath(GetAnalyticsPath());

        ////// Enable log
        GameAnalytics->SetEnabledInfoLog(ProjectSettings.InfoLogBuild);
        GameAnalytics->SetEnabledVerboseLog(ProjectSettings.VerboseLogBuild);

        if(ProjectSettings.AutoDetectAppVersion)
        {
            GameAnalytics->ConfigureAutoDetectAppVersion(ProjectSettings.AutoDetectAppVersion);
        }

        if (ProjectSettings.DisableDeviceInfo)
        {
            GameAnalytics->DisableDeviceInfo();
        }

        //// Configure build version
        if(!ProjectSettings.AutoDetectAppVersion)
        {
            GameAnalytics->ConfigureBuild(PlatformInfo.Build);
        }

        ////// Configure available virtual currencies and item types
        if (ProjectSettings.ResourceCurrencies.Num() > 0)
        {
            GameAnalytics->ConfigureAvailableResourceCurrencies(ProjectSettings.ResourceCurrencies);
        }

        if (ProjectSettings.ResourceItemTypes.Num() > 0)
        {
            GameAnalytics->ConfigureAvailableResourceItemTypes(ProjectSettings.ResourceItemTypes);
        }

        // Configure available custom dimensions
        if (ProjectSettings.CustomDimensions01.Num() > 0)
        {
            GameAnalytics->ConfigureAvailableCustomDimensions01(ProjectSettings.CustomDimensions01);
        }

        if (ProjectSettings.CustomDimensions02.Num() > 0)
        {
            GameAnalytics->ConfigureAvailableCustomDimensions02(ProjectSettings.CustomDimensions02);
        }

        if (ProjectSettings.CustomDimensions03.Num() > 0)
        {
            GameAnalytics->ConfigureAvailableCustomDimensions03(ProjectSettings.CustomDimensions03);
        }

        if(ProjectSettings.UseManualSessionHandling)
        {
            GameAnalytics->SetEnabledManualSessionHandling(ProjectSettings.UseManualSessionHandling);
        }

        GameAnalytics->SetEnabledErrorReporting(ProjectSettings.UseErrorReporting);

        const int32 AttrCount = Attributes.Num();
        FString GameKey;
        FString SecretKey;
        if (AttrCount > 0)
        {
            for (auto Attr : Attributes)
            {
                if (Attr.GetName() == GA_GAME_KEY_NAME)
                {
                    GameKey = Attr.GetValue();
                }
                else if (Attr.GetName() == GA_SECRET_KEY_NAME)
                {
                    SecretKey = Attr.GetValue();
                }
            }
        }
        else
        {
            GameKey   = PlatformInfo.GameKey;
            SecretKey = PlatformInfo.SecretKey;
        }

        GameAnalytics->Initialize(GameKey, SecretKey);
        bHasSessionStarted = true;
    }
    else if(ProjectSettings.UseManualSessionHandling)
    {
        GameAnalytics->StartSession();
    }

    return bHasSessionStarted;
}

void FGameAnalyticsProvider::EndSession()
{
    if (bHasSessionStarted)
    {
        if(ProjectSettings.UseManualSessionHandling)
        {
            GameAnalytics->EndSession();
        }
        else
        {
            UE_LOG(LogGameAnalytics, Warning, TEXT("FGameAnalyticsProvider::EndSession ignored."));
        }
    }
}

void FGameAnalyticsProvider::FlushEvents()
{
    UE_LOG(LogGameAnalytics, Warning, TEXT("FGameAnalyticsProvider::FlushEvents ignored."));
}

void FGameAnalyticsProvider::SetUserID(const FString& InUserID)
{
    if(!bHasSessionStarted)
    {
        UE_LOG(LogGameAnalytics, Display, TEXT("GameAnalytics::SetCustomId('%s')"), *InUserID);
        GameAnalytics->ConfigureUserId(InUserID);
        UserId = InUserID;
    }
    else
    {
        UE_LOG(LogGameAnalytics, Warning, TEXT("FGameAnalyticsProvider::SetCustomId Custom id can only be set when SDK is not initialized."));
    }
}

FString FGameAnalyticsProvider::GetUserID() const
{
    return UserId;
}

FString FGameAnalyticsProvider::GetSessionID() const
{
    UE_LOG(LogGameAnalytics, Warning, TEXT("FGameAnalyticsProvider::GetSessionID ignored."));
    return SessionId;
}

bool FGameAnalyticsProvider::SetSessionID(const FString& InSessionID)
{
    UE_LOG(LogGameAnalytics, Warning, TEXT("FGameAnalyticsProvider::SetSessionID ignored."));
    return !bHasSessionStarted;
}

void FGameAnalyticsProvider::RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        // Send an event for each attribute
        for (auto& Attr : Attributes)
        {
            if (Attr.GetName() == TEXT("custom1"))
            {
                GameAnalytics->SetCustomDimension01(Attr.GetValue());
            }
            else if (Attr.GetName() == TEXT("custom2"))
            {
                GameAnalytics->SetCustomDimension02(Attr.GetValue());
            }
            else if (Attr.GetName() == TEXT("custom3"))
            {
                GameAnalytics->SetCustomDimension03(Attr.GetValue());
            }
            else
            {
                float AttrValue = FCString::Atof(*Attr.GetValue());
                GameAnalytics->AddDesignEventWithValue(Attr.GetName(), AttrValue);
            }
        }
    }
    else if (EventName.Len() > 0)
    {
        // Send an event without value
        GameAnalytics->AddDesignEvent(EventName);
    }
}

void FGameAnalyticsProvider::SetAge(int InAge)
{
}

void FGameAnalyticsProvider::SetGender(const FString& InGender)
{
}

void FGameAnalyticsProvider::RecordError(const FString& Error)
{
    GameAnalytics->AddErrorEvent(EGAErrorSeverity::error, Error);
}

void FGameAnalyticsProvider::RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        for (auto Attr : Attributes)
        {
            if (Attr.GetName() == TEXT("severity"))
            {
                FString const Key = Attr.GetValue().ToLower();
                if (!kSeverityStrings.Contains(Key))
                {
                    UE_LOG(LogGameAnalytics, Warning, TEXT("RecordError: Severity value must be either debug, info, warning, error, critical. Error=%s"), *Error);
                    return;
                }
                
                EGAErrorSeverity ErrorSeverity = kSeverityStrings[Key];
                GameAnalytics->AddErrorEvent(ErrorSeverity, Error);
            }
        }
    }
    else
    {
        GA_USAGE_WARNING();
    }
}

void FGameAnalyticsProvider::RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy)
{
    FString const Key = ProgressType.ToLower();
    if (!kProgressionStrings.Contains(Key))
    {
        UE_LOG(LogGameAnalytics, Warning, TEXT("RecordProgress: ProgressType value must be either start, complete or fail. ProgressType=%s"), *ProgressType);
        return;
    }
    
    EGAProgressionStatus ProgressionStatus = kProgressionStrings[Key];
    GameAnalytics->AddProgressionEvent(ProgressionStatus, ProgressHierarchy);
}

void FGameAnalyticsProvider::RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    FString const Key = ProgressType.ToLower();
    
    if (!kProgressionStrings.Contains(Key))
    {
        UE_LOG(LogGameAnalytics, Warning, TEXT("RecordProgress: ProgressType value must be either start, complete or fail. ProgressType=%s"), *ProgressType);
        return;
    }
    
    EGAProgressionStatus ProgressionStatus = kProgressionStrings[Key];

    for (auto& Attr : Attributes)
    {
        if (Attr.GetName() == TEXT("value"))
        {
            FString const& Val = Attr.GetValue();
            if(Val.IsNumeric())
            {
                int32 value = FCString::Atoi(*Val);
                GameAnalytics->AddProgressionEventWithScore(ProgressionStatus, value, ProgressHierarchy);
                return;
            }
        }
    }

    GameAnalytics->AddProgressionEvent(ProgressionStatus, ProgressHierarchy);
}

void FGameAnalyticsProvider::RecordProgress(const FString& ProgressType, const TArray<FString>& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    FString const Key = ProgressType.ToLower();
    
    if (!kProgressionStrings.Contains(Key))
    {
        UE_LOG(LogGameAnalytics, Warning, TEXT("RecordProgress: ProgressType value must be either start, complete or fail. ProgressType=%s"), *ProgressType);
        return;
    }
    
    EGAProgressionStatus ProgressionStatus = kProgressionStrings[Key];

    const int32 ProgressHierarchyCount = ProgressHierarchy.Num();
    if(ProgressHierarchyCount > 0)
    {
        bool useValue = false;
        int32 value = 0;

        for (auto& Attr : Attributes)
        {
            UE_LOG(LogGameAnalytics, Warning, TEXT("RecordProgress: Attributes. AttrName=%s"), *Attr.GetName());
            if (Attr.GetName() == TEXT("value"))
            {
                useValue = true;
                value    = FCString::Atoi(*Attr.GetValue());
                break;
            }
        }

        switch(ProgressHierarchyCount)
        {
            case 1:
                return useValue ?
                    GameAnalytics->AddProgressionEventWithScore(ProgressionStatus, value, ProgressHierarchy[0]):
                    GameAnalytics->AddProgressionEvent(ProgressionStatus, ProgressHierarchy[0]);
            
            case 2:
                return useValue ?
                    GameAnalytics->AddProgressionEventWithScore(ProgressionStatus, value, ProgressHierarchy[0], ProgressHierarchy[1]):
                    GameAnalytics->AddProgressionEvent(ProgressionStatus, ProgressHierarchy[0], ProgressHierarchy[1]);
            
            default:
                return useValue ?
                    GameAnalytics->AddProgressionEventWithScore(ProgressionStatus, value, ProgressHierarchy[0], ProgressHierarchy[1], ProgressHierarchy[2]):
                    GameAnalytics->AddProgressionEvent(ProgressionStatus, ProgressHierarchy[0], ProgressHierarchy[1], ProgressHierarchy[2]);
        }
    }
    else
    {
        GA_USAGE_WARNING();
    }
}

void FGameAnalyticsProvider::RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity)
{
    UE_LOG(LogGameAnalytics, Warning, TEXT("FGameAnalyticsProvider::RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity) ignored. Please use instead: FGameAnalyticsProvider::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FGameAnalyticsProvider::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    EGAResourceFlowType FlowType = EGAResourceFlowType::source;
    FString Currency;
    FString ItemType;

    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        for (auto& Attr : Attributes)
        {
            if (Attr.GetName() == TEXT("flowType"))
            {
                FString const Key = Attr.GetValue().ToLower();
                if (!kFlowTypes.Contains(Key))
                {
                    UE_LOG(LogGameAnalytics, Warning, TEXT("RecordItemPurchaseError: FlowType value must be either sink or source. flowType=%s"), *Attr.GetValue());
                    return;
                }
                
                FlowType = kFlowTypes[Key];
            }
            else if (Attr.GetName() == TEXT("currency"))
            {
                Currency = Attr.GetValue();
            }
            else if (Attr.GetName() == TEXT("itemType"))
            {
                ItemType = Attr.GetValue();
            }
        }

        if (!Currency.IsEmpty() && !ItemType.IsEmpty())
        {
            GameAnalytics->AddResourceEvent(FlowType, Currency, ItemQuantity, ItemType, ItemId);
        }
        else
        {
            GA_USAGE_WARNING();
        }
    }
    else
    {
        GA_USAGE_WARNING();
    }
}

void FGameAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider)
{
    UE_LOG(LogGameAnalytics, Display, TEXT("FGameAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider) - ignoring call. Instead use: FGameAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FGameAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount)
{
    UE_LOG(LogGameAnalytics, Display, TEXT("FGameAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount) - ignoring call. Instead use: FGameAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FGameAnalyticsProvider::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    FString ItemType;
    FString ItemId;
    FString CartType;
    FString Receipt;
    FString Signature;
    FString Store;
    bool AutoFetchReceipt = false;

    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        for (auto& Attr : Attributes)
        {
            FString AttrString = Attr.GetName();

            if (Attr.GetName() == TEXT("itemType"))
            {
                ItemType = Attr.GetValue();
            }
            else if (Attr.GetName() == TEXT("itemId"))
            {
                ItemId = Attr.GetValue();
            }
            else if (Attr.GetName() == TEXT("cartType"))
            {
                CartType = Attr.GetValue();
            }
            else if (Attr.GetName() == TEXT("receipt"))
            {
                Receipt = Attr.GetValue();
            }
            else if (Attr.GetName() == TEXT("autoFetchReceipt"))
            {
                if (Attr.GetValue().ToBool())
                {
                    AutoFetchReceipt = true;
                }
            }
            else if (Attr.GetName() == TEXT("signature"))
            {
                Signature = Attr.GetValue();
            }
            else if (Attr.GetName() == TEXT("store"))
            {
                Store = Attr.GetValue();
            }
        }

        if (!ItemType.IsEmpty() && !ItemId.IsEmpty() && !CartType.IsEmpty())
        {
            if (!Receipt.IsEmpty())
            {
                GameAnalytics->AddBusinessEventWithReceipt(GameCurrencyType, GameCurrencyAmount, ItemType, ItemId, CartType, Receipt, Store, Signature);
            }
            else if(AutoFetchReceipt)
            {
                GameAnalytics->AddBusinessEventAndAutoFetchReceipt(GameCurrencyType, GameCurrencyAmount, ItemType, ItemId, CartType);
            }
            else
            {
                GameAnalytics->AddBusinessEvent(GameCurrencyType, GameCurrencyAmount, ItemType, ItemId, CartType);
            }
        }
        else
        {
            GA_USAGE_WARNING();
        }
    }
    else
    {
        GA_USAGE_WARNING();
    }
}

void FGameAnalyticsProvider::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount)
{
    UE_LOG(LogGameAnalytics, Display, TEXT("GameAnalytics::RecordCurrencyGiven - ignoring call"));
}

void FGameAnalyticsProvider::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    UE_LOG(LogGameAnalytics, Display, TEXT("GameAnalytics::RecordCurrencyGiven - ignoring call"));
}
