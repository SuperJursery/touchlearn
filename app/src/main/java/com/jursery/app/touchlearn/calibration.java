package com.jursery.app.touchlearn;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class calibration extends AppCompatActivity {
    private ImageView tc_left;
    private ImageView tc_top;
    private ImageView tc_right;
    private ImageView tc_bottom;
    private TextView txv_comfirm;
    private int step;
    private TouchLearnDebug debug_obj;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.calibration_layout);
        debug_obj = (TouchLearnDebug)getApplicationContext();
        tc_left = (ImageView)this.findViewById(R.id.tc_left);
        tc_top = (ImageView)this.findViewById(R.id.tc_top);
        tc_right = (ImageView)this.findViewById(R.id.tc_right);
        tc_bottom = (ImageView)this.findViewById(R.id.tc_bottom);
        txv_comfirm = (TextView)this.findViewById(R.id.txv_comfirm) ;
        Toast.makeText(calibration.this,"Please touch left target!", Toast.LENGTH_SHORT).show();
        step = 1;
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        switch (ev.getAction()) {
            case MotionEvent.ACTION_UP:
                debug_obj.debug_toast_short("Here coordinate X x Y :"+ev.getX()+" x "+ev.getY());
                //Toast.makeText(calibration.this, "Here coordinate X x Y :"+ev.getX()+" x "+ev.getY(), Toast.LENGTH_SHORT).show();
                step_work(step);
                step++;
                break;
             default:
                break;
        }
        return super.dispatchTouchEvent(ev);
    }

    private void step_work(int step) {
        switch(step) {
            case 1:
                tc_left.setVisibility(View.GONE);
                tc_top.setVisibility(View.VISIBLE);
                Toast.makeText(calibration.this,"Please touch top target!", Toast.LENGTH_SHORT).show();
                break;
            case 2:
                tc_top.setVisibility(View.GONE);
                tc_right.setVisibility(View.VISIBLE);
                Toast.makeText(calibration.this,"Please touch right target!", Toast.LENGTH_SHORT).show();
                break;
            case 3:
                tc_right.setVisibility(View.GONE);
                tc_bottom.setVisibility(View.VISIBLE);
                Toast.makeText(calibration.this,"Please touch bottom target!", Toast.LENGTH_SHORT).show();
                break;
            case 4:
                tc_bottom.setVisibility(View.GONE);
                txv_comfirm.setVisibility(View.VISIBLE);
                break;
             default:
                 Toast.makeText(calibration.this, "Comfirm success!", Toast.LENGTH_SHORT).show();
                 Intent intent = new Intent();
                 intent.setClass(calibration.this, TouchconfigMenu.class);
                 startActivity(intent);
                 finish();
                 break;
        }
    }
}
