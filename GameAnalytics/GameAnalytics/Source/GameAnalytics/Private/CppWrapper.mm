//
//  CppWrapper.m
//  GA-SDK-IOS
//
//  Created by Benjamin Schulz on 04/06/15.
//  Copyright (c) 2015 GameAnalytics. All rights reserved.
//

/*

 The implementation in this file adapts the obj-c implementation to c++
 This enables the iOS-SDK to be used via C++.
 
 It is nothing more than an implementation of the GameAnalytics C++ interface that
 converts all arguments to/from C++ to obj-c.
 
 TODO: I'm not sure, if ARC works here, or if we have to release the converted objects manually.
 
 Implementation note: In the implementations of the wrapper functions, I'm doing a return.
 This is to catch the unlikely case, that the return types of the obj-c interface change. In this
 case we'd get a compile error and could adapt the C++ interface accordingly.
*/


#ifndef ANDROID

#include "./GameAnalytics.h" // the C++ interface
#include "../GA-SDK-IOS/GameAnalytics.h" // the obj-c interface

namespace gameanalytics
{
    /*
        Helper functions to convert C++ data types to obj-c data types.
     */
    static NSString* convert(const std::string& s)
    {
        return [NSString stringWithUTF8String:s.c_str()];
    }
    
    static NSArray* convert(const std::vector<std::string>& v)
    {
        NSMutableArray* array = [NSMutableArray arrayWithCapacity:v.size()];

        
        for(NSUInteger i = 0; i != v.size(); ++i)
        {
            NSString* s = convert(v.at(i));
            [array setObject:s atIndexedSubscript:i];
        }
        
        return array;
    }
    
    NSInteger convert(int i)
    {
        return NSInteger(i);
    }
    
    BOOL convert(bool b)
    {
        return b?YES:NO;
    }
    
    NSNumber* convert(float v)
    {
        return [NSNumber numberWithFloat:v];
    }

    NSNumber* convert(double v)
    {
        return [NSNumber numberWithDouble:v];
    }
    
    ::GAResourceFlowType convert(GAResourceFlowType v)
    {
        // we could just do a c-style cast, but it's cleaner this way.
        switch (v) {
            case GAResourceFlowTypeSource: return ::GAResourceFlowTypeSource;
            case GAResourceFlowTypeSink: return ::GAResourceFlowTypeSink;
        }
        assert(false);
        return ::GAResourceFlowTypeSource;
    }
    
    ::GAProgressionStatus convert(GAProgressionStatus v)
    {
        switch (v) {
            case GAProgressionStatusStart: return ::GAProgressionStatusStart;
            case GAProgressionStatusComplete: return ::GAProgressionStatusComplete;
            case GAProgressionStatusFail: return ::GAProgressionStatusFail;
        }
        assert(false);
        return ::GAProgressionStatusStart;
    }
    
    ::GAErrorSeverity convert(GAErrorSeverity v)
    {
        switch (v) {
            case GAErrorSeverityDebug: return ::GAErrorSeverityDebug;
            case GAErrorSeverityInfo: return ::GAErrorSeverityInfo;
            case GAErrorSeverityWarning: return ::GAErrorSeverityWarning;
            case GAErrorSeverityError: return ::GAErrorSeverityError;
            case GAErrorSeverityCritical: return ::GAErrorSeverityCritical;
        }
        assert(false);
        return ::GAErrorSeverityDebug;
    }

    
    /*********************************************************************************************************/
    /***********************************  Implementation of the wrapper  *************************************/
    /*********************************************************************************************************/

    void GameAnalytics::configureAvailableCustomDimensions01(const std::vector<std::string>& customDimensions)
    {
        return [::GameAnalytics configureAvailableCustomDimensions01:convert(customDimensions)];
    }
    
    
    void GameAnalytics::configureAvailableCustomDimensions02(const std::vector<std::string>& customDimensions)
    {
        return [::GameAnalytics configureAvailableCustomDimensions02:convert(customDimensions)];
    }
    
    
    void GameAnalytics::configureAvailableCustomDimensions03(const std::vector<std::string>& customDimensions)
    {
        return [::GameAnalytics configureAvailableCustomDimensions03:convert(customDimensions)];
    }
    
    
    void GameAnalytics::configureAvailableResourceCurrencies(const std::vector<std::string>& resourceCurrencies)
    {
        return [::GameAnalytics configureAvailableResourceCurrencies:convert(resourceCurrencies)];
    }
    
    
    void GameAnalytics::configureAvailableResourceItemTypes(const std::vector<std::string>& resourceItemTypes)
    {
        return [::GameAnalytics configureAvailableResourceItemTypes:convert(resourceItemTypes)];
    }
    
    
    void GameAnalytics::configureBuild(const std::string& build)
    {
        return [::GameAnalytics configureBuild:convert(build)];
    }
    
    
    void GameAnalytics::configureSdkVersion(const std::string& wrapperSdkVersion)
    {
        return [::GameAnalytics configureSdkVersion:convert(wrapperSdkVersion)];
    }
    
    
    void GameAnalytics::configureEngineVersion(const std::string& engineVersion)
    {
        return [::GameAnalytics configureEngineVersion:convert(engineVersion)];
    }
    
    
    void GameAnalytics::initializeWithGameKey(const std::string& gameKey,
                               const std::string& gameSecret)
    {
        return [::GameAnalytics initializeWithGameKey:convert(gameKey) gameSecret:convert(gameSecret)];
    }
    
    
    void GameAnalytics::addBusinessEventWithCurrency(const std::string& currency,
                                             int amount,
                                             const std::string& itemType,
                                             const std::string& itemId,
                                             const std::string& cartType,
                                      const std::string& receipt)
    {
        return [::GameAnalytics addBusinessEventWithCurrency:convert(currency) amount:convert(amount) itemType:convert(itemType) itemId:convert(itemId) cartType:convert(cartType) receipt:convert(receipt)];
    }
    

