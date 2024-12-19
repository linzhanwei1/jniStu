#include <jni.h>
#include <stdio.h>
#include "ConstructorCall.h"

static jstring MyNewString_(JNIEnv *env, jchar *chars, jint len) {
	jclass stringClass;
	jmethodID cid;
	jcharArray elemArr;
	jstring result;

	stringClass = (*env)->FindClass(env, "java/lang/String");
	if(stringClass == NULL) {
		return NULL;	//exception thrown
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
	// jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
	// if(mid == NULL) {
	// 	return;	//method not found
	// }
	printf("In C\n");
	
	// (*env)->CallVoidMethod(env, obj, mid);
	return MyNewString_(env, tmp, sizeof(tmp)/sizeof(tmp[0]));;
}


