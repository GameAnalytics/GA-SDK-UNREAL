using UnrealBuildTool;
using System.IO;
using System;


namespace UnrealBuildTool.Rules
{
    public class GameAnalytics : ModuleRules
    {
#if WITH_FORWARDED_MODULE_RULES_CTOR
        public GameAnalytics(ReadOnlyTargetRules Target) : base(Target)
#else
        public GameAnalytics(TargetInfo Target)
#endif
        {
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

            var GameAnalyticsPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/" ));
            var libPath = Path.Combine(GameAnalyticsPath, "lib");

            switch (Target.Platform)
            {
                case UnrealTargetPlatform.Win64:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "win64", "GameAnalytics.lib"));
                    PrivateDependencyModuleNames.AddRange(new string[] {  "OpenSSL", "libcurl" });
                    break;

                case UnrealTargetPlatform.Win32:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "win32", "GameAnalytics.lib"));
                    PrivateDependencyModuleNames.AddRange(new string[] {  "OpenSSL", "libcurl" });
                    break;

                case UnrealTargetPlatform.Android:
                    PrivateDependencyModuleNames.Add("Launch");
                    PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));
                    break;

                case UnrealTargetPlatform.Mac:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "osx", "libGameAnalytics.a"));
                    PublicAdditionalLibraries.Add("curl");
                    PublicFrameworks.AddRange(
                        new string[] {
                            "CoreFoundation",
                            "Foundation",
                            "CoreServices"
                        }
                    );
                    PrivateDependencyModuleNames.AddRange(new string[] { "OpenSSL" });
                    break;

                case UnrealTargetPlatform.Linux:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "linux", "libGameAnalytics.a"));
                    PrivateDependencyModuleNames.AddRange(new string[] { "OpenSSL", "libcurl" });
                    break;

                case UnrealTargetPlatform.IOS:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "ios", "libGameAnalytics.a"));
                    PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/IOS"));
                    PublicFrameworks.AddRange(
                        new string[] {
                            "AdSupport",
                            "SystemConfiguration"
                        }
                    );

                    PublicAdditionalLibraries.AddRange(
                        new string[] {
                            "sqlite3",
                            "z",
                            "c++"
                    });
                    break;

                case UnrealTargetPlatform.HTML5:
                    if (Target.Architecture != "-win32")
                    {
                        PublicAdditionalLibraries.Add(Path.Combine(libPath, "html5", "GameAnalytics.jspre"));
                        PublicAdditionalLibraries.Add(Path.Combine(libPath, "html5", "GameAnalyticsUnreal.js"));
                    }
                    break;

                case UnrealTargetPlatform.XboxOne:
                case UnrealTargetPlatform.PS4:
                default:
                    throw new NotImplementedException("This target platform is not configured for GameAnalytics SDK: " + Target.Platform.ToString());
            }

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    // ... add other public dependencies that you statically link with here ...
                }
            );

            PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Private")));
            PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Public")));
            PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Public")));


            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "Analytics",
                    "Engine"
                }
            );

            if (Target.Platform == UnrealTargetPlatform.HTML5)
            {
                PrivateDependencyModuleNames.AddRange(
                    new string[]
                    {
                        "Json"
                    }
                );

                PublicIncludePathModuleNames.AddRange(
                    new string[]
                    {
                        "Json"
                    }
                );
            }

            PublicIncludePathModuleNames.AddRange(
                new string[]
                {
                    "Analytics",
                    "Engine"
                }
            );

            if (Target.Platform == UnrealTargetPlatform.Android)
            {
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "GameAnalytics_APL.xml"));
            }
        }
    }
}
