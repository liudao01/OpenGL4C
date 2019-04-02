//
// Created by liuml on 2019/3/21.
//

#include "XYEglHelper.h"


XYEglHelper::XYEglHelper() {
    eglDisplay = EGL_NO_DISPLAY;
    eglSurface = EGL_NO_SURFACE;
    eglContext = EGL_NO_CONTEXT;
    eglConfig = NULL;


}

XYEglHelper::~XYEglHelper() {

}

/**
 * 初始化EGL环境 success
 */
int XYEglHelper::initEgl(EGLNativeWindowType window) {

    //1. 1、得到默认的显示设备（就是窗口） -- eglGetDisplay

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay error ")
        return -1;

    }

    //2、初始化默认显示设备 -- eglInitialize
    EGLint *version = new EGLint[2];
    if (!eglInitialize(eglDisplay, &version[0], &version[1])) {
        LOGE("eglInitialize error ")
        return -1;
    }

    //3、设置显示设备的属性
    const EGLint attribs[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_STENCIL_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE

    };

    //4、从系统中获取对应属性的配置 -- eglChooseConfig
    EGLint num_config;
    if (!eglChooseConfig(eglDisplay, attribs, NULL, 1, &num_config)) {//这一步是为了获得num_config 的值
        LOGE("eglChooseConfig error 1");
        return -1;
    }


    if (!eglChooseConfig(eglDisplay, attribs, &eglConfig, num_config, &num_config)) {
        LOGE("eglChooseConfig error 2");
        return -1;
    }

    //5、创建EglContext -- eglCreateContext
    //版本号
    int attrib_list[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, attrib_list);
    if (eglContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext create error ");
        return -1;
    }

    //6、创建渲染的Surface -- eglCreateWindowSurface

    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, window, NULL);
    if (eglSurface == EGL_NO_SURFACE) {
        LOGE("eglCreateWindowSurface create error ");
        return -1;
    }

    //7、绑定EglContext和Surface到显示设备中 -- eglMakeCurrent

    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
        LOGE("eglMakeCurrent create error ");
        return -1;
    }


    //8、刷新数据，显示渲染场景 -- eglSwapBuffers 单独写个方法

    LOGD("egl init success ")
    return 0;
}

//8、刷新数据，显示渲染场景 -- eglSwapBuffers 单独写个方法
int XYEglHelper::swapBuffers() {
    if (eglDisplay != EGL_NO_DISPLAY && eglSurface != EGL_NO_SURFACE) {

        if (!eglSwapBuffers(eglDisplay, eglSurface)) {
            return 0;
        }
    }

    return -1;
}

//销毁
void XYEglHelper::destroyEgl() {

    if (eglDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    }
    if (eglDisplay != EGL_NO_DISPLAY && eglSurface != EGL_NO_SURFACE) {
        eglDestroyContext(eglDisplay, eglSurface);
        eglSurface = EGL_NO_SURFACE;
    }
    if (eglDisplay != EGL_NO_DISPLAY && eglContext != EGL_NO_CONTEXT) {

        eglDestroySurface(eglDisplay, eglContext);
        eglContext = EGL_NO_CONTEXT;
    }
    if (eglDisplay != EGL_NO_DISPLAY) {
        eglTerminate(eglDisplay);
        eglContext = EGL_NO_DISPLAY;
    }

}
