#include "UEGameAnalytics.h"
#include "Misc/ConfigCacheIni.h"
#include "Interfaces/IAnalyticsProvider.h"
#include "GameAnalyticsProvider.h"
#include "GameAnalytics.h"
#if PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include "../GA-SDK-CPP/GameAnalytics.h"
// #elif PLATFORM_HTML5
// #include "../GA-SDK-HTML5/GameAnalytics.h"
#endif

IMPLEMENT_MODULE( FAnalyticsGameAnalytics, GameAnalytics )

void FAnalyticsGameAnalytics::StartupModule()
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("FAnalyticsGameAnalytics Constructor"));
    GameAnalyticsProvider = MakeShareable(new FAnalyticsProviderGameAnalytics());
}

void FAnalyticsGameAnalytics::ShutdownModule()
{
    if (GameAnalyticsProvider.IsValid())
    {
        UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("FAnalyticsGameAnalytics Destructor"));
#if PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
        UGameAnalytics::onQuit();
#endif
    }
}

#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 13
TSharedPtr<IAnalyticsProvider> FAnalyticsGameAnalytics::CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const
{
    return GameAnalyticsProvider;
}
#else
TSharedPtr<IAnalyticsProvider> FAnalyticsGameAnalytics::CreateAnalyticsProvider(const FAnalytics::FProviderConfigurationDelegate& GetConfigValue) const
{
    return GameAnalyticsProvider;
}
#endif


FAnalyticsGameAnalytics::FGameAnalyticsProjectSettings FAnalyticsGameAnalytics::LoadProjectSettings()
{
    FGameAnalyticsProjectSettings Settings;

    if (!GConfig) return Settings;

    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidGameKey"), Settings.AndroidGameKey, GetIniName()))
    {
        Settings.AndroidGameKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidSecretKey"), Settings.AndroidSecretKey, GetIniName()))
    {
        Settings.AndroidSecretKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidBuild"), Settings.AndroidBuild, GetIniName()))
    {
        Settings.AndroidBuild = "0.1";
    }

    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosGameKey"), Settings.IosGameKey, GetIniName()))
    {
        Settings.IosGameKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosSecretKey"), Settings.IosSecretKey, GetIniName()))
    {
        Settings.IosSecretKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosBuild"), Settings.IosBuild, GetIniName()))
    {
        Settings.IosBuild = "0.1";
    }

    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("MacGameKey"), Settings.MacGameKey, GetIniName()))
    {
        Settings.MacGameKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("MacSecretKey"), Settings.MacSecretKey, GetIniName()))
    {
        Settings.MacSecretKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("MacBuild"), Settings.MacBuild, GetIniName()))
    {
        Settings.MacBuild = "0.1";
    }

    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("WindowsGameKey"), Settings.WindowsGameKey, GetIniName()))
    {
        Settings.WindowsGameKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("WindowsSecretKey"), Settings.WindowsSecretKey, GetIniName()))
    {
        Settings.WindowsSecretKey = "";
    }
    if(!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("WindowsBuild"), Settings.WindowsBuild, GetIniName()))
    {
        Settings.WindowsBuild = "0.1";
    }

    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("LinuxGameKey"), Settings.LinuxGameKey, GetIniName()))
    {
        Settings.LinuxGameKey = "";
    }
    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("LinuxSecretKey"), Settings.LinuxSecretKey, GetIniName()))
    {
        Settings.LinuxSecretKey = "";
    }
    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("LinuxBuild"), Settings.LinuxBuild, GetIniName()))
    {
        Settings.LinuxBuild = "0.1";
    }

    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("Html5GameKey"), Settings.Html5GameKey, GetIniName()))
    {
        Settings.Html5GameKey = "";
    }
    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("Html5SecretKey"), Settings.Html5SecretKey, GetIniName()))
    {
        Settings.Html5SecretKey = "";
    }
    if (!GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("Html5Build"), Settings.Html5Build, GetIniName()))
    {
        Settings.Html5Build = "0.1";
    }

    if(!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("UseManualSessionHandling"), Settings.UseManualSessionHandling, GetIniName()))
    {
        Settings.UseManualSessionHandling = false;
    }
    if(!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AutoDetectAppVersion"), Settings.AutoDetectAppVersion, GetIniName()))
    {
        Settings.AutoDetectAppVersion = false;
    }
    if (!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("DisableDeviceInfo"), Settings.DisableDeviceInfo, GetIniName()))
    {
        Settings.DisableDeviceInfo = false;
    }
    if(!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("InfoLogBuild"), Settings.InfoLogBuild, GetIniName()))
    {
        Settings.InfoLogBuild = true;
    }
    if(!GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("VerboseLogBuild"), Settings.VerboseLogBuild, GetIniName()))
    {
        Settings.VerboseLogBuild = false;
    }

    GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+CustomDimensions01"), Settings.CustomDimensions01, GetIniName());
    GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+CustomDimensions02"), Settings.CustomDimensions02, GetIniName());
    GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+CustomDimensions03"), Settings.CustomDimensions03, GetIniName());
    GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+ResourceCurrencies"), Settings.ResourceCurrencies, GetIniName());
    GConfig->GetArray(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("+ResourceItemTypes"), Settings.ResourceItemTypes, GetIniName());

    return Settings;
}


