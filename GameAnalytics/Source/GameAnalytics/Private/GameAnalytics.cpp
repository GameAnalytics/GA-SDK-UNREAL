#include "GameAnalytics.h"
#if PLATFORM_IOS
#include "../GA-SDK-IOS/GameAnalyticsCpp.h"
#elif PLATFORM_ANDROID
#include "../GA-SDK-ANDROID/GameAnalyticsJNI.h"
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
#if PLATFORM_LINUX
#include "Json.h"
#endif
#include "../GA-SDK-CPP/GameAnalytics.h"
//#elif PLATFORM_HTML5
//#include "Json.h"
//#include "../GA-SDK-HTML5/GameAnalytics.h"
#endif
#include "Misc/EngineVersion.h"

#define GA_VERSION TEXT("4.3.14")

UGameAnalytics::UGameAnalytics(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGameAnalytics::configureAvailableCustomDimensions01(const TArray<FString>& list)
{
#if WITH_EDITOR
    FString s = FString::Join(list, TEXT(","));
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureAvailableCustomDimensions01(%s)"), *s);
#elif PLATFORM_IOS
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    GameAnalyticsCpp::configureAvailableCustomDimensions01(v);
#elif PLATFORM_ANDROID
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::jni_configureAvailableCustomDimensions01(v);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::StringVector v;
    for (const FString& item : list)
    {
        v.add(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::GameAnalytics::configureAvailableCustomDimensions01(v);
// #elif PLATFORM_HTML5
//     TArray<TSharedPtr<FJsonValue>> array;
//     for (const FString& s : list)
//     {
//         TSharedRef<FJsonValueString> JsonValueString = MakeShareable(new FJsonValueString(s));
//         array.Add(JsonValueString);
//     }
//     FString arrayString;
//     TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&arrayString);
//     FJsonSerializer::Serialize(array, Writer);
//     js_configureAvailableCustomDimensions01(TCHAR_TO_UTF8(*arrayString));
#endif
}

void UGameAnalytics::configureAvailableCustomDimensions02(const TArray<FString>& list)
{
#if WITH_EDITOR
    FString s = FString::Join(list, TEXT(","));
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureAvailableCustomDimensions02(%s)"), *s);
#elif PLATFORM_IOS
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    GameAnalyticsCpp::configureAvailableCustomDimensions02(v);
#elif PLATFORM_ANDROID
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::jni_configureAvailableCustomDimensions02(v);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::StringVector v;
    for (const FString& item : list)
    {
        v.add(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::GameAnalytics::configureAvailableCustomDimensions02(v);
// #elif PLATFORM_HTML5
//     TArray<TSharedPtr<FJsonValue>> array;
//     for (const FString& s : list)
//     {
//         TSharedRef<FJsonValueString> JsonValueString = MakeShareable(new FJsonValueString(s));
//         array.Add(JsonValueString);
//     }
//     FString arrayString;
//     TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&arrayString);
//     FJsonSerializer::Serialize(array, Writer);
//     js_configureAvailableCustomDimensions02(TCHAR_TO_UTF8(*arrayString));
#endif
}

void UGameAnalytics::configureAvailableCustomDimensions03(const TArray<FString>& list)
{
#if WITH_EDITOR
    FString s = FString::Join(list, TEXT(","));
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureAvailableCustomDimensions03(%s)"), *s);
#elif PLATFORM_IOS
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    GameAnalyticsCpp::configureAvailableCustomDimensions03(v);
#elif PLATFORM_ANDROID
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::jni_configureAvailableCustomDimensions03(v);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::StringVector v;
    for (const FString& item : list)
    {
        v.add(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::GameAnalytics::configureAvailableCustomDimensions03(v);
// #elif PLATFORM_HTML5
//     TArray<TSharedPtr<FJsonValue>> array;
//     for (const FString& s : list)
//     {
//         TSharedRef<FJsonValueString> JsonValueString = MakeShareable(new FJsonValueString(s));
//         array.Add(JsonValueString);
//     }
//     FString arrayString;
//     TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&arrayString);
//     FJsonSerializer::Serialize(array, Writer);
//     js_configureAvailableCustomDimensions03(TCHAR_TO_UTF8(*arrayString));
#endif
}

void UGameAnalytics::configureAvailableResourceCurrencies(const TArray<FString>& list)
{
#if WITH_EDITOR
    FString s = FString::Join(list, TEXT(","));
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureAvailableResourceCurrencies(%s)"), *s);
#elif PLATFORM_IOS
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    GameAnalyticsCpp::configureAvailableResourceCurrencies(v);
#elif PLATFORM_ANDROID
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::jni_configureAvailableResourceCurrencies(v);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::StringVector v;
    for (const FString& item : list)
    {
        v.add(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::GameAnalytics::configureAvailableResourceCurrencies(v);
// #elif PLATFORM_HTML5
//     TArray<TSharedPtr<FJsonValue>> array;
//     for (const FString& s : list)
//     {
//         TSharedRef<FJsonValueString> JsonValueString = MakeShareable(new FJsonValueString(s));
//         array.Add(JsonValueString);
//     }
//     FString arrayString;
//     TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&arrayString);
//     FJsonSerializer::Serialize(array, Writer);
//     js_configureAvailableResourceCurrencies(TCHAR_TO_UTF8(*arrayString));
#endif
}

void UGameAnalytics::configureAvailableResourceItemTypes(const TArray<FString>& list)
{
#if WITH_EDITOR
    FString s = FString::Join(list, TEXT(","));
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureAvailableResourceItemTypes(%s)"), *s);
#elif PLATFORM_IOS
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    GameAnalyticsCpp::configureAvailableResourceItemTypes(v);
#elif PLATFORM_ANDROID
    std::vector<std::string> v;
    for (const FString& item : list)
    {
        v.push_back(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::jni_configureAvailableResourceItemTypes(v);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::StringVector v;
    for (const FString& item : list)
    {
        v.add(TCHAR_TO_UTF8(*item));
    }
    gameanalytics::GameAnalytics::configureAvailableResourceItemTypes(v);
// #elif PLATFORM_HTML5
//     TArray<TSharedPtr<FJsonValue>> array;
//     for (const FString& s : list)
//     {
//         TSharedRef<FJsonValueString> JsonValueString = MakeShareable(new FJsonValueString(s));
//         array.Add(JsonValueString);
//     }
//     FString arrayString;
//     TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&arrayString);
//     FJsonSerializer::Serialize(array, Writer);
//     js_configureAvailableResourceItemTypes(TCHAR_TO_UTF8(*arrayString));
#endif
}

void UGameAnalytics::configureBuild(const char *build)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureBuild(%s)"), UTF8_TO_TCHAR(build));
#elif PLATFORM_IOS
    GameAnalyticsCpp::configureBuild(build);
#elif PLATFORM_ANDROID
    gameanalytics::jni_configureBuild(build);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::configureBuild(build);
// #elif PLATFORM_HTML5
//     js_configureBuild(build);
#endif
}

void UGameAnalytics::configureAutoDetectAppVersion(bool flag)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureAutoDetectAppVersion(%s)"), flag ? TEXT("true") : TEXT("false"));
#elif PLATFORM_IOS
    GameAnalyticsCpp::configureAutoDetectAppVersion(flag);
#elif PLATFORM_ANDROID
    gameanalytics::jni_configureAutoDetectAppVersion(flag);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
//#elif PLATFORM_HTML5
#endif
}

void UGameAnalytics::disableDeviceInfo()
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::disableDeviceInfo()"));
#elif PLATFORM_IOS
#elif PLATFORM_ANDROID
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::disableDeviceInfo();
//#elif PLATFORM_HTML5
#endif
}

void UGameAnalytics::configureUserId(const char *userId)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureUserId(%s)"), UTF8_TO_TCHAR(userId));
#elif PLATFORM_IOS
    GameAnalyticsCpp::configureUserId(userId);
#elif PLATFORM_ANDROID
    gameanalytics::jni_configureUserId(userId);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::configureUserId(userId);
// #elif PLATFORM_HTML5
//     js_configureUserId(userId);
#endif
}

void UGameAnalytics::configureSdkGameEngineVersion(const char *gameEngineSdkVersion)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureSdkGameEngineVersion(%s)"), UTF8_TO_TCHAR(gameEngineSdkVersion));
#elif PLATFORM_IOS
    GameAnalyticsCpp::configureSdkGameEngineVersion(gameEngineSdkVersion);
#elif PLATFORM_ANDROID
    gameanalytics::jni_configureSdkGameEngineVersion(gameEngineSdkVersion);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::configureSdkGameEngineVersion(gameEngineSdkVersion);
// #elif PLATFORM_HTML5
//     js_configureSdkGameEngineVersion(gameEngineSdkVersion);
#endif
}

void UGameAnalytics::configureGameEngineVersion(const char *gameEngineVersion)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::configureGameEngineVersion(%s)"), UTF8_TO_TCHAR(gameEngineVersion));
#elif PLATFORM_IOS
    GameAnalyticsCpp::configureGameEngineVersion(gameEngineVersion);
#elif PLATFORM_ANDROID
    gameanalytics::jni_configureGameEngineVersion(gameEngineVersion);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::configureGameEngineVersion(gameEngineVersion);
// #elif PLATFORM_HTML5
//     js_configureGameEngineVersion(gameEngineVersion);
#endif
}

void UGameAnalytics::initialize(const char *gameKey, const char *gameSecret)
{
    ////// Configure engine version
    FString EngineVersionString = FString::Printf(TEXT("unreal %d.%d.%d"), FEngineVersion::Current().GetMajor(), FEngineVersion::Current().GetMinor(), FEngineVersion::Current().GetPatch());
    UGameAnalytics::configureGameEngineVersion(TCHAR_TO_UTF8(*EngineVersionString));
    FString SdkVersionString = FString::Printf(TEXT("unreal %s"), GA_VERSION);
    UGameAnalytics::configureSdkGameEngineVersion(TCHAR_TO_UTF8(*SdkVersionString));

#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::initialize(%s, %s)"), UTF8_TO_TCHAR(gameKey), UTF8_TO_TCHAR(gameSecret));
#elif PLATFORM_IOS
    GameAnalyticsCpp::initialize(gameKey, gameSecret);
#elif PLATFORM_ANDROID
    gameanalytics::jni_initialize(gameKey, gameSecret);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::initialize(gameKey, gameSecret);
// #elif PLATFORM_HTML5
//     js_initialize(gameKey, gameSecret);
#endif
}

#if PLATFORM_IOS
void UGameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt)
{
#if !WITH_EDITOR
    GameAnalyticsCpp::addBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, "");
#else
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addBusinessEvent(%s, %d, %s, %s, %s, %s)"), UTF8_TO_TCHAR(currency), amount, UTF8_TO_TCHAR(itemType), UTF8_TO_TCHAR(itemId), UTF8_TO_TCHAR(cartType), UTF8_TO_TCHAR(receipt));
#endif
}

void UGameAnalytics::addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType)
{
#if !WITH_EDITOR
    GameAnalyticsCpp::addBusinessEventAndAutoFetchReceipt(currency, amount, itemType, itemId, cartType, "");
#else
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addBusinessEventAndAutoFetchReceipt(%s, %d, %s, %s, %s)"), UTF8_TO_TCHAR(currency), amount, UTF8_TO_TCHAR(itemType), UTF8_TO_TCHAR(itemId), UTF8_TO_TCHAR(cartType));
#endif
}
#elif PLATFORM_ANDROID
void UGameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *signature)
{
#if !WITH_EDITOR
    gameanalytics::jni_addBusinessEventWithReceipt(currency, amount, itemType, itemId, cartType, receipt, "google_play", signature, "");
#else
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addBusinessEvent(%s, %d, %s, %s, %s, %s, %s)"), UTF8_TO_TCHAR(currency), amount, UTF8_TO_TCHAR(itemType), UTF8_TO_TCHAR(itemId), UTF8_TO_TCHAR(cartType), UTF8_TO_TCHAR(receipt), UTF8_TO_TCHAR(signature));
#endif
}
#endif

void UGameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addBusinessEvent(%s, %d, %s, %s, %s)"), UTF8_TO_TCHAR(currency), amount, UTF8_TO_TCHAR(itemType), UTF8_TO_TCHAR(itemId), UTF8_TO_TCHAR(cartType));
#elif PLATFORM_IOS
    GameAnalyticsCpp::addBusinessEvent(currency, amount, itemType, itemId, cartType, NULL, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addBusinessEvent(currency, amount, itemType, itemId, cartType, "");
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::addBusinessEvent(currency, amount, itemType, itemId, cartType/*, ""*/);
// #elif PLATFORM_HTML5
//     js_addBusinessEvent(currency, amount, itemType, itemId, cartType, "");
#endif
}

void UGameAnalytics::addResourceEvent(EGAResourceFlowType flowType, const char *currency, float amount, const char *itemType, const char *itemId)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addResourceEvent(%d, %s, %f, %s, %s)"), (int)flowType, UTF8_TO_TCHAR(currency), amount, UTF8_TO_TCHAR(itemType), UTF8_TO_TCHAR(itemId));
#elif PLATFORM_IOS
    GameAnalyticsCpp::addResourceEvent((int)flowType, currency, amount, itemType, itemId, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addResourceEvent((int)flowType, currency, amount, itemType, itemId, "");
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::addResourceEvent((gameanalytics::EGAResourceFlowType)((int)flowType), currency, amount, itemType, itemId/*, ""*/);
// #elif PLATFORM_HTML5
//     js_addResourceEvent((int)flowType, currency, amount, itemType, itemId, "");
#endif
}

void UGameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01)
{
#if PLATFORM_IOS
    addProgressionEvent(progressionStatus, progression01, (const char *)NULL, (const char *)NULL);
#else
    addProgressionEvent(progressionStatus, progression01, "", "");
#endif
}

void UGameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, int score)
{
#if PLATFORM_IOS
    addProgressionEvent(progressionStatus, progression01, (const char *)NULL, (const char *)NULL, score);
#else
    addProgressionEvent(progressionStatus, progression01, "", "", score);
#endif
}

void UGameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02)
{
#if PLATFORM_IOS
    addProgressionEvent(progressionStatus, progression01, progression02, (const char *)NULL);
#else
    addProgressionEvent(progressionStatus, progression01, progression02, "");
#endif
}

void UGameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, int score)
{
#if PLATFORM_IOS
    addProgressionEvent(progressionStatus, progression01, progression02, (const char *)NULL, score);
#else
    addProgressionEvent(progressionStatus, progression01, progression02, "", score);
#endif
}

void UGameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addProgressionEvent(%d, %s, %s, %s)"), (int)progressionStatus, UTF8_TO_TCHAR(progression01), UTF8_TO_TCHAR(progression02), UTF8_TO_TCHAR(progression03));
#elif PLATFORM_IOS
    GameAnalyticsCpp::addProgressionEvent((int)progressionStatus, progression01, progression02, progression03, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addProgressionEvent((int)progressionStatus, progression01, progression02, progression03, "");
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)((int)progressionStatus), progression01, progression02, progression03/*, ""*/);
// #elif PLATFORM_HTML5
//     js_addProgressionEvent((int)progressionStatus, progression01, progression02, progression03, "");
#endif
}

void UGameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addProgressionEvent(%d, %s, %s, %s, %d)"), (int)progressionStatus, UTF8_TO_TCHAR(progression01), UTF8_TO_TCHAR(progression02), UTF8_TO_TCHAR(progression03), score);
#elif PLATFORM_IOS
    GameAnalyticsCpp::addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score, "");
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)((int)progressionStatus), progression01, progression02, progression03, score/*, ""*/);
// #elif PLATFORM_HTML5
//     js_addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score, "");
#endif
}

void UGameAnalytics::addDesignEvent(const char *eventId)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addDesignEvent(%s)"), UTF8_TO_TCHAR(eventId));
#elif PLATFORM_IOS
    GameAnalyticsCpp::addDesignEvent(eventId, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addDesignEvent(eventId, "");
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::addDesignEvent(eventId/*, ""*/);
// #elif PLATFORM_HTML5
//     js_addDesignEvent(eventId, "");
#endif
}

void UGameAnalytics::addDesignEvent(const char *eventId, float value)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addDesignEvent(%s, %f)"), UTF8_TO_TCHAR(eventId), value);
#elif PLATFORM_IOS
    GameAnalyticsCpp::addDesignEventWithValue(eventId, value, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addDesignEventWithValue(eventId, value, "");
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::addDesignEvent(eventId, value/*, ""*/);
// #elif PLATFORM_HTML5
//     js_addDesignEventWithValue(eventId, value, "");
#endif
}

