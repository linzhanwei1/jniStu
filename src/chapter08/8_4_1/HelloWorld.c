#include <jni.h>
#include <stdio.h>
#include "C.h"

static JavaVM *cached_jvm;
static jclass Class_C;
static jmethodID MID_C_g;

JNIEnv *JNU_GetEnv() {
    JNIEnv *env;
    (*cached_jvm)->GetEnv(cached_jvm, (void**)&env, JNI_VERSION_1_2);
    return env;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env;
    jclass cls;
    cached_jvm = jvm;   /* cache the JavaVM pointer */

    if((*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_2)) {
        return JNI_ERR; /* JNI version not supported */
    }
    cls = (*env)->FindClass(env, "C");
    if(cls == NULL) {
        return JNI_ERR;
    }

    /* Use weak global ref to allow C class to be unloaded */
    Class_C = (*env)->NewWeakGlobalRef(env, cls);
    if(Class_C == NULL) {
        return JNI_ERR;
    }
    /* Compute and cache the method ID */
    MID_C_g = (*env)->GetMethodID(env, cls, "g", "()V");
    if(MID_C_g == NULL) {
        return JNI_ERR;
    }

    printf("In c: JNI_OnLoad.\n");

    return  JNI_VERSION_1_2;
}

JNIEXPORT void JNICALL JNI_OnUnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env;
    if((*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_2)) {
        return;
    }
    (*env)->DeleteWeakGlobalRef(env, Class_C);
    
    printf("In c: JNI_OnUnLoad.\n");
    return;
}

JNIEXPORT void JNICALL Java_C_print(JNIEnv *env, jobject obj) {
    printf("Hello World, this is your first demo about native coding.\n");
}