#if !UE_BUILD_SHIPPING
/**
* Verifies that the event name matches GameAnalytics's 32 char limit and warns if it doesn't
*/
inline void CheckEventNameLen(const FString& EventName)
{
    const int32 Length = EventName.Len();
    if (Length > 32)
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("GameAnalytics event name is too long: %s and will be truncated by GameAnalytics. 32 character max limit."), *EventName);
    }
    else if (Length == 0)
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("GameAnalytics event name is empty!"));
    }
}

#define WarnIfEventNameIsWrongLength(x) CheckEventNameLen(x)
#else
// Have these compile out
#define WarnIfEventNameIsWrongLength(x)
#endif



// Provider
FAnalyticsProviderGameAnalytics::FAnalyticsProviderGameAnalytics() :
    bHasSessionStarted(false),
    bHasWrittenFirstEvent(false),
    Age(0)
{
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
    AnalyticsFilePath = FPaths::ProjectSavedDir() + TEXT("Analytics/");
#else
    AnalyticsFilePath = FPaths::GameSavedDir() + TEXT("Analytics/");
#endif
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 15
    UserId = FPlatformMisc::GetDeviceId();
#else
    UserId = FPlatformMisc::GetUniqueDeviceId();
#endif
}

FAnalyticsProviderGameAnalytics::~FAnalyticsProviderGameAnalytics()
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("FAnalyticsGameAnalytics ~FAnalyticsProviderGameAnalytics"));
}

