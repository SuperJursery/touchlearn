package com.jursery.app.touchlearn;

public class TouchLearnUtils {
	public static final int CONFIRM_CONFIG = 0x1000;
	public static final int CORRECT_ORIGIN = 0x1001;
	public static final int CORRECT_KEY = 0x1002;
	public static final int CLEAR_KEY = 0x1003;
	
    static {
        System.loadLibrary("jni_touchlearn");
    }
    public static String GetKernelVersion(){
        return nativeGetKernelVersion();
    }
	public static int SetTsConfig(String configName){
		return nativeSetTsConfig(configName);
	}
	public static int GetTsConfig(String path){
		return nativeGetTsConfig(path);
	}
	public static int CorrectTsConfig(int action){
		return nativeCorrectTsConfig(action);
	}
	public static int UseTsConfig(String configName){
		return nativeUseTsConfig(configName);
	}
	public static int IsTouchScreenChanged(){
		return nativeIsTouchScreenChanged();
	}

    private static native String nativeGetKernelVersion();
    private static native int nativeSetTsConfig(String configName);
    private static native int nativeGetTsConfig(String path);
    private static native int nativeCorrectTsConfig(int action);
    private static native int nativeUseTsConfig(String configName);
	private static native int nativeIsTouchScreenChanged();
}
