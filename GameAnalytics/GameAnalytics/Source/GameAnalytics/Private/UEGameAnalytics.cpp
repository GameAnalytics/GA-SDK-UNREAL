#include "GameAnalyticsPrivatePCH.h"

#include "GameAnalytics.h"

#include "EngineVersion.h"

#define GA_VERSION "1.0.0"

//#include "GameAnalyticsProjectSettings.h"

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

	// GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidGameKey"), Settings.AndroidGameKey, GEngineIni);
	// GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidSecretKey"), Settings.AndroidSecretKey, GEngineIni);
	// GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("AndroidBuild"), Settings.AndroidBuild, GEngineIni);

	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosGameKey"), Settings.IosGameKey, GEngineIni);
	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosSecretKey"), Settings.IosSecretKey, GEngineIni);
	GConfig->GetString(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("IosBuild"), Settings.IosBuild, GEngineIni);

	//Settings.SubmitErrors = Configs->Find(TEXT("SubmitErrors"))->ToBool();
	//Settings.SubmitAverageFPS = Configs->Find(TEXT("SubmitAverageFPS"))->ToBool();
	//Settings.SubmitCriticalFPS = Configs->Find(TEXT("SubmitCriticalFPS"))->ToBool();
	//Settings.InfoLogEditor = Configs->Find(TEXT("InfoLogEditor"))->ToBool();
	GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("InfoLogBuild"), Settings.InfoLogBuild, GEngineIni);
	GConfig->GetBool(TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings"), TEXT("VerboseLogBuild"), Settings.VerboseLogBuild, GEngineIni);

	GConfig->GetArray(TEXT("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings"), TEXT("CustomDimensions01"), Settings.CustomDimensions01, GEngineIni);
	GConfig->GetArray(TEXT("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings"), TEXT("CustomDimensions02"), Settings.CustomDimensions02, GEngineIni);
	GConfig->GetArray(TEXT("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings"), TEXT("CustomDimensions03"), Settings.CustomDimensions03, GEngineIni);
	GConfig->GetArray(TEXT("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings"), TEXT("ResourceCurrencies"), Settings.ResourceCurrencies, GEngineIni);
	GConfig->GetArray(TEXT("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings"), TEXT("ResourceItemTypes"), Settings.ResourceItemTypes, GEngineIni);

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

/*#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"

extern void AndroidThunkCpp_GameAnalyticsInit();
#endif*/


bool FAnalyticsProviderGameAnalytics::StartSession(const TArray<FAnalyticsEventAttribute>& Attributes)
{			
/*#if PLATFORM_ANDROID	
	AndroidThunkCpp_GameAnalyticsInit();
#endif*/

	ProjectSettings = FAnalyticsGameAnalytics::LoadProjectSettings();
	
	//// Configure build version
	#if PLATFORM_IOS
	gameanalytics::GameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.IosBuild));
	/*#elif PLATFORM_ANDROID
	gameanalytics::GameAnalytics::configureBuild(TCHAR_TO_ANSI(*ProjectSettings.AndroidBuild));*/
	#else
	#	error "unsupported platform"
	#endif
			
	////// Configure engine version 
	FString EngineVersionString = FString::Printf(TEXT("Unreal %d.%d.%d"), GEngineVersion.GetMajor(), GEngineVersion.GetMinor(), GEngineVersion.GetPatch());	
	gameanalytics::GameAnalytics::configureEngineVersion(TCHAR_TO_ANSI(*EngineVersionString));
	gameanalytics::GameAnalytics::configureSdkVersion(GA_VERSION);

	////// Enable log
	gameanalytics::GameAnalytics::setEnabledInfoLog(ProjectSettings.InfoLogBuild);
	gameanalytics::GameAnalytics::setEnabledVerboseLog(ProjectSettings.VerboseLogBuild);

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
		gameanalytics::GameAnalytics::configureAvailableCustomDimensions01(customDimension03);
	}

	////// Initialize
#if PLATFORM_IOS
	gameanalytics::GameAnalytics::initializeWithGameKey(TCHAR_TO_ANSI(*ProjectSettings.IosGameKey), TCHAR_TO_ANSI(*ProjectSettings.IosSecretKey));
/*#elif PLATFORM_ANDROID
	gameanalytics::GameAnalytics::initializeWithGameKey(TCHAR_TO_ANSI(*ProjectSettings.AndroidGameKey), TCHAR_TO_ANSI(*ProjectSettings.AndroidSecretKey));*/
