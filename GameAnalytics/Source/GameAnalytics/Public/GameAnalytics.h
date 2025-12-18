//
//  GameAnalytics.h
//  GA-SDK-IOS
//
//  Copyright (c) 2015 GameAnalytics. All rights reserved.
//

#pragma once

#include "UObject/Object.h"
#include "Dom/JsonObject.h"

#include "GAEnums.h"
#include "GAWrapper.h"
#include "GameAnalytics.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameAnalytics, Display, All);

USTRUCT(BlueprintType)
struct FGACustomValue
{
    GENERATED_BODY();

    UPROPERTY(BlueprintReadWrite, Category = "GameAnalytics")
    FString Key;

    UPROPERTY(BlueprintReadWrite, Category = "GameAnalytics")
    FString ValueString;

    UPROPERTY(BlueprintReadWrite, Category = "GameAnalytics")
    double ValueNumber = 0.0;

    UPROPERTY(BlueprintReadWrite, Category = "GameAnalytics")
    bool ValueBool = false;

    UPROPERTY(BlueprintReadWrite, Category = "GameAnalytics")
    EGAValueType ValueType = EGAValueType::value_number;
};

USTRUCT(BlueprintType)
struct GAMEANALYTICS_API FGACustomFields
{
    GENERATED_BODY();

    UPROPERTY(BlueprintReadWrite, Category = "GameAnalytics")
    TArray<FGACustomValue> Values;

    bool IsEmpty() const;

    void Set(FString const& Key, double Value);
    void Set(FString const& Key, FString const& Value);
    void Set(FString const& Key, bool Value);

    FString ToString() const;
    
    TSharedRef<FJsonObject> ToJson() const;
};

class UGameAnalyticsPerformance;

UCLASS(BlueprintType)
class GAMEANALYTICS_API UGameAnalytics : public UObject
{
    GENERATED_UCLASS_BODY()

    // pointer to implementation
    TUniquePtr<gameanalytics::GAWrapper> _impl;
    
    // optional performance tracker
    UGameAnalyticsPerformance* _performanceTracker = nullptr;

public:

    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    static UGameAnalytics* GetInstance();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureAvailableCustomDimensions01(const TArray<FString>& List);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureAvailableCustomDimensions02(const TArray<FString>& List);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureAvailableCustomDimensions03(const TArray<FString>& List);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureAvailableResourceCurrencies(const TArray<FString>& List);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureAvailableResourceItemTypes(const TArray<FString>& List);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureBuild(FString const& Build);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureAutoDetectAppVersion(bool Flag);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void DisableDeviceInfo();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureUserId(FString const& UserId);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureExternalUserId(FString const& UserId);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureSdkGameEngineVersion(const FString& GameEngineSdkVersion);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void ConfigureGameEngineVersion(const FString& GameEngineVersion);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void Initialize(FString const& GameKey, FString const& GameSecret);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetEnabledInfoLog(bool Flag);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetEnabledVerboseLog(bool Flag);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetEnabledManualSessionHandling(bool Flag);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetEnabledErrorReporting(bool Flag);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetEnabledEventSubmission(bool Flag);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void StartSession();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void EndSession();

    //////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddBusinessEvent(FString const& Currency, int Amount, FString const& ItemType, FString const& ItemId, FString const& CartType, FString const& Receipt = "", const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddBusinessEventAndAutoFetchReceipt(FString const& Currency, int Amount, FString const& ItemType, FString const& ItemId, FString const& CartType, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddBusinessEventWithReceipt(FString const& Currency, int Amount, FString const& ItemType, FString const& ItemId, FString const& CartType, FString const& Receipt, FString const& Store, FString const& Signature, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddResourceEvent(EGAResourceFlowType FlowType, const FString &Currency, float Amount, const FString &ItemType, const FString &ItemId, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddProgressionEvent(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02 = "", const FString &Progression03 = "", const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddProgressionEventWithScore(EGAProgressionStatus ProgressionStatus, int Score, const FString &Progression01 = "", const FString &Progression02 = "", const FString &Progression03 = "", const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddDesignEvent(const FString& EventId, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddDesignEventWithValue(const FString& EventId, float Value, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddErrorEvent(EGAErrorSeverity Severity, const FString& Message, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    //////////////////////////////////////////////////////
    // AD EVENTS ARE ONLY AVAILABLE FOR IOS AND ANDROID //
    //////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddAdEvent(EGAAdAction Action, EGAAdType AdType, const FString& AdSdkName, const FString& AdPlacement, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddAdEventWithDuration(EGAAdAction Action, EGAAdType AdType, const FString& AdSdkName, const FString& AdPlacement, int64 Duration, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void AddAdEventWithReason(EGAAdAction Action, EGAAdType AdType, const FString& AdSdkName, const FString& AdPlacement, EGAAdError Reason, const FGACustomFields CustomFields = FGACustomFields(), bool MergeFields = false);

    ////////////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetCustomDimension01(const FString& CustomDimension);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetCustomDimension02(const FString& CustomDimension);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetCustomDimension03(const FString& CustomDimension);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    FString GetUserId();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    FString GetExternalUserId();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    FString GetRemoteConfigsValueAsString(const FString& Key, const FString& DefaultValue = "");

    // FJsonObject cannot be exposed to blueprints
    TSharedPtr<FJsonObject> GetRemoteConfigsValueAsJSON(const FString& key);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    bool IsRemoteConfigsReady();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    FString GetRemoteConfigsContentAsString();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    FString GetABTestingId();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    FString GetABTestingVariantId();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void OnQuit();

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void EnableAdvertisingId(bool Value);

    ////////////////////////////////////////////////////////////
    // HEALTH EVENT
    ////////////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void EnableSDKInitEvent(bool Value);
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void EnableFpsHistogram(bool Value);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void EnableMemoryHistogram(bool Value);

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void EnableHealthHardwareInfo(bool Value);

    ////////////////////////////////////////////////////////////

    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    int64 GetElapsedSessionTime();
        
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    int64 GetElapsedTimeFromAllSessions();

    ////////////////////////////////////////////////////////////
    
    UFUNCTION(BlueprintCallable, Category = "GameAnalytics")
    void SetWritablePath(FString const& Path);
};

