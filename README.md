# GA-SDK-UNREAL
GameAnalytics SDK for the Unreal Engine.

Documentation located in the [wiki](https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki).  
For UWP support check out the [master_uwp](https://github.com/GameAnalytics/GA-SDK-UNREAL/tree/master_uwp) branch.

> :information_source:<br>
>
> The Unreal SDK include support for **iOS**, **Android**, **HTML5**, **Windows**, **Linux** and **Mac** platforms
>
> Requirements:<br/>
> **Unreal Engine:** 4.12+<br/>  
> **iOS:** iOS 7+<br/>
> **Android:** Android API Level 14<br/>
> **Windows:** Minimum specs for UE4<br/>
> **Mac:** Minimum specs for UE4

Changelog
---------
<!--(CHANGELOG_TOP)-->
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
