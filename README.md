# GA-SDK-UNREAL
GameAnalytics SDK for the Unreal Engine.

Documentation can be found [here](https://gameanalytics.com/docs/unreal4-sdk).  
For UWP support check out the [master_uwp](https://github.com/GameAnalytics/GA-SDK-UNREAL/tree/master_uwp) branch.

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
