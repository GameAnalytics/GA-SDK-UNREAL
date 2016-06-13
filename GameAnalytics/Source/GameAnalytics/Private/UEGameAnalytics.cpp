#include "GameAnalyticsPrivatePCH.h"
#include "GameAnalytics.h"

#include "EngineVersion.h"

#define GA_VERSION_MAJOR 2
#define GA_VERSION_MINOR 0
#define GA_VERSION_PATCH 0

DEFINE_LOG_CATEGORY_STATIC(LogGameAnalyticsAnalytics, Display, All);

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
		GameAnalyticsProvider->EndSession();
	}
}

TSharedPtr<IAnalyticsProvider> FAnalyticsGameAnalytics::CreateAnalyticsProvider(const FAnalytics::FProviderConfigurationDelegate& GetConfigValue) const
{	
	return GameAnalyticsProvider;
}

FAnalyticsGameAnalytics::FGameAnalyticsProjectSettings FAnalyticsGameAnalytics::LoadProjectSettings()
{
	FGameAnalyticsProjectSettings Settings;

	if (!GConfig) return Settings;

	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidGameKey"), Settings.AndroidGameKey, GetIniName());
	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidSecretKey"), Settings.AndroidSecretKey, GetIniName());
	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidBuild"), Settings.AndroidBuild, GetIniName());

	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosGameKey"), Settings.IosGameKey, GetIniName());
	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosSecretKey"), Settings.IosSecretKey, GetIniName());
	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosBuild"), Settings.IosBuild, GetIniName());

    GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("UseCustomId"), Settings.UseCustomId, GetIniName());
	GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("InfoLogBuild"), Settings.InfoLogBuild, GetIniName());
	GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("VerboseLogBuild"), Settings.VerboseLogBuild, GetIniName());

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
	AnalyticsFilePath = FPaths::GameSavedDir() + TEXT("Analytics/");
	UserId = FPlatformMisc::GetUniqueDeviceId();
}

FAnalyticsProviderGameAnalytics::~FAnalyticsProviderGameAnalytics()
{
	if (bHasSessionStarted)
	{
		EndSession();
	}
}

bool FAnalyticsProviderGameAnalytics::StartSession(const TArray<FAnalyticsEventAttribute>& Attributes)
{
	ProjectSettings = FAnalyticsGameAnalytics::LoadProjectSettings();
	
    ////// Enable log
    gameanalytics::GameAnalytics::setEnabledInfoLog(ProjectSettings.InfoLogBuild);
    gameanalytics::GameAnalytics::setEnabledVerboseLog(ProjectSettings.VerboseLogBuild);
			
	////// Configure engine version 
    FString EngineVersionString = FString::Printf(TEXT("unreal %d.%d.%d"), FEngineVersion::Current().GetMajor(), FEngineVersion::Current().GetMinor(), FEngineVersion::Current().GetPatch());
	gameanalytics::GameAnalytics::configureGameEngineVersion(TCHAR_TO_ANSI(*EngineVersionString));
    FString SdkVersionString = FString::Printf(TEXT("unreal %d.%d.%d"), GA_VERSION_MAJOR, GA_VERSION_MINOR, GA_VERSION_PATCH);
	gameanalytics::GameAnalytics::configureSdkGameEngineVersion(TCHAR_TO_ANSI(*SdkVersionString));
    
    //// Configure build version
#if PLATFORM_IOS
    gameanalytics::GameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.IosBuild));
#elif PLATFORM_ANDROID
    gameanalytics::GameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.AndroidBuild));
#endif

	////// Configure available virtual currencies and item types
	if (ProjectSettings.ResourceCurrencies.Num() > 0)
	{
		std::vector<std::string> currencies;
		for (const FString& currency : ProjectSettings.ResourceCurrencies)
		{
			currencies.push_back(TCHAR_TO_ANSI(*currency));
		}
		gameanalytics::GameAnalytics::configureAvailableResourceCurrencies(currencies);
	}

	if (ProjectSettings.ResourceItemTypes.Num() > 0)
	{
		std::vector<std::string> resourceItem;
		for (const FString& item : ProjectSettings.ResourceItemTypes)
		{
			resourceItem.push_back(TCHAR_TO_ANSI(*item));
		}
		gameanalytics::GameAnalytics::configureAvailableResourceItemTypes(resourceItem);
	}

	// Configure available custom dimensions
	if (ProjectSettings.CustomDimensions01.Num() > 0)
	{
		std::vector<std::string> customDimension01;
		for (const FString& dimension01 : ProjectSettings.CustomDimensions01)
		{
			customDimension01.push_back(TCHAR_TO_ANSI(*dimension01));
		}
		gameanalytics::GameAnalytics::configureAvailableCustomDimensions01(customDimension01);
	}

	if (ProjectSettings.CustomDimensions02.Num() > 0)
	{
		std::vector<std::string> customDimension02;
		for (const FString& dimension02 : ProjectSettings.CustomDimensions02)
		{
			customDimension02.push_back(TCHAR_TO_ANSI(*dimension02));
		}
		gameanalytics::GameAnalytics::configureAvailableCustomDimensions02(customDimension02);
	}

	if (ProjectSettings.CustomDimensions03.Num() > 0)
	{
		std::vector<std::string> customDimension03;
		for (const FString& dimension03 : ProjectSettings.CustomDimensions03)
		{
			customDimension03.push_back(TCHAR_TO_ANSI(*dimension03));
		}
		gameanalytics::GameAnalytics::configureAvailableCustomDimensions03(customDimension03);
	}

    if(!ProjectSettings.UseCustomId)
    {
	////// Initialize
#if PLATFORM_IOS
        gameanalytics::GameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.IosGameKey), TCHAR_TO_ANSI(*ProjectSettings.IosSecretKey));
