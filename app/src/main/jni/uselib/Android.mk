LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := uselib
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../vendor/libjpeg-turbo/libjpeg-turbo-1.4.1
LOCAL_SRC_FILES := \
uselib.c
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := jpeg-turbo

include $(BUILD_SHARED_LIBRARY)