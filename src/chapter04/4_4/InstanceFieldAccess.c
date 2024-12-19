#include <jni.h>
#include <stdio.h>
#include "InstanceFieldAccess.h"

JNIEXPORT void JNICALL Java_InstanceFieldAccess_accessField(JNIEnv *env, jobject obj) {
	static jfieldID fid_s = NULL;	//store the field ID
	jstring jstr;
	const char *str;

	/* Get a reference to obj's class */
	jclass cls = (*env)->GetObjectClass(env, obj);

	/* Caching at the Point of Use */
	if(fid_s == NULL) {
		/* Look for the instance field s in cls */
		fid_s = (*env)->GetFieldID(env, cls, "s", "Ljava/lang/String;");
		if(fid_s == NULL) {
			return;	//failed to find the field
		}
	}

	printf("In C:\n");

	/* Read the instance field s */
	jstr = (*env)->GetObjectField(env, obj, fid_s);
	str = (*env)->GetStringUTFChars(env, jstr, NULL);
	if(str == NULL) {
		return; //out of memory
	}
	printf("  c.s = \"%s\"\n", str);
	(*env)->ReleaseStringUTFChars(env, jstr, str);

	/* Create a new string and overwrite the instance field */
	jstr = (*env)->NewStringUTF(env, "123");
	if(jstr == NULL) {
		return; //out of memory
	}

	(*env)->SetObjectField(env, obj, fid_s, jstr);
}
