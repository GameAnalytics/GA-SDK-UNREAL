// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Interfaces/IAnalyticsProviderModule.h"
#include "Interfaces/IAnalyticsProvider.h"
#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "Runtime/Launch/Resources/Version.h"

#include "GameAnalytics.h"

#if (ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 15) || (ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 0)
#include "Modules/ModuleManager.h"
#endif

/**
 * The public interface to this module
 */
class FGameAnalyticsModule :
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
    static inline FGameAnalyticsModule& Get()
    {
        return FModuleManager::LoadModuleChecked< FGameAnalyticsModule >( "GameAnalytics" );
    }

    inline UGameAnalytics* GetInstance()
    {
        return GameAnalytics;
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
#if (ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 13) || (ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 0)
    using Delegate = FAnalyticsProviderConfigurationDelegate;
#else
    using Delegate = FAnalytics::FProviderConfigurationDelegate;
#endif

    virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const Delegate& GetConfigValue) const override;

    struct FGameAnalyticsProjectSettings
    {
        struct PlatformInfo
        {
            FString GameKey;
            FString SecretKey;
            FString Build;
        };
        
        PlatformInfo iOS;
        PlatformInfo Android;
        PlatformInfo Mac;
        PlatformInfo Windows;
        PlatformInfo Linux;
        
        TArray<FString> CustomDimensions01;
        TArray<FString> CustomDimensions02;
        TArray<FString> CustomDimensions03;
        TArray<FString> ResourceCurrencies;
        TArray<FString> ResourceItemTypes;
        
        bool UseManualSessionHandling;
		bool AutoDetectAppVersion;
        bool DisableDeviceInfo;
        bool UseErrorReporting;
        bool SubmitErrors;
        bool SubmitAverageFPS;
        bool SubmitCriticalFPS;
        bool InfoLogEditor;
        bool InfoLogBuild;
        bool VerboseLogBuild;
        
        PlatformInfo GetActivePlatform() const;
    };

    static FGameAnalyticsProjectSettings LoadProjectSettings();

private:

    UGameAnalytics* GameAnalytics{nullptr};

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    static FORCEINLINE FString GetIniName() { return FString::Printf(TEXT("%sDefaultEngine.ini"), *FPaths::SourceConfigDir()); }
};
