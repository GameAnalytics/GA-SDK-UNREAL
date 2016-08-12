//
// GA-SDK-CPP
// Copyright 2015 CppWrapper. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

namespace gameanalytics 
{

    /*!
     @enum
     @discussion
     This enum is used to specify flow in resource events
     @constant GAResourceFlowTypeSource
     Used when adding to a resource currency
     @constant GAResourceFlowTypeSink
     Used when subtracting from a resource currency
     */
    enum EGAResourceFlowType
    {
        Source = 1,
        Sink = 2
    };

    /*!
     @enum
     @discussion
     his enum is used to specify status for progression event
     @constant GAProgressionStatusStart
     User started progression
     @constant GAProgressionStatusComplete
     User succesfully ended a progression
     @constant GAProgressionStatusFail
     User failed a progression
     */
    enum EGAProgressionStatus
    {
        Start = 1,
        Complete = 2,
        Fail = 3
    };

    /*!
     @enum
     @discussion
     his enum is used to specify severity of an error event
     @constant GAErrorSeverityDebug
     @constant GAErrorSeverityInfo
     @constant GAErrorSeverityWarning
     @constant GAErrorSeverityError
     @constant GAErrorSeverityCritical
     */
    enum EGAErrorSeverity
    {
        Debug = 1,
        Info = 2,
        Warning = 3,
        Error = 4,
        Critical = 5
    };

    enum EGAGender
    {
        Male = 1,
        Female = 2
    };

    class GameAnalytics
    {
     public:
        // configure calls should be used before initialize
        static void configureAvailableCustomDimensions01(const std::vector<std::string>& customDimensions);
        static void configureAvailableCustomDimensions02(const std::vector<std::string>& customDimensions);
        static void configureAvailableCustomDimensions03(const std::vector<std::string>& customDimensions);
        static void configureAvailableResourceCurrencies(const std::vector<std::string>& resourceCurrencies);
        static void configureAvailableResourceItemTypes(const std::vector<std::string>& resourceItemTypes);
        static void configureBuild(const std::string& build);
        static void configureWritablePath(const std::string& writablePath);
        static void configureDeviceModel(const std::string& deviceModel);
        static void configureDeviceManufacturer(const std::string& deviceManufacturer);

        // the version of SDK code used in an engine. Used for sdk_version field.
        // !! if set then it will override the SdkWrapperVersion.
        // example "unity 4.6.9"
        static void configureSdkGameEngineVersion(const std::string& sdkGameEngineVersion);
        // the version of the game engine (if used and version is available)
        static void configureGameEngineVersion(const std::string& engineVersion);

        static void configureUserId(const std::string& uId);

        // initialize - starting SDK (need configuration before starting)
        static void initialize(const std::string& gameKey, const std::string& gameSecret);

        // add events
        static void addBusinessEvent(const std::string& currency,
                                                 int amount,
                                                 const std::string& itemType,
                                                 const std::string& itemId,
                                                 const std::string& cartType);

        static void addResourceEvent(EGAResourceFlowType flowType,
                                                 const std::string& currency,
                                                 float amount,
                                                 const std::string&itemType,
                                                 const std::string& itemId);

        static void addProgressionEvent(EGAProgressionStatus progressionStatus,
                                                             const std::string& progression01,
                                                             const std::string& progression02,
                                                             const std::string& progression03);

        static void addProgressionEvent(EGAProgressionStatus progressionStatus,
                                                             const std::string& progression01,
                                                             const std::string& progression02,
                                                             const std::string& progression03,
                                                             int score);

        static void addDesignEvent(const std::string& eventId);
        static void addDesignEvent(const std::string& eventId, double value);
        static void addErrorEvent(EGAErrorSeverity severity, const std::string& message);

        // set calls can be changed at any time (pre- and post-initialize)
        // some calls only work after a configure is called (setCustomDimension)
        static void setEnabledInfoLog(bool flag);
        static void setEnabledVerboseLog(bool flag);
        static void setEnabledManualSessionHandling(bool flag);
        static void setCustomDimension01(const std::string& dimension01);
        static void setCustomDimension02(const std::string& dimension02);
        static void setCustomDimension03(const std::string& dimension03);
        static void setFacebookId(const std::string& facebookId);
        static void setGender(EGAGender gender);
        static void setBirthYear(int birthYear);

        static void startSession();
        static void endSession();

        // game state changes
        // will affect how session is started / ended
        static void onResume();
        static void onStop();

     private:
        static bool isSdkReady(bool needsInitialized);
        static bool isSdkReady(bool needsInitialized, bool warn);
        static bool isSdkReady(bool needsInitialized, bool warn, std::string message);
    };
} // namespace gameanalytics
