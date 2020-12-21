#import "../../GA-SDK-IOS/GameAnalytics.h"
#import "../../GA-SDK-IOS/GameAnalyticsCpp.h"

void GameAnalyticsCpp::configureAvailableCustomDimensions01(const std::vector<std::string>& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (std::string s : list)
    {
        [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableCustomDimensions01:list_array];
}

void GameAnalyticsCpp::configureAvailableCustomDimensions02(const std::vector<std::string>& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (std::string s : list)
    {
        [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableCustomDimensions02:list_array];
}

void GameAnalyticsCpp::configureAvailableCustomDimensions03(const std::vector<std::string>& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (std::string s : list)
    {
        [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableCustomDimensions03:list_array];
}

void GameAnalyticsCpp::configureAvailableResourceCurrencies(const std::vector<std::string>& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (std::string s : list)
    {
        [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableResourceCurrencies:list_array];
}

void GameAnalyticsCpp::configureAvailableResourceItemTypes(const std::vector<std::string>& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (std::string s : list)
    {
        [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableResourceItemTypes:list_array];
}

void GameAnalyticsCpp::configureBuild(const char *build) {
    NSString *buildString = build != NULL ? [NSString stringWithUTF8String:build] : nil;
    [GameAnalytics configureBuild:buildString];
}

void GameAnalyticsCpp::configureAutoDetectAppVersion(bool flag) {
    [GameAnalytics configureAutoDetectAppVersion:flag];
}

void GameAnalyticsCpp::configureUserId(const char *userId) {
    NSString *userIdString = userId != NULL ? [NSString stringWithUTF8String:userId] : nil;
    [GameAnalytics configureUserId:userIdString];
}

void GameAnalyticsCpp::configureSdkGameEngineVersion(const char *gameEngineSdkVersion) {
    NSString *gameEngineSdkVersionString = gameEngineSdkVersion != NULL ? [NSString stringWithUTF8String:gameEngineSdkVersion] : nil;
    [GameAnalytics configureSdkVersion:gameEngineSdkVersionString];
}

void GameAnalyticsCpp::configureGameEngineVersion(const char *gameEngineVersion) {
    NSString *gameEngineVersionString = gameEngineVersion != NULL ? [NSString stringWithUTF8String:gameEngineVersion] : nil;
    [GameAnalytics configureEngineVersion:gameEngineVersionString];
}

void GameAnalyticsCpp::initialize(const char *gameKey, const char *gameSecret) {
    NSString *gameKeyString = gameKey != NULL ? [NSString stringWithUTF8String:gameKey] : nil;
    NSString *gameSecretString = gameSecret != NULL ? [NSString stringWithUTF8String:gameSecret] : nil;

    [GameAnalytics initializeWithGameKey:gameKeyString gameSecret:gameSecretString];
}

void GameAnalyticsCpp::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *fields) {
    NSString *currencyString = currency != NULL ? [NSString stringWithUTF8String:currency] : nil;
    NSInteger amountInteger = (NSInteger)amount;
    NSString *itemTypeString = itemType != NULL ? [NSString stringWithUTF8String:itemType] : nil;
    NSString *itemIdString = itemId != NULL ? [NSString stringWithUTF8String:itemId] : nil;
    NSString *cartTypeString = cartType != NULL ? [NSString stringWithUTF8String:cartType] : nil;
    NSString *receiptString = receipt != NULL ? [NSString stringWithUTF8String:receipt] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addBusinessEventWithCurrency:currencyString
                                         amount:amountInteger
                                       itemType:itemTypeString
                                         itemId:itemIdString
                                       cartType:cartTypeString
                                        receipt:receiptString
                                         /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *fields) {
    NSString *currencyString = currency != NULL ? [NSString stringWithUTF8String:currency] : nil;
    NSInteger amountInteger = (NSInteger)amount;
    NSString *itemTypeString = itemType != NULL ? [NSString stringWithUTF8String:itemType] : nil;
    NSString *itemIdString = itemId != NULL ? [NSString stringWithUTF8String:itemId] : nil;
    NSString *cartTypeString = cartType != NULL ? [NSString stringWithUTF8String:cartType] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addBusinessEventWithCurrency:currencyString
                                         amount:amountInteger
                                       itemType:itemTypeString
                                         itemId:itemIdString
                                       cartType:cartTypeString
                               autoFetchReceipt:true
                                         /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addResourceEvent(int flowType, const char *currency, float amount, const char *itemType, const char *itemId, const char *fields) {
    NSString *currencyString = currency != NULL ? [NSString stringWithUTF8String:currency] : nil;
    NSNumber *amountNumber = [NSNumber numberWithFloat:amount];
    NSString *itemTypeString = itemType != NULL ? [NSString stringWithUTF8String:itemType] : nil;
    NSString *itemIdString = itemId != NULL ? [NSString stringWithUTF8String:itemId] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addResourceEventWithFlowType:(GAResourceFlowType)flowType
                                       currency:currencyString
                                         amount:amountNumber
                                       itemType:itemTypeString
                                         itemId:itemIdString
                                         /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addProgressionEvent(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, const char *fields) {
    NSString *progression01String = progression01 != NULL ? [NSString stringWithUTF8String:progression01] : nil;
    NSString *progression02String = progression02 != NULL ? [NSString stringWithUTF8String:progression02] : nil;
    NSString *progression03String = progression03 != NULL ? [NSString stringWithUTF8String:progression03] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addProgressionEventWithProgressionStatus:(GAProgressionStatus)progressionStatus
                                              progression01:progression01String
                                              progression02:progression02String
                                              progression03:progression03String
                                                     /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addProgressionEventWithScore(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const char *fields) {
    NSString *progression01String = progression01 != NULL ? [NSString stringWithUTF8String:progression01] : nil;
    NSString *progression02String = progression02 != NULL ? [NSString stringWithUTF8String:progression02] : nil;
    NSString *progression03String = progression03 != NULL ? [NSString stringWithUTF8String:progression03] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addProgressionEventWithProgressionStatus:(GAProgressionStatus)progressionStatus
                                              progression01:progression01String
                                              progression02:progression02String
                                              progression03:progression03String
                                                      score:score
                                                     /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addDesignEvent(const char *eventId, const char *fields) {
    NSString *eventIdString = eventId != NULL ? [NSString stringWithUTF8String:eventId] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addDesignEventWithEventId:eventIdString value:nil /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addDesignEventWithValue(const char *eventId, float value, const char *fields) {
    NSString *eventIdString = eventId != NULL ? [NSString stringWithUTF8String:eventId] : nil;
    NSNumber *valueNumber = [NSNumber numberWithFloat:value];
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addDesignEventWithEventId:eventIdString value:valueNumber /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addErrorEvent(int severity, const char *message, const char *fields) {
    NSString *messageString = message != NULL ? [NSString stringWithUTF8String:message] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addErrorEventWithSeverity:(GAErrorSeverity)severity message:messageString /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addAdEvent(int action, int adType, const char *adSdkName, const char *adPlacement, const char *fields) {
    NSString *adSdkNameString = adSdkName != NULL ? [NSString stringWithUTF8String:adSdkName] : nil;
    NSString *adPlacementString = adPlacement != NULL ? [NSString stringWithUTF8String:adPlacement] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }
    [GameAnalytics addAdEventWithAction:(GAAdAction)action
                                 adType:(GAAdType)adType
                              adSdkName:adSdkNameString
                            adPlacement:adPlacementString
                               /*fields:fields_dict*/];
}
void GameAnalyticsCpp::addAdEventWithDuration(int action, int adType, const char *adSdkName, const char *adPlacement, int64_t duration, const char *fields) {
    NSString *adSdkNameString = adSdkName != NULL ? [NSString stringWithUTF8String:adSdkName] : nil;
    NSString *adPlacementString = adPlacement != NULL ? [NSString stringWithUTF8String:adPlacement] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }
    [GameAnalytics addAdEventWithAction:(GAAdAction)action
                                 adType:(GAAdType)adType
                              adSdkName:adSdkNameString
                            adPlacement:adPlacementString
                               duration:(NSInteger)duration
                               /*fields:fields_dict*/];
}

void GameAnalyticsCpp::addAdEventWithNoAdReason(int action, int adType, const char *adSdkName, const char *adPlacement, int noAdReason, const char *fields) {
    NSString *adSdkNameString = adSdkName != NULL ? [NSString stringWithUTF8String:adSdkName] : nil;
    NSString *adPlacementString = adPlacement != NULL ? [NSString stringWithUTF8String:adPlacement] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }
    [GameAnalytics addAdEventWithAction:(GAAdAction)action
                                 adType:(GAAdType)adType
                              adSdkName:adSdkNameString
                            adPlacement:adPlacementString
                               noAdReason:(GAAdError)noAdReason
                               /*fields:fields_dict*/];
}

void GameAnalyticsCpp::setEnabledInfoLog(bool flag) {
    [GameAnalytics setEnabledInfoLog:flag];
}

void GameAnalyticsCpp::setEnabledVerboseLog(bool flag) {
    [GameAnalytics setEnabledVerboseLog:flag];
}

void GameAnalyticsCpp::setEnabledManualSessionHandling(bool flag) {
    [GameAnalytics setEnabledManualSessionHandling:flag];
}

void GameAnalyticsCpp::setEnabledEventSubmission(bool flag) {
    [GameAnalytics setEnabledEventSubmission:flag];
}

void GameAnalyticsCpp::setCustomDimension01(const char *customDimension) {
    NSString *customDimensionString = customDimension != NULL ? [NSString stringWithUTF8String:customDimension] : nil;
    [GameAnalytics setCustomDimension01:customDimensionString];
}

void GameAnalyticsCpp::setCustomDimension02(const char *customDimension) {
    NSString *customDimensionString = customDimension != NULL ? [NSString stringWithUTF8String:customDimension] : nil;
    [GameAnalytics setCustomDimension02:customDimensionString];
}

void GameAnalyticsCpp::setCustomDimension03(const char *customDimension) {
    NSString *customDimensionString = customDimension != NULL ? [NSString stringWithUTF8String:customDimension] : nil;
    [GameAnalytics setCustomDimension03:customDimensionString];
}

void GameAnalyticsCpp::startSession() {
    [GameAnalytics startSession];
}

void GameAnalyticsCpp::endSession() {
    [GameAnalytics endSession];
}

void GameAnalyticsCpp::getRemoteConfigsValueAsString(const char *key, char** out) {
    NSString *keyString = key != NULL ? [NSString stringWithUTF8String:key] : nil;
    NSString *result = [GameAnalytics getRemoteConfigsValueAsString:keyString];

    std::string s = result != nil ? [result UTF8String] : "";
    char* tmp = new char[s.size() + 1];
    snprintf(tmp, s.size() + 1, "%s", s.c_str());
    *out = tmp;
}

void GameAnalyticsCpp::getRemoteConfigsValueAsString(const char *key, const char *defaultValue, char** out) {
    NSString *keyString = key != NULL ? [NSString stringWithUTF8String:key] : nil;
    NSString *defaultValueString = key != NULL ? [NSString stringWithUTF8String:defaultValue] : nil;
    NSString *result = [GameAnalytics getRemoteConfigsValueAsString:keyString defaultValue:defaultValueString];

    std::string s = result != nil ? [result UTF8String] : "";
    char* tmp = new char[s.size() + 1];
    snprintf(tmp, s.size() + 1, "%s", s.c_str());
    *out = tmp;
}

bool GameAnalyticsCpp::isRemoteConfigsReady() {
    return [GameAnalytics isRemoteConfigsReady] ? true : false;
}

void GameAnalyticsCpp::getRemoteConfigsContentAsString(char** out) {
    NSString *result = [GameAnalytics getRemoteConfigsContentAsString];

    std::string s = result != nil ? [result UTF8String] : "";
    char* tmp = new char[s.size() + 1];
    snprintf(tmp, s.size() + 1, "%s", s.c_str());
    *out = tmp;
}

void GameAnalyticsCpp::getABTestingId(char** out) {
    NSString *result = [GameAnalytics getABTestingId];

    std::string s = result != nil ? [result UTF8String] : "";
    char* tmp = new char[s.size() + 1];
    snprintf(tmp, s.size() + 1, "%s", s.c_str());
    *out = tmp;
}

void GameAnalyticsCpp::getABTestingVariantId(char** out) {
    NSString *result = [GameAnalytics getABTestingVariantId];

    std::string s = result != nil ? [result UTF8String] : "";
    char* tmp = new char[s.size() + 1];
    snprintf(tmp, s.size() + 1, "%s", s.c_str());
    *out = tmp;
}
