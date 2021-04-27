package com.jursery.app.touchlearn;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.Toast;

public class TouchconfigMenu extends AppCompatActivity {
    private TouchLearnDebug debug_obj;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);

        debug_obj = (TouchLearnDebug)getApplicationContext();;
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
        CheckBox debug_mode = (CheckBox)this.findViewById(R.id.debug_mode);
        debug_mode.setOnCheckedChangeListener(
                new CompoundButton.OnCheckedChangeListener() {
                    @Override
                    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                        debug_obj.debug_mask = isChecked;
                        if (isChecked) {
                            debug_obj.checksystem();
                        }
                    }
                }
        );
    }
}
