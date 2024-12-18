#include <jni.h>
#include <stdio.h>
#include "Prompt.h"

# if 0
// 3.2 Accessing Strings
JNIEXPORT jstring JNICALL Java_Prompt_getLine(JNIEnv *env, jobject obj, jstring prompt) {
	char buf[128];
	const jbyte *str;

	str = (*env)->GetStringUTFChars(env, prompt, NULL);
	if(NULL == str) {
		return NULL;//OutOfMemoryError already thrown
	}
	printf("%s", str);
	(*env)->ReleaseStringUTFChars(env, prompt, str);
	/* We assume here that the user does not type more than 127 characters */
	scanf("%s", buf);
	return (*env)->NewStringUTF(env, buf);
}
#endif

// 3.2.5 New JNI String Functions
JNIEXPORT jstring JNICALL Java_Prompt_getLine(JNIEnv *env, jobject obj, jstring prompt) {
	char buf[128];
	const jbyte *str;

	str = (*env)->GetStringUTFChars(env, prompt, NULL);
	if(NULL == str) {
		return NULL;//OutOfMemoryError already thrown
	}
	printf("%s", str);
	(*env)->ReleaseStringUTFChars(env, prompt, str);
	/* We assume here that the user does not type more than 127 characters */
	scanf("%s", buf);
	return (*env)->NewStringUTF(env, buf);
}