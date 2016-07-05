#include "GameAnalyticsPrivatePCH.h"
#include "GameAnalytics.h"
#if PLATFORM_IOS
#include "../GA-SDK-IOS/GameAnalyticsCpp.h"
#elif PLATFORM_ANDROID
#include "../GA-SDK-ANDROID/GameAnalyticsJNI.h"
#elif PLATFORM_MAC || PLATFORM_WINDOWS
#include "../GA-SDK-CPP/GameAnalytics.h"
#endif

namespace gameanalytics 
{
    namespace unreal
    {
    	void GameAnalytics::configureAvailableCustomDimensions01(const std::vector<std::string>& list)
    	{
#if PLATFORM_IOS
    		GameAnalyticsCpp::configureAvailableCustomDimensions01(list);
#elif PLATFORM_ANDROID
    		jni_configureAvailableCustomDimensions01(list);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureAvailableCustomDimensions01(list);
#endif
    	}

        void GameAnalytics::configureAvailableCustomDimensions02(const std::vector<std::string>& list)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::configureAvailableCustomDimensions02(list);
#elif PLATFORM_ANDROID
        	jni_configureAvailableCustomDimensions02(list);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureAvailableCustomDimensions02(list);
#endif
        }

        void GameAnalytics::configureAvailableCustomDimensions03(const std::vector<std::string>& list)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::configureAvailableCustomDimensions03(list);
#elif PLATFORM_ANDROID
        	jni_configureAvailableCustomDimensions03(list);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureAvailableCustomDimensions03(list);
#endif
        }
        
        void GameAnalytics::configureAvailableResourceCurrencies(const std::vector<std::string>& list)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::configureAvailableResourceCurrencies(list);
#elif PLATFORM_ANDROID
        	jni_configureAvailableResourceCurrencies(list);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureAvailableResourceCurrencies(list);
#endif
        }

        void GameAnalytics::configureAvailableResourceItemTypes(const std::vector<std::string>& list)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::configureAvailableResourceItemTypes(list);
#elif PLATFORM_ANDROID
        	jni_configureAvailableResourceItemTypes(list);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureAvailableResourceItemTypes(list);
#endif
        }
        
        void GameAnalytics::configureBuild(const char *build)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::configureBuild(build);
#elif PLATFORM_ANDROID
        	jni_configureBuild(build);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureBuild(build);
#endif
        }

        void GameAnalytics::configureUserId(const char *userId)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::configureUserId(userId);
#elif PLATFORM_ANDROID
        	jni_configureUserId(userId);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureUserId(userId);
#endif
        }

        void GameAnalytics::configureSdkGameEngineVersion(const char *gameEngineSdkVersion)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::configureSdkGameEngineVersion(gameEngineSdkVersion);
#elif PLATFORM_ANDROID
        	jni_configureSdkGameEngineVersion(gameEngineSdkVersion);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureSdkGameEngineVersion(gameEngineSdkVersion);
#endif
        }

        void GameAnalytics::configureGameEngineVersion(const char *gameEngineVersion)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::configureGameEngineVersion(gameEngineVersion);
#elif PLATFORM_ANDROID
        	jni_configureGameEngineVersion(gameEngineVersion);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::configureGameEngineVersion(gameEngineVersion);
#endif
        }

        void GameAnalytics::initialize(const char *gameKey, const char *gameSecret)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::initialize(gameKey, gameSecret);
#elif PLATFORM_ANDROID
        	jni_initialize(gameKey, gameSecret);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::initialize(gameKey, gameSecret);
#endif
        }
        
#if PLATFORM_IOS
        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt)
        {
        	GameAnalyticsCpp::addBusinessEvent(currency, amount, itemType, itemId, cartType, receipt);
        }

        void GameAnalytics::addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType)
        {
        	GameAnalyticsCpp::addBusinessEventAndAutoFetchReceipt(currency, amount, itemType, itemId, cartType);
        }
#elif PLATFORM_ANDROID
        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *signature)
        {
        	jni_addBusinessEventWithReceipt(currency, amount, itemType, itemId, cartType, receipt, "google_play", signature);
        }
#endif

        void GameAnalytics::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::addBusinessEvent(currency, amount, itemType, itemId, cartType, NULL);
#elif PLATFORM_ANDROID
        	jni_addBusinessEvent(currency, amount, itemType, itemId, cartType);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::addBusinessEvent(currency, amount, itemType, itemId, cartType);
#endif
        }

        void GameAnalytics::addResourceEvent(EGAResourceFlowType flowType, const char *currency, float amount, const char *itemType, const char *itemId)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::addResourceEvent((int)flowType, currency, amount, itemType, itemId);
