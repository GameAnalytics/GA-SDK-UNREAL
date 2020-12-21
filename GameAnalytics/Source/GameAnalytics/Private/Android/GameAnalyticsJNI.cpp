#include "../GA-SDK-ANDROID/GameAnalyticsJNI.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"

#define GAMEANALYTICS_CLASS_NAME "com/gameanalytics/sdk/GameAnalytics"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "GameAnalytics"

namespace gameanalytics {
    extern "C"
    {
        void jni_configureAvailableCustomDimensions01(const std::vector<std::string>& list)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureAvailableCustomDimensions01";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureAvailableCustomDimensions02(const std::vector<std::string>& list)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureAvailableCustomDimensions02";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureAvailableCustomDimensions03(const std::vector<std::string>& list)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureAvailableCustomDimensions03";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureAvailableResourceCurrencies(const std::vector<std::string>& list)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureAvailableResourceCurrencies";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureAvailableResourceItemTypes(const std::vector<std::string>& list)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureAvailableResourceItemTypes";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureBuild(const char *build)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureBuild";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(build);
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureAutoDetectAppVersion(bool flag)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureAutoDetectAppVersion";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureUserId(const char *userId)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureUserId";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(userId);
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureSdkGameEngineVersion(const char *gameEngineSdkVersion)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureSdkGameEngineVersion";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(gameEngineSdkVersion);
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_configureGameEngineVersion(const char *gameEngineSdkVersion)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "configureGameEngineVersion";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(gameEngineSdkVersion);
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_initialize(const char *gameKey, const char *gameSecret)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "initializeWithGameKey";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;)V");

