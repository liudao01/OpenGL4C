//
// Created by liuml on 2019/4/14.
//

#include "OpenglControl.h"


/**
 * create 回调
 */
void callback_SurfaceCreate(void *ctx) {

    OpenglControl *openglControl = static_cast<OpenglControl *>(ctx);
    if (openglControl != NULL) {
        if (openglControl->baseOpengl != NULL) {
            openglControl->baseOpengl->onCreate();//实际调用了base 里面的oncreate方法 最终调用FilterOne 的oncreate
        }
    }

}

/**
 * change 回调
 */
void callback_SurfaceChange(int width, int height, void *ctx) {
    OpenglControl *openglControl = static_cast<OpenglControl *>(ctx);
    if (openglControl != NULL) {
        if (openglControl->baseOpengl != NULL) {
            openglControl->baseOpengl->onChange(width,height);
        }
    }


}

/**
 * draw
 */
void callback_SurfaceOndraw(void *ctx) {
    OpenglControl *openglControl = static_cast<OpenglControl *>(ctx);
    if (openglControl != NULL) {
        if (openglControl->baseOpengl != NULL) {
            openglControl->baseOpengl->onDraw();
        }
    }

}

OpenglControl::OpenglControl() {

}

OpenglControl::~OpenglControl() {

}


void OpenglControl::onCreateSurface(JNIEnv *env, jobject surface) {

    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new XYEglThread();

    eglThread->setRenderType(OPENGL_RENDER_HANDLE);
    eglThread->callBackOnCreate(callback_SurfaceCreate, this);
    eglThread->callBackOnChange(callback_SurfaceChange, this);
    eglThread->callBackOnDraw(callback_SurfaceOndraw, this);

    //base
    baseOpengl = new FilterOne();

    eglThread->onSurfaceCreate(nativeWindow);

}

void OpenglControl::onChangeSurface(int width, int height) {

    if (eglThread != NULL) {
        if (baseOpengl != NULL) {
            baseOpengl->surface_width = width;
            baseOpengl->surface_height = height;

        }
        //进入回调函数
        eglThread->onSurfaceChange(width, height);
    }
}


void OpenglControl::onDestorySurface() {

    if (eglThread != NULL) {
        eglThread->destory();
    }

    if (baseOpengl != NULL) {
        baseOpengl->destory();
        delete baseOpengl;
        baseOpengl = NULL;
    }

    if (nativeWindow != NULL) {
        ANativeWindow_release(nativeWindow);
        nativeWindow = NULL;
    }




}

void OpenglControl::setPilex(void *data, int widht, int height, int length) {

    pic_width = widht;
    pic_height = height;
    pilex = malloc(length);
    memcpy(pilex, data, length);
    if (baseOpengl != NULL) {
        //调用
        baseOpengl->setPilex(pilex, widht, height, length);
    }

    if (eglThread != NULL) {
        LOGD("setPilex 更新")
        eglThread->notifyRender();
    }

}