void UGameAnalytics::addErrorEvent(EGAErrorSeverity severity, const char *message)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addErrorEvent(%d, %s)"), (int)severity, UTF8_TO_TCHAR(message));
#elif PLATFORM_IOS
    GameAnalyticsCpp::addErrorEvent((int)severity, message, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addErrorEvent((int)severity, message, "");
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::addErrorEvent((gameanalytics::EGAErrorSeverity)((int)severity), message/*, ""*/);
// #elif PLATFORM_HTML5
//     js_addErrorEvent((int)severity, message, "");
#endif
}

#if PLATFORM_IOS || PLATFORM_ANDROID
void UGameAnalytics::addAdEvent(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addAdEvent(%d, %d, %s, %s)"), (int)action, (int)adType, UTF8_TO_TCHAR(adSdkName), UTF8_TO_TCHAR(adPlacement));
#elif PLATFORM_IOS
    GameAnalyticsCpp::addAdEvent((int)action, (int)action, adSdkName, adPlacement, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addAdEvent((int)action, (int)action, adSdkName, adPlacement, "");
#endif
}

void UGameAnalytics::addAdEventWithDuration(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, int64_t duration)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addAdEventWithDuration(%d, %d, %s, %s, %d)"), (int)action, (int)adType, UTF8_TO_TCHAR(adSdkName), UTF8_TO_TCHAR(adPlacement), duration);
#elif PLATFORM_IOS
    GameAnalyticsCpp::addAdEventWithDuration((int)action, (int)action, adSdkName, adPlacement, duration, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addAdEventWithDuration((int)action, (int)action, adSdkName, adPlacement, duration, "");
#endif
}

void UGameAnalytics::addAdEventWithNoAdReason(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, EGAAdError noAdReason)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::addAdEventWithNoAdReason(%d, %d, %s, %s, %d)"), (int)action, (int)adType, UTF8_TO_TCHAR(adSdkName), UTF8_TO_TCHAR(adPlacement), (int)noAdReason);
#elif PLATFORM_IOS
    GameAnalyticsCpp::addAdEventWithNoAdReason((int)action, (int)action, adSdkName, adPlacement, (int)noAdReason, "");
#elif PLATFORM_ANDROID
    gameanalytics::jni_addAdEventWithNoAdReason((int)action, (int)action, adSdkName, adPlacement, (int)noAdReason, "");
#endif
}
#endif

