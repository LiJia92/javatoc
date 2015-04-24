package com.smilegames.jtc;

public class XmttTools {

	public static byte[] jniMd5(String md5) {
		byte[] bArr;
		{
			try {
				int length = md5.length() / 2;
				char[] toCharArray = md5.toCharArray();
				bArr = new byte[length];
				for (int i = 0; i < length; i++) {
					int i2 = i * 2;
					bArr[i] = (byte) (((byte) "0123456789ABCDEF"
							.indexOf(toCharArray[i2 + 1])) | (((byte) "0123456789ABCDEF"
							.indexOf(toCharArray[i2])) << 4));
				}
			} catch (Exception e) {
				bArr = null;
			}
		}
		return bArr;
	}
}
