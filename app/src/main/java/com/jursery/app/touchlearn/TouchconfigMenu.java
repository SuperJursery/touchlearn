package com.jursery.app.touchlearn;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

public class TouchconfigMenu extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);

        Button btn_cab = (Button) this.findViewById(R.id.btn_cab);
        btn_cab.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View V){
                //显式方式 切换activity
                Intent intent = new Intent();
                intent.setClass(TouchconfigMenu.this, calibration.class);
                startActivity(intent);
            }
        });
    }
}
