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
    js_addBusinessEvent: function(currency, amount, itemType, itemId, cartType, fields)
    {
        gameanalytics.GameAnalytics.addBusinessEvent(Pointer_stringify(currency), amount, Pointer_stringify(itemType), Pointer_stringify(itemId), Pointer_stringify(cartType)/*, JSON.parse(Pointer_stringify(fields))*/);
    },
    js_addResourceEvent: function(flowType, currency, amount, itemType, itemId, fields)
    {
        gameanalytics.GameAnalytics.addResourceEvent(flowType, Pointer_stringify(currency), amount, Pointer_stringify(itemType), Pointer_stringify(itemId)/*, JSON.parse(Pointer_stringify(fields))*/);
    },
    js_addProgressionEvent: function(progressionStatus, progression01, progression02, progression03, fields)
    {
        gameanalytics.GameAnalytics.addProgressionEvent(progressionStatus, Pointer_stringify(progression01), Pointer_stringify(progression02), Pointer_stringify(progression03)/*, JSON.parse(Pointer_stringify(fields))*/);
    },
    js_addProgressionEventWithScore: function(progressionStatus, progression01, progression02, progression03, score, fields)
    {
        gameanalytics.GameAnalytics.addProgressionEvent(progressionStatus, Pointer_stringify(progression01), Pointer_stringify(progression02), Pointer_stringify(progression03), score/*, JSON.parse(Pointer_stringify(fields))*/);
    },
    js_addDesignEvent: function(eventId, fields)
    {
        gameanalytics.GameAnalytics.addDesignEvent(Pointer_stringify(eventId)/*, JSON.parse(Pointer_stringify(fields))*/);
    },
    js_addDesignEventWithValue: function(eventId, value, fields)
    {
        gameanalytics.GameAnalytics.addDesignEvent(Pointer_stringify(eventId), value/*, JSON.parse(Pointer_stringify(fields))*/);
    },
    js_addErrorEvent: function(severity, message, fields)
    {
        gameanalytics.GameAnalytics.addErrorEvent(severity, Pointer_stringify(message)/*, JSON.parse(Pointer_stringify(fields))*/);
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
    js_getRemoteConfigsValueAsString: function(key)
    {
        var returnStr = gameanalytics.GameAnalytics.getRemoteConfigsValueAsString(Pointer_stringify(key));
        var bufferSize = lengthBytesUTF8(returnStr) + 1;
        var buffer = _malloc(bufferSize);
        stringToUTF8(returnStr, buffer, bufferSize);
        return buffer;
    },
    js_getRemoteConfigsValueAsStringWithDefaultValue: function(key, defaultValue)
    {
        var returnStr = gameanalytics.GameAnalytics.getRemoteConfigsValueAsString(Pointer_stringify(key), Pointer_stringify(defaultValue));
        var bufferSize = lengthBytesUTF8(returnStr) + 1;
        var buffer = _malloc(bufferSize);
        stringToUTF8(returnStr, buffer, bufferSize);
        return buffer;
    },
    js_isRemoteConfigsReady: function()
    {
        return gameanalytics.GameAnalytics.isRemoteConfigsReady();
    },
    js_getRemoteConfigsContentAsString: function()
    {
        var returnStr = gameanalytics.GameAnalytics.getRemoteConfigsContentAsString();
        var bufferSize = lengthBytesUTF8(returnStr) + 1;
        var buffer = _malloc(bufferSize);
        stringToUTF8(returnStr, buffer, bufferSize);
        return buffer;
    },
    js_getABTestingId: function()
    {
        var returnStr = gameanalytics.GameAnalytics.getABTestingId();
        var bufferSize = lengthBytesUTF8(returnStr) + 1;
        var buffer = _malloc(bufferSize);
        stringToUTF8(returnStr, buffer, bufferSize);
        return buffer;
    },
    js_getABTestingVariantId: function()
    {
        var returnStr = gameanalytics.GameAnalytics.getABTestingVariantId();
        var bufferSize = lengthBytesUTF8(returnStr) + 1;
        var buffer = _malloc(bufferSize);
        stringToUTF8(returnStr, buffer, bufferSize);
        return buffer;
    }
};

mergeInto(LibraryManager.library, GameAnalyticsUnreal);
