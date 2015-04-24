package com.example.call;

import android.content.Context;

public class InitJNI {
	
	public static native byte[] init(Context context, String param) throws Exception;

}
