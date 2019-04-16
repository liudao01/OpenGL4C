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

    XYEglThread *eglThread = static_cast<XYEglThread *>(context);

    if (eglThread != NULL) {

        XYEglHelper *eglHelper = new XYEglHelper();
        eglHelper->initEgl(eglThread->nativeWindow);
        eglThread->isExit = false;

        while (true) {
            if (eglThread->isCreate) {
                LOGD("eglthread call SurfaceCreate")

                eglThread->isCreate = false;
                eglThread->onCreate(eglThread->onCreateCtx);
            }
            if (eglThread->isChange) {
                LOGD("eglthread call SurfaceChange")

                eglThread->isChange = false;


                eglThread->onChange(eglThread->surfaceWidth, eglThread->surfaceHeight,
                                      eglThread->onChangeCtx);

                //opengl
//                glViewport(0, 0, eglThread->surfaceWidth, eglThread->surfaceHeight);
                eglThread->isStart = true;
            }

            //draw
            if (eglThread->isStart) {

//                glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
//                glClear(GL_COLOR_BUFFER_BIT);
                eglThread->onDraw(eglThread->onDrawCtx);
                //调用绘制
                eglHelper->swapBuffers();
            }


            LOGD("eglthread call draw")
            if (eglThread->renderType == OPENGL_RENDER_AUTO) {
                usleep(1000000 / 60);
            } else {
                //线程加锁
                pthread_mutex_lock(&eglThread->pthread_mutex);
                //根据pthread_cond 等待
                pthread_cond_wait(&eglThread->pthread_cond,&eglThread->pthread_mutex);
                //线程解锁
                pthread_mutex_unlock(&eglThread->pthread_mutex);
            }

            if (eglThread->isExit) {
                eglHelper->destroyEgl();
                delete eglHelper;
                eglHelper = NULL;
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

void XYEglThread::callBackOnDraw(XYEglThread::OnDraw onDraw1, void *ctx) {
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

void XYEglThread::destory() {
    isExit = true;
    notifyRender();
    //线程同步
    pthread_join(eglThread, NULL);
    nativeWindow = NULL;
    eglThread = -1;
}