void UGameAnalytics::setEnabledInfoLog(bool flag)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::setEnabledInfoLog(%s)"), flag ? TEXT("true") : TEXT("false"));
#elif PLATFORM_IOS
    GameAnalyticsCpp::setEnabledInfoLog(flag);
#elif PLATFORM_ANDROID
    gameanalytics::jni_setEnabledInfoLog(flag);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::setEnabledInfoLog(flag);
// #elif PLATFORM_HTML5
//     js_setEnabledInfoLog(flag);
#endif
}

void UGameAnalytics::setEnabledVerboseLog(bool flag)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::setEnabledVerboseLog(%s)"), flag ? TEXT("true") : TEXT("false"));
#elif PLATFORM_IOS
    GameAnalyticsCpp::setEnabledVerboseLog(flag);
#elif PLATFORM_ANDROID
    gameanalytics::jni_setEnabledVerboseLog(flag);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::setEnabledVerboseLog(flag);
// #elif PLATFORM_HTML5
//     js_setEnabledVerboseLog(flag);
#endif
}

void UGameAnalytics::setEnabledManualSessionHandling(bool flag)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::setEnabledManualSessionHandling(%s)"), flag ? TEXT("true") : TEXT("false"));
#elif PLATFORM_IOS
    GameAnalyticsCpp::setEnabledManualSessionHandling(flag);
#elif PLATFORM_ANDROID
    gameanalytics::jni_setEnabledManualSessionHandling(flag);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::setEnabledManualSessionHandling(flag);
// #elif PLATFORM_HTML5
//     js_setManualSessionHandling(flag);
#endif
}

void UGameAnalytics::setEnabledEventSubmission(bool flag)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::setEnabledEventSubmission(%s)"), flag ? TEXT("true") : TEXT("false"));
#elif PLATFORM_IOS
    GameAnalyticsCpp::setEnabledEventSubmission(flag);
