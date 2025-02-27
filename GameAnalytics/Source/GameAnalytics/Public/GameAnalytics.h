//
//  GameAnalytics.h
//  GA-SDK-IOS
//
//  Copyright (c) 2015 GameAnalytics. All rights reserved.
//

#pragma once


#include <string>
#include <vector>
#include <stdint.h>


#include "UObject/Object.h"
#include "Dom/JsonObject.h"
#include "GameAnalytics.generated.h"

#if PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    #define GA_USE_CPP_SDK 1
#else
    #define GA_USE_CPP_SDK 0
#endif

DEFINE_LOG_CATEGORY_STATIC(LogGameAnalyticsAnalytics, Display, All);

UENUM()
enum class EGAResourceFlowType : uint8
{
    undefined = 0,
    source = 1,
    sink = 2
};

UENUM()
enum class EGAProgressionStatus : uint8
{
    undefined = 0,
    start = 1,
    complete = 2,
    fail = 3
};

UENUM()
enum class EGAErrorSeverity : uint8
{
    undefined = 0,
    debug = 1,
    info = 2,
    warning = 3,
    error = 4,
    critical = 5
};

UENUM()
enum class EGAAdAction : uint8
{
    undefined = 0,
    clicked = 1,
    show = 2,
    failedshow = 3,
    rewardreceived = 4,
    request = 5,
    loaded = 6
};

UENUM()
enum class EGAAdType : uint8
{
    undefined = 0,
    video = 1,
    rewardedvideo = 2,
    playable = 3,
    interstitial = 4,
    offerwall = 5,
    banner = 6
};

UENUM()
enum class EGAAdError : uint8
{
    undefined = 0,
    unknown = 1,
    offline = 2,
    nofill = 3,
    internalerror = 4,
    invalidrequest = 5,
    unabletoprecache = 6
};

USTRUCT(BlueprintType)
struct FGameAnalyticsCustomEventField
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameAnalytics")
    FString Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameAnalytics")
    FString Value;
};

UCLASS()
class GAMEANALYTICS_API UGameAnalytics : public UObject
{
    GENERATED_UCLASS_BODY()

public:

    static void configureAvailableCustomDimensions01(const TArray<FString>& list);
    static void configureAvailableCustomDimensions02(const TArray<FString>& list);
    static void configureAvailableCustomDimensions03(const TArray<FString>& list);

    static void configureAvailableResourceCurrencies(const TArray<FString>& list);
    static void configureAvailableResourceItemTypes(const TArray<FString>& list);

    static void configureBuild(const char *build);
    static void configureAutoDetectAppVersion(bool flag);
    static void disableDeviceInfo();
    static void configureUserId(const char *userId);
    static void configureSdkGameEngineVersion(const char *gameEngineSdkVersion);
    static void configureGameEngineVersion(const char *gameEngineVersion);
    static void initialize(const char *gameKey, const char *gameSecret);

#if PLATFORM_IOS
    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt);
    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const TSharedRef<FJsonObject> &customFields);
    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType);
    static void addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const TSharedRef<FJsonObject> &customFields);
    static void addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
#elif PLATFORM_ANDROID
    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *signature);
    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *signature, const TSharedRef<FJsonObject> &customFields);
    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *signature, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
