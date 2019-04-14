//
// Created by liuml on 2019/4/14.
// opengl 控制类 操作类 需要在这里创建线程 使用 XYEglThread
//

#ifndef OPENGL4C_OPENGLCONTROL_H
#define OPENGL4C_OPENGLCONTROL_H

#include "../egl/XYEglThread.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "BaseOpengl.h"
#include "FilterOne.h"
class OpenglControl {

public:
    XYEglThread *eglThread = NULL;
    ANativeWindow *nativeWindow = NULL;
    BaseOpengl *baseOpengl = NULL;

public:
    OpenglControl();
    ~OpenglControl();

    void onCreateSurface(JNIEnv *env, jobject surface);

    void onChangeSurface(int width, int height);


    void onDestorySurface();
};


#endif //OPENGL4C_OPENGLCONTROL_H
