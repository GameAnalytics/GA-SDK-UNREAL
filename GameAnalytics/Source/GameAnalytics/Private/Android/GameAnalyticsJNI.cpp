/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "GameAnalyticsJNI.h"
#include "JniHelper.h"
#include <android/log.h>
#include <string>

#define GAMEANALYTICS_CLASS_NAME "com/gameanalytics/sdk/GameAnalytics"
static const char* kTAG = "GameAnalytics";
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))

namespace gameanalytics {
    extern "C"
    {
        JNIEXPORT void JNICALL Java_com_gameanalytics_sdk_GameAnalyticsJNI_nativeSetContext(JNIEnv*  env, jobject thiz, jobject context)
        {
            JniHelper::setClassLoaderFrom(context);
        }

        void jni_setJavaVM(JavaVM* vm)
        {
            JniHelper::setJavaVM(vm);
        }

        void jni_setContext(jobject activity)
        {
            JniHelper::setClassLoaderFrom(activity);
        }

        void jni_configureAvailableCustomDimensions01(const std::vector<std::string>& list)
        {
            if(JniHelper::getActivity() == nullptr)
            {
                LOGW("jni_configureAvailableCustomDimensions01: context has not been set yet, ");
                return;
            }
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureAvailableCustomDimensions01", "([Ljava/lang/String;)V"))
            {
                jstring str;
                jobjectArray j_array = 0;
                jsize len = list.size();
                j_array = methodInfo.env->NewObjectArray(len, methodInfo.env->FindClass("java/lang/String"), 0);

                int i = 0;
                for (std::string s : list)
                {
                    str = methodInfo.env->NewStringUTF(s.c_str());
                    methodInfo.env->SetObjectArrayElement(j_array, i, str);
                    ++i;
                }

                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_array);
                for (i = 0; i < list.size(); ++i)
                {
                    jobject localRef = methodInfo.env->GetObjectArrayElement(j_array, i);
                    methodInfo.env->DeleteLocalRef(localRef);
                }
                methodInfo.env->DeleteLocalRef(j_array);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureAvailableCustomDimensions02(const std::vector<std::string>& list)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureAvailableCustomDimensions02", "([Ljava/lang/String;)V"))
            {
                jstring str;
                jobjectArray j_array = 0;
                jsize len = list.size();
                j_array = methodInfo.env->NewObjectArray(len, methodInfo.env->FindClass("java/lang/String"), 0);

                int i = 0;
                for (std::string s : list)
                {
                    str = methodInfo.env->NewStringUTF(s.c_str());
                    methodInfo.env->SetObjectArrayElement(j_array, i, str);
                    ++i;
                }

                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_array);
                for (i = 0; i < list.size(); ++i)
                {
                    jobject localRef = methodInfo.env->GetObjectArrayElement(j_array, i);
                    methodInfo.env->DeleteLocalRef(localRef);
                }
                methodInfo.env->DeleteLocalRef(j_array);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureAvailableCustomDimensions03(const std::vector<std::string>& list)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureAvailableCustomDimensions03", "([Ljava/lang/String;)V"))
            {
                jstring str;
                jobjectArray j_array = 0;
                jsize len = list.size();
                j_array = methodInfo.env->NewObjectArray(len, methodInfo.env->FindClass("java/lang/String"), 0);

                int i = 0;
                for (std::string s : list)
                {
                    str = methodInfo.env->NewStringUTF(s.c_str());
                    methodInfo.env->SetObjectArrayElement(j_array, i, str);
                    ++i;
                }

                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_array);
                for (i = 0; i < list.size(); ++i)
                {
                    jobject localRef = methodInfo.env->GetObjectArrayElement(j_array, i);
                    methodInfo.env->DeleteLocalRef(localRef);
                }
                methodInfo.env->DeleteLocalRef(j_array);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureAvailableResourceCurrencies(const std::vector<std::string>& list)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureAvailableResourceCurrencies", "([Ljava/lang/String;)V"))
            {
                jstring str;
                jobjectArray j_array = 0;
                jsize len = list.size();
                j_array = methodInfo.env->NewObjectArray(len, methodInfo.env->FindClass("java/lang/String"), 0);

                int i = 0;
                for (std::string s : list)
                {
                    str = methodInfo.env->NewStringUTF(s.c_str());
                    methodInfo.env->SetObjectArrayElement(j_array, i, str);
                    ++i;
                }

                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_array);
                for (i = 0; i < list.size(); ++i)
                {
                    jobject localRef = methodInfo.env->GetObjectArrayElement(j_array, i);
                    methodInfo.env->DeleteLocalRef(localRef);
                }
                methodInfo.env->DeleteLocalRef(j_array);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setEnabledEventSubmission(bool flag)
        {
            JniMethodInfo methodInfo;

            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setEnabledEventSubmission",
                "(Z)"))
            {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, static_cast<jboolean>(flag));
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureAvailableResourceItemTypes(const std::vector<std::string>& list)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureAvailableResourceItemTypes", "([Ljava/lang/String;)V"))
            {
                jstring str;
                jobjectArray j_array = 0;
                jsize len = list.size();
                j_array = methodInfo.env->NewObjectArray(len, methodInfo.env->FindClass("java/lang/String"), 0);

                int i = 0;
                for (std::string s : list)
                {
                    str = methodInfo.env->NewStringUTF(s.c_str());
                    methodInfo.env->SetObjectArrayElement(j_array, i, str);
                    ++i;
                }

                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_array);
                for (i = 0; i < list.size(); ++i)
                {
                    jobject localRef = methodInfo.env->GetObjectArrayElement(j_array, i);
                    methodInfo.env->DeleteLocalRef(localRef);
                }
                methodInfo.env->DeleteLocalRef(j_array);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureBuild(const char *build)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureBuild", "(Ljava/lang/String;)V"))
            {
                jstring j_string = methodInfo.env->NewStringUTF(build);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_string);
                methodInfo.env->DeleteLocalRef(j_string);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureAutoDetectAppVersion(bool flag)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureAutoDetectAppVersion",
                                               "(Z)V"))
            {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, flag);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureUserId(const char *userId)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureUserId", "(Ljava/lang/String;)V"))
            {
                jstring j_string = methodInfo.env->NewStringUTF(userId);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_string);
                methodInfo.env->DeleteLocalRef(j_string);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureSdkGameEngineVersion(const char *gameEngineSdkVersion)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureSdkGameEngineVersion", "(Ljava/lang/String;)V"))
            {
                jstring j_string = methodInfo.env->NewStringUTF(gameEngineSdkVersion);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_string);
                methodInfo.env->DeleteLocalRef(j_string);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_configureGameEngineVersion(const char *gameEngineVersion)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "configureGameEngineVersion", "(Ljava/lang/String;)V"))
            {
                jstring j_string = methodInfo.env->NewStringUTF(gameEngineVersion);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_string);
                methodInfo.env->DeleteLocalRef(j_string);
            }
        }

