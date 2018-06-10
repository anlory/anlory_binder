#ifndef __I_TEST_H__
#define __I_TEST_H__

#include <binder/IInterface.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
namespace android{



class ITestService:public IInterface
{
	public:
		DECLARE_META_INTERFACE(TestService);
		virtual int getFd(void) = 0;
		virtual void setValue(int val) = 0;
		virtual int  getValue(void) = 0;
};


class BnTestService:public BnInterface<ITestService>
{
private: 
	int g_value = 111;
	int fd = 123;
public:
    virtual status_t    onTransact(uint32_t code, const Parcel& data, Parcel* reply,
	                                uint32_t flags = 0);

	virtual int getFd(void);
	virtual void setValue(int val);
	virtual int getValue(void) ;

	BnTestService();
	BnTestService(int fd);
	
};

}


#endif
