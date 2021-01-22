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

            if(Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "win64", "GameAnalytics.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "win64", "Sqlite.lib"));
                PrivateDependencyModuleNames.AddRange(new string[] {  "OpenSSL", "libcurl" });
            }
            else if(Target.Platform == UnrealTargetPlatform.Win32)
            {
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "win32", "GameAnalytics.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "win32", "Sqlite.lib"));
                PrivateDependencyModuleNames.AddRange(new string[] {  "OpenSSL", "libcurl" });
            }
            else if(Target.Platform == UnrealTargetPlatform.Android)
            {
                PrivateDependencyModuleNames.Add("Launch");
                PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));
            }
            else if(Target.Platform == UnrealTargetPlatform.Mac)
            {
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "osx", "libGameAnalytics.a"));
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "osx", "libSqlite.a"));
                PublicAdditionalLibraries.Add("curl");
                PublicFrameworks.AddRange(
                    new string[] {
                        "CoreFoundation",
                        "Foundation",
                        "CoreServices"
                    }
                );
                PrivateDependencyModuleNames.AddRange(new string[] { "OpenSSL" });
            }
            else if(Target.Platform == UnrealTargetPlatform.Linux)
            {
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "linux", "libGameAnalytics.a"));
                PublicAdditionalLibraries.Add(Path.Combine(libPath, "linux", "libSqlite.a"));
                PrivateDependencyModuleNames.AddRange(new string[] { "OpenSSL", "libcurl" });
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

            /*if (Target.Platform == UnrealTargetPlatform.HTML5)
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
            }*/

            PublicIncludePathModuleNames.AddRange(
                new string[]
                {
                    "Analytics",
                    "Engine"
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
