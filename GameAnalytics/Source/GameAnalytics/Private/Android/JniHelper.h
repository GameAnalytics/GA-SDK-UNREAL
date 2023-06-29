#pragma once

#include <jni.h>

namespace gameanalytics {

    typedef struct JniMethodInfo_
    {
        JNIEnv *    env;
        jclass      classID;
        jmethodID   methodID;
    } JniMethodInfo;

    class JniHelper
    {
    public:
        static void setJavaVM(JavaVM *javaVM);
        static JavaVM* getJavaVM();
        static JNIEnv* getEnv();
        static jobject getActivity();

        static bool setClassLoaderFrom(jobject activityInstance);
        static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
        static bool getMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);

        static jmethodID loadclassMethod_methodID;
        static jobject classloader;

    private:
        
        static bool getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
        static JavaVM* _psJavaVM;
        static jobject _activity;
    };
}
