package com.jursery.app.touchlearn;

import android.app.Application;
import android.content.Context;
import android.widget.Toast;

public class TouchLearnDebug extends Application {
    public static boolean debug_mask = false;

    public void debug_toast_short(String str){
        if(debug_mask)
            Toast.makeText(TouchLearnDebug.this, str, Toast.LENGTH_SHORT).show();
    }
    public void checksystem(){
        String rst_msg;
        rst_msg = TouchLearnUtils.GetKernelVersion();
        Toast.makeText(TouchLearnDebug.this, rst_msg, Toast.LENGTH_SHORT).show();

    }
}