bool FAnalyticsProviderGameAnalytics::StartSession(const TArray<FAnalyticsEventAttribute>& Attributes)
{
    if(!bHasSessionStarted)
    {
        ProjectSettings = FAnalyticsGameAnalytics::LoadProjectSettings();

#if WITH_EDITOR
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 18
        gameanalytics::GameAnalytics::configureWritablePath(TCHAR_TO_UTF8(*FPaths::ProjectSavedDir()));
#else
        gameanalytics::GameAnalytics::configureWritablePath(TCHAR_TO_UTF8(*FPaths::GameSavedDir()));
#endif
#endif

        ////// Enable log
        UGameAnalytics::setEnabledInfoLog(ProjectSettings.InfoLogBuild);
        UGameAnalytics::setEnabledVerboseLog(ProjectSettings.VerboseLogBuild);

        if(ProjectSettings.AutoDetectAppVersion)
        {
            UGameAnalytics::configureAutoDetectAppVersion(ProjectSettings.AutoDetectAppVersion);
        }

        if (ProjectSettings.DisableDeviceInfo)
        {
            UGameAnalytics::disableDeviceInfo();
        }

        //// Configure build version
#if PLATFORM_IOS
        if(!ProjectSettings.AutoDetectAppVersion)
        {
            UGameAnalytics::configureBuild(TCHAR_TO_UTF8(*ProjectSettings.IosBuild));
        }
#elif PLATFORM_ANDROID
        if(!ProjectSettings.AutoDetectAppVersion)
        {
            UGameAnalytics::configureBuild(TCHAR_TO_UTF8(*ProjectSettings.AndroidBuild));
        }
#elif PLATFORM_MAC
        UGameAnalytics::configureBuild(TCHAR_TO_UTF8(*ProjectSettings.MacBuild));
#elif PLATFORM_WINDOWS
        UGameAnalytics::configureBuild(TCHAR_TO_UTF8(*ProjectSettings.WindowsBuild));
#elif PLATFORM_LINUX
        UGameAnalytics::configureBuild(TCHAR_TO_UTF8(*ProjectSettings.LinuxBuild));
// #elif PLATFORM_HTML5
//         UGameAnalytics::configureBuild(TCHAR_TO_UTF8(*ProjectSettings.Html5Build));
#endif

        ////// Configure available virtual currencies and item types
        if (ProjectSettings.ResourceCurrencies.Num() > 0)
        {
            UGameAnalytics::configureAvailableResourceCurrencies(ProjectSettings.ResourceCurrencies);
        }

        if (ProjectSettings.ResourceItemTypes.Num() > 0)
        {
            UGameAnalytics::configureAvailableResourceItemTypes(ProjectSettings.ResourceItemTypes);
        }

        // Configure available custom dimensions
        if (ProjectSettings.CustomDimensions01.Num() > 0)
        {
            UGameAnalytics::configureAvailableCustomDimensions01(ProjectSettings.CustomDimensions01);
        }

        if (ProjectSettings.CustomDimensions02.Num() > 0)
        {
            UGameAnalytics::configureAvailableCustomDimensions02(ProjectSettings.CustomDimensions02);
        }

        if (ProjectSettings.CustomDimensions03.Num() > 0)
        {
            UGameAnalytics::configureAvailableCustomDimensions03(ProjectSettings.CustomDimensions03);
        }

        if(ProjectSettings.UseManualSessionHandling)
        {
            UGameAnalytics::setEnabledManualSessionHandling(ProjectSettings.UseManualSessionHandling);
        }

        const int32 AttrCount = Attributes.Num();
        FString gameKey;
        FString secretKey;
        if (AttrCount > 0)
        {
            for (auto Attr : Attributes)
            {
#if PLATFORM_IOS
                if (Attr.GetName() == TEXT("ios_gameKey"))
                {
                    gameKey = Attr.GetValue();
                }
                else if (Attr.GetName() == TEXT("ios_secretKey"))
                {
                    secretKey = Attr.GetValue();
                }
#elif PLATFORM_ANDROID
                if (Attr.GetName() == TEXT("android_gameKey"))
                {
                    gameKey = Attr.GetValue();
                }
                else if (Attr.GetName() == TEXT("android_secretKey"))
                {
                    secretKey = Attr.GetValue();
                }
#elif PLATFORM_MAC
                if (Attr.GetName() == TEXT("mac_gameKey"))
                {
                    gameKey = Attr.GetValue();
                }
                else if (Attr.GetName() == TEXT("mac_secretKey"))
                {
                    secretKey = Attr.GetValue();
                }
#elif PLATFORM_WINDOWS
                if (Attr.GetName() == TEXT("windows_gameKey"))
                {
                    gameKey = Attr.GetValue();
                }
                else if (Attr.GetName() == TEXT("windows_secretKey"))
                {
                    secretKey = Attr.GetValue();
                }
#elif PLATFORM_LINUX
                if (Attr.GetName() == TEXT("linux_gameKey"))
                {
                    gameKey = Attr.GetValue();
                }
                else if (Attr.GetName() == TEXT("linux_secretKey"))
                {
                    secretKey = Attr.GetValue();
                }
// #elif PLATFORM_HTML5
//                 if (Attr.GetName() == TEXT("html5_gameKey"))
//                 {
//                     gameKey = Attr.GetValue();
//                 }
//                 else if (Attr.GetName() == TEXT("html5_secretKey"))
//                 {
//                     secretKey = Attr.GetValue();
//                 }
#endif
            }
        }
        else
        {
#if PLATFORM_IOS
            gameKey = ProjectSettings.IosGameKey;
            secretKey = ProjectSettings.IosSecretKey;
#elif PLATFORM_ANDROID
            gameKey = ProjectSettings.AndroidGameKey;
            secretKey = ProjectSettings.AndroidSecretKey;
#elif PLATFORM_MAC
            gameKey = ProjectSettings.MacGameKey;
            secretKey = ProjectSettings.MacSecretKey;
#elif PLATFORM_WINDOWS
            gameKey = ProjectSettings.WindowsGameKey;
            secretKey = ProjectSettings.WindowsSecretKey;
#elif PLATFORM_LINUX
            gameKey = ProjectSettings.LinuxGameKey;
            secretKey = ProjectSettings.LinuxSecretKey;
// #elif PLATFORM_HTML5
//             gameKey = ProjectSettings.Html5GameKey;
//             secretKey = ProjectSettings.Html5SecretKey;
#endif
        }
        UGameAnalytics::initialize(TCHAR_TO_UTF8(*gameKey), TCHAR_TO_UTF8(*secretKey));
        bHasSessionStarted = true;
    }
    else if(ProjectSettings.UseManualSessionHandling)
    {
        UGameAnalytics::startSession();
    }

    return bHasSessionStarted;
}

