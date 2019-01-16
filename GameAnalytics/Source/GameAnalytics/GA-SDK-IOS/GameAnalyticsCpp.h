#pragma once

#import <vector>
#import <string>

class GameAnalyticsCpp {
public:
    static void configureAvailableCustomDimensions01(const std::vector<std::string>& list);
    static void configureAvailableCustomDimensions02(const std::vector<std::string>& list);
    static void configureAvailableCustomDimensions03(const std::vector<std::string>& list);

    static void configureAvailableResourceCurrencies(const std::vector<std::string>& list);
    static void configureAvailableResourceItemTypes(const std::vector<std::string>& list);

    static void configureBuild(const char *build);
    static void configureUserId(const char *userId);
    static void configureSdkGameEngineVersion(const char *gameEngineSdkVersion);
    static void configureGameEngineVersion(const char *gameEngineVersion);
    static void initialize(const char *gameKey, const char *gameSecret);

    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *fields);
    static void addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *fields);
    static void addResourceEvent(int flowType, const char *currency, float amount, const char *itemType, const char *itemId, const char *fields);
    static void addProgressionEvent(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, const char *fields);
    static void addProgressionEventWithScore(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const char *fields);
    static void addDesignEvent(const char *eventId, const char *fields);
    static void addDesignEventWithValue(const char *eventId, float value, const char *fields);
    static void addErrorEvent(int severity, const char *message, const char *fields);

    static void setEnabledInfoLog(bool flag);
    static void setEnabledVerboseLog(bool flag);
    static void setEnabledManualSessionHandling(bool flag);
    static void setEnabledEventSubmission(bool flag);
    static void setCustomDimension01(const char *customDimension);
    static void setCustomDimension02(const char *customDimension);
    static void setCustomDimension03(const char *customDimension);
    static void setFacebookId(const char *facebookId);
    static void setGender(const char *gender);
    static void setBirthYear(int birthYear);

    static void startSession();
    static void endSession();

    static const char* getCommandCenterValueAsString(const char *key);
    static const char* getCommandCenterValueAsString(const char *key, const char *defaultValue);
    static bool isCommandCenterReady();
    static const char* getConfigurationsContentAsString();
};
