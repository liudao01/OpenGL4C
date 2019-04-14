//
// Created by liuml on 2019/4/14.
//

#include "OpenglControl.h"


/**
 * create 回调
 */
void callback_SurfaceCreate(void *ctx) {

}

/**
 * change 回调
 */
void callback_SurfaceChange(int width, int height, void *ctx) {

}

/**
 * draw
 */
void callback_SurfaceOndraw(void *ctx) {

}

OpenglControl::OpenglControl() {

}

OpenglControl::~OpenglControl() {

}


void OpenglControl::onCreateSurface(JNIEnv *env, jobject surface) {

    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new XYEglThread();

    eglThread->setRenderType(OPENGL_RENDER_HANDLE);
    eglThread->callBackOnCreate(callback_SurfaceCreate, eglThread);
    eglThread->callBackOnChange(callback_SurfaceChange, eglThread);
    eglThread->callBackOnDraw(callback_SurfaceOndraw, eglThread);

    //base
    baseOpengl = new FilterOne();

    eglThread->onSurfaceCreate(nativeWindow);

}

void OpenglControl::onChangeSurface(int width, int height) {

}


void OpenglControl::onDestorySurface() {

}

