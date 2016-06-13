// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreUObject.h"

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
enum class EGAGender : uint8
{
    undefined = 0,
    male = 1,
    female = 2
};

class FAnalyticsProviderGameAnalytics :
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
	

	/** Settings for GameAnalytics, loaded from project configuration files */
	FAnalyticsGameAnalytics::FGameAnalyticsProjectSettings ProjectSettings;

public:
	FAnalyticsProviderGameAnalytics();
	virtual ~FAnalyticsProviderGameAnalytics();

	virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override;
	virtual void EndSession() override;
	virtual void FlushEvents() override;

	virtual void SetUserID(const FString& InUserID) override;
	virtual FString GetUserID() const override;

	virtual FString GetSessionID() const override;
	virtual bool SetSessionID(const FString& InSessionID) override;

	virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override;

	virtual void SetGender(const FString& InGender) ;
	virtual void SetAge(const int32 InAge) ;

    virtual void RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity);
	virtual void RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes);
    virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider);
    virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount);
	virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes);
    virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount);
	virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes);
    virtual void RecordError(const FString& Error);
	virtual void RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& Attributes);
    virtual void RecordProgress(const FString& ProgressType, const TArray<FString>& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& Attributes);
    
    template <typename EnumType>
    static FORCEINLINE EnumType GetEnumValueFromString(const FString& EnumName, const FString& String)
    {
        UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
        if(!Enum)
        {
            return EnumType(0);
        }
        return (EnumType)Enum->FindEnumIndex(FName(*String));
    }
};
