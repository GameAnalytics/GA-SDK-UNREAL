//
// GA-SDK-CPP
// Copyright 2015 CppWrapper. All rights reserved.
//

#pragma once

#include <vector>
#include <memory>

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

	class IRemoteConfigsListener
	{
	public:
		virtual void onRemoteConfigsUpdated() = 0;
	};

    struct CharArray
    {
    public:
        char array[65] = "";
    };

    struct StringVector
    {
    public:
        StringVector& add(const char* s)
        {
            v.push_back(CharArray());
            snprintf(v[v.size() - 1].array, sizeof(v[v.size() - 1].array), "%s", s);
            return *this;
        }

        const std::vector<CharArray>& getVector() const
        {
            return v;
        }

    private:
        std::vector<CharArray> v;
    };

    class GameAnalytics
    {
     public:
         // configure calls should be used before initialize
         static void configureAvailableCustomDimensions01(const StringVector& customDimensions);
         static void configureAvailableCustomDimensions01(const char* customDimensions);
         static void configureAvailableCustomDimensions02(const StringVector& customDimensions);
         static void configureAvailableCustomDimensions02(const char* customDimensions);
         static void configureAvailableCustomDimensions03(const StringVector& customDimensions);
         static void configureAvailableCustomDimensions03(const char* customDimensions);
         static void configureAvailableResourceCurrencies(const StringVector& resourceCurrencies);
         static void configureAvailableResourceCurrencies(const char* resourceCurrencies);
         static void configureAvailableResourceItemTypes(const StringVector& resourceItemTypes);
         static void configureAvailableResourceItemTypes(const char* resourceItemTypes);
         static void configureBuild(const char* build);
         static void configureWritablePath(const char* writablePath);
         static void disableDeviceInfo();
         static void configureDeviceModel(const char* deviceModel);
         static void configureDeviceManufacturer(const char* deviceManufacturer);

         // the version of SDK code used in an engine. Used for sdk_version field.
         // !! if set then it will override the SdkWrapperVersion.
         // example "unity 4.6.9"
         static void configureSdkGameEngineVersion(const char* sdkGameEngineVersion);
         // the version of the game engine (if used and version is available)
         static void configureGameEngineVersion(const char* engineVersion);

         static void configureUserId(const char* uId);

         // initialize - starting SDK (need configuration before starting)
         static void initialize(const char* gameKey, const char* gameSecret);

         // add events
         static void addBusinessEvent(const char* currency, int amount, const char* itemType, const char* itemId, const char* cartType);

         static void addResourceEvent(EGAResourceFlowType flowType, const char* currency, float amount, const char* itemType, const char* itemId);

         static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char* progression01, const char* progression02, const char* progression03);

         static void addProgressionEvent(EGAProgressionStatus progressionStatus, const char* progression01, const char* progression02, const char* progression03, int score);

         static void addDesignEvent(const char* eventId);

         static void addDesignEvent(const char* eventId, double value);
         static void addErrorEvent(EGAErrorSeverity severity, const char* message);

         // set calls can be changed at any time (pre- and post-initialize)
         // some calls only work after a configure is called (setCustomDimension)
         static void setEnabledInfoLog(bool flag);
         static void setEnabledVerboseLog(bool flag);
         static void setEnabledManualSessionHandling(bool flag);
         static void setEnabledErrorReporting(bool flag);
         static void setEnabledEventSubmission(bool flag);
         static void setCustomDimension01(const char* dimension01);
         static void setCustomDimension02(const char* dimension02);
         static void setCustomDimension03(const char* dimension03);

         static void startSession();
         static void endSession();

         static std::vector<char> getRemoteConfigsValueAsString(const char* key);
         static std::vector<char> getRemoteConfigsValueAsString(const char* key, const char* defaultValue);
         static bool isRemoteConfigsReady();
         static void addRemoteConfigsListener(const std::shared_ptr<IRemoteConfigsListener>& listener);
         static void removeRemoteConfigsListener(const std::shared_ptr<IRemoteConfigsListener>& listener);
         static std::vector<char> getRemoteConfigsContentAsString();

         static std::vector<char> getABTestingId();
         static std::vector<char> getABTestingVariantId();

         // game state changes
         // will affect how session is started / ended
         static void onResume();
         static void onSuspend();
         static void onQuit();

         static bool isThreadEnding();
    };
} // namespace gameanalytics
