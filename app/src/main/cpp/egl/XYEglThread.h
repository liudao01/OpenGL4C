//
// Created by liuml on 2019/3/26.
//

#ifndef OPENGL4C_WLEGLTHREAD_H
#define OPENGL4C_WLEGLTHREAD_H

#include <pthread.h>
#include <EGL/eglplatform.h>
#import "XYEglHelper.h"
#include <unistd.h>

#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>

#include <GLES2/gl2.h>

#define OPENGL_RENDER_AUTO 1
#define OPENGL_RENDER_HANDLE 2

class XYEglThread {

public :
    pthread_t eglThread = -1;
    ANativeWindow *nativeWindow = NULL;

    bool isCreate = false;
    bool isChange = false;
    bool isExit = false;
    bool isStart = false;

    int surfaceWidth = 0;
    int surfaceHeight = 0;

    typedef void(*OnCreate)(void *);

    OnCreate onCreate;
    void *onCreateCtx;

    typedef void(*OnChange)(int width, int height, void *);

    OnChange onChange;
    void *onChangeCtx;


    typedef void(*OnDraw)(void *);

    OnDraw onDraw;
    void *onDrawCtx;

    //渲染模式
    int renderType = OPENGL_RENDER_AUTO;

    //互斥锁
    pthread_mutex_t pthread_mutex;
    pthread_cond_t pthread_cond;



public:
    XYEglThread();

    ~XYEglThread();

    void onSurfaceCreate(EGLNativeWindowType window);

    void onSurfaceChange(int width, int height);

    void callBackOnCreate(OnCreate onCreate1, void *ctx);

    void callBackOnChange(OnChange onChange1, void *ctx);

    void callBackOnDraw(OnDraw onDraw1, void *ctx);

    void setRenderType(int renderType);

    void notifyRender();

    void destory();
};


#endif //OPENGL4C_WLEGLTHREAD_H