void FAnalyticsProviderGameAnalytics::EndSession()
{
    if (bHasSessionStarted)
    {
        if(ProjectSettings.UseManualSessionHandling)
        {
            UGameAnalytics::endSession();
        }
        else
        {
#if WITH_EDITOR
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
            gameanalytics::GameAnalytics::onSuspend();
// #elif PLATFORM_HTML5
//             js_onStop();
#else
            UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::EndSession ignored."));
#endif
        }
    }
}

void FAnalyticsProviderGameAnalytics::FlushEvents()
{
    UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::FlushEvents ignored."));
}

void FAnalyticsProviderGameAnalytics::SetUserID(const FString& InUserID)
{
    if(!bHasSessionStarted)
    {
        UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::SetCustomId('%s')"), *InUserID);
        UGameAnalytics::configureUserId(TCHAR_TO_UTF8(*InUserID));
        UserId = InUserID;
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::SetCustomId Custom id can only be set when SDK is not initialized."));
    }
}

FString FAnalyticsProviderGameAnalytics::GetUserID() const
{
    return UserId;
}

FString FAnalyticsProviderGameAnalytics::GetSessionID() const
{
    UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::GetSessionID ignored."));
    return SessionId;
}

bool FAnalyticsProviderGameAnalytics::SetSessionID(const FString& InSessionID)
{
    UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::SetSessionID ignored."));
    return !bHasSessionStarted;
}

void FAnalyticsProviderGameAnalytics::RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        // Send an event for each attribute
        for (auto Attr : Attributes)
        {
            if (Attr.GetName() == TEXT("custom1"))
            {
                UGameAnalytics::setCustomDimension01(TCHAR_TO_UTF8(*Attr.GetValue()));
            }
            else if (Attr.GetName() == TEXT("custom2"))
            {
                UGameAnalytics::setCustomDimension02(TCHAR_TO_UTF8(*Attr.GetValue()));
            }
            else if (Attr.GetName() == TEXT("custom3"))
            {
                UGameAnalytics::setCustomDimension03(TCHAR_TO_UTF8(*Attr.GetValue()));
            }
            else
            {
                float AttrValue = FCString::Atof(*Attr.GetValue());
                UGameAnalytics::addDesignEvent(TCHAR_TO_UTF8(*Attr.GetName()), AttrValue);
            }
        }
    }
    else if (EventName.Len() > 0)
    {
        // Send an event without value
        UGameAnalytics::addDesignEvent(TCHAR_TO_UTF8(*EventName));
    }
}

void FAnalyticsProviderGameAnalytics::SetAge(int InAge)
{
}

void FAnalyticsProviderGameAnalytics::SetGender(const FString& InGender)
{
}

void FAnalyticsProviderGameAnalytics::RecordError(const FString& Error)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordError(const FString& Error) - ignoring call"));
}

void FAnalyticsProviderGameAnalytics::RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    EGAErrorSeverity ErrorSeverity = GetEnumValueFromString<EGAErrorSeverity>("EGAErrorSeverity", Error.ToLower());

    if (ErrorSeverity == EGAErrorSeverity(0))
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordError: Error value must be either debug, info, warning, error, critical. Error=%s"), *Error);
        return;
    }

    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        for (auto Attr : Attributes)
        {
            if (Attr.GetName() == TEXT("message"))
            {
                UGameAnalytics::addErrorEvent(ErrorSeverity, TCHAR_TO_UTF8(*Attr.GetValue()));
            }
        }
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordError wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Error%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy)
{
    EGAProgressionStatus ProgressionStatus = GetEnumValueFromString<EGAProgressionStatus>("EGAProgressionStatus", ProgressType.ToLower());

    if (ProgressionStatus == EGAProgressionStatus(0))
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordProgress: ProgressType value must be either start, complete or fail. ProgressType=%s"), *ProgressType);
        return;
    }

    UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy));
}

void FAnalyticsProviderGameAnalytics::RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    EGAProgressionStatus ProgressionStatus = GetEnumValueFromString<EGAProgressionStatus>("EGAProgressionStatus", ProgressType.ToLower());

    if (ProgressionStatus == EGAProgressionStatus(0))
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordProgress: ProgressType value must be either start, complete or fail. ProgressType=%s"), *ProgressType);
        return;
    }

    bool useValue = false;

    for (auto Attr : Attributes)
    {
        if (Attr.GetName() == TEXT("value"))
        {
            int32 value = FCString::Atoi(*Attr.GetValue());
            useValue = true;

            UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy), value);
            break;
        }
    }

    if (!useValue)
    {
        UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy));
    }
}

