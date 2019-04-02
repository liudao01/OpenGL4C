package com.xy.www.opengl4c;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.xy.www.opengl4c.opengl.MySuraceView;
import com.xy.www.opengl4c.opengl.NativeOpengl;

public class MainActivity extends AppCompatActivity {
    private MySuraceView mySurfaceview;

    private NativeOpengl nativeOpengl;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
    }

    private void initView() {
        mySurfaceview = findViewById(R.id.my_surfaceview);
        nativeOpengl = new NativeOpengl();
        mySurfaceview.setNativeOpengl(nativeOpengl);
    }
}
