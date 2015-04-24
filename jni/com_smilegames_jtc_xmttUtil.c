#include <android/log.h>
#include <stdio.h>
#include <string.h>

static JNIEnv *envSave;

static jobject classLoader = NULL; //ClassLoader对象
static jclass classInvoke = NULL; //RefInvoke类
static jmethodID invokeStaticMethodID = NULL; //invokeStaticMethod方法ID
static jmethodID getTypedStaticFieldOjbectID = NULL; //getTypedStaticFieldOjbect方法ID

const char* paramArray[] = { "mm.purchasesdk.fingerprint.IdentifyApp",
		"base64encode", "md5", "SHA1Digest", "getSignature", "getAppTrustInfo",
		"contentEncrypt", "encryptPassword", "gatherAppSignature",
		"getLastError",
		"getAppSignature", //10
		"mm.purchasesdk.Purchase", "mPurchaseCore", "getPurchseCore",
		"mm.purchasesdk.core.utils.e", "generateTransactionID" };

//const char* testArray[] = { "com.example.impl.FunctionImpl", "realizeFunction" };
//
//#define COM_EXAMPLE_IMPL_FUNCTIONIMPL testArray[0]
//#define COM_EXAMPLE_IMPL_FUNCTIONIMPL_REALIZEFUNCTION testArray[1]

#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP paramArray[0]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_BASE64ENCODE paramArray[1]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_MD5 paramArray[2]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_SHA1DIGEST paramArray[3]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_GETSIGNATURE paramArray[4]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_GETAPPTRUSTINFO paramArray[5]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_CONTENTENCRYPT paramArray[6]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_ENCRYPTPASSWORD paramArray[7]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_GATHERAPPSIGNATURE paramArray[8]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_GETLASTERROR paramArray[9]
#define MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_GETAPPSIGNATURE paramArray[10]
#define MM_PURCHASESDK_PURCHASE paramArray[11]
#define MM_PURCHASESDK_PURCHASE_MPURCHASECORE paramArray[12]
#define MM_PURCHASESDK_PURCHASE_GETPURCHSECORE paramArray[13]
#define MM_PURCHASESDK_CORE_UTILS_E paramArray[14]
#define MM_PURCHASESDK_CORE_UTILS_E_GENERATETRANSACTIONID paramArray[15]

#define TAG "JaceLi" // 这个是自定义的LOG的标识
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
//通过对象获得类
jclass GetObjectClass(jobject obj) {
	jclass class = (*envSave)->GetObjectClass(envSave, obj);
	if ((*envSave)->ExceptionOccurred(envSave)) {
		(*envSave)->ExceptionClear(envSave);
		return NULL;
	}
	return class;
}

//通过类路径（包含包名）获得类
jclass FindClass(const char* className) {
	jclass class = (*envSave)->FindClass(envSave, className);
	if ((*envSave)->ExceptionOccurred(envSave)) {
		(*envSave)->ExceptionClear(envSave);
		return NULL;
	}
	return class;
}

//获得非静态方法
jmethodID GetMethodID(jclass className, const char* methodName,
		const char* signature) {
	jmethodID methodID = (*envSave)->GetMethodID(envSave, className, methodName,
			signature);
	if ((*envSave)->ExceptionOccurred(envSave)) {
		(*envSave)->ExceptionClear(envSave);
		return NULL;
	}
	return methodID;
}

//获得静态方法
jmethodID GetStaticMethodID(jclass className, const char* methodName,
		const char* signature) {
	jmethodID methodID = (*envSave)->GetStaticMethodID(envSave, className,
			methodName, signature);
	if ((*envSave)->ExceptionOccurred(envSave)) {
		(*envSave)->ExceptionClear(envSave);
		return NULL;
	}
	return methodID;
}