#elif PLATFORM_ANDROID
        gameanalytics::GameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.AndroidGameKey), TCHAR_TO_ANSI(*ProjectSettings.AndroidSecretKey));
#endif
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::StartSession Custom id is enabled. Initialize is delayed until custom id has been set."));
    }

	bHasSessionStarted = true;
    
    return bHasSessionStarted;
}

void FAnalyticsProviderGameAnalytics::EndSession()
{
	UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::EndSession ignored."));
}

void FAnalyticsProviderGameAnalytics::FlushEvents()
{
	UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::FlushEvents ignored."));
}

void FAnalyticsProviderGameAnalytics::SetUserID(const FString& InUserID)
{
    if(ProjectSettings.UseCustomId)
    {
        UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::SetCustomId('%s')"), *InUserID);
        gameanalytics::GameAnalytics::configureUserId(TCHAR_TO_ANSI(*InUserID));
        UserId = InUserID;
#if PLATFORM_IOS
        gameanalytics::GameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.IosGameKey), TCHAR_TO_ANSI(*ProjectSettings.IosSecretKey));
#elif PLATFORM_ANDROID
        gameanalytics::GameAnalytics::initialize(TCHAR_TO_ANSI(*ProjectSettings.AndroidGameKey), TCHAR_TO_ANSI(*ProjectSettings.AndroidSecretKey));
#endif
    }
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::SetCustomId Custom id is not enabled."));
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
            if (Attr.AttrName == TEXT("custom1"))
            {
                gameanalytics::GameAnalytics::setCustomDimension01(TCHAR_TO_ANSI(*Attr.AttrValue));
            }
            else if (Attr.AttrName == TEXT("custom2"))
            {
                gameanalytics::GameAnalytics::setCustomDimension02(TCHAR_TO_ANSI(*Attr.AttrValue));
            }
            else if (Attr.AttrName == TEXT("custom3"))
            {
                gameanalytics::GameAnalytics::setCustomDimension03(TCHAR_TO_ANSI(*Attr.AttrValue));
            }
            else if (Attr.AttrName == TEXT("facebook"))
            {
                gameanalytics::GameAnalytics::setFacebookId(TCHAR_TO_ANSI(*Attr.AttrValue));
            }
            else
            {
                float AttrValue = FCString::Atof(*Attr.AttrValue);
                gameanalytics::GameAnalytics::addDesignEvent(TCHAR_TO_ANSI(*Attr.AttrName), AttrValue);
            }
        }
    }
    else if (EventName.Len() > 0)
    {
        // Send an event without value
        gameanalytics::GameAnalytics::addDesignEvent(TCHAR_TO_ANSI(*EventName));
    }
}

void FAnalyticsProviderGameAnalytics::SetAge(int InAge)
{
	gameanalytics::GameAnalytics::setBirthYear(InAge);
}

void FAnalyticsProviderGameAnalytics::SetGender(const FString& InGender)
{
    gameanalytics::EGAGender gender = GetEnumValueFromString<gameanalytics::EGAGender>("EGAGender", InGender.ToLower());
    
    if (gender == gameanalytics::EGAGender(0))
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("SetGender: Error value must be either male or female."));
        return;
    }
    
	gameanalytics::GameAnalytics::setGender(gender);
}

void FAnalyticsProviderGameAnalytics::RecordError(const FString& Error)
{
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordError(const FString& Error) - ignoring call"));
}

void FAnalyticsProviderGameAnalytics::RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& Attributes)
{	
	gameanalytics::EGAErrorSeverity ErrorSeverity = GetEnumValueFromString<gameanalytics::EGAErrorSeverity>("EGAErrorSeverity", Error.ToLower());

	if (ErrorSeverity == gameanalytics::EGAErrorSeverity(0))
	{
		UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordError: Error value must be either debug, info, warning, error, critical. Error=%s"), *Error);
		return;
	}

	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0)
	{
		for (auto Attr : Attributes)
		{
			if (Attr.AttrName == TEXT("message"))
			{
				gameanalytics::GameAnalytics::addErrorEvent(ErrorSeverity, TCHAR_TO_ANSI(*Attr.AttrValue));
			}
		}
	}
    else
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::RecordError wrong usage, for correct usage see: https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Error%20Event"));
    }
}

