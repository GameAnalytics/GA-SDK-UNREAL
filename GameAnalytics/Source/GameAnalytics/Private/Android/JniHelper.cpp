#include "JniHelper.h"
#include <android/log.h>
#include <pthread.h>

#include "Android/AndroidPlatform.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static pthread_key_t g_key;

jclass _getClassID(const char *className) {
    if (nullptr == className) {
        return nullptr;
    }

    JNIEnv* env = gameanalytics::JniHelper::getEnv();
    jclass _clazz = env->FindClass(className);

    if (nullptr == _clazz) {
        LOGE("Classloader failed to find class of %s", className);
        env->ExceptionClear();
    }

    return _clazz;
}

void _detachCurrentThread(void* a) {
    gameanalytics::JniHelper::getJavaVM()->DetachCurrentThread();
}

namespace gameanalytics {

    JavaVM* JniHelper::_psJavaVM = nullptr;
    jmethodID JniHelper::loadclassMethod_methodID = nullptr;
    jobject JniHelper::classloader = nullptr;

    jobject JniHelper::_activity = nullptr;

    JavaVM* JniHelper::getJavaVM()
    {
        pthread_t thisthread = pthread_self();
        LOGD("JniHelper::getJavaVM(), pthread_self() = %ld", thisthread);
        return _psJavaVM;
    }

    void JniHelper::setJavaVM(JavaVM *javaVM)
    {
        pthread_t thisthread = pthread_self();
        LOGD("JniHelper::setJavaVM(%p), pthread_self() = %ld", javaVM, thisthread);
        _psJavaVM = javaVM;

        pthread_key_create(&g_key, _detachCurrentThread);
    }

    JNIEnv* JniHelper::cacheEnv(JavaVM* jvm)
    {
        JNIEnv* _env = nullptr;
        // get jni environment

        LOGD("GA: getting the jni environment");
        jint ret = jvm->GetEnv((void**)&_env, JNI_VERSION_1_6);

        LOGD("GA: retrieved the jni environment");
        switch (ret) {
        case JNI_OK :
            // Success!
            pthread_setspecific(g_key, _env);
            return _env;

        case JNI_EDETACHED :
            // Thread not attached
            if (jvm->AttachCurrentThread(&_env, nullptr) < 0)
                {
                    LOGE("Failed to get the environment using AttachCurrentThread()");

                    return nullptr;
                } else {
                // Success : Attached and obtained JNIEnv!
                pthread_setspecific(g_key, _env);
                return _env;
            }

        case JNI_EVERSION :
            // Cannot recover from this error
            LOGE("JNI interface version 1.6 not supported");
        default :
            LOGE("Failed to get the environment using GetEnv()");
            return nullptr;
        }
    }

    JNIEnv* JniHelper::getEnv()
    {
        JNIEnv *_env = FAndroidApplication::GetJavaEnv(true);
        if (_env == nullptr)
            _env = JniHelper::cacheEnv(_psJavaVM);
        return _env;
    }

    jobject JniHelper::getActivity() {
        return _activity;
    }

    bool JniHelper::setClassLoaderFrom(jobject activityinstance) {
        JniMethodInfo _getclassloaderMethod;
        if (!JniHelper::getMethodInfo_DefaultClassLoader(_getclassloaderMethod, "android/content/Context", "getClassLoader", "()Ljava/lang/ClassLoader;")) {
            return false;
        }

        jobject _c = JniHelper::getEnv()->CallObjectMethod(activityinstance, _getclassloaderMethod.methodID);

        if (nullptr == _c) {
            return false;
        }

        JniMethodInfo _m;
        if (!JniHelper::getMethodInfo_DefaultClassLoader(_m, "java/lang/ClassLoader", "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;")) {
            return false;
        }

        JniHelper::classloader = JniHelper::getEnv()->NewGlobalRef(_c);
        JniHelper::loadclassMethod_methodID = _m.methodID;
        JniHelper::_activity = JniHelper::getEnv()->NewGlobalRef(activityinstance);

        return true;
    }

    bool JniHelper::getStaticMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
    {
        if ((nullptr == className) ||
            (nullptr == methodName) ||
            (nullptr == paramCode)) {
            return false;
        }

        JNIEnv *env = JniHelper::getEnv();
        if (!env) {
            LOGE("Failed to get JNIEnv");
            return false;
        }

        jclass classID = _getClassID(className);
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetStaticMethodID(classID, methodName, paramCode);
        if (! methodID) {
            LOGE("Failed to find static method id of %s", methodName);
            env->ExceptionClear();
            return false;
        }

        methodinfo.classID = classID;
        methodinfo.env = env;
        methodinfo.methodID = methodID;
        return true;
    }

    bool JniHelper::getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode) {
        if ((nullptr == className) ||
            (nullptr == methodName) ||
            (nullptr == paramCode)) {
            return false;
        }

        JNIEnv *env = JniHelper::getEnv();
        if (!env) {
            return false;
        }

        jclass classID = env->FindClass(className);
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
        if (! methodID) {
            LOGE("Failed to find method id of %s", methodName);
            env->ExceptionClear();
            return false;
        }

        methodinfo.classID = classID;
        methodinfo.env = env;
        methodinfo.methodID = methodID;

        return true;
    }

    bool JniHelper::getMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode) {
        if ((nullptr == className) ||
            (nullptr == methodName) ||
            (nullptr == paramCode)) {
            return false;
        }

        JNIEnv *env = JniHelper::getEnv();
        if (!env) {
            return false;
        }

        jclass classID = _getClassID(className);
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
        if (! methodID) {
            LOGE("Failed to find method id of %s", methodName);
            env->ExceptionClear();
            return false;
        }

        methodinfo.classID = classID;
        methodinfo.env = env;
        methodinfo.methodID = methodID;

        return true;
    }
}
