#ifndef __SERIAL_DTYPE_H
#define __SERIAL_DTYPE_H
#include "stdio.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "stdbool.h"
#include "delay.h"


#define FRAME_START 154
#define FRAME_END1	1
#define FRAME_END2	2
#define FRAME_END3	3

#define DATA_LEN	9
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

