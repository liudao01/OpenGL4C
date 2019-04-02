//
// Created by liuml on 2019/3/21.
//

#ifndef OPENGL4C_WLEGLHELPER_H
#define OPENGL4C_WLEGLHELPER_H

#include "EGL/egl.h"
#include "../log/AndroidLog.h"
class XYEglHelper {

public :
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLConfig eglConfig;
    EGLContext eglContext;
public:
    XYEglHelper();

    ~XYEglHelper();

    int initEgl(EGLNativeWindowType win);

    int swapBuffers();

    void destroyEgl();
};


#endif //OPENGL4C_WLEGLHELPER_H
