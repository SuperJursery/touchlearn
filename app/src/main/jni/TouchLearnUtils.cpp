//
// Created by user on 2021/4/27.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//NDK compile debug log head file
#include <android/log.h>
#include "com_jursery_app_touchlearn_TouchLearnUtils.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "touchlearn_jni", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "touchlearn_jni", __VA_ARGS__)
#define LEN_MAX 512
#define LINUX_VERSION_IFO "/proc/version"

JNIEXPORT jstring JNICALL Java_com_jursery_app_touchlearn_TouchLearnUtils_nativeGetKernelVersion
  (JNIEnv *env, jclass){

    int fd, ret;
    char buf[LEN_MAX]={'\0'};
    fd = open(LINUX_VERSION_IFO,O_RDONLY);
    if(fd < 0){
        LOGE("open file %s error!",LINUX_VERSION_IFO);
        return env->NewStringUTF("JNI: open kernel version fail!");
    }
    ret = read(fd, buf, LEN_MAX);
    if(ret <= 0){
        LOGE("read file %s error!",LINUX_VERSION_IFO);
        close(fd);
        return env->NewStringUTF("JNI: read kernel version fail!");
    }
    close(fd);
    buf[LEN_MAX-1] = '\0';
    LOGD("get kernel version is %s\n",buf);
    return env->NewStringUTF(buf);
  }