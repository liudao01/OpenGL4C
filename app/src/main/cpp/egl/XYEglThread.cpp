//
// Created by liuml on 2019/3/26.
//


#include "XYEglThread.h"

XYEglThread::XYEglThread() {

    pthread_mutex_init(&pthread_mutex, NULL);
    pthread_cond_init(&pthread_cond, NULL);
}

XYEglThread::~XYEglThread() {
    pthread_mutex_destroy(&pthread_mutex);
    pthread_cond_destroy(&pthread_cond);
}

void *eglThreadImpl(void *context) {

    XYEglThread *wlEglThread = static_cast<XYEglThread *>(context);

    if (wlEglThread != NULL) {

        XYEglHelper *wlEglHelper = new XYEglHelper();
        wlEglHelper->initEgl(wlEglThread->nativeWindow);
        wlEglThread->isExit = false;

        while (true) {
            if (wlEglThread->isCreate) {
                LOGD("eglthread call SurfaceCreate")

                wlEglThread->isCreate = false;
                wlEglThread->onCreate(wlEglThread->onCreateCtx);
            }
            if (wlEglThread->isChange) {
                LOGD("eglthread call SurfaceChange")

                wlEglThread->isChange = false;


                wlEglThread->onChange(wlEglThread->surfaceWidth, wlEglThread->surfaceHeight,
                                      wlEglThread->onChangeCtx);

                //opengl
//                glViewport(0, 0, wlEglThread->surfaceWidth, wlEglThread->surfaceHeight);
                wlEglThread->isStart = true;
            }

            //draw
            if (wlEglThread->isStart) {

//                glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
//                glClear(GL_COLOR_BUFFER_BIT);
                wlEglThread->onDraw(wlEglThread->onDrawCtx);
                //调用绘制
                wlEglHelper->swapBuffers();
            }


            LOGD("eglthread call draw")
            if (wlEglThread->renderType == OPENGL_RENDER_AUTO) {
                usleep(1000000 / 60);
            } else {
                //线程加锁
                pthread_mutex_lock(&wlEglThread->pthread_mutex);
                //根据pthread_cond 等待
                pthread_cond_wait(&wlEglThread->pthread_cond,&wlEglThread->pthread_mutex);
                //线程解锁
                pthread_mutex_unlock(&wlEglThread->pthread_mutex);
            }

            if (wlEglThread->isExit) {
                LOGD("eglthread call isExit")
                break;
            }
        }

    }


    return 0;
}


void XYEglThread::onSurfaceCreate(EGLNativeWindowType window) {

    if (eglThread == -1) {
        isCreate = true;
        nativeWindow = window;

        pthread_create(&eglThread, NULL, eglThreadImpl, this);
    }

}

void XYEglThread::onSurfaceChange(int width, int height) {

    isChange = true;
    surfaceWidth = width;
    surfaceHeight = height;

}

void XYEglThread::callBackOnCreate(XYEglThread::OnCreate onCreate1, void *ctx) {
    this->onCreate = onCreate1;
    this->onCreateCtx = ctx;
}

void XYEglThread::callBackOnChange(XYEglThread::OnChange onChange1, void *ctx) {
    this->onChange = onChange1;
    this->onCreateCtx = ctx;
}

void XYEglThread::callBackONDraw(XYEglThread::OnDraw onDraw1, void *ctx) {
    this->onDraw = onDraw1;
    this->onDrawCtx = ctx;
}

void XYEglThread::setRenderType(int renderType) {
    this->renderType = renderType;

}

void XYEglThread::notifyRender() {
    //同样加锁 因为很多地方调用
    pthread_mutex_lock(&pthread_mutex);
    //发送信号
    pthread_cond_signal(&pthread_cond);

    pthread_mutex_unlock(&pthread_mutex);
}