//初始化ClassLoader对象、RefInvoke类、invokeStaticMethod方法ID、getTypedStaticFieldOjbect方法ID
int initInvoke(jobject context) {
	jclass class = GetObjectClass(context);
	if (class == NULL) {
		return 0;
	}
	jmethodID getClassLoader = GetMethodID(class, "getClassLoader",
			"()Ljava/lang/ClassLoader;");
	if (getClassLoader == NULL) {
		return 0;
	}
	classLoader = (*envSave)->CallObjectMethod(envSave, context,
			getClassLoader);
	if ((*envSave)->ExceptionOccurred(envSave)) {
		(*envSave)->ExceptionClear(envSave);
		return 0;
	}
	classInvoke = FindClass("com/smilegames/jtc/RefInvoke");
	if (classInvoke == NULL) {
		return 0;
	}
	invokeStaticMethodID =
			GetStaticMethodID(classInvoke, "invokeStaticMethod",
					"(Ljava/lang/ClassLoader;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Class;[Ljava/lang/Object;)Ljava/lang/Object;");
	if (invokeStaticMethodID == NULL) {
		return 0;
	}
	getTypedStaticFieldOjbectID =
			GetStaticMethodID(classInvoke, "getTypedStaticFieldOjbect",
					"(Ljava/lang/ClassLoader;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
	if (getTypedStaticFieldOjbectID == NULL) {
		return 0;
	}
	return 1;
}

/**
 * md5加密
 */
jbyteArray jniMd5(JNIEnv* env, jobject context, jstring byteArr) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring md5 = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_MD5);
	//创建对应Class[]参数的数组
	jclass paraClass = FindClass("java/lang/Class");
	if (paraClass == NULL) {
		return NULL;
	}
	jobjectArray classArray = (*envSave)->NewObjectArray(envSave, 1, paraClass,
			NULL);
	jclass byteArrClass = FindClass("[B");
	if (byteArrClass == NULL) {
		return NULL;
	}
	(*envSave)->SetObjectArrayElement(envSave, classArray, 0, byteArrClass); //给第一个元素赋值

	//创建对应Object[]参数的数组
	jclass paraObject = FindClass("java/lang/Object");
	if (paraObject == NULL) {
		return NULL;
	}
	jobjectArray objectArray = (*envSave)->NewObjectArray(envSave, 1,
			paraObject, NULL);
	//jstring-->char*-->jbyte-->jbyteArray
	const char* str = (*envSave)->GetStringUTFChars(envSave, byteArr, NULL);
	int len = strlen(str);
	jbyteArray jba = (*envSave)->NewByteArray(envSave, len); //创建jbyteArray
	(*envSave)->SetByteArrayRegion(envSave, jba, 0, len, (jbyte*) str); //给jbyteArray赋值
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 0, jba);

	jobject rtnMd5 = (*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, md5, classArray,
			objectArray);
	//调用java工具类
	jclass toolClass = FindClass("com/smilegames/jtc/XmttTools");
	if (toolClass == NULL) {
		return NULL;
	}
	jmethodID jniMd5ID = GetStaticMethodID(toolClass, "jniMd5",
			"(Ljava/lang/String;)[B");
	if (jniMd5ID == NULL) {
		return NULL;
	}
	return (*envSave)->CallStaticObjectMethod(envSave, toolClass, jniMd5ID,
			(jstring) rtnMd5);
}

/**
 * 获取包的SHA1摘要
 */
jstring getSHA1Digest(JNIEnv* env, jobject context) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring digest = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_SHA1DIGEST);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, digest, NULL, NULL);
}

/**
 * 获取原包的签名
 */
jstring getApkPKI(JNIEnv* env, jobject context) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring getsignature = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_GETSIGNATURE);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, getsignature, NULL,
			NULL);
}

/**
 * 获取包的静态标识
 */