        void jni_initialize(const char *gameKey, const char *gameSecret)
        {
            JniMethodInfo methodInfo1;
            if (JniHelper::getStaticMethodInfo(methodInfo1, GAMEANALYTICS_CLASS_NAME, "initialize", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;)V"))
            {
                jstring j_gameKey = methodInfo1.env->NewStringUTF(gameKey);
                jstring j_gameSecret = methodInfo1.env->NewStringUTF(gameSecret);
                methodInfo1.env->CallStaticVoidMethod(methodInfo1.classID, methodInfo1.methodID, JniHelper::getActivity(), j_gameKey, j_gameSecret);
                methodInfo1.env->DeleteLocalRef(j_gameKey);
                methodInfo1.env->DeleteLocalRef(j_gameSecret);

                methodInfo1.env->DeleteLocalRef(methodInfo1.classID);
            }
        }

        void jni_addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addBusinessEvent",
                "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V"))
            {
                jstring j_currency = methodInfo.env->NewStringUTF(currency);
                jstring j_itemType = methodInfo.env->NewStringUTF(itemType);
                jstring j_itemId = methodInfo.env->NewStringUTF(itemId);
                jstring j_cartType = methodInfo.env->NewStringUTF(cartType);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_currency, amount, j_itemType, j_itemId, j_cartType, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_currency);
                methodInfo.env->DeleteLocalRef(j_itemType);
                methodInfo.env->DeleteLocalRef(j_itemId);
                methodInfo.env->DeleteLocalRef(j_cartType);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addBusinessEventWithReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType,
            const char *receipt, const char *store, const char *signature, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addBusinessEvent",
                                               "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V"))
            {
                jstring j_currency = methodInfo.env->NewStringUTF(currency);
                jstring j_itemType = methodInfo.env->NewStringUTF(itemType);
                jstring j_itemId = methodInfo.env->NewStringUTF(itemId);
                jstring j_cartType = methodInfo.env->NewStringUTF(cartType);
                jstring j_receipt = methodInfo.env->NewStringUTF(receipt);
                jstring j_store = methodInfo.env->NewStringUTF(store);
                jstring j_signature = methodInfo.env->NewStringUTF(signature);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_currency, amount, j_itemType, j_itemId, j_cartType, j_receipt, j_store, j_signature, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_currency);
                methodInfo.env->DeleteLocalRef(j_itemType);
                methodInfo.env->DeleteLocalRef(j_itemId);
                methodInfo.env->DeleteLocalRef(j_cartType);
                methodInfo.env->DeleteLocalRef(j_receipt);
                methodInfo.env->DeleteLocalRef(j_store);
                methodInfo.env->DeleteLocalRef(j_signature);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addResourceEvent(int flowType, const char *currency, float amount, const char *itemType, const char *itemId, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addResourceEvent",
                "(ILjava/lang/String;FLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V"))
            {
                jstring j_currency = methodInfo.env->NewStringUTF(currency);
                jstring j_itemType = methodInfo.env->NewStringUTF(itemType);
                jstring j_itemId = methodInfo.env->NewStringUTF(itemId);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, flowType, j_currency, amount, j_itemType, j_itemId, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_currency);
                methodInfo.env->DeleteLocalRef(j_itemType);
                methodInfo.env->DeleteLocalRef(j_itemId);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addProgressionEvent(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addProgressionEvent",
                "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V"))
            {
                jstring j_progression01 = methodInfo.env->NewStringUTF(progression01);
                jstring j_progression02 = methodInfo.env->NewStringUTF(progression02);
                jstring j_progression03 = methodInfo.env->NewStringUTF(progression03);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, progressionStatus, j_progression01, j_progression02, j_progression03, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_progression01);
                methodInfo.env->DeleteLocalRef(j_progression02);
                methodInfo.env->DeleteLocalRef(j_progression03);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addProgressionEventWithScore(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addProgressionEvent",
                "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;DLjava/lang/String;Z)V"))
            {
                jstring j_progression01 = methodInfo.env->NewStringUTF(progression01);
                jstring j_progression02 = methodInfo.env->NewStringUTF(progression02);
                jstring j_progression03 = methodInfo.env->NewStringUTF(progression03);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, progressionStatus, j_progression01, j_progression02, j_progression03, (double)score, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_progression01);
                methodInfo.env->DeleteLocalRef(j_progression02);
                methodInfo.env->DeleteLocalRef(j_progression03);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addDesignEvent(const char *eventId, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addDesignEvent",
                "(Ljava/lang/String;Ljava/lang/String;Z)V"))
            {
                jstring j_eventId = methodInfo.env->NewStringUTF(eventId);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_eventId, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_eventId);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addDesignEventWithValue(const char *eventId, float value, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addDesignEvent",
                "(Ljava/lang/String;DLjava/lang/String;Z)V"))
            {
                jstring j_eventId = methodInfo.env->NewStringUTF(eventId);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_eventId, value, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_eventId);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addErrorEvent(int severity, const char *message, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addErrorEvent",
                "(ILjava/lang/String;Ljava/lang/String;Z)V"))
            {
                jstring j_message = methodInfo.env->NewStringUTF(message);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, severity, j_message, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_message);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addAdEventWithDuration(int adAction, int adType, const char *adSdkName, const char *adPlacement, int64_t duration, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addAdEvent",
                                               "(IILjava/lang/String;Ljava/lang/String;JLjava/lang/String;Z)V"))
            {
                jstring j_adSdkName = methodInfo.env->NewStringUTF(adSdkName);
                jstring j_adPlacement = methodInfo.env->NewStringUTF(adPlacement);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, adAction, adType, j_adSdkName, j_adPlacement, duration, j_fields, j_fields);
                methodInfo.env->DeleteLocalRef(j_adSdkName);
                methodInfo.env->DeleteLocalRef(j_adPlacement);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addAdEventWithReason(int adAction, int adType, const char *adSdkName, const char *adPlacement, int noAdReason, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addAdEvent",
                                               "(IILjava/lang/String;Ljava/lang/String;ILjava/lang/String;Z)V"))
            {
                jstring j_adSdkName = methodInfo.env->NewStringUTF(adSdkName);
                jstring j_adPlacement = methodInfo.env->NewStringUTF(adPlacement);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, adAction, adType, j_adSdkName, j_adPlacement, noAdReason, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_adSdkName);
                methodInfo.env->DeleteLocalRef(j_adPlacement);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_addAdEvent(int adAction, int adType, const char *adSdkName, const char *adPlacement, const char *fields, bool mergeFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "addAdEvent",
                                               "(IILjava/lang/String;Ljava/lang/String;)V"))
            {
                jstring j_adSdkName = methodInfo.env->NewStringUTF(adSdkName);
                jstring j_adPlacement = methodInfo.env->NewStringUTF(adPlacement);
                jstring j_fields = methodInfo.env->NewStringUTF(fields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, adAction, adType, j_adSdkName, j_adPlacement, j_fields, mergeFields);
                methodInfo.env->DeleteLocalRef(j_adSdkName);
                methodInfo.env->DeleteLocalRef(j_adPlacement);
                methodInfo.env->DeleteLocalRef(j_fields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setEnabledInfoLog(bool flag)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setEnabledInfoLog",
                "(Z)V"))
            {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, flag);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setEnabledVerboseLog(bool flag)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setEnabledVerboseLog",
                "(Z)V"))
            {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, flag);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setEnabledManualSessionHandling(bool flag)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setEnabledManualSessionHandling",
                "(Z)V"))
            {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, flag);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setEnabledErrorReporting(bool flag)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setEnabledErrorReporting",
                                               "(Z)V"))
            {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, flag);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setCustomDimension01(const char *customDimension)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setCustomDimension01",
                "(Ljava/lang/String;)V"))
            {
                jstring j_customDimension = methodInfo.env->NewStringUTF(customDimension);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_customDimension);
                methodInfo.env->DeleteLocalRef(j_customDimension);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setCustomDimension02(const char *customDimension)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setCustomDimension02",
                "(Ljava/lang/String;)V"))
            {
                jstring j_customDimension = methodInfo.env->NewStringUTF(customDimension);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_customDimension);
                methodInfo.env->DeleteLocalRef(j_customDimension);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setCustomDimension03(const char *customDimension)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setCustomDimension03",
                "(Ljava/lang/String;)V"))
            {
                jstring j_customDimension = methodInfo.env->NewStringUTF(customDimension);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_customDimension);
                methodInfo.env->DeleteLocalRef(j_customDimension);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_setGlobalCustomEventFields(const char *customFields)
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "setGlobalCustomEventFields",
                                               "(Ljava/lang/String;)V"))
            {
                jstring j_customFields = methodInfo.env->NewStringUTF(customFields);
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, j_customFields);
                methodInfo.env->DeleteLocalRef(j_customFields);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_startSession()
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "startSession",
                "()V"))
            {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_endSession()
        {
            JniMethodInfo methodInfo;
            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "endSession",
                "()V"))
            {
                methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }
        }

        void jni_getRemoteConfigsValueAsString(const char *key, char** out)
        {
            JniMethodInfo methodInfo;
            std::string result;

            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "getRemoteConfigsValueAsString",
                "(Ljava/lang/String;)Ljava/lang/String;"))
            {
                jstring j_key = methodInfo.env->NewStringUTF(key);
                jstring j_s = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, j_key);
                const char* s = methodInfo.env->GetStringUTFChars(j_s, 0);
                result = s;
                methodInfo.env->ReleaseStringUTFChars(j_s, s);
                methodInfo.env->DeleteLocalRef(j_key);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }

        void jni_getRemoteConfigsValueAsStringWithDefaultValue(const char *key, const char *defaultValue, char** out)
        {
            JniMethodInfo methodInfo;
            std::string result;

            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "getRemoteConfigsValueAsString",
                "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"))
            {
                jstring j_key = methodInfo.env->NewStringUTF(key);
                jstring j_defaultValue = methodInfo.env->NewStringUTF(defaultValue);
                jstring j_s = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, j_key, j_defaultValue);
                const char* s = methodInfo.env->GetStringUTFChars(j_s, 0);
                result = s;
                methodInfo.env->ReleaseStringUTFChars(j_s, s);
                methodInfo.env->DeleteLocalRef(j_key);
                methodInfo.env->DeleteLocalRef(j_defaultValue);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }

        bool jni_isCommandCenterReady()
        {
            JniMethodInfo methodInfo;
            bool result = false;

            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "isRemoteConfigsReady",
                "()Z"))
            {
                result = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }

            return result;
        }

        void jni_getRemoteConfigsContentAsString(char** out)
        {
            JniMethodInfo methodInfo;
            std::string result;

            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "getRemoteConfigsContentAsString",
                "()Ljava/lang/String;"))
            {
                jstring j_s = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
                const char* s = methodInfo.env->GetStringUTFChars(j_s, 0);
                result = s;
                methodInfo.env->ReleaseStringUTFChars(j_s, s);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }

        void jni_getABTestingId(char** out)
        {
            JniMethodInfo methodInfo;
            std::string result;

            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "getABTestingId",
                                               "()Ljava/lang/String;"))
            {
                jstring j_s = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
                const char* s = methodInfo.env->GetStringUTFChars(j_s, 0);
                result = s;
                methodInfo.env->ReleaseStringUTFChars(j_s, s);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }

        void jni_getABTestingVariantId(char** out)
        {
            JniMethodInfo methodInfo;
            std::string result;

            if (JniHelper::getStaticMethodInfo(methodInfo, GAMEANALYTICS_CLASS_NAME, "getABTestingVariantId",
                                               "()Ljava/lang/String;"))
            {
                jstring j_s = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
                const char* s = methodInfo.env->GetStringUTFChars(j_s, 0);
                result = s;
                methodInfo.env->ReleaseStringUTFChars(j_s, s);
                methodInfo.env->DeleteLocalRef(methodInfo.classID);
            }

            char* tmp = new char[result.size() + 1];
            snprintf(tmp, result.size() + 1, "%s", result.c_str());
            *out = tmp;
        }
    }
}
