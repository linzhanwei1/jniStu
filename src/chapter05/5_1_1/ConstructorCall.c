#include <jni.h>
#include <stdio.h>
#include "ConstructorCall.h"

/* This code is illegal */
static jstring MyNewString_(JNIEnv *env, jchar *chars, jint len) {
	static jclass stringClass = NULL;	// 想要缓存String类引用
	jmethodID cid;
	jcharArray elemArr;
	jstring result;

	if(stringClass == NULL) {
		stringClass = (*env)->FindClass(env, "java/lang/String");
		if(stringClass == NULL) {
			return NULL;	//exception thrown
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
	(*env)->DeleteLocalRef(env, stringClass);

	return result;
}

JNIEXPORT jstring JNICALL Java_ConstructorCall_MyNewString(JNIEnv *env, jobject obj) {
	jclass cls = (*env)->GetObjectClass(env, obj);
	jchar tmp[] = {'a','b','c'};

	printf("In C\n");
	return MyNewString_(env, tmp, sizeof(tmp)/sizeof(tmp[0]));;
}


