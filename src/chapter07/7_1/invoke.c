#include <jni.h>
#include <stdlib.h>
#include <stdio.h>

#define PATH_SEPARATOR ';'
#define USER_CLASSPATH "."

int main(int argc, char *argv[]) {
    JNIEnv *env;
    JavaVM *jvm;
    jint res;
    jclass cls;
    jmethodID mid;
    jstring jstr;
    jclass stringClass;
    jobjectArray args;

#ifdef JNI_VERSION_1_2
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];
    options[0].optionString = "-Djava.class.path=" USER_CLASSPATH;
    vm_args.version = 0x00010002;
    vm_args.options = options;
    vm_args.nOptions = 1;
    vm_args.ignoreUnrecognized = JNI_TRUE;
    /* Create the Java VM */
    res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
#else
    /* TO DO */
#endif
    if(res < 0) {
        fprintf(stderr, "Can't create Java VM\n");
        exit(1);
    }
    cls = (*env)->FindClass(env, "Prog");
    if(cls == NULL) {
        goto destroy;
    }

    mid = (*env)->GetStaticMethodID(env, cls, "main", "([Ljava/lang/String;)V");
    if(mid == NULL) {
        goto destroy;
    }
    jstr = (*env)->NewStringUTF(env, "from C!");
    if(jstr == NULL) {
        goto destroy;
    }
    stringClass = (*env)->FindClass(env, "java/lang/String");
    args = (*env)->NewObjectArray(env, 1, stringClass, jstr);
    if(args == NULL) {
        goto destroy;
    }
    (*env)->CallStaticVoidMethod(env, cls, mid, args);

destroy:
    if((*env)->ExceptionOccurred(env)) {
        (*env)->ExceptionDescribe(env);
    }
    (*jvm)->DestroyJavaVM(jvm);

    return 0;
}