                if(jMethod)
                {
                    jobject activity = FAndroidApplication::GetGameActivityThis();
                    jstring j_gameKey = env->NewStringUTF(gameKey);
                    jstring j_gameSecret = env->NewStringUTF(gameSecret);
                    env->CallStaticVoidMethod(jClass, jMethod, activity, j_gameKey, j_gameSecret);
                    env->DeleteLocalRef(j_gameKey);
                    env->DeleteLocalRef(j_gameSecret);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addBusinessEventWithCurrency";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_currency = env->NewStringUTF(currency);
                    jstring j_itemType = env->NewStringUTF(itemType);
                    jstring j_itemId = env->NewStringUTF(itemId);
                    jstring j_cartType = env->NewStringUTF(cartType);
                    jstring j_fields = env->NewStringUTF(fields);
                    env->CallStaticVoidMethod(jClass, jMethod, j_currency, amount, j_itemType, j_itemId, j_cartType/*, j_fields*/);
                    env->DeleteLocalRef(j_currency);
                    env->DeleteLocalRef(j_itemType);
                    env->DeleteLocalRef(j_itemId);
                    env->DeleteLocalRef(j_cartType);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addBusinessEventWithReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType,
            const char *receipt, const char *store, const char *signature, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addBusinessEventWithCurrency";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_currency = env->NewStringUTF(currency);
                    jstring j_itemType = env->NewStringUTF(itemType);
                    jstring j_itemId = env->NewStringUTF(itemId);
                    jstring j_cartType = env->NewStringUTF(cartType);
                    jstring j_receipt = env->NewStringUTF(receipt);
                    jstring j_store = env->NewStringUTF(store);
                    jstring j_signature = env->NewStringUTF(signature);
                    jstring j_fields = env->NewStringUTF(fields);
                    env->CallStaticVoidMethod(jClass, jMethod, j_currency, amount, j_itemType, j_itemId, j_cartType, j_receipt, j_store, j_signature/*, j_fields*/);
                    env->DeleteLocalRef(j_currency);
                    env->DeleteLocalRef(j_itemType);
                    env->DeleteLocalRef(j_itemId);
                    env->DeleteLocalRef(j_cartType);
                    env->DeleteLocalRef(j_receipt);
                    env->DeleteLocalRef(j_store);
                    env->DeleteLocalRef(j_signature);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addResourceEvent(int flowType, const char *currency, float amount, const char *itemType, const char *itemId, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addResourceEventWithFlowType";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(ILjava/lang/String;FLjava/lang/String;Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_currency = env->NewStringUTF(currency);
                    jstring j_itemType = env->NewStringUTF(itemType);
                    jstring j_itemId = env->NewStringUTF(itemId);
                    jstring j_fields = env->NewStringUTF(fields);
                    env->CallStaticVoidMethod(jClass, jMethod, flowType, j_currency, amount, j_itemType, j_itemId/*, j_fields*/);
                    env->DeleteLocalRef(j_currency);
                    env->DeleteLocalRef(j_itemType);
                    env->DeleteLocalRef(j_itemId);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addProgressionEvent(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addProgressionEventWithProgressionStatus";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_progression01 = env->NewStringUTF(progression01);
                    jstring j_progression02 = env->NewStringUTF(progression02);
                    jstring j_progression03 = env->NewStringUTF(progression03);
                    jstring j_fields = env->NewStringUTF(fields);
                    env->CallStaticVoidMethod(jClass, jMethod, progressionStatus, j_progression01, j_progression02, j_progression03/*, j_fields*/);
                    env->DeleteLocalRef(j_progression01);
                    env->DeleteLocalRef(j_progression02);
                    env->DeleteLocalRef(j_progression03);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addProgressionEventWithScore(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addProgressionEventWithProgressionStatus";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;D)V");

                if(jMethod)
                {
                    jstring j_progression01 = env->NewStringUTF(progression01);
                    jstring j_progression02 = env->NewStringUTF(progression02);
                    jstring j_progression03 = env->NewStringUTF(progression03);
                    jstring j_fields = env->NewStringUTF(fields);
                    env->CallStaticVoidMethod(jClass, jMethod, progressionStatus, j_progression01, j_progression02, j_progression03, (double)score/*, j_fields*/);
                    env->DeleteLocalRef(j_progression01);
                    env->DeleteLocalRef(j_progression02);
                    env->DeleteLocalRef(j_progression03);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addDesignEvent(const char *eventId, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addDesignEventWithEventId";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_eventId = env->NewStringUTF(eventId);
                    jstring j_fields = env->NewStringUTF(fields);
                    env->CallStaticVoidMethod(jClass, jMethod, j_eventId/*, j_fields*/);
                    env->DeleteLocalRef(j_eventId);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addDesignEventWithValue(const char *eventId, float value, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addDesignEventWithEventId";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;D)V");

                if(jMethod)
                {
                    jstring j_eventId = env->NewStringUTF(eventId);
                    jstring j_fields = env->NewStringUTF(fields);
                    env->CallStaticVoidMethod(jClass, jMethod, j_eventId, value/*, j_fields*/);
                    env->DeleteLocalRef(j_eventId);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addErrorEvent(int severity, const char *message, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addErrorEventWithSeverity";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(ILjava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_message = env->NewStringUTF(message);
                    jstring j_fields = env->NewStringUTF(fields);
                    env->CallStaticVoidMethod(jClass, jMethod, severity, j_message/*, j_fields*/);
                    env->DeleteLocalRef(j_message);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addAdEvent(int action, int adType, const char *adSdkName, const char *adPlacement, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addAdEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(IILjava/lang/String;Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_adSdkName = env->NewStringUTF(adSdkName);
                    jstring j_adPlacement = env->NewStringUTF(adPlacement);
                    env->CallStaticVoidMethod(jClass, jMethod, action, adType, j_adSdkName, j_adPlacement/*, j_fields*/);
                    env->DeleteLocalRef(j_adSdkName);
                    env->DeleteLocalRef(j_adPlacement);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addAdEventWithDuration(int action, int adType, const char *adSdkName, const char *adPlacement, int64_t duration, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addAdEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(IILjava/lang/String;Ljava/lang/String;J)V");

                if(jMethod)
                {
                    jstring j_adSdkName = env->NewStringUTF(adSdkName);
                    jstring j_adPlacement = env->NewStringUTF(adPlacement);
                    env->CallStaticVoidMethod(jClass, jMethod, action, adType, j_adSdkName, j_adPlacement, duration/*, j_fields*/);
                    env->DeleteLocalRef(j_adSdkName);
                    env->DeleteLocalRef(j_adPlacement);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_addAdEventWithNoAdReason(int action, int adType, const char *adSdkName, const char *adPlacement, int noAdReason, const char *fields)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "addAdEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(IILjava/lang/String;Ljava/lang/String;I)V");

                if(jMethod)
                {
                    jstring j_adSdkName = env->NewStringUTF(adSdkName);
                    jstring j_adPlacement = env->NewStringUTF(adPlacement);
                    env->CallStaticVoidMethod(jClass, jMethod, action, adType, j_adSdkName, j_adPlacement, noAdReason/*, j_fields*/);
                    env->DeleteLocalRef(j_adSdkName);
                    env->DeleteLocalRef(j_adPlacement);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_setEnabledInfoLog(bool flag)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "setEnabledInfoLog";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_setEnabledVerboseLog(bool flag)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "setEnabledVerboseLog";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_setEnabledManualSessionHandling(bool flag)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "setEnabledManualSessionHandling";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_setEnabledEventSubmission(bool flag)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "setEnabledEventSubmission";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_setCustomDimension01(const char *customDimension)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "setCustomDimension01";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_customDimension = env->NewStringUTF(customDimension);
                    env->CallStaticVoidMethod(jClass, jMethod, j_customDimension);
                    env->DeleteLocalRef(j_customDimension);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_setCustomDimension02(const char *customDimension)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "setCustomDimension02";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_customDimension = env->NewStringUTF(customDimension);
                    env->CallStaticVoidMethod(jClass, jMethod, j_customDimension);
                    env->DeleteLocalRef(j_customDimension);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_setCustomDimension03(const char *customDimension)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "setCustomDimension03";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_customDimension = env->NewStringUTF(customDimension);
                    env->CallStaticVoidMethod(jClass, jMethod, j_customDimension);
                    env->DeleteLocalRef(j_customDimension);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_startSession()
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "startSession";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "()V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_endSession()
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "endSession";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "()V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void jni_getRemoteConfigsValueAsString(const char *key, char** out)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "getRemoteConfigsValueAsString";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_key = env->NewStringUTF(key);
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod, j_key);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                    env->DeleteLocalRef(j_key);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }

        void jni_getRemoteConfigsValueAsStringWithDefaultValue(const char *key, const char *defaultValue, char** out)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "getRemoteConfigsValueAsString";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_key = env->NewStringUTF(key);
                    jstring j_defaultValue = env->NewStringUTF(defaultValue);
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod, j_key, j_defaultValue);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                    env->DeleteLocalRef(j_key);
                    env->DeleteLocalRef(j_defaultValue);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }

        bool jni_isRemoteConfigsReady()
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "isRemoteConfigsReady";
            bool result = false;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "()Z");

                if(jMethod)
                {
                    result = env->CallStaticBooleanMethod(jClass, jMethod);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            return result;
        }

        void jni_getRemoteConfigsContentAsString(char** out)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "getRemoteConfigsContentAsString";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "()Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }

        void jni_getABTestingId(char** out)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "getABTestingId";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "()Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }

        void jni_getABTestingVariantId(char** out)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(GAMEANALYTICS_CLASS_NAME);
            const char* strMethod = "getABTestingVariantId";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "()Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }
    }
}