jstring getStaticMark(JNIEnv* env, jobject context, jstring szAppID,
		jstring szKey, jstring szCpu, jstring szTimeStamp) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring purchase = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_PURCHASE);
	jstring mpurchasecore = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_PURCHASE_MPURCHASECORE);
	jobject SMSPurchaseEntity = (*envSave)->CallStaticObjectMethod(envSave,
			classInvoke, getTypedStaticFieldOjbectID, classLoader, purchase,
			mpurchasecore);
	if (SMSPurchaseEntity == NULL) {
		//创建对应Class[]参数的数组
		jclass paraClass = FindClass("java/lang/Class");
		if (paraClass == NULL) {
			return NULL;
		}
		jobjectArray classArray = (*envSave)->NewObjectArray(envSave, 1,
				paraClass, NULL);
		jclass contextClass = FindClass("android/content/Context");
		if (contextClass == NULL) {
			return NULL;
		}
		(*envSave)->SetObjectArrayElement(envSave, classArray, 0, contextClass); //给第一个元素赋值

		//创建对应Object[]参数的数组
		jclass paraObject = FindClass("java/lang/Object");
		if (paraObject == NULL) {
			return NULL;
		}
		jobjectArray objectArray = (*envSave)->NewObjectArray(envSave, 1,
				paraObject, NULL);
		(*envSave)->SetObjectArrayElement(envSave, objectArray, 0, context);
		jstring getpurchsecore = (*envSave)->NewStringUTF(envSave,
				MM_PURCHASESDK_PURCHASE_GETPURCHSECORE);
		SMSPurchaseEntity = (*envSave)->CallStaticObjectMethod(envSave,
				classInvoke, invokeStaticMethodID, classLoader, purchase,
				getpurchsecore, classArray, objectArray);
	}
	jclass SMSClass = GetObjectClass(SMSPurchaseEntity);
	if (SMSClass == NULL) {
		return NULL;
	}
	jmethodID getClassLoader = GetMethodID(SMSClass, "getClassLoader",
			"()Ljava/lang/ClassLoader;");
	if (getClassLoader == NULL) {
		return NULL;
	}
	jobject SMSClassLoader = (*envSave)->CallObjectMethod(envSave,
			SMSPurchaseEntity, getClassLoader);
	if ((*envSave)->ExceptionOccurred(envSave)) {
		(*envSave)->ExceptionClear(envSave);
		return NULL;
	}
	//创建对应Class[]参数的数组
	jclass paramClass1 = FindClass("java/lang/Class");
	if (paramClass1 == NULL) {
		return NULL;
	}
	jobjectArray classArray1 = (*envSave)->NewObjectArray(envSave, 4,
			paramClass1, NULL);
	jclass stringClass = FindClass("java/lang/String");
	if (stringClass == NULL) {
		return NULL;
	}
	int k;
	for (k = 0; k < 3; k++) {
		(*envSave)->SetObjectArrayElement(envSave, classArray1, k, stringClass); //给元素赋值
	}

	//创建对应Object[]参数的数组
	jclass paraObject1 = FindClass("java/lang/Object");
	if (paraObject1 == NULL) {
		return NULL;
	}
	jobjectArray objectArray1 = (*envSave)->NewObjectArray(envSave, 4,
			paraObject1, NULL);
	(*envSave)->SetObjectArrayElement(envSave, objectArray1, 0, szAppID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray1, 1, szKey);
	(*envSave)->SetObjectArrayElement(envSave, objectArray1, 2, szCpu);
	(*envSave)->SetObjectArrayElement(envSave, objectArray1, 3, szTimeStamp);
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring getapptrustinfo = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_GETAPPTRUSTINFO);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, getapptrustinfo,
			classArray1, objectArray1);
}

/**
 * 生成订单
 */
jstring genTradeID(JNIEnv* env, jobject context, jstring szAppID,
		jstring szPaycode) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring purchase = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_PURCHASE);
	jstring mpurchasecore = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_PURCHASE_MPURCHASECORE);
	jobject SMSPurchaseEntity = (*envSave)->CallStaticObjectMethod(envSave,
			classInvoke, getTypedStaticFieldOjbectID, classLoader, purchase,
			mpurchasecore);
	if (SMSPurchaseEntity == NULL) {
		//创建对应Class[]参数的数组
		jclass paraClass = FindClass("java/lang/Class");
		if (paraClass == NULL) {
			return NULL;
		}
		jobjectArray classArray = (*envSave)->NewObjectArray(envSave, 1,
				paraClass, NULL);
		jclass contextClass = FindClass("android/content/Context");
		if (contextClass == NULL) {
			return NULL;
		}
		(*envSave)->SetObjectArrayElement(envSave, classArray, 0, contextClass); //给第一个元素赋值

		//创建对应Object[]参数的数组
		jclass paraObject = FindClass("java/lang/Object");
		if (paraObject == NULL) {
			return NULL;
		}
		jobjectArray objectArray = (*envSave)->NewObjectArray(envSave, 1,
				paraObject, NULL);
		(*envSave)->SetObjectArrayElement(envSave, objectArray, 0, context);
		jstring getpurchsecore = (*envSave)->NewStringUTF(envSave,
				MM_PURCHASESDK_PURCHASE_GETPURCHSECORE);
		SMSPurchaseEntity = (*envSave)->CallStaticObjectMethod(envSave,
				classInvoke, invokeStaticMethodID, classLoader, purchase,
				getpurchsecore, classArray, objectArray);
	}
	jclass SMSClass = GetObjectClass(SMSPurchaseEntity);
	if (SMSClass == NULL) {
		return NULL;
	}
	jmethodID getClassLoader = GetMethodID(SMSClass, "getClassLoader",
			"()Ljava/lang/ClassLoader;");
	if (getClassLoader == NULL) {
		return NULL;
	}
	jobject SMSClassLoader = (*envSave)->CallObjectMethod(envSave,
			SMSPurchaseEntity, getClassLoader);
	if ((*envSave)->ExceptionOccurred(envSave)) {
		(*envSave)->ExceptionClear(envSave);
		return NULL;
	}
	//创建对应Class[]参数的数组
	jclass paramClass1 = FindClass("java/lang/Class");
	if (paramClass1 == NULL) {
		return NULL;
	}
	jobjectArray classArray1 = (*envSave)->NewObjectArray(envSave, 2,
			paramClass1, NULL);
	jclass stringClass = FindClass("java/lang/String");
	if (stringClass == NULL) {
		return NULL;
	}
	int k;
	for (k = 0; k < 2; k++) {
		(*envSave)->SetObjectArrayElement(envSave, classArray1, k, stringClass); //给元素赋值
	}

	//创建对应Object[]参数的数组
	jclass paraObject1 = FindClass("java/lang/Object");
	if (paraObject1 == NULL) {
		return NULL;
	}
	jobjectArray objectArray1 = (*envSave)->NewObjectArray(envSave, 2,
			paraObject1, NULL);
	(*envSave)->SetObjectArrayElement(envSave, objectArray1, 0, szAppID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray1, 1, szPaycode);
	jstring e = (*envSave)->NewStringUTF(envSave, MM_PURCHASESDK_CORE_UTILS_E);
	jstring generatetransactionid = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_CORE_UTILS_E_GENERATETRANSACTIONID);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, e, generatetransactionid,
			classArray1, objectArray1);
}