void FAnalyticsProviderGameAnalytics::RecordProgress(const FString& ProgressType, const TArray<FString>& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    EGAProgressionStatus ProgressionStatus = GetEnumValueFromString<EGAProgressionStatus>("EGAProgressionStatus", ProgressType.ToLower());

    if (ProgressionStatus == EGAProgressionStatus(0))
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordProgress: ProgressType value must be either start, complete or fail. ProgressType=%s"), *ProgressType);
        return;
    }

    const int32 ProgressHierarchyCount = ProgressHierarchy.Num();
    if(ProgressHierarchyCount > 0)
    {
        bool useValue = false;

        for (auto Attr : Attributes)
        {
            UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordProgress: Attributes. AttrName=%s"), *Attr.GetName());
            if (Attr.GetName() == TEXT("value"))
            {
                int32 value = FCString::Atoi(*Attr.GetValue());
                useValue = true;

                if (ProgressHierarchyCount > 2)
                {
                    UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy[0]), TCHAR_TO_UTF8(*ProgressHierarchy[1]), TCHAR_TO_UTF8(*ProgressHierarchy[2]), value);
                }
                else if (ProgressHierarchyCount > 1)
                {
                    UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy[0]), TCHAR_TO_UTF8(*ProgressHierarchy[1]), value);
                }
                else
                {
                    UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy[0]), value);
                }
                break;
            }
        }

        if (ProgressHierarchyCount > 2)
        {
            if(!useValue)
            {
                UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy[0]), TCHAR_TO_UTF8(*ProgressHierarchy[1]), TCHAR_TO_UTF8(*ProgressHierarchy[2]));
            }
        }
        else if (ProgressHierarchyCount > 1)
        {
            if(!useValue)
            {
                UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy[0]), TCHAR_TO_UTF8(*ProgressHierarchy[1]));
            }
        }
        else
        {
            if(!useValue)
            {
                UGameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*ProgressHierarchy[0]));
            }
        }
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordProgress wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Progression%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity)
{
    UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity) ignored. Instead use: FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    EGAResourceFlowType FlowType = EGAResourceFlowType::source;
    FString Currency;
    FString ItemType;

    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        for (auto Attr : Attributes)
        {
            if (Attr.GetName() == TEXT("flowType"))
            {
                FlowType = GetEnumValueFromString<EGAResourceFlowType>("EGAResourceFlowType", Attr.GetValue().ToLower());

                if (FlowType == EGAResourceFlowType(0))
                {
                    UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordItemPurchaseError: FlowType value must be either sink or source. flowType=%s"), *Attr.GetValue());
                    return;
                }
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
            UGameAnalytics::addResourceEvent(FlowType, TCHAR_TO_UTF8(*Currency), ItemQuantity, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId));
        }
        else
        {
            UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordItemPurchase wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Resource%20Event"));
        }
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordItemPurchase wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Resource%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider) - ignoring call. Instead use: FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount) - ignoring call. Instead use: FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)"));
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    FString ItemType;
    FString ItemId;
    FString CartType;
    FString Receipt;
    FString Signature;
    bool AutoFetchReceipt = false;

    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0)
    {
        for (auto Attr : Attributes)
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
        }

        if (!ItemType.IsEmpty() && !ItemId.IsEmpty() && !CartType.IsEmpty())
        {
#if PLATFORM_ANDROID
            if (!Receipt.IsEmpty() && !Signature.IsEmpty())
            {
                UGameAnalytics::addBusinessEvent(TCHAR_TO_UTF8(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType), TCHAR_TO_UTF8(*Receipt), TCHAR_TO_UTF8(*Signature));
            }
            else
            {
                UGameAnalytics::addBusinessEvent(TCHAR_TO_UTF8(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType));
            }
#elif PLATFORM_IOS
            if (!Receipt.IsEmpty())
            {
                UGameAnalytics::addBusinessEvent(TCHAR_TO_UTF8(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType), TCHAR_TO_UTF8(*Receipt));
            }
            else
            {
                if(AutoFetchReceipt)
                {
                    UGameAnalytics::addBusinessEventAndAutoFetchReceipt(TCHAR_TO_UTF8(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType));
                }
                else
                {
                    UGameAnalytics::addBusinessEvent(TCHAR_TO_UTF8(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType));
                }
            }
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
            UGameAnalytics::addBusinessEvent(TCHAR_TO_UTF8(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType));
#endif
        }
        else
        {
            UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Business%20Event"));
        }
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Business%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordCurrencyGiven - ignoring call"));
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordCurrencyGiven - ignoring call"));
}