void FAnalyticsProviderGameAnalytics::RecordProgress(const FString& ProgressType, const TArray<FString>& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes)
{
    gameanalytics::EGAProgressionStatus ProgressionStatus = GetEnumValueFromString<gameanalytics::EGAProgressionStatus>("EGAProgressionStatus", ProgressType.ToLower());
    
    if (ProgressionStatus == gameanalytics::EGAProgressionStatus(0))
    {
        UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordProgress: ProgressType value must be either start, complete or fail. ProgressType=%s"), *ProgressType);
        return;
    }
    
    const int32 ProgressHierarchyCount = ProgressHierarchy.Num();
    if(ProgressHierarchyCount > 0)
    {
        int32 value;
        bool useValue = false;
        
        for (auto Attr : Attributes)
        {
            if (Attr.AttrName == TEXT("value"))
            {
                value = FCString::Atod(*Attr.AttrValue);
                useValue = true;
                break;
            }
        }
        
        if (ProgressHierarchyCount > 2)
        {
            if(useValue)
            {
                gameanalytics::GameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), TCHAR_TO_ANSI(*ProgressHierarchy[1]), TCHAR_TO_ANSI(*ProgressHierarchy[2]), value);
            }
            else
            {
                gameanalytics::GameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), TCHAR_TO_ANSI(*ProgressHierarchy[1]), TCHAR_TO_ANSI(*ProgressHierarchy[2]));
            }
        }
        else if (ProgressHierarchyCount > 1)
        {
            if(useValue)
            {
                gameanalytics::GameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), TCHAR_TO_ANSI(*ProgressHierarchy[1]), value);
            }
            else
            {
                gameanalytics::GameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), TCHAR_TO_ANSI(*ProgressHierarchy[1]));
            }
        }
        else
        {
            if(useValue)
            {
                gameanalytics::GameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]), value);
            }
            else
            {
                gameanalytics::GameAnalytics::addProgressionEvent(ProgressionStatus, TCHAR_TO_ANSI(*ProgressHierarchy[0]));
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
    gameanalytics::EGAResourceFlowType FlowType = gameanalytics::EGAResourceFlowType::source;
	FString Currency;
	FString ItemType;	

	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0)
	{
		for (auto Attr : Attributes)
		{
			if (Attr.AttrName == TEXT("flowType"))
			{
                FlowType = GetEnumValueFromString<gameanalytics::EGAResourceFlowType>("EGAResourceFlowType", Attr.AttrValue.ToLower());
				
                if (FlowType == gameanalytics::EGAResourceFlowType(0))
				{
					UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordItemPurchaseError: FlowType value must be either sink or source. flowType=%s"), *Attr.AttrValue);
					return;
				}
			}
			else if (Attr.AttrName == TEXT("currency"))
			{
				Currency = Attr.AttrValue;
			}
			else if (Attr.AttrName == TEXT("itemType"))
			{
				ItemType = Attr.AttrValue;
			}
		}

		if (!Currency.IsEmpty() && !ItemType.IsEmpty())
		{
			gameanalytics::GameAnalytics::addResourceEvent(FlowType, TCHAR_TO_ANSI(*Currency), ItemQuantity, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId));
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
			FString AttrString = Attr.AttrName;

			if (Attr.AttrName == TEXT("itemType"))
			{
				ItemType = Attr.AttrValue;
			}
			else if (Attr.AttrName == TEXT("itemId"))
			{
				ItemId = Attr.AttrValue;
			}
			else if (Attr.AttrName == TEXT("cartType"))
			{
				CartType = Attr.AttrValue;
			}
			else if (Attr.AttrName == TEXT("receipt"))
			{
				Receipt = Attr.AttrValue;
			}
			else if (Attr.AttrName == TEXT("autoFetchReceipt"))
			{
				if (Attr.AttrValue.ToBool())
				{
					AutoFetchReceipt = true;
				}
			}
			else if (Attr.AttrName == TEXT("signature"))
			{ 
				Signature = Attr.AttrValue;
			}
		}

		if (!ItemType.IsEmpty() && !ItemId.IsEmpty() && !CartType.IsEmpty())
		{
#if PLATFORM_ANDROID
			if (!Receipt.IsEmpty() && !Signature.IsEmpty())
			{
				gameanalytics::GameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType), TCHAR_TO_ANSI(*Receipt), TCHAR_TO_ANSI(*Signature));
			}
			else
			{
				gameanalytics::GameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType));
			}
#elif PLATFORM_IOS
			if (!Receipt.IsEmpty())
			{				
                gameanalytics::GameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType), TCHAR_TO_ANSI(*Receipt));
			}
			else
			{
                if(AutoFetchReceipt)
                {
                    gameanalytics::GameAnalytics::addBusinessEventAndAutoFetchReceipt(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType));
                }
                else
                {
                    gameanalytics::GameAnalytics::addBusinessEvent(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType));
                }
			}
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