/**
 * 生成动态签名
 */
jstring genDynamicMark(JNIEnv* env, jobject context, jstring szTimeStamp,
		jstring szIMEI, jstring szChannelID, jstring szKey_01, jstring szDyMark,
		jstring szKey_00, jstring szKey_02, jstring szAppID, jstring szAppKey,
		jstring szProgramID, jstring szIMSI, jstring szPayCode,
		jstring szPKICurrent, jstring szApkSHA, jstring szDyMark_01,
		jstring szSessionID, jstring szSidSignature, jstring szApkPKI) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring contentencrypt = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_CONTENTENCRYPT);
	jclass paraClass = FindClass("java/lang/Class");
	if (paraClass == NULL) {
		return NULL;
	}
	jobjectArray classArray = (*envSave)->NewObjectArray(envSave, 19, paraClass,
			NULL);
	jclass stringClass = FindClass("java/lang/String");
	if (stringClass == NULL) {
		return NULL;
	}
	int k;
	for (k = 0; k < 19; k++) {
		(*envSave)->SetObjectArrayElement(envSave, classArray, k, stringClass); //给第一个元素赋值
	}

	//创建对应Object[]参数的数组
	jclass paraObject = FindClass("java/lang/Object");
	if (paraObject == NULL) {
		return NULL;
	}
	jobjectArray objectArray = (*envSave)->NewObjectArray(envSave, 1,
			paraObject, NULL);
	jstring apksignature = (*envSave)->NewStringUTF(envSave, "apksignature");
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 0, szTimeStamp);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 1, szIMEI);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 2, szChannelID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 3, szKey_01);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 4, szDyMark);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 5, szKey_00);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 6, szKey_02);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 7, szAppID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 8, szAppKey);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 9, szProgramID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 10, szIMSI);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 11, szPayCode);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 12, apksignature);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 13, szPKICurrent);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 14, szApkSHA);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 15, szDyMark);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 16, szSessionID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 17, szSidSignature);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 18, szApkPKI);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, contentencrypt,
			classArray, objectArray);
}

/**
 * 加密ap签名
 */
jstring genApData(JNIEnv* env, jobject context, jstring szTimeStamp, jstring szIMEI, jstring szChannelID, jstring szKey_01,
		jstring szDyMark, jstring szKey_00, jstring szKey_02, jstring szAppID, jstring szAppKey,
		jstring szProgramID, jstring szIMSI, jstring szPayCode, jstring szPKICurrent, jstring szApkSHA,
		jstring szDyMark_01, jstring szSessionID, jstring szSidSignature, jstring szApkPKI) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring contentencrypt = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_CONTENTENCRYPT);
	jclass paraClass = FindClass("java/lang/Class");
	if (paraClass == NULL) {
		return NULL;
	}
	jobjectArray classArray = (*envSave)->NewObjectArray(envSave, 19, paraClass,
			NULL);
	jclass stringClass = FindClass("java/lang/String");
	if (stringClass == NULL) {
		return NULL;
	}
	int k;
	for (k = 0; k < 19; k++) {
		(*envSave)->SetObjectArrayElement(envSave, classArray, k, stringClass); //给第一个元素赋值
	}

	//创建对应Object[]参数的数组
	jclass paraObject = FindClass("java/lang/Object");
	if (paraObject == NULL) {
		return NULL;
	}
	jobjectArray objectArray = (*envSave)->NewObjectArray(envSave, 1,
			paraObject, NULL);
	jstring apksignature = (*envSave)->NewStringUTF(envSave, "apksignature");
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 0, szTimeStamp);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 1, szIMEI);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 2, szChannelID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 3, szKey_01);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 4, szDyMark);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 5, szKey_00);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 6, szKey_02);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 7, szAppID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 8, szAppKey);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 9, szProgramID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 10, szIMSI);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 11, szPayCode);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 12, apksignature);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 13, szPKICurrent);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 14, szApkSHA);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 15, szDyMark);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 16, szSessionID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 17, szSidSignature);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 18, szApkPKI);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, contentencrypt,
			classArray, objectArray);
}

