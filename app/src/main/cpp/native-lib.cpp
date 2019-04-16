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
#import "matrix/Matrix.h"
#import "opengl/OpenglControl.h"

XYEglThread *eglThread = NULL;
ANativeWindow *nativeWindow = NULL;


int program;
GLint vPosition;
GLint fPosition;
GLint sampler;
GLuint textureId;//
GLint u_matrix;

OpenglControl *openglControl = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_xy_www_opengl4c_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance,
                                                           jobject surface) {

    if (openglControl == NULL) {
        openglControl = new OpenglControl();
    }
    openglControl->onCreateSurface(env, surface);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_xy_www_opengl4c_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance,
                                                           jint width, jint height) {

    if (openglControl != NULL) {
        openglControl->onChangeSurface(width, height);
    }
    // TODO
//    if (eglThread != NULL) {
//        eglThread->onSurfaceChange(width, height);
//
//        usleep(1000000);
//        eglThread->notifyRender();
//    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_xy_www_opengl4c_opengl_NativeOpengl_imgData(JNIEnv *env, jobject instance, jint width,
                                                     jint height, jint length, jbyteArray data_) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    if (openglControl != NULL) {
        openglControl->setPilex(data, width, height, length);
    }
    env->ReleaseByteArrayElements(data_, data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_xy_www_opengl4c_opengl_NativeOpengl_surfaceDestory(JNIEnv *env, jobject instance) {

    // TODO
    if (openglControl != NULL) {
        openglControl->onDestorySurface();
        delete openglControl;
        openglControl = NULL;
    }

}