#ifndef __SERIAL_DTYPE_H
#define __SERIAL_DTYPE_H
#include "stdio.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "stdbool.h"
#include "delay.h"


#define FRAME_START 154


typedef char u8;
typedef short u16;
#pragma pack(1)
typedef struct {
	u8  frame_s;        //帧头
	u8  frame_t;        //帧类别
	u16 frame_len;      //帧长度
	u16 frame_CRC;      //帧CRC校验
	u8  data_t;         //帧数据类型
	u8  data_n;       //数据大小
    u8  data[DATA_LEN];
	u8  frame_e[3];
} S_base_Data;


typedef struct _UltraSound_DATA_Frame{
	u8 s_flag;//start frame flag
	u8 f_type;//frame data type
	u16 f_len;//frame len
	u16 f_CRC;//frame crc code 
	u8 data_type;//
	u8 u_sound_n;//ultrasound number
	u16 u_data[8];
	u8 end_flag[3];
}UltraSound_Data_Frame;

typedef struct _EncodeDisk_DATA_Frame{
	u8 s_flag;//start frame flag
	u8 f_type;//frame data type
	u16 f_len;//frame len
	u16 f_CRC;//frame crc code 
	u8 data_flag;
	u8 data_type;//
	u8 Edisk_n;//EncodeDisk number
	u8 e_data[2];
	u8 end_flag[3];
}EncodeDisk_Data_Frame;

#pragma pack()


#endif

