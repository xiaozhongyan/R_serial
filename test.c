#include <iostream>
#include "serial_Dtype.h"

u8 frame_tail1 = FRAME_END1;
u8 frame_tail2 = FRAME_END2;
u8 frame_tail3 = FRAME_END3;
u8 frame_head  = FRAME_START;

using namespace std;
int main()
{
	Serial_base_data serial_dat;
	ulS_base_data uls;
	char* p = (char*)&serial_dat;
	*(p+2)=0x02;
	*(p+3)=0x03;
	serial_dat.frame_s='a';
	cout<<"data-----:"<<&serial_dat<<endl;
	cout<<"frame_len:"<<&(serial_dat.frame_len)<<endl;
	cout<<"p--------:"<<(*p)<<endl;
	cout<<"seriallen:"<<hex<<serial_dat.frame_len<<endl;
	cout<<dec<<endl;
	serial_dat.frame_len=156;
	int test_num=156;
	if(serial_dat.frame_len==test_num)
	{
		cout<<"here................1<<<"<<endl;
	}
	serial_dat.frame_s=0x9a;
	if(serial_dat.frame_s==frame_head)
	{
		cout<<"here................2>>>:"<<endl;
		
	}
	cout<<"sizeof ulS_base_data:"<<sizeof(uls)<<endl;
	cout<<"sizeof codecD_base_data:"<<sizeof(codecD_base_data)<<endl;
	cout<<"sizeof IMU_base_data:"<<sizeof(Imu_base_data)<<endl;
	return 0;
}
