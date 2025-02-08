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

            var ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/"));
            var GA_SDK_CppPath = Path.GetFullPath(Path.Combine(ThirdPartyPath, "GA-SDK-CPP", "lib"));
            var libPath = Path.Combine(ThirdPartyPath, "lib");

            if(Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicAdditionalLibraries.Add(Path.Combine(GA_SDK_CppPath, "Win64", "GameAnalytics.lib"));
                PrivateDependencyModuleNames.AddRange(new string[] {  "OpenSSL", "libcurl" });
                PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "GA-SDK-CPP")));
            }
            else if(Target.Platform == UnrealTargetPlatform.Android)
            {
                PrivateDependencyModuleNames.Add("Launch");
                PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));
            }
            else if(Target.Platform == UnrealTargetPlatform.Mac)
            {
                PublicAdditionalLibraries.Add(Path.Combine(GA_SDK_CppPath, "Mac", "libGameAnalytics.a"));
                
                PublicFrameworks.AddRange(
                    new string[] {
                        "CoreFoundation",
                        "Foundation",
                        "CoreServices",
                        "SystemConfiguration"
                    }
                );
                PrivateDependencyModuleNames.AddRange(new string[] { "OpenSSL", "libcurl" });

                PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "GA-SDK-CPP")));
            }
            else if(Target.Platform == UnrealTargetPlatform.Linux)
            {
                PublicAdditionalLibraries.Add(Path.Combine(GA_SDK_CppPath, "Linux-clang", "libGameAnalytics.a"));
                PrivateDependencyModuleNames.AddRange(new string[] { "OpenSSL", "libcurl" });
                PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "GA-SDK-CPP")));
            }
            else if(Target.Platform == UnrealTargetPlatform.IOS)
            {
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "ios", "libGameAnalytics.a"));
                PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/IOS"));
                PublicFrameworks.AddRange(
                    new string[] {
                        "AdSupport",
                        "SystemConfiguration",
                        "AppTrackingTransparency"
                    }
                );

                PublicAdditionalLibraries.AddRange(
                    new string[] {
                        "sqlite3",
                        "z",
                        "c++"
                });

                string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "GameAnalytics_iOS_UPL.xml"));
            }
            /*else if(Target.Platform == UnrealTargetPlatform.HTML5)
            {
                if (Target.Architecture != "-win32")
                {
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "html5", "GameAnalytics.jspre"));
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "html5", "GameAnalyticsUnreal.js"));
                }
            }*/
            else
            {
                throw new NotImplementedException("This target platform is not configured for GameAnalytics SDK: " + Target.Platform.ToString());
            }

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "Json"
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
                    "Engine",
                    "Json"
                }
            );

            PublicIncludePathModuleNames.AddRange(
                new string[]
                {
                    "Analytics",
                    "Engine",
                    "Json"
                }
            );

            if (Target.Platform == UnrealTargetPlatform.Android)
            {
                string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "GameAnalytics_APL.xml"));
            }
        }
    }
}
