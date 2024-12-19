#include <jni.h>
#include <stdio.h>
#include "InstanceMethodCall.h"

static jmethodID MID_InstanceMethodCall_callback;

JNIEXPORT void JNICALL Java_InstanceMethodCall_initIDS(JNIEnv *env, jclass cls) {
	MID_InstanceMethodCall_callback = (*env)->GetMethodID(env, cls, "callback", "()V");
}

JNIEXPORT void JNICALL Java_InstanceMethodCall_nativeMethod(JNIEnv *env, jobject obj) {
	printf("In C\n");
	(*env)->CallVoidMethod(env, obj, MID_InstanceMethodCall_callback);
}
