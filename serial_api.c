/**
version:v2.4
@author:yuanzhongyan
@email:yz.yan@siat.ac.cn m15579395792@163.com
@date:2018-4-10
Build instructions:
1. g++ cp210x_gpio_example.c -o cp210x_gpio_example
2. sudo chmod 666 /dev/ttyUSB0
3. ./cp210x_gpio_example
extra detail information about serial see
:http://digilander.libero.it/robang/rubrica/serial.htm?cm_mc_uid=24282200558714969797805&cm_mc_sid_50200000=1497521087
**/



#include <iostream>
#include <fcntl.h>
#include <stropts.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>    /*PPSIX 终端控制定义*/
#include <sys/ioctl.h>    /* BSD and Linux */
#include <stropts.h>    /* XSI STREAMS */
#include "serial_Dtype.h"

#define FRAME_SIZE 41

using namespace std;
/**
 *@fuction :initial_serial();串口初始化函数
 *@author:
 *@parameter
 	@baubrate ，波特率，可设为现有一些波特率值 如115200则设B115200
 	@databits,数据有效位，5位时为CS5，6位时为CS6，7位时为CS7，8位时为CS8
 	@parity，奇偶校验，为奇校验时置'O' 为偶校验时置'E' 不进行奇偶校验时置 'N'
 	@onestopbit，一位停止位使能，当设两位停止位时置false，一位停止位时true
 	@softwareHandshake,软件握手协议使能，打开置true,关闭置flase
 	@hardwareHandshake,硬件握手协议使能，打开置true,关闭置flase
 *@return 初始化成功返回 0,否则返回-1；
*/

int initial_serial(int m_fd,speed_t baudrate, int databits, const char parity, bool onestopbit, bool softwareHandshake, bool hardwareHandshake)
{
   struct termios Opt;
//   memset(&Opt, 0, sizeof(Opt));
   if (tcgetattr(m_fd, &Opt)!=0)
   {
      cout<<"tcgetattr() 1 failed"<<endl;
      return -1;
   }

   cfsetospeed(&Opt, baudrate);
   cfsetispeed(&Opt, baudrate);

   /* We generate mark and space parity ourself. */
   if (databits == 7 && (parity=='M'/*"Mark"*/ || parity == 'S'/*"Space"*/))
   {
      databits = 8;
   }
   switch (databits)
   {
   case 5:
      Opt.c_cflag = (Opt.c_cflag & ~CSIZE) | CS5;
      break;
   case 6:
      Opt.c_cflag = (Opt.c_cflag & ~CSIZE) | CS6;
      break;
   case 7:
      Opt.c_cflag = (Opt.c_cflag & ~CSIZE) | CS7;
      break;
   case 8:
   default:
      Opt.c_cflag = (Opt.c_cflag & ~CSIZE) | CS8;
      break;
   }
   Opt.c_cflag |= CLOCAL | CREAD;

   //parity
   Opt.c_cflag &= ~(PARENB | PARODD);
   if (parity == 'E'/*"Even"*/)
   {
      Opt.c_cflag |= PARENB;
   }
   else if (parity== 'O'/*"Odd"*/)
   {
      Opt.c_cflag |= (PARENB | PARODD);
   }

   //hardware handshake
   Opt.c_cflag &= ~CRTSCTS;

   //stopbits
   if (onestopbit)
   {
   	Opt.c_cflag &= ~CSTOPB;    
   }
   else
   {
      	Opt.c_cflag |= CSTOPB;
   }

   Opt.c_iflag=IGNBRK;

   //software handshake
   if (softwareHandshake)
   {
      Opt.c_iflag |= IXON | IXOFF;
   }
   else
   {
      Opt.c_iflag &= ~(IXON|IXOFF|IXANY);
   }

   Opt.c_lflag=0;
   Opt.c_oflag=0;

   Opt.c_cc[VTIME]=1;
   Opt.c_cc[VMIN]=FRAME_SIZE;

//   tcflush(m_fd, TCIFLUSH);
   if (tcsetattr(m_fd, TCSANOW, &Opt)!=0)
   {
      cout<<"tcsetattr() 1 failed"<<endl;
      return -1;
   }

   int mcs=0;
   ioctl(m_fd, TIOCMGET, &mcs);
   mcs |= TIOCM_RTS;
   ioctl(m_fd, TIOCMSET, &mcs);

   if (tcgetattr(m_fd, &Opt)!=0)
   {
      cout<<"tcgetattr() 2 failed"<<endl;
      return -1;
   }

   //hardware handshake
   if (hardwareHandshake)
   {
      Opt.c_cflag |= CRTSCTS;
   }
   else
   {
      Opt.c_cflag &= ~CRTSCTS;
   }
   if (tcsetattr(m_fd, TCSANOW, &Opt)!=0)
   {
      cout<<"tcsetattr() 2 failed"<<endl;
      return -1;
   }
   return 0;

}

