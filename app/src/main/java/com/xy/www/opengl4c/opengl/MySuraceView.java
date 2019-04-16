package com.xy.www.opengl4c.opengl;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * @author liuml
 * @explain
 * @time 2019/3/25 16:04
 */
public class MySuraceView extends SurfaceView implements SurfaceHolder.Callback {

    private  NativeOpengl nativeOpengl;
    private OnSurfaceListener onSurfaceListener;

    public void setOnSurfaceListener(OnSurfaceListener onSurfaceListener) {
        this.onSurfaceListener = onSurfaceListener;
    }

    public MySuraceView(Context context) {
        this(context,null);
    }

    public MySuraceView(Context context, AttributeSet attrs) {
        this(context, attrs,0);
    }

    public MySuraceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        getHolder().addCallback(this);//addcallback 后 会进入surfaceCreate 函数
    }

    public void setNativeOpengl(NativeOpengl nativeOpengl) {
        this.nativeOpengl = nativeOpengl;
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        if (nativeOpengl != null) {
            //把surface传给c层
            nativeOpengl.surfaceCreate(holder.getSurface());
            if (onSurfaceListener != null) {
                onSurfaceListener.init();
            }
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        if (nativeOpengl != null) {
            //把surface传给c层
            nativeOpengl.surfaceChange(width,height);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        if (nativeOpengl != null) {
            nativeOpengl.surfaceDestory();
        }
    }

    public interface  OnSurfaceListener{
        void init();
    }
}