/**
 * 加密dex的sha签名
 */
jstring genDexData(JNIEnv* env, jobject context, jstring szTimeStamp, jstring szIMEI, jstring szChannelID, jstring szKey_01,
		jstring szDyMark, jstring szKey_00, jstring szKey_02, jstring szAppID, jstring szAppKey,
		jstring szProgramID, jstring szIMSI, jstring szPayCode, jstring szPKICurrent, jstring szApkSHA,
		jstring szDyMark_01, jstring szSessionID, jstring szSidSignature, jstring szApkPKI) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring contentencrypt = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_CONTENTENCRYPT);
	jclass paraClass = FindClass("java/lang/Class");
	if (paraClass == NULL) {
		return NULL;
	}
	jobjectArray classArray = (*envSave)->NewObjectArray(envSave, 19, paraClass,
			NULL);
	jclass stringClass = FindClass("java/lang/String");
	if (stringClass == NULL) {
		return NULL;
	}
	int k;
	for (k = 0; k < 19; k++) {
		(*envSave)->SetObjectArrayElement(envSave, classArray, k, stringClass); //给第一个元素赋值
	}

	//创建对应Object[]参数的数组
	jclass paraObject = FindClass("java/lang/Object");
	if (paraObject == NULL) {
		return NULL;
	}
	jobjectArray objectArray = (*envSave)->NewObjectArray(envSave, 19,
			paraObject, NULL);
	jstring apksignature = (*envSave)->NewStringUTF(envSave, "apksignature");
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 0, szTimeStamp);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 1, szIMEI);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 2, szChannelID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 3, szKey_01);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 4, szDyMark);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 5, szKey_00);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 6, szKey_02);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 7, szAppID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 8, szAppKey);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 9, szProgramID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 10, szIMSI);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 11, szPayCode);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 12, apksignature);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 13, szPKICurrent);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 14, szApkSHA);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 15, szDyMark);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 16, szSessionID);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 17, szSidSignature);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 18, szApkPKI);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, contentencrypt,
			classArray, objectArray);
}

/**
 *  用sessionid生成PayPwd
 */
jstring genEncryptPassword(JNIEnv* env, jobject context, jstring password, jstring sessionid) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring encryptpassword = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_ENCRYPTPASSWORD);
	jclass paraClass = FindClass("java/lang/Class");
	if (paraClass == NULL) {
		return NULL;
	}
	jobjectArray classArray = (*envSave)->NewObjectArray(envSave, 2, paraClass,
			NULL);
	jclass stringClass = FindClass("java/lang/String");
	if (stringClass == NULL) {
		return NULL;
	}
	int k;
	for (k = 0; k < 2; k++) {
		(*envSave)->SetObjectArrayElement(envSave, classArray, k, stringClass); //给第一个元素赋值
	}

	//创建对应Object[]参数的数组
	jclass paraObject = FindClass("java/lang/Object");
	if (paraObject == NULL) {
		return NULL;
	}
	jobjectArray objectArray = (*envSave)->NewObjectArray(envSave, 2,
			paraObject, NULL);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 0, password);
	(*envSave)->SetObjectArrayElement(envSave, objectArray, 1, sessionid);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, encryptpassword,
			classArray, objectArray);
}

/**
 * 解码后从so中获取dyAnswer
 */
jstring getDyAnswer(JNIEnv* env, jobject context) {
	envSave = env;
	if (initInvoke(context) == 0) {
		return NULL;
	}
	jstring identifyapp = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP);
	jstring digest = (*envSave)->NewStringUTF(envSave,
			MM_PURCHASESDK_FINGERPRINT_IDENTIFYAPP_GETAPPSIGNATURE);
	return (jstring)(*envSave)->CallStaticObjectMethod(envSave, classInvoke,
			invokeStaticMethodID, classLoader, identifyapp, digest, NULL, NULL);
}
