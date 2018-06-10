#define LOG_TAG "TestClient"
//#define LOG_NDEBUG 0

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#define SIZE 1024

// from LOCAL_C_INCLUDES

#include "ITest.h"


using namespace android;


int main(int argc,char** argv)
{
	
	int value;
	int fd;
	char buf[SIZE] = {0};
	sp<ProcessState> proc(ProcessState::self());

	sp<IServiceManager> sm = defaultServiceManager();

	sp<IBinder> binder = sm->getService(String16("anlory"));

	sp<ITestService> service = interface_cast<ITestService>(binder);

	service->setValue(22);
	
	value = service->getValue();

	ALOGE("getValue:%d\n",value);

	value = service->getValue();

	ALOGE("getValue:%d\n",value);
	
	fd = service->getFd();
	lseek(fd,0,SEEK_SET);
	int len = read(fd,buf,SIZE);
	buf[len] = '\0';
	ALOGE("Read 1.txt:%s\n",buf);
	
	return 0;
}




