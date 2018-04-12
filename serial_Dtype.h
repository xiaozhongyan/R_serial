#ifndef __SERIAL_DTYPE_H
#define __SERIAL_DTYPE_H


#define FRAME_START 154 //0x9a
#define FRAME_END1	156	//0x9c
#define FRAME_END2	13 //0x0d
#define FRAME_END3	10 //0xoa

#define DATA_LEN	35 //数据大小 
//数据大小

typedef char u8;
typedef short u16;
#pragma pack(1)
typedef struct {
	u8  frame_s;        //帧头
	u8  frame_t;        //帧类别
	u16 frame_len;      //帧长度
	u16 frame_CRC;      //帧CRC校验
	u8  data_t;         //帧数据类型
	u8  data_n;       	//数据大小
    u8  data[DATA_LEN];	//数据
//	u8  frame_e[3];		//帧尾
} Serial_base_data;

#pragma pack()


#endif

