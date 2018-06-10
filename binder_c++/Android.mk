LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	ITest.cpp \
	server.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog \
	libbinder 

LOCAL_MODULE:= server
LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	ITest.cpp \
	client.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog \
	libbinder 


LOCAL_MODULE:= client
LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)