    void GameAnalytics::addBusinessEventWithCurrency(const std::string& currency,
                                             int amount,
                                             const std::string& itemType,
                                             const std::string& itemId,
                                             const std::string& cartType,
                                      bool autoFetchReceipt)
    {
        return [::GameAnalytics addBusinessEventWithCurrency:convert(currency) amount:convert(amount) itemType:convert(itemType) itemId:convert(itemId) cartType:convert(cartType) autoFetchReceipt:convert(autoFetchReceipt)];
    }
    
    
    void GameAnalytics::addResourceEventWithFlowType(GAResourceFlowType flowType,
                                             const std::string& currency,
                                             float amount,
                                             const std::string&itemType,
                                      const std::string& itemId)
    {
        return [::GameAnalytics addResourceEventWithFlowType:convert(flowType) currency:convert(currency) amount:convert(amount) itemType:convert(itemType) itemId:convert(itemId)];
    }
    

    void GameAnalytics::addProgressionEventWithProgressionStatus(GAProgressionStatus progressionStatus,
                                                         const std::string& progression01,
                                                         const std::string& progression02,
                                                  const std::string& progression03)
    {
        return [::GameAnalytics addProgressionEventWithProgressionStatus:convert(progressionStatus) progression01:convert(progression01) progression02:convert(progression02) progression03:convert(progression03)];
    }
    

    void GameAnalytics::addProgressionEventWithProgressionStatus(GAProgressionStatus progressionStatus,
                                                         const std::string& progression01,
                                                         const std::string& progression02,
                                                         const std::string& progression03,
                                                  int score)
    {
        return [::GameAnalytics addProgressionEventWithProgressionStatus:convert(progressionStatus) progression01:convert(progression01) progression02:convert(progression02) progression03:convert(progression03) score:convert(score)];
    }
    
    
    void GameAnalytics::addDesignEventWithEventId(const std::string& eventId)
    {
        return [::GameAnalytics addDesignEventWithEventId:convert(eventId)];
    }
    
    
    void GameAnalytics::addDesignEventWithEventId(const std::string& eventId,
                                   double value)
    {
        return [::GameAnalytics addDesignEventWithEventId:convert(eventId) value:convert(value)];
    }


    void GameAnalytics::addErrorEventWithSeverity(GAErrorSeverity severity,
                                   const std::string& message)
    {
        return [::GameAnalytics addErrorEventWithSeverity:convert(severity) message:convert(message)];
    }
    
    
    void GameAnalytics::setEnabledInfoLog(bool flag)
    {
        return [::GameAnalytics setEnabledInfoLog:convert(flag)];
    }
    

    void GameAnalytics::setEnabledVerboseLog(bool flag)
    {
        return [::GameAnalytics setEnabledVerboseLog:convert(flag)];
    }
    

    void GameAnalytics::setCustomDimension01(const std::string& dimension01)
    {
        return [::GameAnalytics setCustomDimension01:convert(dimension01)];
    }
    

    void GameAnalytics::setCustomDimension02(const std::string& dimension02)
    {
        return [::GameAnalytics setCustomDimension02:convert(dimension02)];
    }
    

    void GameAnalytics::setCustomDimension03(const std::string& dimension03)
    {
        return [::GameAnalytics setCustomDimension03:convert(dimension03)];
    }
    

    void GameAnalytics::setFacebookId(const std::string& facebookId)
    {
        return [::GameAnalytics setFacebookId:convert(facebookId)];
    }
    

    void GameAnalytics::setGender(const std::string& gender)
    {
        return [::GameAnalytics setGender:convert(gender)];
    }
    
    
    void GameAnalytics::setBirthYear(int birthYear)
    {
        return [::GameAnalytics setBirthYear:convert(birthYear)];
    }
}

#endif