#endif

    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType);
    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const TSharedRef<FJsonObject> &customFields);
    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addResourceEvent(EGAResourceFlowType flowType, const char *currency, float amount, const char *itemType, const char *itemId);
    static void addResourceEvent(EGAResourceFlowType flowType, const char *currency, float amount, const char *itemType, const char *itemId, const TSharedRef<FJsonObject> &customFields);
    static void addResourceEvent(EGAResourceFlowType flowType, const char *currency, float amount, const char *itemType, const char *itemId, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const TSharedRef<FJsonObject> &customFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, int score);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, int score, const TSharedRef<FJsonObject> &customFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, int score, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const TSharedRef<FJsonObject> &customFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, int score);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, int score, const TSharedRef<FJsonObject> &customFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, int score, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, const TSharedRef<FJsonObject> &customFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const TSharedRef<FJsonObject> &customFields);
    static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addDesignEvent(const char *eventId);
    static void addDesignEvent(const char *eventId, const TSharedRef<FJsonObject> &customFields);
    static void addDesignEvent(const char *eventId, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addDesignEvent(const char *eventId, float value);
    static void addDesignEvent(const char *eventId, float value, const TSharedRef<FJsonObject> &customFields);
    static void addDesignEvent(const char *eventId, float value, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addErrorEvent(EGAErrorSeverity severity, const char *message);
    static void addErrorEvent(EGAErrorSeverity severity, const char *message, const TSharedRef<FJsonObject> &customFields);
    static void addErrorEvent(EGAErrorSeverity severity, const char *message, const TSharedRef<FJsonObject> &customFields, bool mergeFields);

#if PLATFORM_IOS || PLATFORM_ANDROID
    static void addAdEvent(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement);
    static void addAdEvent(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, const TSharedRef<FJsonObject> &customFields);
    static void addAdEvent(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addAdEventWithDuration(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, int64_t duration);
    static void addAdEventWithDuration(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, int64_t duration, const TSharedRef<FJsonObject> &customFields);
    static void addAdEventWithDuration(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, int64_t duration, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
    static void addAdEventWithNoAdReason(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, EGAAdError noAdReason);
    static void addAdEventWithNoAdReason(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, EGAAdError noAdReason, const TSharedRef<FJsonObject> &customFields);
    static void addAdEventWithNoAdReason(EGAAdAction action, EGAAdType adType, const char *adSdkName, const char *adPlacement, EGAAdError noAdReason, const TSharedRef<FJsonObject> &customFields, bool mergeFields);
#endif

    static void setEnabledInfoLog(bool flag);
    static void setEnabledVerboseLog(bool flag);
    static void setEnabledManualSessionHandling(bool flag);
    static void setEnabledErrorReporting(bool flag);
    static void setEnabledEventSubmission(bool flag);
    static void setCustomDimension01(const char *customDimension);
    static void setCustomDimension02(const char *customDimension);
    static void setCustomDimension03(const char *customDimension);

    static void startSession();
    static void endSession();

    static void onQuit();

    static FString getRemoteConfigsValueAsString(const char *key);
    static FString getRemoteConfigsValueAsString(const char *key, const char *defaultValue);
    static bool isRemoteConfigsReady();
    static FString getRemoteConfigsContentAsString();

    static FString getABTestingId();
    static FString getABTestingVariantId();

    // Bluprint functions

    // ONLY FOR IOS
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventIOS(const FString &Currency, int Amount, const FString &ItemType, const FString &ItemId, const FString &CartType, const FString &Receipt);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventIOSWithFields(const FString& Currency, int Amount, const FString& ItemType, const FString& ItemId, const FString& CartType, const FString& Receipt, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventIOSWithMergeFields(const FString &Currency, int Amount, const FString &ItemType, const FString &ItemId, const FString &CartType, const FString &Receipt, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    // ONLY FOR IOS
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventAndAutoFetchReceipt(const FString &Currency, int Amount, const FString &ItemType, const FString &ItemId, const FString &CartType);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventAndAutoFetchReceiptWithFields(const FString& Currency, int Amount, const FString& ItemType, const FString& ItemId, const FString& CartType, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventAndAutoFetchReceiptWithMergeFields(const FString &Currency, int Amount, const FString &ItemType, const FString &ItemId, const FString &CartType, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    // ONLY FOR ANDROID
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventAndroid(const FString &Currency, int Amount, const FString &ItemType, const FString &ItemId, const FString &CartType, const FString &Receipt, const FString &Signature);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventAndroidWithFields(const FString& Currency, int Amount, const FString& ItemType, const FString& ItemId, const FString& CartType, const FString& Receipt, const FString& Signature, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventAndroidWithMergeFields(const FString &Currency, int Amount, const FString &ItemType, const FString &ItemId, const FString &CartType, const FString &Receipt, const FString &Signature, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEvent(const FString &Currency, int Amount, const FString &ItemType, const FString &ItemId, const FString &CartType);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventWithFields(const FString& Currency, int Amount, const FString& ItemType, const FString& ItemId, const FString& CartType, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddBusinessEventWithMergeFields(const FString &Currency, int Amount, const FString &ItemType, const FString &ItemId, const FString &CartType, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddResourceEvent(EGAResourceFlowType FlowType, const FString &Currency, float Amount, const FString &ItemType, const FString &ItemId);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddResourceEventWithFields(EGAResourceFlowType FlowType, const FString& Currency, float Amount, const FString& ItemType, const FString& ItemId, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddResourceEventWithMergeFields(EGAResourceFlowType FlowType, const FString &Currency, float Amount, const FString &ItemType, const FString &ItemId, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOne(EGAProgressionStatus ProgressionStatus, const FString &Progression01);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneAndFields(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneAndMergeFields(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneAndScore(EGAProgressionStatus ProgressionStatus, const FString &Progression01, int Score);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneScoreAndFields(EGAProgressionStatus ProgressionStatus, const FString& Progression01, int Score, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneScoreAndMergeFields(EGAProgressionStatus ProgressionStatus, const FString &Progression01, int Score, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneAndTwo(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoAndFields(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const FString& Progression02, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoAndMergeFields(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoAndScore(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02, int Score);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoScoreAndFields(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const FString& Progression02, int Score, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoScoreAndMergeFields(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02, int Score, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoAndThree(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02, const FString &Progression03);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoThreeAndFields(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const FString& Progression02, const FString& Progression03, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoThreeAndMergeFields(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02, const FString &Progression03, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoThreeAndScore(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02, const FString &Progression03, int Score);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoThreeScoreAndFields(EGAProgressionStatus ProgressionStatus, const FString& Progression01, const FString& Progression02, const FString& Progression03, int Score, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddProgressionEventWithOneTwoThreeScoreAndMergeFields(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02, const FString &Progression03, int Score, const TArray<FGameAnalyticsCustomEventField> &CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddDesignEvent(const FString &EventId);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddDesignEventWithFields(const FString& EventId, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddDesignEventWithMergeFields(const FString& EventId, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddDesignEventWithValue(const FString &EventId, float Value);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddDesignEventWithValueAndFields(const FString& EventId, float Value, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddDesignEventWithValueAndMergeFields(const FString& EventId, float Value, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddErrorEvent(EGAErrorSeverity Severity, const FString &Message);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddErrorEventWithFields(EGAErrorSeverity Severity, const FString& Message, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddErrorEventWithMergeFields(EGAErrorSeverity Severity, const FString& Message, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    // ONLY FOR IOS AND ANDROID
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEvent(EGAAdAction action, EGAAdType adType, const FString &adSdkName, const FString &adPlacement);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEventWithFields(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEventWithMergeFields(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    // ONLY FOR IOS AND ANDROID
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEventWithDuration(EGAAdAction action, EGAAdType adType, const FString &adSdkName, const FString &adPlacement, int64 duration);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEventWithDurationAndFields(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, int64 duration, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEventWithDurationAndMergeFields(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, int64 duration, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    // ONLY FOR IOS AND ANDROID
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEventWithNoAdReason(EGAAdAction action, EGAAdType adType, const FString &adSdkName, const FString &adPlacement, EGAAdError noAdReason);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEventWithNoAdReasonAndFields(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, EGAAdError noAdReason, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void AddAdEventWithNoAdReasonAndMergeFields(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, EGAAdError noAdReason, const TArray<FGameAnalyticsCustomEventField>& CustomFields);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void SetCustomDimension01(const FString& CustomDimension);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void SetCustomDimension02(const FString& CustomDimension);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void SetCustomDimension03(const FString& CustomDimension);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static FString GetRemoteConfigsValueAsString(const FString& Key);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static FString GetRemoteConfigsValueAsStringWithDefaultValue(const FString& Key, const FString& DefaultValue);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static bool IsRemoteConfigsReady();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static FString GetRemoteConfigsContentAsString();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static FString GetABTestingId();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static FString GetABTestingVariantId();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void OnQuit();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void DisableAdvertisingId(bool value);

    ////////////////////////////////////////////////////////////
    // HEALTH EVENT
    ////////////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void EnableSDKInitEvent(bool value);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void EnableFpsHistogram(bool value);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void EnableMemoryHistogram(bool value);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static void EnableHealthHardwareInfo(bool value);
};
