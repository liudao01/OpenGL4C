package com.xy.www.opengl4c;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.xy.www.opengl4c.opengl.MySuraceView;
import com.xy.www.opengl4c.opengl.NativeOpengl;

import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "Mainactivity";
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


        //图
        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),
                R.drawable.pikaqiu);
        ByteBuffer fcbuffer = ByteBuffer.allocate(bitmap.getHeight() * bitmap.getWidth() * 4);
        bitmap.copyPixelsToBuffer(fcbuffer);
        fcbuffer.flip();
        byte[] pixels = fcbuffer.array();
        Log.e(TAG, "initView: pixels " + pixels.length);
        nativeOpengl.imgData(bitmap.getWidth(), bitmap.getHeight(), pixels.length, pixels);
    }
}
