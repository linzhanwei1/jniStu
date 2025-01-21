#include <jni.h>
#include <stdio.h>
#include "RegisteringNativeMethod.h"

#define		NUM_ARRAY_ELEMENTS(p)		((int) sizeof(p) / sizeof(p[0]))

static JavaVM *cached_jvm;
static jclass Class_RegisteringNativeMethod;
static jmethodID MID_C_g;

JNIEnv *JNU_GetEnv() {
    JNIEnv *env;
    (*cached_jvm)->GetEnv(cached_jvm, (void**)&env, JNI_VERSION_1_2);
    return env;
}

jint registerNativeMethods(JNIEnv* env, const char *className, JNINativeMethod *methods, int numMethods) {
    int result = 0;

    jclass clazz = (*env)->FindClass(env, className);
    if(clazz) {
        int result = (*env)->RegisterNatives(env, clazz, methods, numMethods);
        if(result < 0) {
            printf("registerNativeMethods failed(class=%s)", className);
        }else{
            printf("registerNativeMethods: class'%s' not found", className);
        }
    }

    return result;
}

void firstFunction(JNIEnv *env, jobject obj) {
    printf("This is FirstFunction.\n");
}

jint SecondFunction(JNIEnv *env, jobject obj) {
    printf("This is SecondFunction.\n");
    return 521;
}


static JNINativeMethod methods[] = {
    {"firstFunction", "()V", (void*)firstFunction},
    {"SecondFunction", "()I", (void*)SecondFunction},
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env;
    jclass cls;
    cached_jvm = jvm;   /* cache the JavaVM pointer */

    if((*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_2)) {
        return JNI_ERR; /* JNI version not supported */
    }
    cls = (*env)->FindClass(env, "RegisteringNativeMethod");
    if(cls == NULL) {
        return JNI_ERR;
    }

    /* Use weak global ref to allow RegisteringNativeMethod class to be unloaded */
    Class_RegisteringNativeMethod = (*env)->NewWeakGlobalRef(env, cls);
    if(Class_RegisteringNativeMethod == NULL) {
        return JNI_ERR;
    }

    /* Register functions */
    registerNativeMethods(env, "RegisteringNativeMethod", methods, NUM_ARRAY_ELEMENTS(methods));


    printf("In c: JNI_OnLoad.\n");

    return  JNI_VERSION_1_2;
}

JNIEXPORT void JNICALL JNI_OnUnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env;
    if((*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_2)) {
        return;
    }
    (*env)->DeleteWeakGlobalRef(env, Class_RegisteringNativeMethod);
    
    printf("In c: JNI_OnUnLoad.\n");
    return;
}



