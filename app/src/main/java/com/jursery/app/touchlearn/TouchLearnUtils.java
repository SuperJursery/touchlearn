package com.jursery.app.touchlearn;

public class TouchLearnUtils {
    static {
        System.loadLibrary("jni_touchlearn");
    }
    public static String GetKernelVersion(){
        return nativeGetKernelVersion();
    }
    private static native String nativeGetKernelVersion();
}