#elif PLATFORM_ANDROID
    gameanalytics::jni_setEnabledEventSubmission(flag);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::setEnabledEventSubmission(flag);
// #elif PLATFORM_HTML5
//     js_setEventSubmission(flag);
#endif
}

void UGameAnalytics::setCustomDimension01(const char *customDimension)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::setCustomDimension01(%s)"), UTF8_TO_TCHAR(customDimension));
#elif PLATFORM_IOS
    GameAnalyticsCpp::setCustomDimension01(customDimension);
#elif PLATFORM_ANDROID
    gameanalytics::jni_setCustomDimension01(customDimension);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::setCustomDimension01(customDimension);
// #elif PLATFORM_HTML5
//     js_setCustomDimension01(customDimension);
#endif
}

void UGameAnalytics::setCustomDimension02(const char *customDimension)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::setCustomDimension02(%s)"), UTF8_TO_TCHAR(customDimension));
#elif PLATFORM_IOS
    GameAnalyticsCpp::setCustomDimension02(customDimension);
#elif PLATFORM_ANDROID
    gameanalytics::jni_setCustomDimension02(customDimension);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::setCustomDimension02(customDimension);
// #elif PLATFORM_HTML5
//     js_setCustomDimension02(customDimension);
#endif
}

void UGameAnalytics::setCustomDimension03(const char *customDimension)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::setCustomDimension03(%s)"), UTF8_TO_TCHAR(customDimension));
#elif PLATFORM_IOS
    GameAnalyticsCpp::setCustomDimension03(customDimension);
#elif PLATFORM_ANDROID
    gameanalytics::jni_setCustomDimension03(customDimension);
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::setCustomDimension03(customDimension);
// #elif PLATFORM_HTML5
//     js_setCustomDimension03(customDimension);
#endif
}

void UGameAnalytics::startSession()
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::startSession()"));
#elif PLATFORM_IOS
    GameAnalyticsCpp::startSession();
#elif PLATFORM_ANDROID
    gameanalytics::jni_startSession();
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::startSession();
// #elif PLATFORM_HTML5
//     js_startSession();
#endif
}

void UGameAnalytics::endSession()
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::endSession()"));
#elif PLATFORM_IOS
    GameAnalyticsCpp::endSession();
#elif PLATFORM_ANDROID
    gameanalytics::jni_endSession();
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::endSession();
// #elif PLATFORM_HTML5
//     js_endSession();
#endif
}

void UGameAnalytics::onQuit()
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::onQuit()"));
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    gameanalytics::GameAnalytics::onQuit();
#endif
}

FString UGameAnalytics::getRemoteConfigsValueAsString(const char *key)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::getRemoteConfigsValueAsString(%s)"), UTF8_TO_TCHAR(key));
    return "";
