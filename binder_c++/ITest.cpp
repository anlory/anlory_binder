#include"ITest.h"


namespace android{
	enum {
		TEST_GETFD = IBinder::FIRST_CALL_TRANSACTION,
		TEST_GETVALUE,
		TEST_SETVALUE,
	};


class BpTestService:public BpInterface<ITestService>
{
	public :
		BpTestService(const sp<IBinder> &impl)
		:BpInterface<ITestService>(impl)
		{

		}

		int getValue(void){
			Parcel data,reply;
			data.writeInt32(0);
			remote()->transact(TEST_GETVALUE,data,&reply);
			int exception = reply.readInt32();
			if(exception){
				return -1;
			}else{
				return reply.readInt32();
			}
		}

		int getFd(void){
			Parcel data,reply;
			data.writeInt32(0);
			remote()->transact(TEST_GETFD,data,&reply);
			int exception = reply.readInt32();
			int rawfd = reply.readFileDescriptor();
			ALOGE("BpTestService fd:%d\n",rawfd);
			if(exception){
				return -1;
			}else{
				return dup(rawfd);
			}
		}

		void setValue(int val){
			Parcel data,reply;
			data.writeInt32(0);
			data.writeInt32(val);
			remote()->transact(TEST_SETVALUE,data,&reply);
		}
	
};


IMPLEMENT_META_INTERFACE(TestService,"android.meida.ITestService");



BnTestService::BnTestService(){

}
BnTestService::BnTestService(int fd){
	this->fd = fd;
}

status_t BnTestService::onTransact(
		uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
	{
		switch (code) {
	
			case TEST_GETFD: {
				int fd = getFd();
				reply->writeInt32(0);
				
				reply->writeDupFileDescriptor(fd);
				
				
				return NO_ERROR;
			}
	
			case TEST_GETVALUE: {
				reply->writeInt32(0);
				reply->writeInt32(getValue());
				
				return NO_ERROR;
			}

			case TEST_SETVALUE: {
				int policy = data.readInt32();
				int val = data.readInt32();
				setValue(val);
				reply->writeInt32(0);
				
				return NO_ERROR;
			}
			
	
			default:
				return BBinder::onTransact(code, data, reply, flags);
		}
	}



int BnTestService::getFd(void){
	
	return this->fd;
}

void BnTestService::setValue(int val){
	this->g_value = val;
	
}


int BnTestService::getValue(void){
	return this->g_value++;
}

}



