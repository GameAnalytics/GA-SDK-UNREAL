using UnrealBuildTool;
using System.IO;
using System;


namespace UnrealBuildTool.Rules
{
	public class GameAnalytics : ModuleRules
	{
        public GameAnalytics(TargetInfo Target)
		{
            var GameAnalyticsPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/" ));
            var libPath = Path.Combine(GameAnalyticsPath, "lib");

            PublicIncludePaths.Add(Path.Combine(GameAnalyticsPath, "include"));

            switch (Target.Platform)
            {
                case UnrealTargetPlatform.Win64:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "win64", "GameAnalytics.lib"));
                    break;
                case UnrealTargetPlatform.Win32:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "win32", "GameAnalytics.lib"));
                    break;
                /*case UnrealTargetPlatform.Android:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "android-armeabi", "libGameAnalytics.a"));
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "android-armeabi-v7a", "libGameAnalytics.a"));
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "android-x86", "libGameAnalytics.a"));

                    PrivateIncludePaths.AddRange(new string[] { "../../../../../../Source/Runtime/Launch/Private" });

                    break;*/
                case UnrealTargetPlatform.Mac:
                    //PublicAdditionalLibraries.Add(Path.Combine(libPath, "osx", "libGameAnalytics.a"));
                    //break;
                case UnrealTargetPlatform.IOS:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "ios", "libGameAnalytics.a"));
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

                case UnrealTargetPlatform.Android:
                case UnrealTargetPlatform.XboxOne:
                case UnrealTargetPlatform.PS4:
                case UnrealTargetPlatform.WinRT:
                case UnrealTargetPlatform.WinRT_ARM:
                case UnrealTargetPlatform.HTML5:
                case UnrealTargetPlatform.Linux:
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

            /*PrivateDependencyModuleNames.AddRange(
                new string[]
				{
					"Analytics",
					// ... add private dependencies that you statically link with here ...
				}
                );*/

            PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Private")));
            PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Public")));
            PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "Public")));


            PrivateDependencyModuleNames.AddRange(
                new string[]
				{
                    "Analytics",
                    "Engine"
					// ... add private dependencies that you statically link with here ...
				}
            );

            PublicIncludePathModuleNames.AddRange(
                new string[]
                {
                    "Analytics",
                    "Engine"
                }
            );
        }
	}
}