//
// Created by liuml on 2019/3/21.
//

#ifndef OPENGL4C_MYANDROIDLOG_H
#define OPENGL4C_MYANDROIDLOG_H

#include "android/log.h"


#define LOG_SHOW true

#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"jnilib",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jnilib",FORMAT,##__VA_ARGS__);


#endif //OPENGL4C_MYANDROIDLOG_H