#else
#	error "unsupported platform"
#endif

	bHasSessionStarted = true;

	/*//// start using the SDK

	//// set dimension (will persist cross session)
	gameanalytics::GameAnalytics::setCustomDimension01("ninja");

	// GameAnalytics::addBusinessEventWithCurrency("USD", 1000, "item", "id", "cart", "");
	// GameAnalytics::addBusinessEventWithCurrency("USD", 1000, "item", "id", "cart", true);
	// UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("AWESOME Unreal currency!"));

	gameanalytics::GameAnalytics::addDesignEventWithEventId("someEvent");
	gameanalytics::GameAnalytics::addDesignEventWithEventId("someEvent");
	gameanalytics::GameAnalytics::addDesignEventWithEventId("someEvent");
	gameanalytics::GameAnalytics::addDesignEventWithEventId("someOtherEvent", 100);
	gameanalytics::GameAnalytics::addErrorEventWithSeverity(gameanalytics::GAErrorSeverityInfo, "This is some info");
	gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(gameanalytics::GAProgressionStatusStart, "world01", "level01", "phase01");
	gameanalytics::GameAnalytics::addResourceEventWithFlowType(gameanalytics::GAResourceFlowTypeSource, "gems", 100, "boost", "id");
	gameanalytics::GameAnalytics::addResourceEventWithFlowType(gameanalytics::GAResourceFlowTypeSink, "gems", 100, "boost", "id");
	UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("AWESOME Unreal some events!"));

	gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(gameanalytics::GAProgressionStatusFail, "world01", "level01", "phase01", 10000);
	UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("AWESOME Unreal progress event 0!"));

	gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(gameanalytics::GAProgressionStatusStart, "world01", "level01", "phase01");
	gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(gameanalytics::GAProgressionStatusFail, "world01", "level01", "phase01", 15000);
	UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("AWESOME Unreal progress event 1!"));

	gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(gameanalytics::GAProgressionStatusStart, "world01", "level01", "phase01");
	gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(gameanalytics::GAProgressionStatusComplete, "world01", "level01", "phase01", 20000);
	UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("AWESOME Unreal progress event 2!"));

	gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(gameanalytics::GAProgressionStatusStart, "world01", "level01", "phase01");
	gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(gameanalytics::GAProgressionStatusComplete, "world01", "level01", "phase01", 20000);
	gameanalytics::GameAnalytics::setGender("female");
	gameanalytics::GameAnalytics::setBirthYear(1980);
	UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("AWESOME Unreal progress event 3!"));*/
    
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
	gameanalytics::GameAnalytics::setFacebookId(TCHAR_TO_ANSI(*InUserID));
}

FString FAnalyticsProviderGameAnalytics::GetUserID() const
{
	UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("FAnalyticsProviderGameAnalytics::GetUserID ignored."));
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
            else
            {
                double AttrValue = FCString::Atod(*Attr.AttrValue);
                gameanalytics::GameAnalytics::addDesignEventWithEventId(TCHAR_TO_ANSI(*Attr.AttrName), AttrValue);
            }
        }
    }
    else if (EventName.Len() > 0)
    {
        // Send an event without value
        gameanalytics::GameAnalytics::addDesignEventWithEventId(TCHAR_TO_ANSI(*EventName));
    }
    
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordEvent('%s', %d attributes)"), *EventName, AttrCount);
}

void FAnalyticsProviderGameAnalytics::SetAge(int InAge)
{
	gameanalytics::GameAnalytics::setBirthYear(InAge);
}

void FAnalyticsProviderGameAnalytics::SetGender(const FString& InGender)
{
	gameanalytics::GameAnalytics::setGender(TCHAR_TO_ANSI(*InGender));
}

void FAnalyticsProviderGameAnalytics::RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& Attributes)
{	
	gameanalytics::GAErrorSeverity ErrorSeverity;

	if (Error == TEXT("debug"))
	{
		ErrorSeverity = gameanalytics::GAErrorSeverityDebug;
	}
	else if (Error == TEXT("info"))
	{
		ErrorSeverity = gameanalytics::GAErrorSeverityInfo;
	}
	else if (Error == TEXT("warning"))
	{
		ErrorSeverity = gameanalytics::GAErrorSeverityWarning;
	}
	else if (Error == TEXT("error"))
	{
		ErrorSeverity = gameanalytics::GAErrorSeverityError;
	}
	else if (Error == TEXT("critical"))
	{
		ErrorSeverity = gameanalytics::GAErrorSeverityCritical;
	}
	else
	{
		UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordError: Error value must be either debug, info, warning, error, critical."));
		return;
	}

	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0)
	{
		for (auto Attr : Attributes)
		{
			if (Attr.AttrName == TEXT("message"))
			{
				gameanalytics::GameAnalytics::addErrorEventWithSeverity(ErrorSeverity, TCHAR_TO_ANSI(*Attr.AttrValue));
			}
		}
	}

	UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("GameAnalytics::RecordError"));
}

