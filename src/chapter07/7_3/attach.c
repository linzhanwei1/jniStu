#include <jni.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

JavaVM *jvm;    /* The virtual machine instance */

#define PATH_SEPARATOR ';'
#define USER_CLASSPATH "."  /* where Prog.class is */

void threadFun(void *arg) {
    jint res;
    jclass cls;
    jmethodID mid;
    jstring jstr;
    jclass stringClass;
    jobjectArray args;
    JNIEnv *env;
    char buf[100];
    int threadNum = (int)arg;
    /* Pass NULL as the third argument */
    
#ifdef JNI_VERSION_1_2
    res = (*jvm)->AttachCurrentThread(jvm, (void**)&env, NULL);
#else

#endif
    if(res < 0) {
        fprintf(stderr, "Attach failed\n");
        return;
    }
    cls = (*env)->FindClass(env, "Prog");
    if(cls == NULL) {
        goto detach;
    }
    mid = (*env)->GetStaticMethodID(env, cls, "main", "([Ljava/lang/String;)V");
    if(mid == NULL) {
        goto detach;
    }
    sprintf(buf, " from Thread %d", threadNum);
    jstr = (*env)->NewStringUTF(env, buf);
    if(jstr == NULL) {
        goto detach;
    }
    stringClass = (*env)->FindClass(env, "java/lang/String");
    args = (*env)->NewObjectArray(env, 1, stringClass, jstr);
    if(args == NULL) {
        goto detach;
    }
    (*env)->CallStaticVoidMethod(env, cls, mid, args);

detach:
    if((*env)->ExceptionOccurred(env)) {
        (*env)->ExceptionDescribe(env);
    }
    (*jvm)->DetachCurrentThread(jvm);

    return;
}

int main(int argc, char* argv[]) {
    JNIEnv *env;
    int i;
    jint res;

#ifdef JNI_VERSION_1_2
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];
    options[0].optionString = "-Djava.class.path=" USER_CLASSPATH;
    vm_args.version = 0x00010002;
    vm_args.options = options;
    vm_args.nOptions = 1;
    vm_args.ignoreUnrecognized = JNI_TRUE;
    res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
#else
    // TO DO
#endif
    if(res < 0) {
        fprintf(stderr, "Can't create Java VM\n");
        exit(1);
    }
    for(i = 0; i < 5; i++) {
        pthread_t id;
        int ret = -1;
        // /* We pass the thread number to every thread */
        ret = pthread_create(&id, NULL, threadFun, (void*)i);
    }

    sleep(1);   /* wait for threads to start */
    (*jvm)->DestroyJavaVM(jvm);

    return 0;
}