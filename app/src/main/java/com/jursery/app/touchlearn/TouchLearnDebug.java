package com.jursery.app.touchlearn;

import android.app.Application;
import android.widget.Toast;

public class TouchLearnDebug extends Application {
    public static boolean debug_mask = false;

    public void debug_toast_short(String str){
        if(debug_mask)
            Toast.makeText(TouchLearnDebug.this, str, Toast.LENGTH_SHORT).show();
    }
}
