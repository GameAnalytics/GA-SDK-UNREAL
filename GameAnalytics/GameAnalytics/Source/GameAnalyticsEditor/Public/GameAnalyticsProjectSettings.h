// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameAnalyticsProjectSettings.generated.h"

UCLASS(Config=Engine, DefaultConfig)
class UGameAnalyticsProjectSettings : public UObject
{
    GENERATED_UCLASS_BODY()
    
public:
    
    // Game Key
    UPROPERTY(Config, EditAnywhere, Category=IosSetup)
    FString IosGameKey;
    
    // Secret Key
    UPROPERTY(Config, EditAnywhere, Category=IosSetup)
	FString IosSecretKey;

	// Build
	UPROPERTY(Config, EditAnywhere, Category = IosSetup)
	FString IosBuild = "0.1";
    
    // Game Key
    /*UPROPERTY(Config, EditAnywhere, Category=AndroidSetup)
    FString AndroidGameKey;
    
    // Secret Key
    UPROPERTY(Config, EditAnywhere, Category=AndroidSetup)
    FString AndroidSecretKey;
	
	// Build
	UPROPERTY(Config, EditAnywhere, Category = AndroidSetup)
	FString AndroidBuild = "0.1";*/

    // Custom Dimensions 01
    UPROPERTY(Config, EditAnywhere, Category=CustomDimensions)
    TArray<FString> CustomDimensions01;

    // Custom Dimensions 02
    UPROPERTY(Config, EditAnywhere, Category=CustomDimensions)
    TArray<FString> CustomDimensions02;
    
    // Custom Dimensions 03
    UPROPERTY(Config, EditAnywhere, Category=CustomDimensions)
    TArray<FString> CustomDimensions03;
    
    // Resource Currencies
    UPROPERTY(Config, EditAnywhere, Category=ResourceTypes)
    TArray<FString> ResourceCurrencies;
    
    // Resource Item Types
    UPROPERTY(Config, EditAnywhere, Category=ResourceTypes)
    TArray<FString> ResourceItemTypes;
    
    // Submit Errors
    //UPROPERTY(Config, EditAnywhere, Category=Advanced)
    //bool SubmitErrors = true;
    
    // Submit Average Frames Per Second
    //UPROPERTY(Config, EditAnywhere, Category=Advanced)
    //bool SubmitAverageFPS = true;
    
    // Submit Critical Frames Per Second
    //UPROPERTY(Config, EditAnywhere, Category=Advanced)
    //bool SubmitCriticalFPS = true;
    
    // Info Log Editor
    //UPROPERTY(Config, EditAnywhere, Category=Debug)
    //bool InfoLogEditor = true;
    
    // Info Log Build
    UPROPERTY(Config, EditAnywhere, Category=Debug)
    bool InfoLogBuild = true;
    
    // Verbose Log Build
    UPROPERTY(Config, EditAnywhere, Category=Debug)
    bool VerboseLogBuild = false;
};