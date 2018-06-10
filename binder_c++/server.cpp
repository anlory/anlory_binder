#define LOG_TAG "TestServer"
//#define LOG_NDEBUG 0

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>



#include "ITest.h"
#define SIZE 1024

using namespace android;

int main(int argc , char **argv )
{
	char buf[SIZE] = {0};
	int fd = open("1.txt",O_RDWR);
	int len = read(fd,buf,SIZE);
	buf[len] = '\0';
	ALOGE("Read 1.txt:%s\n",buf);
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm(defaultServiceManager());
    ALOGI("ServiceManager: %p", sm.get());
	sm->addService(String16("anlory"),new BnTestService(fd));
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
}

