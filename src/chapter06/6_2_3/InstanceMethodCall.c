#include <jni.h>
#include <stdio.h>
#include "InstanceMethodCall.h"


static jvalue JNU_CallMethodByName(JNIEnv *env, jboolean *hasException, jobject obj, const char *name,
    const char *descriptor, ...) {
    va_list args;
    jclass clazz;
    jmethodID mid;
    jvalue result;

    if((*env)->EnsureLocalCapacity(env, 2) == JNI_OK) {
        clazz = (*env)->GetObjectClass(env, obj);
        mid = (*env)->GetMethodID(env, clazz, name, descriptor);
        if(mid) {
            const char *p = descriptor;
            /* skip over argument types to find out the return type */
            while(*p != ')') p++;
            /* skiop ')' */
			p++;
            va_start(args, descriptor);
            switch(*p) {
                case 'V':
                    (*env)->CallVoidMethodV(env, obj, mid, args);
                    break;
                case '[':
                case 'L':
                    result.l = (*env)->CallObjectMethodV(env, obj, mid, args);
                    break;
                case 'Z':
                    result.z = (*env)->CallBooleanMethodV(env, obj, mid, args);
                    break;
                case 'B':
                    result.b = (*env)->CallByteMethodV(env, obj, mid, args);
                    break;
                case 'C':
                    result.c = (*env)->CallCharMethodV(env, obj, mid, args);
                    break;
                case 'S':
                    result.s = (*env)->CallShortMethodV(env, obj, mid, args);
                    break;
                case 'I':
                    result.i = (*env)->CallIntMethodV(env, obj, mid, args);
                    break;
                case 'J':
                    result.j = (*env)->CallLongMethodV(env, obj, mid, args);
                    break;
                case 'F':
                    result.f = (*env)->CallFloatMethodV(env, obj, mid, args);
                    break;
                case 'D':
                    result.d = (*env)->CallDoubleMethodV(env, obj, mid, args);
                    break;
                default:
                    (*env)->FatalError(env, "illegal descriptor");
            }
            va_end(args);
        }
        (*env)->DeleteLocalRef(env, clazz);
    }
    if(hasException) {
        /* returns JNI_TRUE when there is a pending exception */
        *hasException = (*env)->ExceptionCheck(env);
#if 0
        /* The previous code would have to be rewritten as follows in JDK release 1.1 */
        if(hasException) {
            jthrowable exc = (*env)->ExceptionOccurred(env);
            *hasException = exc != NULL;
            (*env)->DeleteLocalRef(env, exc);
        }
#endif
    }
    return result;
}

#if 0
/* Code in 4.2 */
JNIEXPORT void JNICALL Java_InstanceMethodCall_nativeMethod(JNIEnv *env, jobject obj) {
	jclass cls = (*env)->GetObjectClass(env, obj);
	jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
	if(mid == NULL) {
		return;	//method not found
	}
	printf("In C\n");
	(*env)->CallVoidMethod(env, obj, mid);
}
#endif

#if 1
/* Code in 6.2.3 */
JNIEXPORT void JNICALL Java_InstanceMethodCall_nativeMethod(JNIEnv *env, jobject obj) {
	printf("In C\n");
	JNU_CallMethodByName(env, NULL, obj, "callback", "()V");
}
#endif