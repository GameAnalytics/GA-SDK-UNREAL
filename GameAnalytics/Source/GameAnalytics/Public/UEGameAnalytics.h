// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IAnalyticsProviderModule.h"
#include "Core.h"
#include "Runtime/Launch/Resources/Version.h"

class IAnalyticsProvider;

/**
 * The public interface to this module
 */
class FAnalyticsGameAnalytics :
	public IAnalyticsProviderModule
{
	/** Singleton for analytics */
	TSharedPtr<IAnalyticsProvider> GameAnalyticsProvider;

	//--------------------------------------------------------------------------
	// Module functionality
	//--------------------------------------------------------------------------
public:
	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline FAnalyticsGameAnalytics& Get()
	{
		return FModuleManager::LoadModuleChecked< FAnalyticsGameAnalytics >( "GameAnalytics" );
	}

	//--------------------------------------------------------------------------
	// provider factory functions
	//--------------------------------------------------------------------------
public:
	/**
	 * IAnalyticsProviderModule interface.
	 * Creates the analytics provider given a configuration delegate.
	 * The keys required exactly match the field names in the Config object. 
	 */
    
#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 13
    virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;
#else
    virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalytics::FProviderConfigurationDelegate& GetConfigValue) const override;
#endif
	
	struct FGameAnalyticsProjectSettings
	{
		FString IosGameKey;
		FString IosSecretKey;
		FString IosBuild;
		FString AndroidGameKey;
		FString AndroidSecretKey;
		FString AndroidBuild;
        FString MacGameKey;
        FString MacSecretKey;
        FString MacBuild;
		FString WindowsGameKey;
		FString WindowsSecretKey;
        FString WindowsBuild;
		TArray<FString> CustomDimensions01;
		TArray<FString> CustomDimensions02;
		TArray<FString> CustomDimensions03;
		TArray<FString> ResourceCurrencies;
		TArray<FString> ResourceItemTypes;
        bool UseCustomId;
        bool UseManualSessionHandling;
		bool SubmitErrors;
		bool SubmitAverageFPS;
		bool SubmitCriticalFPS;
		bool InfoLogEditor;
		bool InfoLogBuild;
		bool VerboseLogBuild;
	};

	static FGameAnalyticsProjectSettings LoadProjectSettings();

	
private:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
    
    static FORCEINLINE FString GetIniName() { return FString::Printf(TEXT("%sDefaultEngine.ini"), *FPaths::SourceConfigDir()); }
};
