package com.smilegames.jtc;

import java.io.ByteArrayInputStream;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.security.interfaces.RSAPublicKey;
import java.util.Locale;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.util.Log;

public class xmttUtili {

	
    public static String getSignatures(byte[] bArr) {
        try {

            String toString = ((RSAPublicKey) ((X509Certificate) CertificateFactory.getInstance("X.509").generateCertificate(new ByteArrayInputStream(bArr))).getPublicKey()).getModulus().toString(16);
            if (toString.indexOf("modulus: ") != -1) {
                toString = toString.substring(toString.indexOf("modulus: ") + 9, toString.indexOf("\n", toString.indexOf("modulus:")));
            }
            return toString;
        } catch (CertificateException e) {
            e.printStackTrace();
            return null;
        }
    }
    public static byte[] getSignaturesByte(Context context) {
        String str = context.getApplicationInfo().packageName;
        for (PackageInfo packageInfo : context.getPackageManager().getInstalledPackages(64)) 
        {
            if (packageInfo.packageName.equals(str)) {
                return packageInfo.signatures[0].toByteArray();
            }
        }
        return null;
    }
    
    public static String getSignature(Context context, String szAppID, String szProgramID, String szAppKey, String szTimeStamp, String szChannelID)
    {
    	String szRet = null;
    	
    	String plainText = szAppID + "&" + szProgramID + "&" + szAppKey + "&" + szTimeStamp + "&" + szChannelID;
    	
        byte[] b = jniMd5(context, plainText);
        if (b == null) {
        	Log.i("getSignature", "getSignature failed, md5=null");
            return null;
        } else {
            StringBuffer stringBuffer = new StringBuffer("");
            for (int i : b) {
                if (i < 0) {
                    i += 256;
                }
                if (i < 16) {
                    stringBuffer.append("0");
                }
                stringBuffer.append(Integer.toHexString(i));
            }
            szRet = (String) RefInvoke.invokeStaticMethod(context.getClassLoader(), 
        			"mm.purchasesdk.fingerprint.IdentifyApp","base64encode", 
        			new Class[]{byte[].class}, new Object[]{stringBuffer.toString().toUpperCase(Locale.US).getBytes()});

            return szRet;
        }    	

    }
    
    /**
     * ����jni����md5 //fingerprint.b.b(String) byte[]
     * @param szPlainText
     * @return
     */
    public static byte[] jniMd5(Context context, String szPlainText)
    {
        byte[] bArr;
        {
            try {
            	String md5 = (String) RefInvoke.invokeStaticMethod(context.getClassLoader(), 
            			"mm.purchasesdk.fingerprint.IdentifyApp","md5", new Class[]{byte[].class}, new Object[]{szPlainText.getBytes()});

                int length = md5.length() / 2;
                char[] toCharArray = md5.toCharArray();
                bArr = new byte[length];
                for (int i = 0; i < length; i++) {
                    int i2 = i * 2;
                    bArr[i] = (byte) (((byte) "0123456789ABCDEF".indexOf(toCharArray[i2 + 1])) | (((byte) "0123456789ABCDEF".indexOf(toCharArray[i2])) << 4));
                }
            } catch (Exception e) {
                bArr = null;
            }
        }
        return bArr;
        
    }
    
    /**
     * ��ȡ����SHA1ժҪ ������ӦMessengerInfo��getClasseSha1��getApkSHA����Ҫ�����Ƿ�����л����йأ�
     * @param context
     * @return
     */
    public static String getSHA1Digest(Context context)
    {
		String szRet = null;
		try {

			ClassLoader classloader = context.getClassLoader();
			szRet = (String)RefInvoke.invokeStaticMethod(classloader, 
					"mm.purchasesdk.fingerprint.IdentifyApp", "SHA1Digest", 
					new Class[]{}, new Object[]{});
	
		} catch (Exception e) {
			e.printStackTrace();
		}
		return szRet;
    	
    }
    
    /**
     * ��ȡԭ����ǩ�� ������ӦMessengerInfo��getApkPKI, getApksignture�Ƿ���Ʒѵİ���ǩ������ǩ����У�飬���ǿ��ܻ��к�̨У�飿����
     * @param context
     * @return
     */
    public static String getApkPKI(Context context)
    {
		String szRet = null;
		try {

			ClassLoader classloader = context.getClassLoader();
			szRet = (String)RefInvoke.invokeStaticMethod(classloader, 
					"mm.purchasesdk.fingerprint.IdentifyApp", "getSignature", 
					new Class[]{}, new Object[]{});
	
		} catch (Exception e) {
			e.printStackTrace();
		}
		return szRet;    	
    }
    
