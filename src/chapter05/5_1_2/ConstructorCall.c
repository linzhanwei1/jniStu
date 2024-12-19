#include <jni.h>
#include <stdio.h>
#include "ConstructorCall.h"

/* Global reference */
static jstring MyNewString_(JNIEnv *env, jchar *chars, jint len) {
	static jclass stringClass = NULL;	// 想要缓存String类引用
	jmethodID cid;
	jcharArray elemArr;
	jstring result;

	if(stringClass == NULL) {
		jclass localRefCls = (*env)->FindClass(env, "java/lang/String");
		if(localRefCls == NULL) {
			return NULL;	//exception thrown
		}
		/* Create a global reference */
		stringClass = (*env)->NewGlobalRef(env, localRefCls);

		/* The local reference is no longer useful */
		(*env)->DeleteLocalRef(env, localRefCls);

		/* Is the global reference created successfully? */
		if(stringClass == NULL) {
			return NULL;	/* out of memory exception thrown */
		}
	}

	//Get the method ID for the String(char[]) constructor
	cid = (*env)->GetMethodID(env, stringClass, "<init>", "([C)V");
	if(cid == NULL) {
		return NULL; //exception thrown
	}

	//Create a char[] that holds the string characters
	elemArr = (*env)->NewCharArray(env, len);
	if(elemArr == NULL) {
		return NULL;	// exception thrown
	}
	(*env)->SetCharArrayRegion(env, elemArr, 0, len, chars);

	//Construct a java.lang.String object
	result = (*env)->NewObject(env, stringClass, cid, elemArr);

	//Free local references
	(*env)->DeleteLocalRef(env, elemArr);
	// (*env)->DeleteLocalRef(env, stringClass);

	return result;
}

JNIEXPORT jstring JNICALL Java_ConstructorCall_MyNewString(JNIEnv *env, jobject obj) {
	jclass cls = (*env)->GetObjectClass(env, obj);
	jchar tmp[] = {'a','b','c'};

	printf("In C\n");
	return MyNewString_(env, tmp, sizeof(tmp)/sizeof(tmp[0]));;
}