#elif PLATFORM_ANDROID
        	jni_addResourceEvent((int)flowType, currency, amount, itemType, itemId);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::addResourceEvent((gameanalytics::EGAResourceFlowType)((int)flowType), currency, amount, itemType, itemId);
#endif
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01)
        {
            addProgressionEvent(progressionStatus, progression01, (const char *)NULL, (const char *)NULL);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, int score)
        {
            addProgressionEvent(progressionStatus, progression01, (const char *)NULL, (const char *)NULL, score);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, (const char *)NULL);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, int score)
        {
            addProgressionEvent(progressionStatus, progression01, progression02, (const char *)NULL, score);
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::addProgressionEvent((int)progressionStatus, progression01, progression02, progression03);
#elif PLATFORM_ANDROID
        	jni_addProgressionEvent((int)progressionStatus, progression01, progression02, progression03);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)((int)progressionStatus), progression01, progression02, progression03);
#endif
        }

        void GameAnalytics::addProgressionEvent(EGAProgressionStatus progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score);
#elif PLATFORM_ANDROID
        	jni_addProgressionEventWithScore((int)progressionStatus, progression01, progression02, progression03, score);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)((int)progressionStatus), progression01, progression02, progression03, score);
#endif
        }

        void GameAnalytics::addDesignEvent(const char *eventId)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::addDesignEvent(eventId);
#elif PLATFORM_ANDROID
        	jni_addDesignEvent(eventId);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::addDesignEvent(eventId);
#endif
        }

        void GameAnalytics::addDesignEvent(const char *eventId, float value)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::addDesignEventWithValue(eventId, value);
#elif PLATFORM_ANDROID
        	jni_addDesignEventWithValue(eventId, value);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::addDesignEvent(eventId, value);
#endif
        }

        void GameAnalytics::addErrorEvent(EGAErrorSeverity severity, const char *message)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::addErrorEvent((int)severity, message);
#elif PLATFORM_ANDROID
        	jni_addErrorEvent((int)severity, message);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::addErrorEvent((gameanalytics::EGAErrorSeverity)((int)severity), message);
#endif
        }
        
        void GameAnalytics::setEnabledInfoLog(bool flag)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::setEnabledInfoLog(flag);
#elif PLATFORM_ANDROID
        	jni_setEnabledInfoLog(flag);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::setEnabledInfoLog(flag);
#endif
        }

        void GameAnalytics::setEnabledVerboseLog(bool flag)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::setEnabledVerboseLog(flag);
#elif PLATFORM_ANDROID
        	jni_setEnabledVerboseLog(flag);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::setEnabledVerboseLog(flag);
#endif
        }

        void GameAnalytics::setCustomDimension01(const char *customDimension)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::setCustomDimension01(customDimension);
#elif PLATFORM_ANDROID
        	jni_setCustomDimension01(customDimension);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::setCustomDimension01(customDimension);
#endif
        }

        void GameAnalytics::setCustomDimension02(const char *customDimension)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::setCustomDimension02(customDimension);
#elif PLATFORM_ANDROID
        	jni_setCustomDimension02(customDimension);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::setCustomDimension02(customDimension);
#endif
        }

        void GameAnalytics::setCustomDimension03(const char *customDimension)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::setCustomDimension03(customDimension);
#elif PLATFORM_ANDROID
        	jni_setCustomDimension03(customDimension);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::setCustomDimension03(customDimension);
#endif
        }

        void GameAnalytics::setFacebookId(const char *facebookId)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::setFacebookId(facebookId);
#elif PLATFORM_ANDROID
        	jni_setFacebookId(facebookId);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::setFacebookId(facebookId);
#endif
        }
        
        void GameAnalytics::setGender(EGAGender gender)
        {
        	switch(gender)
        	{
        		case male:
        		{
#if PLATFORM_IOS
        			GameAnalyticsCpp::setGender("male");
#elif PLATFORM_ANDROID
        			jni_setGender((int)gender);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
                    gameanalytics::GameAnalytics::setGender((gameanalytics::EGAGender)((int)gender));
#endif
        		}
        		break;

        		case female:
        		{
#if PLATFORM_IOS
        			GameAnalyticsCpp::setGender("female");
#elif PLATFORM_ANDROID
        			jni_setGender((int)gender);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
                    gameanalytics::GameAnalytics::setGender((gameanalytics::EGAGender)((int)gender));
#endif
        		}
        		break;
        	}
        }

        void GameAnalytics::setBirthYear(int birthYear)
        {
#if PLATFORM_IOS
        	GameAnalyticsCpp::setBirthYear(birthYear);
#elif PLATFORM_ANDROID
        	jni_setBirthYear(birthYear);
#elif PLATFORM_MAC || PLATFORM_WINDOWS
            gameanalytics::GameAnalytics::setBirthYear(birthYear);
#endif
        }
    }
}