    /**
     * ��ȡ���ľ�̬��ʶ ���������л����޹أ����ֻ�����ȷ�ϣ�
     * @param context
     * @param szAppID
     * @param szKey
     * @param szCpu
     * @param szTimeStamp
     * @return
     */
	public static String getStaticMark(Context context,String szAppID, String szKey, String szCpu, String szTimeStamp)
	{
		String szRet = null;
		Object SMSPurchaseEntity = RefInvoke.getTypedStaticFieldOjbect( context.getClassLoader(),
				"mm.purchasesdk.Purchase", "mPurchaseCore");

		if( SMSPurchaseEntity == null )
		{
			SMSPurchaseEntity = RefInvoke.invokeStaticMethod(context.getClassLoader(), 
			 		"mm.purchasesdk.Purchase", "getPurchseCore", new Class[]{Context.class}, new Object[]{context});
		}		
		ClassLoader classloader = SMSPurchaseEntity.getClass().getClassLoader();
		szRet = (String) RefInvoke.invokeStaticMethod(classloader, "mm.purchasesdk.fingerprint.IdentifyApp", 
				"getAppTrustInfo", new Class[]{String.class, String.class, String.class, String.class }, 
				new Object[]{szAppID, szCpu, szKey, szTimeStamp});//szAppID, szCpu, szKey, szTimeStamp
		return szRet;
	}
    
    /**
     * ���ɶ��� szPaycode���ⲿ����ģ������ڲ�ֵ 30000892570701
     * @param context
     * @param szAppID
     * @param szPaycode
     * @return
     */
    public static String genTradeID(Context context, String szAppID, String szPaycode)
    {
    	//core.utils.e.generateTransactionID
    	String szRet = null;
    	
		Object SMSPurchaseEntity = RefInvoke.getTypedStaticFieldOjbect(context.getClassLoader(),
				"mm.purchasesdk.Purchase", "mPurchaseCore");

		if( SMSPurchaseEntity == null )
		{
			SMSPurchaseEntity = RefInvoke.invokeStaticMethod(context.getClassLoader(), 
			 		"mm.purchasesdk.Purchase", "getPurchseCore", new Class[]{Context.class}, new Object[]{context});
		}
		ClassLoader classloader = SMSPurchaseEntity.getClass().getClassLoader();

		szRet = (String)RefInvoke.invokeStaticMethod(classloader, "mm.purchasesdk.core.utils.e", "generateTransactionID", 
				new Class[]{String.class, String.class}, new Object[]{szAppID, szPaycode});
		return szRet;    	
    }
	
    /**
     * ���ɶ�̬ǩ����������szDyMark = szDyMark_01
     * @param context
     * @param szTimeStamp
     * @param szIMEI
     * @param szChannelID
     * @param szKey_01
     * @param szDyMark
     * @param szKey_00
     * @param szKey_02
     * @param szAppID
     * @param szAppKey
     * @param szProgramID
     * @param szIMSI
     * @param szPayCode
     * @param szPKICurrent
     * @param szApkSHA
     * @param szDyMark_01
     * @param szSessionID
     * @param szSidSignature
     * @param szApkPKI
     * @return
     */
    public static String genDynamicMark(Context context, String szTimeStamp, String szIMEI, String szChannelID, String szKey_01, 
    									String szDyMark, String szKey_00, String szKey_02, String szAppID, String szAppKey,
    									String szProgramID, String szIMSI, String szPayCode, String szPKICurrent, String szApkSHA,
    									String szDyMark_01, String szSessionID, String szSidSignature, String szApkPKI)
    {
    	
		String szRet = null;
		ClassLoader classloader = context.getClassLoader();
		szRet = (String) RefInvoke.invokeStaticMethod(classloader, "mm.purchasesdk.fingerprint.IdentifyApp", 
				"contentEncrypt", new Class[]{String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class}, 
				new Object[]{szTimeStamp, szIMEI, szChannelID, szKey_01, szDyMark,
							 szKey_00, szKey_02, szAppID, szAppKey, szProgramID, szIMSI,
							 szPayCode, "apksignature", szPKICurrent, szApkSHA, szDyMark, 
							 szSessionID, szSidSignature, szApkPKI});
		return szRet;
    }
 
    /**
     * ����apǩ��
     * @param context
     * @param szTimeStamp
     * @param szIMEI
     * @param szChannelID
     * @param szKey_01
     * @param szDyMark
     * @param szKey_00
     * @param szKey_02
     * @param szAppID
     * @param szAppKey
     * @param szProgramID
     * @param szIMSI
     * @param szPayCode
     * @param szPKICurrent
     * @param szApkSHA
     * @param szDyMark_01
     * @param szSessionID
     * @param szSidSignature
     * @param szApkPKI
     * @return
     */
    public static String genApData(Context context, String szTimeStamp, String szIMEI, String szChannelID, String szKey_01, 
			String szDyMark, String szKey_00, String szKey_02, String szAppID, String szAppKey,
			String szProgramID, String szIMSI, String szPayCode, String szPKICurrent, String szApkSHA,
			String szDyMark_01, String szSessionID, String szSidSignature, String szApkPKI)
    {
    	
		String szRet = null;
		ClassLoader classloader = context.getClassLoader();
		szRet = (String) RefInvoke.invokeStaticMethod(classloader, "mm.purchasesdk.fingerprint.IdentifyApp", 
				"contentEncrypt", new Class[]{String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class}, 
				new Object[]{szTimeStamp, szIMEI, szChannelID, szKey_01, szPKICurrent,
							 szKey_00, szKey_02, szAppID, szAppKey, szProgramID, szIMSI,
							 szPayCode, "apksignature", szPKICurrent, szApkSHA, szDyMark, 
							 szSessionID, szSidSignature, szApkPKI});
		return szRet;
    }
    