#elif PLATFORM_IOS
	char* out = NULL;
	GameAnalyticsCpp::getRemoteConfigsValueAsString(key, &out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_ANDROID
	char* out = NULL;
	gameanalytics::jni_getRemoteConfigsValueAsString(key, &out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_WINDOWS
	return FString(gameanalytics::GameAnalytics::getRemoteConfigsValueAsString(key).data());
// #elif PLATFORM_HTML5
//     return FString(js_getRemoteConfigsValueAsString(key));
#endif
}

FString UGameAnalytics::getRemoteConfigsValueAsString(const char *key, const char *defaultValue)
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::getRemoteConfigsValueAsString(%s, %s)"), UTF8_TO_TCHAR(key), UTF8_TO_TCHAR(defaultValue));
    return "";
#elif PLATFORM_IOS
	char* out = NULL;
    GameAnalyticsCpp::getRemoteConfigsValueAsString(key, defaultValue, &out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_ANDROID
	char* out = NULL;
    gameanalytics::jni_getRemoteConfigsValueAsStringWithDefaultValue(key, defaultValue, &out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_WINDOWS
	return FString(gameanalytics::GameAnalytics::getRemoteConfigsValueAsString(key, defaultValue).data());
// #elif PLATFORM_HTML5
//     return FString(js_getRemoteConfigsValueAsStringWithDefaultValue(key, defaultValue));
#endif
}

bool UGameAnalytics::isRemoteConfigsReady()
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::isRemoteConfigsReady()"));
    return false;
#elif PLATFORM_IOS
    return GameAnalyticsCpp::isRemoteConfigsReady();
#elif PLATFORM_ANDROID
    return gameanalytics::jni_isRemoteConfigsReady();
#elif PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    return gameanalytics::GameAnalytics::isRemoteConfigsReady();
// #elif PLATFORM_HTML5
//     return js_isRemoteConfigsReady();
#endif
}

FString UGameAnalytics::getRemoteConfigsContentAsString()
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::getRemoteConfigsContentAsString()"));
    return "";
#elif PLATFORM_IOS
	char* out = NULL;
    GameAnalyticsCpp::getRemoteConfigsContentAsString(&out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_ANDROID
	char* out = NULL;
    gameanalytics::jni_getRemoteConfigsContentAsString(&out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_WINDOWS
    return FString(gameanalytics::GameAnalytics::getRemoteConfigsContentAsString().data());
// #elif PLATFORM_HTML5
//     return FString(js_getRemoteConfigsContentAsString());
#endif
}

FString UGameAnalytics::getABTestingId()
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::getABTestingId()"));
    return "";
#elif PLATFORM_IOS
	char* out = NULL;
    GameAnalyticsCpp::getABTestingId(&out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_ANDROID
	char* out = NULL;
    gameanalytics::jni_getABTestingId(&out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_WINDOWS
    return FString(gameanalytics::GameAnalytics::getABTestingId().data());
// #elif PLATFORM_HTML5
//     return FString(js_getABTestingId());
#endif
}

FString UGameAnalytics::getABTestingVariantId()
{
#if WITH_EDITOR
    UE_LOG(LogGameAnalyticsAnalytics, Display, TEXT("UGameAnalytics::getABTestingVariantId()"));
    return "";
#elif PLATFORM_IOS
	char* out = NULL;
    GameAnalyticsCpp::getABTestingVariantId(&out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_ANDROID
	char* out = NULL;
    gameanalytics::jni_getABTestingVariantId(&out);
	FString result(out);
	delete[] out;
	return result;
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_WINDOWS
    return FString(gameanalytics::GameAnalytics::getABTestingVariantId().data());
// #elif PLATFORM_HTML5
//     return FString(js_getABTestingVariantId());
#endif
}

// Blueprint functions

void UGameAnalytics::AddBusinessEventIOS(const FString& Currency, int Amount, const FString& ItemType, const FString& ItemId, const FString& CartType, const FString& Receipt/*, const char *fields*/)
{
#if PLATFORM_IOS
    addBusinessEvent(TCHAR_TO_UTF8(*Currency), Amount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType), TCHAR_TO_UTF8(*Receipt));
#endif
}

void UGameAnalytics::AddBusinessEventAndAutoFetchReceipt(const FString& Currency, int Amount, const FString& ItemType, const FString& ItemId, const FString& CartType/*, const char *fields*/)
{
#if PLATFORM_IOS
    addBusinessEventAndAutoFetchReceipt(TCHAR_TO_UTF8(*Currency), Amount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType));
#endif
}

void UGameAnalytics::AddBusinessEventAndroid(const FString& Currency, int Amount, const FString& ItemType, const FString& ItemId, const FString& CartType, const FString& Receipt, const FString& Signature/*, const char *fields*/)
{
#if PLATFORM_ANDROID
    addBusinessEvent(TCHAR_TO_UTF8(*Currency), Amount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType), TCHAR_TO_UTF8(*Receipt), TCHAR_TO_UTF8(*Signature));
#endif
}

void UGameAnalytics::AddBusinessEvent(const FString& Currency, int Amount, const FString& ItemType, const FString& ItemId, const FString& CartType/*, const char *fields*/)
{
    addBusinessEvent(TCHAR_TO_UTF8(*Currency), Amount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*CartType));
}

void UGameAnalytics::AddResourceEvent(EGAResourceFlowType FlowType, const FString& Currency, float Amount, const FString& ItemType, const FString& ItemId/*, const char *fields*/)
{
    addResourceEvent(FlowType, TCHAR_TO_UTF8(*Currency), Amount, TCHAR_TO_UTF8(*ItemType), TCHAR_TO_UTF8(*ItemId));
}

void UGameAnalytics::AddProgressionEventWithOne(EGAProgressionStatus ProgressionStatus, const FString& Progression01/*, const char *fields*/)
{
    addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*Progression01));
}

