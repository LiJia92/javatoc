#include "com_example_call_InitJNI.h"
#include <com_smilegames_jtc_xmttUtil.c>

//static JNIEnv *envSave;

//#define TAG "lijia" // 这个是自定义的LOG的标识
//#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型

//void realizeFunction_c();
//extern jstring getSHA1Digest(JNIEnv *env, jobject context);

JNIEXPORT jbyteArray JNICALL Java_com_example_call_InitJNI_init(
		JNIEnv *env, jclass cls, jobject context, jstring param) {
//	Class classz = (*env)->FindClass(env, "com/example/impl/FunctionImpl");
//	jmethodID method1 = (*env)->GetMethodID(env, classz, "realizeFunction","(Ljava/lang/String;)Ljava/lang/String;");
//	jobject obj = (*env)->AllocObject(env, classz);
//	jstring param = (*env)->NewStringUTF(env, "Hello world! I am Native interface.");
//	jstring msg = (*env)->CallObjectMethod(env, obj, method1, param);
//	const char *dname = (*env)->GetStringUTFChars(env, msg, 0);
//    return msg;
	//return (*env)->NewStringUTF(env, "Hello world! I am Native interface.");
//	int i = 0;
//	LOGI("########## i = %d", i);
//	envSave = env;
	return jniMd5(env,context,param);
//	realizeFunction_c();
//	LOGI("%s",dname);
//	void ReleaseStringUTFChars(env, msg, dname);
}

//#define callclass "com/example/impl/FunctionImpl" // 定义call函数类名
//#define callmethod "realizeFunction" // 定义call函数方法名
//
//void realizeFunction_c(){
//	int i = 1;
//	LOGI("########## i = %s", "lijia");
//	jclass classz = (*envSave)->FindClass(envSave, callclass);
//	jmethodID method1 = (*envSave)->GetMethodID(envSave, classz, callmethod,"()Lcom/example/impl/ReturnClass;");
//	jobject obj = (*envSave)->AllocObject(envSave, classz);
//	(*envSave)->CallObjectMethod(envSave, obj, method1);
//}
//jclass GetObjectClass(jobject obj){
//	jclass class = (*envSave)->GetObjectClass(envSave, obj);
//	if ((*envSave)->ExceptionOccurred(envSave)) {
//		(*envSave)->ExceptionClear(envSave);
//		return NULL;
//	}
//	return class;
//}
//
//jclass FindClass(const char* className){
//	jclass class = (*envSave)->FindClass(envSave, className);
//	if ((*envSave)->ExceptionOccurred(envSave)) {
//		(*envSave)->ExceptionClear(envSave);
//		return NULL;
//	}
//	return class;
//}
//
//jmethodID GetMethodID(jclass className, const char* methodName, const char* signature){
//	jmethodID methodID = (*envSave)->GetMethodID(envSave, className, methodName, signature);
//	if ((*envSave)->ExceptionOccurred(envSave)) {
//		(*envSave)->ExceptionClear(envSave);
//		return NULL;
//	}
//	return methodID;
//}
//
//jmethodID GetStaticMethodID(jclass className, const char* methodName, const char* signature){
//	jmethodID methodID = (*envSave)->GetStaticMethodID(envSave, className, methodName, signature);
//	if ((*envSave)->ExceptionOccurred(envSave)) {
//		(*envSave)->ExceptionClear(envSave);
//		return NULL;
//	}
//	return methodID;
//}
//
//
//jstring getSHA1Digest(jobject context)
//{
//	jclass classLoader = (*envSave)->GetObjectClass(envSave, context);
//	jmethodID getClassLoader = (*envSave)->GetMethodID(envSave, classLoader, "getClassLoader","()Ljava/lang/ClassLoader;");
//	jobject classloader = (*envSave)->CallObjectMethod(envSave, context, getClassLoader);
//    jclass classInvoke = FindClass("com/smilegames/jtc/RefInvoke");
//    if(classInvoke == NULL){
//    	return NULL;
//    }
////    jobjectArray classArray = NULL;
////    jobjectArray objectArray = NULL;
////    if ((*envSave)->ExceptionOccurred(envSave)){
////	if (classInvoke == NULL) {
////		jclass jcError;
////		(*envSave)->ExceptionDescribe(envSave);
////		(*envSave)->ExceptionClear(envSave);
////		jcError = (*envSave)->FindClass(envSave, "java/lang/Exception");
////		(*envSave)->ThrowNew(envSave, jcError, "come from C code.");
////		return NULL;
////	}
////	jmethodID invokeStaticMethod = (*envSave)->GetStaticMethodID(envSave, classInvoke, "invokeStaticMethod", "(Ljava/lang/ClassLoader;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Class;[Ljava/lang/Object;)Ljava/lang/Object;");
//    jmethodID invokeStaticMethod = GetStaticMethodID(classInvoke, "invokeStaticMethod", "(Ljava/lang/ClassLoader;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Class;[Ljava/lang/Object;)Ljava/lang/Object;");
//    if(invokeStaticMethod == NULL){
//    	return NULL;
//    }
//	jstring mm = (*envSave)->NewStringUTF(envSave, "com.example.impl.FunctionImpl");
//	jstring digest = (*envSave)->NewStringUTF(envSave, "realizeFunction");
//	return (jstring) (*envSave)->CallStaticObjectMethod(envSave, classInvoke, invokeStaticMethod, classloader, mm, digest, NULL, NULL);
//}