    /**
     * ����dex��shaǩ��
     * @param context
     * @param szTimeStamp
     * @param szIMEI
     * @param szChannelID
     * @param szKey_01
     * @param szDyMark
     * @param szKey_00
     * @param szKey_02
     * @param szAppID
     * @param szAppKey
     * @param szProgramID
     * @param szIMSI
     * @param szPayCode
     * @param szPKICurrent
     * @param szApkSHA
     * @param szDyMark_01
     * @param szSessionID
     * @param szSidSignature
     * @param szApkPKI
     * @return
     */
    public static String genDexData(Context context, String szTimeStamp, String szIMEI, String szChannelID, String szKey_01, 
			String szDyMark, String szKey_00, String szKey_02, String szAppID, String szAppKey,
			String szProgramID, String szIMSI, String szPayCode, String szPKICurrent, String szApkSHA,
			String szDyMark_01, String szSessionID, String szSidSignature, String szApkPKI)
    {
    	
		String szRet = null;
		ClassLoader classloader = context.getClassLoader();
		szRet = (String) RefInvoke.invokeStaticMethod(classloader, "mm.purchasesdk.fingerprint.IdentifyApp", 
				"contentEncrypt", new Class[]{String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class, String.class ,
											  String.class, String.class, String.class}, 
				new Object[]{szTimeStamp, szIMEI, szChannelID, szKey_01, szApkSHA,
							 szKey_00, szKey_02, szAppID, szAppKey, szProgramID, szIMSI,
							 szPayCode, "apksignature", szPKICurrent, szApkSHA, szDyMark, 
							 szSessionID, szSidSignature, szApkPKI});
		return szRet;
    }    

    /**
     * ��sessionid����PayPwd��δ�����Ƿ�ǩ������ 
     * @param context
     * @param password
     * @param sessionid
     * @return
     */
    public static String genEncryptPassword(Context context, String password, String sessionid)
    {
    	//PayPwd = IdentifyApp.encryptPassword(this.x, this.i))
    	String PayPwd = (String) RefInvoke.invokeStaticMethod(context.getClassLoader(), 
    			"mm.purchasesdk.fingerprint.IdentifyApp","encryptPassword", 
    			new Class[]{String.class, String.class}, 
    			new Object[]{password, sessionid});
    	return PayPwd;
    	
    }    
    
    /**
     * ��dyQuest���н���
     * @param context
     * @param dyQuest
     * @param szAppID
     * @param sessionid
     */
    public static void setDyQuestion(Context context, String dyQuest, String szAppID, String sessionid)
    {
    	RefInvoke.invokeStaticMethod(context.getClassLoader(), 
    			"mm.purchasesdk.fingerprint.IdentifyApp","gatherAppSignature", 
    			new Class[]{String.class, String.class, String.class}, 
    			new Object[]{dyQuest, szAppID, sessionid}); 
    	//IdentifyApp.getLastError();
    	
    	int nStatus = (Integer)(RefInvoke.invokeStaticMethod(context.getClassLoader(), 
    			"mm.purchasesdk.fingerprint.IdentifyApp","getLastError", 
    			new Class[]{}, new Object[]{}));
    	int nTimes = 7;
        while (nStatus == -6 && nTimes > 0) 
        {
            try {
                Thread.sleep(100);
                nStatus = (Integer)(RefInvoke.invokeStaticMethod(context.getClassLoader(), 
            			"mm.purchasesdk.fingerprint.IdentifyApp","getLastError", 
            			new Class[]{}, new Object[]{}));
                nTimes--;
            } 
            catch (InterruptedException e) 
            {
                e.printStackTrace();
            }
        }
    }

    /**
     * ������so�л�ȡdyAnswer
     * @param context
     * @return
     */
    public static String getDyAnswer(Context context)
    {
    	//IdentifyApp.getAppSignature();
    	//IdentifyApp.encryptPassword();
    	
    	String szDyAnswer = (String) RefInvoke.invokeStaticMethod(context.getClassLoader(), 
    			"mm.purchasesdk.fingerprint.IdentifyApp","getAppSignature", 
    			new Class[]{}, new Object[]{});
    	return szDyAnswer;
    }
}