void UGameAnalytics::AddProgressionEventWithOneAndScore(EGAProgressionStatus ProgressionStatus, const FString& Progression01, int Score/*, const char *fields*/)
{
    addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*Progression01), Score);
}

void UGameAnalytics::AddProgressionEventWithOneAndTwo(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const FString& Progression02/*, const char *fields*/)
{
    addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*Progression01), TCHAR_TO_UTF8(*Progression02));
}

void UGameAnalytics::AddProgressionEventWithOneTwoAndScore(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const FString& Progression02, int Score/*, const char *fields*/)
{
    addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*Progression01), TCHAR_TO_UTF8(*Progression02), Score);
}

void UGameAnalytics::AddProgressionEventWithOneTwoAndThree(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const FString& Progression02, const FString& Progression03/*, const char *fields*/)
{
    addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*Progression01), TCHAR_TO_UTF8(*Progression02), TCHAR_TO_UTF8(*Progression03));
}

void UGameAnalytics::AddProgressionEventWithOneTwoThreeAndScore(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const FString& Progression02, const FString& Progression03, int Score/*, const char *fields*/)
{
    addProgressionEvent(ProgressionStatus, TCHAR_TO_UTF8(*Progression01), TCHAR_TO_UTF8(*Progression02), TCHAR_TO_UTF8(*Progression03), Score);
}

void UGameAnalytics::AddDesignEvent(const FString& EventId/*, const char *fields*/)
{
    addDesignEvent(TCHAR_TO_UTF8(*EventId));
}

void UGameAnalytics::AddDesignEventWithValue(const FString& EventId, float Value/*, const char *fields*/)
{
    addDesignEvent(TCHAR_TO_UTF8(*EventId), Value);
}

void UGameAnalytics::AddErrorEvent(EGAErrorSeverity Severity, const FString& Message/*, const char *fields*/)
{
    addErrorEvent(Severity, TCHAR_TO_UTF8(*Message));
}

void UGameAnalytics::AddAdEvent(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement/*, const char *fields*/)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    addAdEvent(action, adType, TCHAR_TO_UTF8(*adSdkName), TCHAR_TO_UTF8(*adPlacement));
#endif
}

void UGameAnalytics::AddAdEventWithDuration(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, int64 duration/*, const char *fields*/)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    addAdEventWithDuration(action, adType, TCHAR_TO_UTF8(*adSdkName), TCHAR_TO_UTF8(*adPlacement), duration);
#endif
}

void UGameAnalytics::AddAdEventWithNoAdReason(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, EGAAdError noAdReason/*, const char *fields*/)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    addAdEventWithNoAdReason(action, adType, TCHAR_TO_UTF8(*adSdkName), TCHAR_TO_UTF8(*adPlacement), noAdReason);
#endif
}

void UGameAnalytics::SetCustomDimension01(const FString& CustomDimension)
{
    setCustomDimension01(TCHAR_TO_UTF8(*CustomDimension));
}

void UGameAnalytics::SetCustomDimension02(const FString& CustomDimension)
{
    setCustomDimension02(TCHAR_TO_UTF8(*CustomDimension));
}

void UGameAnalytics::SetCustomDimension03(const FString& CustomDimension)
{
    setCustomDimension03(TCHAR_TO_UTF8(*CustomDimension));
}

void UGameAnalytics::OnQuit()
{
    onQuit();
}

FString UGameAnalytics::GetRemoteConfigsValueAsString(const FString& Key)
{
    return getRemoteConfigsValueAsString(TCHAR_TO_UTF8(*Key));
}

FString UGameAnalytics::GetRemoteConfigsValueAsStringWithDefaultValue(const FString& Key, const FString& DefaultValue)
{
    return getRemoteConfigsValueAsString(TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*DefaultValue));
}

bool UGameAnalytics::IsRemoteConfigsReady()
{
    return isRemoteConfigsReady();
}

FString UGameAnalytics::GetRemoteConfigsContentAsString()
{
    return getRemoteConfigsContentAsString();
}

FString UGameAnalytics::GetABTestingId()
{
    return getABTestingId();
}

FString UGameAnalytics::GetABTestingVariantId()
{
    return getABTestingVariantId();
}
