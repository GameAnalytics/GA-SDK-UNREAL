var GameAnalyticsUnreal = {
    js_configureAvailableCustomDimensions01: function(list)
    {
        ga.GameAnalytics.configureAvailableCustomDimensions01(JSON.parse(Pointer_stringify(list)));
    },
    js_configureAvailableCustomDimensions02: function(list)
    {
        ga.GameAnalytics.configureAvailableCustomDimensions02(JSON.parse(Pointer_stringify(list)));
    },
    js_configureAvailableCustomDimensions03: function(list)
    {
        ga.GameAnalytics.configureAvailableCustomDimensions03(JSON.parse(Pointer_stringify(list)));
    },
    js_configureAvailableResourceCurrencies: function(list)
    {
        ga.GameAnalytics.configureAvailableResourceCurrencies(JSON.parse(Pointer_stringify(list)));
    },
    js_configureAvailableResourceItemTypes: function(list)
    {
        ga.GameAnalytics.configureAvailableResourceItemTypes(JSON.parse(Pointer_stringify(list)));
    },
    js_configureSdkGameEngineVersion: function(unitySdkVersion)
    {
        ga.GameAnalytics.configureSdkGameEngineVersion(Pointer_stringify(unitySdkVersion));
    },
    js_configureGameEngineVersion: function(unityEngineVersion)
    {
        ga.GameAnalytics.configureGameEngineVersion(Pointer_stringify(unityEngineVersion));
    },
    js_configureBuild: function(build)
    {
        ga.GameAnalytics.configureBuild(Pointer_stringify(build));
    },
    js_configureUserId: function(userId)
    {
        ga.GameAnalytics.configureUserId(Pointer_stringify(userId));
    },
    js_initialize: function(gamekey, gamesecret)
    {
        ga.GameAnalytics.initialize(Pointer_stringify(gamekey), Pointer_stringify(gamesecret));
    },
    js_setCustomDimension01: function(customDimension)
    {
        ga.GameAnalytics.setCustomDimension01(Pointer_stringify(customDimension));
    },
    js_setCustomDimension02: function(customDimension)
    {
        ga.GameAnalytics.setCustomDimension02(Pointer_stringify(customDimension));
    },
    js_setCustomDimension03: function(customDimension)
    {
        ga.GameAnalytics.setCustomDimension03(Pointer_stringify(customDimension));
    },
    js_addBusinessEvent: function(currency, amount, itemType, itemId, cartType)
    {
        ga.GameAnalytics.addBusinessEvent(Pointer_stringify(currency), amount, Pointer_stringify(itemType), Pointer_stringify(itemId), Pointer_stringify(cartType));
    },
    js_addResourceEvent: function(flowType, currency, amount, itemType, itemId)
    {
        ga.GameAnalytics.addResourceEvent(flowType, Pointer_stringify(currency), amount, Pointer_stringify(itemType), Pointer_stringify(itemId));
    },
    js_addProgressionEvent: function(progressionStatus, progression01, progression02, progression03)
    {
        ga.GameAnalytics.addProgressionEvent(progressionStatus, Pointer_stringify(progression01), Pointer_stringify(progression02), Pointer_stringify(progression03));
    },
    js_addProgressionEventWithScore: function(progressionStatus, progression01, progression02, progression03, score)
    {
        ga.GameAnalytics.addProgressionEvent(progressionStatus, Pointer_stringify(progression01), Pointer_stringify(progression02), Pointer_stringify(progression03), score);
    },
    js_addDesignEvent: function(eventId)
    {
        ga.GameAnalytics.addDesignEvent(Pointer_stringify(eventId));
    },
    js_addDesignEventWithValue: function(eventId, value)
    {
        ga.GameAnalytics.addDesignEvent(Pointer_stringify(eventId), value);
    },
    js_addErrorEvent: function(severity, message)
    {
        ga.GameAnalytics.addErrorEvent(severity, Pointer_stringify(message));
    },
    js_setEnabledInfoLog: function(enabled)
    {
        ga.GameAnalytics.setEnabledInfoLog(enabled);
    },
    js_setEnabledVerboseLog: function(enabled)
    {
        ga.GameAnalytics.setEnabledVerboseLog(enabled);
    },
    js_setManualSessionHandling: function(enabled)
    {
        ga.GameAnalytics.setEnabledManualSessionHandling(enabled);
    },
    js_startSession: function()
    {
        ga.GameAnalytics.startSession();
    },
    js_endSession: function()
    {
        ga.GameAnalytics.endSession();
    },
    js_onStop: function()
    {
        ga.GameAnalytics.onStop();
    },
    js_setFacebookId: function(facebookId)
    {
        ga.GameAnalytics.setFacebookId(Pointer_stringify(facebookId));
    },
    js_setGender: function(gender)
    {
        ga.GameAnalytics.setGender(gender);
    },
    js_setBirthYear: function(birthYear)
    {
        ga.GameAnalytics.setBirthYear(birthYear);
    }
};

mergeInto(LibraryManager.library, GameAnalyticsUnreal);
