#include "GameAnalyticsModule.h"
#include "GameAnalytics.h"
#include "GameAnalyticsProvider.h"
#include "Misc/ConfigCacheIni.h"

#define GA_PROJECT_SETTINGS TEXT("/Script/GameAnalyticsEditor.GameAnalyticsProjectSettings")

IMPLEMENT_MODULE( FGameAnalyticsModule, GameAnalytics )

FGameAnalyticsModule::FGameAnalyticsProjectSettings::PlatformInfo FGameAnalyticsModule::FGameAnalyticsProjectSettings::GetActivePlatform() const
{
    #if PLATFORM_IOS
        return iOS;
    #elif PLATFORM_ANDROID
        return Android;
    #elif PLATFORM_MAC
        return Mac;
    #elif PLATFORM_WINDOWS
        return Windows;
    #elif PLATFORM_LINUX
        return Linux;
    #else
        return {};
    #endif
}

void FGameAnalyticsModule::StartupModule()
{
    UE_LOG(LogGameAnalytics, Display, TEXT("FGameAnalyticsModule Constructor"));

    GameAnalytics = NewObject<UGameAnalytics>(GetTransientPackage(), UGameAnalytics::StaticClass(), "GameAnalytics", EObjectFlags::RF_Standalone);
    GameAnalytics->AddToRoot();

    GameAnalyticsProvider = MakeShareable(new FGameAnalyticsProvider(GameAnalytics));
}

void FGameAnalyticsModule::ShutdownModule()
{
    if (!GExitPurge && IsValid(GameAnalytics))
    {
        GameAnalytics->RemoveFromRoot();
    }
    
    GameAnalytics = nullptr;
}

#if (ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 13) || (ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 0)
TSharedPtr<IAnalyticsProvider> FGameAnalyticsModule::CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const
{
    return GameAnalyticsProvider;
}
#else
TSharedPtr<IAnalyticsProvider> FGameAnalyticsModule::CreateAnalyticsProvider(const FAnalytics::FProviderConfigurationDelegate& GetConfigValue) const
{
    return GameAnalyticsProvider;
}
#endif

FGameAnalyticsModule::FGameAnalyticsProjectSettings FGameAnalyticsModule::LoadProjectSettings()
{
    FGameAnalyticsProjectSettings Settings;

    if (!GConfig) return Settings;

    // Android 
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("AndroidGameKey"), Settings.Android.GameKey, GetIniName()))
    {
        Settings.Android.GameKey = TEXT("");
    }
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("AndroidSecretKey"), Settings.Android.SecretKey, GetIniName()))
    {
        Settings.Android.SecretKey = TEXT("");
    }
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("AndroidBuild"), Settings.Android.Build, GetIniName()))
    {
        Settings.Android.Build = TEXT("0.1");
    }

    // iOS
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("IosGameKey"), Settings.iOS.GameKey, GetIniName()))
    {
        Settings.iOS.GameKey = TEXT("");
    }
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("IosSecretKey"), Settings.iOS.SecretKey, GetIniName()))
    {
        Settings.iOS.SecretKey = TEXT("");
    }
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("IosBuild"), Settings.iOS.Build, GetIniName()))
    {
        Settings.iOS.Build = TEXT("0.1");
    }

    // MacOS
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("MacGameKey"), Settings.Mac.GameKey, GetIniName()))
    {
        Settings.Mac.GameKey = TEXT("");
    }
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("MacSecretKey"), Settings.Mac.SecretKey, GetIniName()))
    {
        Settings.Mac.SecretKey = TEXT("");
    }
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("MacBuild"), Settings.Mac.Build, GetIniName()))
    {
        Settings.Mac.Build = TEXT("0.1");
    }

    // Windows
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("WindowsGameKey"), Settings.Windows.GameKey, GetIniName()))
    {
        Settings.Windows.GameKey = TEXT("");
    }
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("WindowsSecretKey"), Settings.Windows.SecretKey, GetIniName()))
    {
        Settings.Windows.SecretKey = TEXT("");
    }
    if(!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("WindowsBuild"), Settings.Windows.Build, GetIniName()))
    {
        Settings.Windows.Build = TEXT("0.1");
    }

    // Linux
    if (!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("LinuxGameKey"), Settings.Linux.GameKey, GetIniName()))
    {
        Settings.Linux.GameKey = TEXT("");
    }
    if (!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("LinuxSecretKey"), Settings.Linux.SecretKey, GetIniName()))
    {
        Settings.Linux.SecretKey = TEXT("");
    }
    if (!GConfig->GetString(GA_PROJECT_SETTINGS, TEXT("LinuxBuild"), Settings.Linux.Build, GetIniName()))
    {
        Settings.Linux.Build = TEXT("0.1");
    }

    // Global options
    if(!GConfig->GetBool(GA_PROJECT_SETTINGS, TEXT("UseManualSessionHandling"), Settings.UseManualSessionHandling, GetIniName()))
    {
        Settings.UseManualSessionHandling = false;
    }
    if(!GConfig->GetBool(GA_PROJECT_SETTINGS, TEXT("AutoDetectAppVersion"), Settings.AutoDetectAppVersion, GetIniName()))
    {
        Settings.AutoDetectAppVersion = false;
    }
    if (!GConfig->GetBool(GA_PROJECT_SETTINGS, TEXT("DisableDeviceInfo"), Settings.DisableDeviceInfo, GetIniName()))
    {
        Settings.DisableDeviceInfo = false;
    }
    if (!GConfig->GetBool(GA_PROJECT_SETTINGS, TEXT("UseErrorReporting"), Settings.UseErrorReporting, GetIniName()))
    {
        Settings.UseErrorReporting = true;
    }
    if(!GConfig->GetBool(GA_PROJECT_SETTINGS, TEXT("InfoLogBuild"), Settings.InfoLogBuild, GetIniName()))
    {
        Settings.InfoLogBuild = true;
    }
    if(!GConfig->GetBool(GA_PROJECT_SETTINGS, TEXT("VerboseLogBuild"), Settings.VerboseLogBuild, GetIniName()))
    {
        Settings.VerboseLogBuild = false;
    }

    GConfig->GetArray(GA_PROJECT_SETTINGS, TEXT("+CustomDimensions01"), Settings.CustomDimensions01, GetIniName());
    GConfig->GetArray(GA_PROJECT_SETTINGS, TEXT("+CustomDimensions02"), Settings.CustomDimensions02, GetIniName());
    GConfig->GetArray(GA_PROJECT_SETTINGS, TEXT("+CustomDimensions03"), Settings.CustomDimensions03, GetIniName());
    GConfig->GetArray(GA_PROJECT_SETTINGS, TEXT("+ResourceCurrencies"), Settings.ResourceCurrencies, GetIniName());
    GConfig->GetArray(GA_PROJECT_SETTINGS, TEXT("+ResourceItemTypes"),  Settings.ResourceItemTypes,  GetIniName());

    return Settings;
}
