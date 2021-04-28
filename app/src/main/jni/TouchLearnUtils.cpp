//
// Created by user on 2021/4/27.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
//NDK compile debug log head file
#include <android/log.h>
#include "com_jursery_app_touchlearn_TouchLearnUtils.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "touchlearn_jni", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "touchlearn_jni", __VA_ARGS__)
#define LEN_MAX 512
#define LINUX_VERSION_IFO "/proc/version"

#define CONFIG_IOCTL_SET_TS_CFG    _IOW('C', 0, char*)
#define CONFIG_IOCTL_GET_TS_CFG    _IOR('C', 1, char*)
#define CONFIG_IOCTL_CON_TS_CFG    _IOW('C', 2, int)
#define CONFIRM_CONFIG             0x1000
#define CORRECT_ORIGIN             0x1001
#define CORRECT_KEY                0x1002
#define CLEAR_KEY                  0x1003
#define CTPNODE        "/dev/ctp_config"
#define CTP_CHANGE_NODE "/sys/kernel/dev_cfg/change"


JNIEXPORT jstring JNICALL Java_com_jursery_app_touchlearn_TouchLearnUtils_nativeGetKernelVersion
  (JNIEnv *env, jclass clazz){

    int fd, ret;
    char buf[LEN_MAX]={'\0'};
    fd = open(LINUX_VERSION_IFO,O_RDONLY);
    if(fd < 0){
        LOGE("open file %s error! err_info=%s",LINUX_VERSION_IFO,strerror(fd));
        return env->NewStringUTF("JNI: open kernel version fail!");
    }
    ret = read(fd, buf, LEN_MAX);
    if(ret <= 0){
        LOGE("read file %s error! err_info=%s",LINUX_VERSION_IFO, strerror(ret));
        close(fd);
        return env->NewStringUTF("JNI: read kernel version fail!");
    }
    close(fd);
    buf[LEN_MAX-1] = '\0';
    LOGD("get kernel version is %s\n",buf);
    return env->NewStringUTF(buf);
  }

JNIEXPORT jint JNICALL Java_com_jursery_app_touchlearn_TouchLearnUtils_nativeSetTsConfig(JNIEnv *env, jclass clazz, jstring config)
{
    jint fd;
    jint ret = -1;
    
    const char *str = env->GetStringUTFChars(config, NULL);
    if (str == NULL) {
        LOGE("TP name: null point!!!");
        return -1;
    }
    LOGD("daily set TP name: %s", str);
    env->ReleaseStringUTFChars(config, str);
    fd = open(CTPNODE, O_RDWR);
    if (fd == -1) {
        LOGE("SetTsConfig open %s error! err_info=%s", CTPNODE,strerror(fd));
        return -1;
    }
    ret = ioctl(fd, CONFIG_IOCTL_SET_TS_CFG, NULL);
    if (ret) {
        LOGE("set TP name error, the error ret = %d", ret);
    }
    close(fd);
    return ret;
}

JNIEXPORT jint JNICALL Java_com_jursery_app_touchlearn_TouchLearnUtils_nativeGetTsConfig(JNIEnv *env, jclass clazz, jstring path)
{
    jint fd;
    jint ret = -1;
    char buff[50] = {0};
    
    const char *str = env->GetStringUTFChars(path, NULL);
    if (str == NULL) {
        LOGE("path: null point!!!");
        return -1;
    }
    if ((strlen(str) + 1) > sizeof(buff)) {
        LOGE("path: invalid length!!!");
        return -1;
    }
    strcpy(buff, str);
    env->ReleaseStringUTFChars(path, str);
    LOGD("Get TP config path is: %s", buff);
    fd = open(CTPNODE, O_RDWR);
    if (fd == -1) {
        LOGE("GetTsConfig open %s error! err_info=%s",CTPNODE,strerror(fd));
        return -1;
    }
    ret = ioctl(fd, CONFIG_IOCTL_GET_TS_CFG, buff);
    if (ret) {
        LOGE("GetTsConfig ioctl get TP config error, the error ret = %d", ret);
    }
    close(fd);
    return ret;
}

JNIEXPORT jint JNICALL Java_com_jursery_app_touchlearn_TouchLearnUtils_nativeCorrectTsConfig(JNIEnv *env, jclass clazz, jint value)
{
    jint ret = -1;
    jint fd = -1;
    jint action = -1;
    
    LOGD("CorrectTsConfig action is: 0x%x", value);
    switch (value)
    {
        case CONFIRM_CONFIG:
            action = CONFIRM_CONFIG;
            break;
        case CORRECT_ORIGIN:
            action = CORRECT_ORIGIN;
            break;
        case CORRECT_KEY:
            action = CORRECT_KEY;
            break;
        case CLEAR_KEY:
            action = CLEAR_KEY;
            break;
        default:
            if (value > 0)
                action = value;
    }
    fd = open(CTPNODE, O_RDWR);
    if (fd == -1) {
        LOGE("CorrectTsConfig open %s error! err_info=%s",CTPNODE,strerror(fd));
        return ret;
    }
    ret = ioctl(fd, CONFIG_IOCTL_CON_TS_CFG, (unsigned long)&action);
    if (ret)
        LOGE("CorrectTsConfig correct TP error, the error ret = %d", ret);
    close(fd);

    return ret;
}

JNIEXPORT jint JNICALL Java_com_jursery_app_touchlearn_TouchLearnUtils_nativeUseTsConfig(JNIEnv *env, jclass clazz, jstring config)
{
    jint fd;
    jint ret = -1;
    char buff[32] = {0};

    const char *str = env->GetStringUTFChars(config, NULL);
    if (str == NULL) {
        LOGE("UseTsConfig tp config name: null point!!!");
        return ret;
    }
    strcpy(buff, str);
    env->ReleaseStringUTFChars(config, str);
    LOGD("UseTsConfig set TP name: %s", buff);
    fd = open(CTPNODE, O_RDWR);
    if (fd == -1) {
        LOGE("UseTsConfig open %s error! err_info=%s",CTPNODE,strerror(fd));
        return ret;
    }
    ret = write(fd, buff, strlen(buff) + 1);
    close(fd);
    if (ret != (jint)(strlen(buff) + 1)) {
        LOGE("UseTsConfig use TP config error");
        ret = -1;
    } else {
        ret = 0;
    }

    return ret;
}

JNIEXPORT jint JNICALL Java_com_jursery_app_touchlearn_TouchLearnUtils_nativeIsTouchScreenChanged(JNIEnv *env, jclass clazz)
{
    jint fd;
    int state = 0;
    char buffer[10] = {0};

    fd = open(CTP_CHANGE_NODE, O_RDONLY);
    if (fd == -1) {
        LOGE("IsTouchScreenChanged open %s error! err_info=%s",CTP_CHANGE_NODE,strerror(fd));
        return -1;
    }
    if (read(fd, buffer, 2) <= 0)
    {
        LOGE("Get touch screen changed error");
        close(fd);
        return -1;
    }
    close(fd);
    state = atoi(buffer);
    LOGD("Get  touch screen changed is: %d", state);

    return state = (state == 1) ? 1 : 0;
}