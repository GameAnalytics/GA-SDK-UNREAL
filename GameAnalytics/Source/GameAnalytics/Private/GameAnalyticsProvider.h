// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"

#include "GameAnalytics.h"
#include "GameAnalyticsModule.h"

class FGameAnalyticsProvider :
    public IAnalyticsProvider
{
    /** Path where analytics files are saved out */
    FString AnalyticsFilePath;
    /** Tracks whether we need to start the session or restart it */
    bool bHasSessionStarted;
    /** Whether an event was written before or not */
    bool bHasWrittenFirstEvent;
    /** Id representing the user the analytics are recording for */
    FString UserId;
    /** Unique Id representing the session the analytics are recording for */
    FString SessionId;
    /** Holds the Age if set */
    int32 Age;

    /** handles GA */
    UGameAnalytics* GameAnalytics;

    /** Settings for GameAnalytics, loaded from project configuration files */
    FGameAnalyticsModule::FGameAnalyticsProjectSettings ProjectSettings;
    
    FString GetAnalyticsPath() const;
    FString GenerateUserId() const;

public:

    FGameAnalyticsProvider(UGameAnalytics* GameAnalytics);
    virtual ~FGameAnalyticsProvider();

    virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override;
    virtual void EndSession() override;
    virtual void FlushEvents() override;
    
    void OnQuit();

    virtual void SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&& Attributes) override;
    virtual TArray<FAnalyticsEventAttribute> GetDefaultEventAttributesSafe() const override;
    virtual int32 GetDefaultEventAttributeCount() const override;
    virtual FAnalyticsEventAttribute GetDefaultEventAttribute(int AttributeIndex) const override;

    virtual void SetUserID(const FString& InUserID) override;
    virtual FString GetUserID() const override;

    virtual FString GetSessionID() const override;
    virtual bool SetSessionID(const FString& InSessionID) override;

    virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override;

    virtual void SetGender(const FString& InGender) ;
    virtual void SetAge(const int32 InAge) ;

    virtual void RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity) override;
    virtual void RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes) override;
    virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider) override;
    virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount) override;
    virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes) override;
    virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount) override;
    virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes) override;
    virtual void RecordError(const FString& Error) override;
    virtual void RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& Attributes) override;
    virtual void RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy) override;
    virtual void RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes) override;
    virtual void RecordProgress(const FString& ProgressType, const TArray<FString>& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes) override;
};
