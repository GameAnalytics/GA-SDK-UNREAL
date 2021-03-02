# GA-SDK-UNREAL
GameAnalytics SDK for the Unreal Engine.

Documentation can be found [here](https://gameanalytics.com/docs/item/unreal-sdk).  
For UWP support check out the [master_uwp](https://github.com/GameAnalytics/GA-SDK-UNREAL/tree/master_uwp) branch.

If you have any issues or feedback regarding the SDK, please contact our friendly support team [here](https://gameanalytics.com/contact).

> :information_source:
>
> The Unreal SDK include support for **iOS**, **Android**, **HTML5**, **Windows**, **Linux** and **Mac** platforms
>
> Requirements:
> * **Unreal Engine:** 4.15+  &nbsp;
> * **iOS:** iOS 7+ &nbsp;
> * **Android:** Android API Level 14 &nbsp;
> * **Windows:** Minimum specs for UE4 &nbsp;
> * **Mac:** Minimum specs for UE4 &nbsp;    
>   
> **Build size:**   
> Note that download size differ from the actual build size.   
>   
> **Android:**   
> The SDK build size in a native Android app is only around **49Kb** and the dependecies take up to **820Kb** depending if your app already uses some of the same dependencies.   
>   
> **iOS:**   
> The SDK build size in a native iOS app is only around **242Kb** (armv7) / **259Kb** (armv8).
>   
> **NOTE:** Are you getting compile errors using Unreal Engine v4.15.x? Look [here](https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki/Manual-Installation#compile-errors-on-unreal-engine-v415x) for how to fix these errors.

Changelog
---------
<!--(CHANGELOG_TOP)-->
**4.3.14**
* added idfa consent status field to events (ios)

**4.3.13**
* added disable device info to settings

**4.3.12**
* updated client ts validator

**4.3.11**
* fixed dependencies for iOS (min. XCode 12 required)

**4.3.10**
* fixed return values for remote configs and ab testing functions

**4.3.9**
* added support for unreal engine 4.26

**4.3.8**
* corrected ad event annotation

**4.3.7**
* added ARM64 architecture to mac libs

**4.3.6**
* fixed build errors for linux

**4.3.5**
* fixed log messages output to console in editor

**4.3.4**
* added editor logs when calling functions in editor play mode

**4.3.3**
* improved user identifer flow for ios (ios)

**4.3.2**
* fix to the seperation of sqlite code for some platforms

**4.3.1**
* seperated sqlite code into its own library (osx, windows, linux)

**4.3.0**
* updated user identifier flow to prepare for iOS 14 IDFA changes (ios)

**4.2.1**
* fixed progression event with scores (android)

**4.2.0**
* exposed functions to get AB testing id and variant id

**4.1.5**
* fixed link errors for ios

**4.1.4**
* added support for unreal engine 4.25

**4.1.3**
* fixed compile errors

**4.1.2**
* compile error fix for int64

**4.1.1**
* compile error fixes

**4.1.0**
* added ad event (ios, android)
* organizations added to games key list

**4.0.13**
* logo updated

**4.0.12**
* uplugin fix

**4.0.11**
* compile fixes

**4.0.10**
* removed facebook, gender and birthyear methods
* added auto detect app version for build field option (only android, ios)

**4.0.9**
* changed editor module type from 'Developer' to 'DeveloperTool'

**4.0.8**
* removed html5 related code

**4.0.7**
* A/B testing fixes

**4.0.6**
* removed compile warnings

**4.0.5**
* added support for Unreal Engine 4.24

**4.0.4**
* fixed getRemoteConfigsValueAsString (ios)

**4.0.3**
* remote configs fixes

**4.0.2**
* corrected naming of function

**4.0.1**
* small fixes

**4.0.0**
* Remote Config calls have been updated and the old calls have deprecated. Please see GA documentation for the new SDK calls and migration guide
* A/B testing support added

**3.1.13**
* compile error fixes for html5

**3.1.12**
* compile error fixes for html5

**3.1.11**
* fixes android builds

**3.1.10**
* fixed build errors

**3.1.9**
* fixed command center bugs

**3.1.8**
* added support for unreal engine 4.23

**3.1.7**
* added check if log files and database can't be created (desktop platforms)

**3.1.6**
* fixed progression event for desktop platforms
* fixed hanging background thread when closing application down for desktop platforms

**3.1.5**
* fixes to warnings and errors

**3.1.4**
* fixed build errors for html5

**3.1.3**
* fixed initialize method to be able to be called from code

**3.1.2**
* added support for unreal engine v4.22

**3.1.1**
* html5 build fix
* various other bug fixes

**3.1.0**
* added enable/disable event submission function

**3.0.6**
* fixed business event validation

**3.0.5**
* updated to support unreal engine 4.21

**3.0.4**
* android bug fixes

**3.0.3**
* fixed shutdown bugs for desktop platforms

**3.0.2**
* fixed thread hanging on shutdown for desktop platforms

**3.0.1**
* fixed compile errors

**3.0.0**
* added command center functionality
* added gameanalytics blueprint functions

**2.6.28**
* fixed more compile errors for mac

**2.6.27**
* fixed android crash

**2.6.26**
* fixed compile errors

**2.6.19**
* compile fixes for android (android)
* updated to be compatible with unreal engine v4.20

**2.6.18**
* various bug fixes

**2.6.17**
* fixes building for linux (linux)

**2.6.16**
* added custom dimensions to design error events
* added option to startsession with gamekey and secretkey instead of getting keys from settings object

**2.6.15**
* fixed session length bug
* fixed not allowing to add events when session is not started

**2.6.14**
* fixed crash bug for closing down sdk for desktop platforms (windows, mac, linux)

**2.6.13**
* iOS support temporarily removed until Epic fixes some issues the iOS toolchain causes in Unreal Engine 4.19

**2.6.12**
* added compatability for Unreal Engine v4.19

**2.6.11**
* log library has been replaced which caused some problems on machine with certain locales set (mac, windows, linux)

**2.6.10**
* bug fix to progression event crashes

**2.6.9**
* additional fixes to Unreal Engine 4.18 compatability

**2.6.8**
* fixes to Unreal Engine 4.18 compatability

**2.6.7**
* fixed javascript library (html5)

**2.6.6**
* updated to be compatible with Unreal Engine 4.18

**2.6.5**
* bug fix to android JNI memory leak (android)

**2.6.4**
* made compatible with Unreal Engine 4.17

**2.6.3**
* jni bug fix for progression events with scores (android)

**2.6.2**
* switched to use third party OpenSSL and libCurl libraries bundled with Unreal Engine

**2.6.1**
* editor UI bug fix when running game in editor viewport with GameAnalytics plugin enabled

**2.6.0**
* changed the behaviour of using IMEI with the 'READ_PHONE_STATE' permission to guarantee precise analytics for certain regions (android)

**2.5.5**
* fixed compile warnings

**2.5.4**
* fixed html5 wrapper to use correct namespace (html5)

**2.5.3**
* bug fix for end session when using manual session handling

**2.5.2**
* session length precision improvement

**2.5.1**
* custom user id bug fix

**2.5.0**
* added support for linux

**2.4.0**
* added support for html5

**2.2.13**
* corrected win32 library (win32)

**2.2.12**
* bug fix for progression event with score in Android builds (android)

**2.2.11**
* proguard fix when making distribution build (android)

**2.2.10**
* possible to set custom dimensions and demographics before initialise

**2.2.9**
* fixed missing namespace for JNI function calls (android)

**2.2.8**
* fix for using plugin directly from C++ code in your project

**2.2.7**
* fix for empty user_id bug (windows, mac)

**2.2.6**
* added support for both Unreal Engine 4.12 and 4.13

**2.2.5**
* bug fix to error when cooking and packaging build

**2.2.4**
* fixed user_id tracking for iOS 10 (ios)
* small fix related to manual session handling (android)

**2.2.3**
* fix for empty user id in events (mac, windows)

**2.2.2**
* Updated to be compatible with Unreal 4.13
* Updated Google Play Services libraries to use latest version (android)

**2.2.1**
* wrong platform in events bug fix (windows, mac)
* crash bug fix (windows, mac)

**2.2.0**
* added manual session handling

**2.1.2**
* fixed default GameAnalytics settings values

**2.1.1**
* bug fix for missing configureUsedId in native iOS lib (ios)

**2.1.0**
* Windows and Mac support added (windows and mac)

**2.0.0**
* various Blueprint event bug fixes
* Android support added (android)

**0.1.3**
* fixed third party include path

**0.1.2**
* fixed compile warnings for Unreal Engine 4.11

**0.1.1**
* minor fixes

**0.1.0**
* initial version (iOS)
