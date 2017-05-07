var GameAnalyticsUnreal = {
    js_configureAvailableCustomDimensions01: function(list)
    {
        gameanalytics.GameAnalytics.configureAvailableCustomDimensions01(JSON.parse(Pointer_stringify(list)));
    },
    js_configureAvailableCustomDimensions02: function(list)
    {
        gameanalytics.GameAnalytics.configureAvailableCustomDimensions02(JSON.parse(Pointer_stringify(list)));
    },
    js_configureAvailableCustomDimensions03: function(list)
    {
        gameanalytics.GameAnalytics.configureAvailableCustomDimensions03(JSON.parse(Pointer_stringify(list)));
    },
    js_configureAvailableResourceCurrencies: function(list)
    {
        gameanalytics.GameAnalytics.configureAvailableResourceCurrencies(JSON.parse(Pointer_stringify(list)));
    },
    js_configureAvailableResourceItemTypes: function(list)
    {
        gameanalytics.GameAnalytics.configureAvailableResourceItemTypes(JSON.parse(Pointer_stringify(list)));
    },
    js_configureSdkGameEngineVersion: function(unitySdkVersion)
    {
        gameanalytics.GameAnalytics.configureSdkGameEngineVersion(Pointer_stringify(unitySdkVersion));
    },
    js_configureGameEngineVersion: function(unityEngineVersion)
    {
        gameanalytics.GameAnalytics.configureGameEngineVersion(Pointer_stringify(unityEngineVersion));
    },
    js_configureBuild: function(build)
    {
        gameanalytics.GameAnalytics.configureBuild(Pointer_stringify(build));
    },
    js_configureUserId: function(userId)
    {
        gameanalytics.GameAnalytics.configureUserId(Pointer_stringify(userId));
    },
    js_initialize: function(gamekey, gamesecret)
    {
        gameanalytics.GameAnalytics.initialize(Pointer_stringify(gamekey), Pointer_stringify(gamesecret));
    },
    js_setCustomDimension01: function(customDimension)
    {
        gameanalytics.GameAnalytics.setCustomDimension01(Pointer_stringify(customDimension));
    },
    js_setCustomDimension02: function(customDimension)
    {
        gameanalytics.GameAnalytics.setCustomDimension02(Pointer_stringify(customDimension));
    },
    js_setCustomDimension03: function(customDimension)
    {
        gameanalytics.GameAnalytics.setCustomDimension03(Pointer_stringify(customDimension));
    },
    js_addBusinessEvent: function(currency, amount, itemType, itemId, cartType)
    {
        gameanalytics.GameAnalytics.addBusinessEvent(Pointer_stringify(currency), amount, Pointer_stringify(itemType), Pointer_stringify(itemId), Pointer_stringify(cartType));
    },
    js_addResourceEvent: function(flowType, currency, amount, itemType, itemId)
    {
        gameanalytics.GameAnalytics.addResourceEvent(flowType, Pointer_stringify(currency), amount, Pointer_stringify(itemType), Pointer_stringify(itemId));
    },
    js_addProgressionEvent: function(progressionStatus, progression01, progression02, progression03)
    {
        gameanalytics.GameAnalytics.addProgressionEvent(progressionStatus, Pointer_stringify(progression01), Pointer_stringify(progression02), Pointer_stringify(progression03));
    },
    js_addProgressionEventWithScore: function(progressionStatus, progression01, progression02, progression03, score)
    {
        gameanalytics.GameAnalytics.addProgressionEvent(progressionStatus, Pointer_stringify(progression01), Pointer_stringify(progression02), Pointer_stringify(progression03), score);
    },
    js_addDesignEvent: function(eventId)
    {
        gameanalytics.GameAnalytics.addDesignEvent(Pointer_stringify(eventId));
    },
    js_addDesignEventWithValue: function(eventId, value)
    {
        gameanalytics.GameAnalytics.addDesignEvent(Pointer_stringify(eventId), value);
    },
    js_addErrorEvent: function(severity, message)
    {
        gameanalytics.GameAnalytics.addErrorEvent(severity, Pointer_stringify(message));
    },
    js_setEnabledInfoLog: function(enabled)
    {
        gameanalytics.GameAnalytics.setEnabledInfoLog(enabled);
    },
    js_setEnabledVerboseLog: function(enabled)
    {
        gameanalytics.GameAnalytics.setEnabledVerboseLog(enabled);
    },
    js_setManualSessionHandling: function(enabled)
    {
        gameanalytics.GameAnalytics.setEnabledManualSessionHandling(enabled);
    },
    js_startSession: function()
    {
        gameanalytics.GameAnalytics.startSession();
    },
    js_endSession: function()
    {
        gameanalytics.GameAnalytics.endSession();
    },
    js_onStop: function()
    {
        gameanalytics.GameAnalytics.onStop();
    },
    js_setFacebookId: function(facebookId)
    {
        gameanalytics.GameAnalytics.setFacebookId(Pointer_stringify(facebookId));
    },
    js_setGender: function(gender)
    {
        gameanalytics.GameAnalytics.setGender(gender);
    },
    js_setBirthYear: function(birthYear)
    {
        gameanalytics.GameAnalytics.setBirthYear(birthYear);
    }
};

mergeInto(LibraryManager.library, GameAnalyticsUnreal);
