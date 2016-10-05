# GA-SDK-UNREAL
GameAnalytics SDK for the Unreal Engine.

Documentation located in the [wiki](https://github.com/GameAnalytics/GA-SDK-UNREAL/wiki).  

> :information_source:<br>
>
> The Unreal SDK include support for **iOS**, **Android**, **Windows** and **Mac** platforms
>
> Requirements:<br/>
> **Unreal Engine:** 4.13<br/>  
> For **Unreal Engine** 4.12 please download the 2.2.2 version of the SDK or older from our [releases](https://github.com/GameAnalytics/GA-SDK-UNREAL/releases)
> **iOS:** iOS 7+<br/>
> **Android:** Android API Level 14<br/>
> **Windows:** Minimum specs for UE4<br/>
> **Mac:** Minimum specs for UE4

Changelog
---------
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
