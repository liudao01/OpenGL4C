package com.xy.www.opengl4c.opengl;

import android.view.Surface;

/**
 * @author liuml
 * @explain
 * @time 2019/3/25 15:48
 */
public class NativeOpengl {
    static {
        System.loadLibrary("native-lib");
    }

    public native void surfaceCreate(Surface surface);

    public native void surfaceChange(int width, int height);

    //length data的长度
    public native void imgData(int width, int height,int length,byte[] data);

}