#define BUF_SIZE_MAX    120
#define DAT_SIZE_MAX    60
#define FRAME_TAIL_SIZE 3
#define READ_SIZE       32

char frame_tail1 = FRAME_END1;
char frame_tail2 = FRAME_END2;
char frame_tail3 = FRAME_END3;
char frame_head  = FRAME_START;


int main()
{
	int     fd;             //硬件设备句柄
	int     available_len; //可用的数据长度
	char    serial_buf[BUF_SIZE_MAX];	//串口缓存
	char    data[DAT_SIZE_MAX]; //数据空间
	char    temp;               //临时中转数据
	int     datCursor;          //当前数据指针
	int     bufCursor;          //当前缓存指针
	int 	i;
	int currentLength;
	Serial_base_data * serial_data;
	serial_data = (Serial_base_data *) data;
	//serial_data = data;
	//打开串口设备
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY/* | O_NDELAY*/);	
	if (fd == -1)
	{
		cout << "Error opening port /dev/ttyUSB0\n";
		return -1;
	}
	//初始化串口设备
	if(initial_serial(fd,B115200,8,'N', true, false, false)==-1)
	{
		cout<<"initial serial error"<<endl;
		return -1;
	}

	currentLength=0;//当前读取的缓存数据长度
	datCursor=0;
	while(true){	
		available_len=read(fd,serial_buf+currentLength,READ_SIZE);
		if(available_len<0){
			cout<<"read data error.."<<endl;
			continue;
		}	
		currentLength = currentLength + available_len;
		cout<<"read ok : available_len"<< available_len<<"currentLength:"<<currentLength<<endl;		
		bufCursor=0;//缓存指针
		//如果接收可用的数据大于数据帧尾标识大小则解析
		
		while(currentLength > 3)
		{
		    //检测到帧尾,并同时提取帧数据
		    data[datCursor++] = serial_buf[bufCursor];
		    currentLength--;
		    if(serial_buf[bufCursor++] != frame_tail1)
		    {
		        continue;
		    }
		    
		    data[datCursor++] = serial_buf[bufCursor];
		    currentLength--;
		    if(serial_buf[bufCursor++] != frame_tail2)
		    {
		        continue;
		    }
		    data[datCursor++] = serial_buf[bufCursor];
		    currentLength--;
		    if(serial_buf[bufCursor++] != frame_tail3)
		    {
		        continue;
		    }
		    //获取完整的一帧数据，并判断数据是否完整 
		    cout<<"test tail-----datCursor:"<<datCursor<<endl;
		    //cout 数据
		    i=0;
		    while(i<datCursor)
		    {
		    	cout<<hex<<(int)(data[i++] & 0xff)<<":";
		    }
		    cout<<endl;
		    //以下为检查数据。。。。
		   /*
		    i=(int)(data[2]&0xff);
		    cout<<"i="<<i<<endl;
		    cout<<"bufSize: "<< data[2] <<endl;
		    if(datCursor!= (int)(*serial_data->frame_len))
		    {
				//出错
				cout<<"frame size error!!"<<endl;
				//清除结构体的数据
				datCursor=0;
		        continue;
		    }
		    //判断数据帧头是否正确
		    if(*serial_data->frame_s=frame_head)
		    {
		        //出错
		        cout<<"frame head error!!"<<endl;
		        //清除结构体的数据
				datCursor=0;
		        continue;
		    }
		    else
			{
				//读取数据
				//使用 *serial->data[]				
			}
	    */
		    //余下缓冲的数据保存。
		    datCursor=0;
		    while(currentLength>0)
		    {
		        data[datCursor++]=serial_buf[bufCursor++];
		        currentLength--;
		    }
		    	    
		}//end while(currentLength > end_len)
		//残留字节移到缓冲区首
		i=0;
		
		while(currentLength>i)
		{
		    temp = serial_buf[bufCursor++];
		    serial_buf[i++]=temp;
		}		
		//usleep();		
	}//end while(true)
	
}

