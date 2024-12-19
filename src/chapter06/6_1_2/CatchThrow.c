#include <jni.h>
#include <stdio.h>
#include "CatchThrow.h"

static void JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg) {
    jclass cls = (*env)->FindClass(env, name);

    /* if cls is NULL, an exception has already been throw */
    if(cls != NULL) {
        (*env)->ThrowNew(env, cls, msg);
    }
    /* free the local ref */
    (*env)->DeleteLocalRef(env, cls);
}

JNIEXPORT void JNICALL Java_CatchThrow_doit(JNIEnv *env, jobject obj) {
    jthrowable exc;
    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
    if(mid == NULL) {
        return;
    }
    (*env)->CallVoidMethod(env, obj, mid);
    /* detect exception by calling the JNI function ExceptionOccurred. */
    exc = (*env)->ExceptionOccurred(env);
    if(exc) {
        /* We don't do much with the exception, except that we print a debug message for
          it, clear it, and throw a new exception.
         */
        jclass newExcCls;
        printf("===========================================================\n");
        /* when an exception is detected,the native code outputs a descriptive message
           about the exception by calling ExceptionDescribe 
         */
        (*env)->ExceptionDescribe(env);
        printf("===========================================================\n");
        /* clears the exception using */
        (*env)->ExceptionClear(env);
        
        newExcCls = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
        if(newExcCls == NULL) {
            /* Unable to find the exception class, give up. */
            printf("In C:Unable to find the exception class, give up.\n");
            return;
        }

        // (*env)->ThrowNew(env, newExcCls, "thrown from C code");
        JNU_ThrowByName(env, "java/lang/IllegalArgumentException", "thrown from C code from utility function.");
    }
}