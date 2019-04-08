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

XYEglThread *eglThread = NULL;
ANativeWindow *nativeWindow = NULL;

//
//const char *vertex = "attribute vec4 v_Position;\n"
//                     "attribute vec2 f_Position;\n"
//                     "varying vec2 ft_Position;\n"
//                     "void main() {\n"
//                     "    ft_Position = f_Position;\n"
//                     "    gl_Position = v_Position;\n"
//                     "}";

const char *vertex = "attribute vec4 v_Position;\n"
                     "attribute vec2 f_Position;\n"
                     "varying vec2 ft_Position;\n"
                     "uniform mat4 u_Matrix;\n"
                     "void main() {\n"
                     "    ft_Position = f_Position;\n"
                     "    gl_Position = v_Position * u_Matrix;\n"
                     "}";


const char *fragment = "precision mediump float;\n"
                       "varying vec2 ft_Position;\n"
                       "uniform sampler2D sTexture;\n"
                       "void main() {\n"
                       "    gl_FragColor=texture2D(sTexture, ft_Position);\n"
                       "}";

int program;
GLint vPosition;
GLint fPosition;
GLint sampler;
GLuint textureId;//
GLint u_matrix;

int w;
int h;
void *pixels = NULL;

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

//纹理坐标

float fragments[] = {
        1, 1,
        1, 0,
        0, 1,
        0, 0
};

//自己建立的矩阵
float matrix[16];


void callback_SurfaceCreate(void *ctx) {
    LOGD("callback_SurfaceCreate")
    XYEglThread *wlEglThread = static_cast<XYEglThread *>(ctx);


    program = createProgram(vertex, fragment);
    LOGD("opengl program %d", program)

    //顶点坐标
    vPosition = glGetAttribLocation(program, "v_Position");
    //纹理坐标
    fPosition = glGetAttribLocation(program, "f_Position");
    //2d 纹理
    sampler = glGetUniformLocation(program, "sTexture");

    //矩阵
    u_matrix = glGetUniformLocation(program, "u_Matrix");

    //初始化矩阵
    initMatrix(matrix);

    //生成纹理
    glGenTextures(1, &textureId);

    //绑定纹理
    glBindTexture(GL_TEXTURE_2D, textureId);

    //环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    if (pixels != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }

    //解绑
    glBindTexture(GL_TEXTURE_2D, 0);//0就是解绑

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

    //使用矩阵
    glUniformMatrix4fv(u_matrix, 1, GL_FALSE, matrix);

    //激活纹理
//    glActiveTexture(GL_TEXTURE5);
    //给uniformli 变量赋值 sampler
//    glUniform1i(sampler, 5);

    //绑定纹理id
    glBindTexture(GL_TEXTURE_2D, textureId);

    //启用顶点
    glEnableVertexAttribArray(vPosition);//可用
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);//赋值

    //启用纹理
    glEnableVertexAttribArray(fPosition);
    glVertexAttribPointer(fPosition, 2, GL_FLOAT, false, 8, fragments);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//两个三角形
//    glDrawArrays(GL_TRIANGLES, 0, 3);

    //绘制完成后解绑
    glBindTexture(GL_TEXTURE_2D, 0);//0就是解绑

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

extern "C"
JNIEXPORT void JNICALL
Java_com_xy_www_opengl4c_opengl_NativeOpengl_imgData(JNIEnv *env, jobject instance, jint width,
                                                     jint height, jint length, jbyteArray data_) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    w = width;
    h = height;
    pixels = malloc(length);
    memcpy(pixels, data, length);//内存拷贝


    env->ReleaseByteArrayElements(data_, data, 0);
}