void FAnalyticsProviderGameAnalytics::RecordProgress(const FString& ProgressType, const FString& ProgressName, const TArray<FAnalyticsEventAttribute>& Attributes)
{	
	gameanalytics::GAProgressionStatus ProgressionStatus;

	if (ProgressType == TEXT("start"))
	{
		ProgressionStatus = gameanalytics::GAProgressionStatusStart;
	}
	else if (ProgressType == TEXT("complete"))
	{
		ProgressionStatus = gameanalytics::GAProgressionStatusComplete;
	}
	else if (ProgressType == TEXT("fail"))
	{
		ProgressionStatus = gameanalytics::GAProgressionStatusFail;
	}
	else
	{
		UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordError: Error value must be either start, complete or fail."));
		return;
	}

	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0)
	{
		FString Progression01 = Attributes[0].AttrValue;
		FString Progression02;
		FString Progression03;

		if (AttrCount > 1)
		{
			Progression02 = Attributes[1].AttrValue;
		}
		if (AttrCount > 2)
		{
			Progression03 = Attributes[2].AttrValue;
		}

		if (!Progression01.IsEmpty())
		{
			gameanalytics::GameAnalytics::addProgressionEventWithProgressionStatus(ProgressionStatus, TCHAR_TO_ANSI(*Progression01), TCHAR_TO_ANSI(*Progression02), TCHAR_TO_ANSI(*Progression03));
		}
	}
}

void FAnalyticsProviderGameAnalytics::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	gameanalytics::GAResourceFlowType FlowType = gameanalytics::GAResourceFlowTypeSource;
	FString Currency;
	FString ItemType;	

	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0)
	{
		for (auto Attr : Attributes)
		{
			if (Attr.AttrName == TEXT("flowType"))
			{

				if (Attr.AttrValue == TEXT("sink"))
				{
					FlowType = gameanalytics::GAResourceFlowTypeSink;
				}
				else if (Attr.AttrValue == TEXT("source"))
				{
					FlowType = gameanalytics::GAResourceFlowTypeSource;
				}
				else
				{
					UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("RecordItemPurchaseError: FlowType value must be either sink or source."));
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
			gameanalytics::GameAnalytics::addResourceEventWithFlowType(FlowType, TCHAR_TO_ANSI(*Currency), ItemQuantity, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId));
		}
	}
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{	
	UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("Awesome CurrencyPurchase"));
	FString ItemType;
	FString ItemId;
	FString CartType;
	FString Receipt;
	FString Store;
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
			else if (Attr.AttrValue == TEXT("store"))
			{
				Store = Attr.AttrValue;
			}
			else if (Attr.AttrName == TEXT("signature"))
			{ 
				Signature = Attr.AttrValue;
			}
		}

		if (!ItemType.IsEmpty() && !ItemId.IsEmpty() && !CartType.IsEmpty())
		{
/*#if PLATFORM_ANDROID
			if (!Receipt.IsEmpty() && !Store.IsEmpty() && !Signature.IsEmpty())
			{
				UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("Awesome CurrencyPurchase 0a"));
				gameanalytics::GameAnalytics::addBusinessEventWithCurrency(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType), TCHAR_TO_ANSI(*Receipt), TCHAR_TO_ANSI(*Store), TCHAR_TO_ANSI(*Signature));			
				UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("Awesome CurrencyPurchase 0b"));
			}
			else
			{
				UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("Awesome CurrencyPurchase 1a"));
				gameanalytics::GameAnalytics::addBusinessEventWithCurrency(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType));
				UE_LOG(LogGameAnalyticsAnalytics, Warning, TEXT("Awesome CurrencyPurchase 1b"));			
			}*/
#if PLATFORM_IOS
			if (!Receipt.IsEmpty())
			{				
					gameanalytics::GameAnalytics::addBusinessEventWithCurrency(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType), TCHAR_TO_ANSI(*Receipt));
			}
			else
			{				
					gameanalytics::GameAnalytics::addBusinessEventWithCurrency(TCHAR_TO_ANSI(*GameCurrencyType), GameCurrencyAmount, TCHAR_TO_ANSI(*ItemType), TCHAR_TO_ANSI(*ItemId), TCHAR_TO_ANSI(*CartType), AutoFetchReceipt);
			}
#endif
		}
	}
}

void FAnalyticsProviderGameAnalytics::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("GameAnalytics::RecordCurrencyGiven - ignoring call"));
}
