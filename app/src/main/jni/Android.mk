LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := jni_touchlearn
LOCAL_SRC_FILES := TouchLearnUtils.cpp
#NDK add debug log lib
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)