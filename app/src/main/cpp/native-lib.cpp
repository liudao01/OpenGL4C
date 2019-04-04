#include <jni.h>
#include <string>


#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>

#include <GLES2/gl2.h>
#include "egl/XYEglThread.h"

#include "shaderutil/ShaderUtil.h"

XYEglThread *eglThread = NULL;
ANativeWindow *nativeWindow = NULL;


const char *vertex = "attribute vec4 a_position;\n"
                     "\n"
                     "void main(){\n"
                     "    gl_Position = a_position;\n"
                     "}";
const char *fragment = "precision mediump float;\n"
                       "\n"
                       "void main(){\n"
                       "    gl_FragColor = vec4(1f,0f,0f,1f);\n"
                       "}";

int program;
GLint vPosition;

//顶点数据
//float vertexs[] = {
//        -1, -1,
////        1, 0,
//        1,-1,
//        0, 1
//};
float vertexs[] = {
        1, -1,
        1, 1,
        -1, -1,
        -1, 1
};

void callback_SurfaceCreate(void *ctx) {
    LOGD("callback_SurfaceCreate")
    XYEglThread *wlEglThread = static_cast<XYEglThread *>(ctx);


    program = createProgram(vertex, fragment);
    LOGD("opengl program %d", program)

    vPosition = glGetAttribLocation(program, "a_position");


}

void callback_SurfaceChange(int w, int h, void *ctx) {

    LOGD("callback_SurfaceChange")
    XYEglThread *wlEglThread = static_cast<XYEglThread *>(ctx);
    LOGD("w = %d, h = %d", w, h)
    glViewport(0, 0, w, h);
}

void callback_SurfaceOndraw(void *ctx) {
    LOGD("callback_SurfaceDraw");
    XYEglThread *xyEglThread = static_cast<XYEglThread *>(ctx);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //使用program  赋值的操作 数据传递的操作都在这个useProgram之后
    glUseProgram(program);

    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//两个三角形
//    glDrawArrays(GL_TRIANGLES, 0, 3);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_xy_www_opengl4c_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance,
                                                           jobject surface) {

    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new XYEglThread();

    eglThread->setRenderType(OPENGL_RENDER_HANDLE);
    eglThread->callBackOnCreate(callback_SurfaceCreate, eglThread);
    eglThread->callBackOnChange(callback_SurfaceChange, eglThread);
    eglThread->callBackOnDraw(callback_SurfaceOndraw, eglThread);

    eglThread->onSurfaceCreate(nativeWindow);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_xy_www_opengl4c_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance,
                                                           jint width, jint height) {

    // TODO
    if (eglThread != NULL) {
        eglThread->onSurfaceChange(width, height);

        usleep(1000000);
        eglThread->notifyRender();
    }

}