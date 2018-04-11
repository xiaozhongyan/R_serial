
#include "dev_communicate.h"
//#include "led.h"

//EncodeDisk_Data_Frame EnDisk_tx_Data;
//EncodeDisk_Data_Frame EnDisk_rx_Data;

//UltraSound_Data_Frame UltSound_tx_Data;
//UltraSound_Data_Frame UltSound_rx_Data;

//IMU_Quart_or_Eul_DataFrame IMU_tx_Data;
//IMU_Quart_or_Eul_DataFrame IMU_tx_Data;



/////////////////////////////////////////////////////////////////////////////////////////
void UltraSound_Data_Frame_DeInit(UltraSound_Data_Frame* data)
{
	data->s_flag =0x9a;
	data->f_type =0x7a;	
	data->f_len = (u16)sizeof(UltraSound_Data_Frame);
	data->data_type =0x7a;
	data->end_flag[0]=0x9c;
	data->end_flag[1]=0x0d;
	data->end_flag[2]=0x0a;
};
//init function

//void use_spi_dma_tx_init(SPI_TypeDef* SPIx);
//void use_spi_tx_init(SPI_TypeDef* SPIx);
void use_uart_dma_tx_init(USART_TypeDef* USARTx,u32 boundRate,u32 DMA_MemoryBaseAddr)
{
#if EN_USART1_RX
	if(USART1==USARTx)
	{
		uart1_init(boundRate);
		DMA_Config(DMA1_Channel4,(u32)&USARTx->DR,DMA_MemoryBaseAddr,0);
		USART_DMACmd(USARTx,USART_DMAReq_Tx,ENABLE);
	}
#endif
#if EN_USART2_RX 
	else if(USART2 == USARTx)
	{
		uart2_init(boundRate);
		DMA_Config(DMA1_Channel7,(u32)&USARTx->DR,DMA_MemoryBaseAddr,0);
		USART_DMACmd(USARTx,USART_DMAReq_Tx,ENABLE);
	}
#endif
}
//void use_uart_tx_init(USART_TypeDef* USARTx,u32 boundRate);

//void use_spi_dma_rx_init(SPI_TypeDef* SPIx);
//void use_spi_rx_init(SPI_TypeDef* SPIx);
//void use_uart_dma_rx_init(USART_TypeDef* USARTx,u32 boundRate);
void use_uart_rx_init(USART_TypeDef* USARTx,u8* rx_buf,u16 rx_bufSize)
{
#if EN_USART1_RX
	if(USARTx==USART1)uart1_set_rxbuf(rx_buf,rx_bufSize);
#endif
#if EN_USART2_RX
	else if(USARTx==USART2)uart1_set_rxbuf(rx_buf,rx_bufSize);
#endif
}

//tx
//ultralSound tx
//void use_spi_dma_tx_UltSound(UltraSound_Data_Frame * data);
void use_uart_dma_tx_UltSound(USART_TypeDef* USARTx,u32 DMA_MemoryBaseAddr,u32 dataSize)
{
#if EN_USART1_RX
	if(USART1 == USARTx)
	{		
		DMA_Cmd(DMA1_Channel4, DISABLE );  //关闭USART1 TX DMA1 所指示的通道	
		DMA1_Channel4->CMAR = DMA_MemoryBaseAddr;
		DMA_SetCurrDataCounter(DMA1_Channel4,dataSize);//DMA通道的DMA缓存的大小
		DMA_Cmd(DMA1_Channel4, ENABLE);  //使能USART1 TX DMA1 所指示的通道
	}
#endif
#if EN_USART2_RX
	else if(USART2 == USARTx)
	{
		DMA_Cmd(DMA1_Channel7, DISABLE );  //关闭USART1 TX DMA1 所指示的通道	
		DMA1_Channel7->CMAR = DMA_MemoryBaseAddr;
		DMA_SetCurrDataCounter(DMA1_Channel7,dataSize);//DMA通道的DMA缓存的大小
		DMA_Cmd(DMA1_Channel7, ENABLE);  //使能USART1 TX DMA1 所指示的通道
	}
#endif
}
//void use_spi_tx_UltSound(UltraSound_Data_Frame * data);
//void use_uart_tx_UltSound(UltraSound_Data_Frame * data);

//encodeDisk tx
//void use_spi_dma_tx_EnDisk(EncodeDisk_Data_Frame * data);
void use_uart_dma_tx_EnDisk(USART_TypeDef* USARTx,u32 DMA_MemoryBaseAddr,u32 dataSize)
{
#if EN_USART1_RX
	if(USART1 == USARTx)
	{		
		DMA_Cmd(DMA1_Channel4, DISABLE );  //关闭USART1 TX DMA1 所指示的通道	
		DMA1_Channel4->CMAR = DMA_MemoryBaseAddr;
		DMA_SetCurrDataCounter(DMA1_Channel4,dataSize);//DMA通道的DMA缓存的大小
		DMA_Cmd(DMA1_Channel4, ENABLE);  //使能USART1 TX DMA1 所指示的通道
	}
#endif
#if EN_USART2_RX
	else if(USART2 == USARTx)
	{
		DMA_Cmd(DMA1_Channel7, DISABLE );  //关闭USART1 TX DMA1 所指示的通道	
		DMA1_Channel7->CMAR = DMA_MemoryBaseAddr;
		DMA_SetCurrDataCounter(DMA1_Channel7,dataSize);//DMA通道的DMA缓存的大小
		DMA_Cmd(DMA1_Channel7, ENABLE);  //使能USART1 TX DMA1 所指示的通道
	}
#endif
}
//void use_spi_tx_EnDisk(EncodeDisk_Data_Frame * data);
//void use_uart_tx_EnDisk(EncodeDisk_Data_Frame * data);
//IMU tx
//void use_spi_dma_tx_ImuData(IMU_Quart_or_Eul_DataFrame * data);
void use_uart_dma_tx_ImuData(USART_TypeDef* USARTx,u32 DMA_MemoryBaseAddr,u32 dataSize)
{
#if EN_USART1_RX
	if(USART1 == USARTx)
	{		
		DMA_Cmd(DMA1_Channel4, DISABLE );  //关闭USART1 TX DMA1 所指示的通道	
		DMA1_Channel4->CMAR = DMA_MemoryBaseAddr;
		DMA_SetCurrDataCounter(DMA1_Channel4,dataSize);//DMA通道的DMA缓存的大小
		DMA_Cmd(DMA1_Channel4, ENABLE);  //使能USART1 TX DMA1 所指示的通道
	}
#endif
#if EN_USART2_RX
	else if(USART2 == USARTx)
	{
		DMA_Cmd(DMA1_Channel7, DISABLE );  //关闭USART1 TX DMA1 所指示的通道	
		DMA1_Channel7->CMAR = DMA_MemoryBaseAddr;
		DMA_SetCurrDataCounter(DMA1_Channel7,dataSize);//DMA通道的DMA缓存的大小
		DMA_Cmd(DMA1_Channel7, ENABLE);  //使能USART1 TX DMA1 所指示的通道
	}
#endif
}
//void use_spi_dma_tx_ImuData(IMU_Quart_or_Eul_DataFrame * data);
//void use_uart_dma_tx_ImuData(IMU_Quart_or_Eul_DataFrame * data);

//rx
//_Bool use_spi_dma_rx_UltSound(UltraSound_Data_Frame * data);
//_Bool use_uart_dma_rx_UltSound(UltraSound_Data_Frame * data);
//_Bool use_spi_rx_UltSound(UltraSound_Data_Frame * data);
bool use_uart_rx_UltSound(USART_TypeDef* USARTx)
{	
	UltraSound_Data_Frame * data;
#if EN_USART1_RX
	if(USART1 == USARTx)
	{
		while(USART1_RX_STA !=0X8000);
		USART1_RX_STA=0;
		data = (UltraSound_Data_Frame *)USART1_RX_DATA;
		if((data->s_flag == 0x9a)&&(data->data_type == 0x7a))
		{
			return true;
		}
		else 
		{
			return false;
		}			
	}
#endif
#if EN_USART2_RX
	else if(USART2 == USARTx)
	{
		while(USART2_RX_STA !=0X8000);
		USART2_RX_STA=0;
		data = (UltraSound_Data_Frame *)USART2_RX_DATA;
		if((data->s_flag == 0x9a)&&(data->data_type == 0x7a))
		{
			return true;
		}
		else 
		{
			return false;
		}			
	}
#endif
	return false;
}

//_Bool use_spi_dma_rx_EnDisk(EncodeDisk_Data_Frame * data);
//_Bool use_uart_dma_rx_EnDisk(EncodeDisk_Data_Frame * data);
//_Bool use_spi_rx_EnDisk(EncodeDisk_Data_Frame * data);
bool use_uart_rx_EnDisk(USART_TypeDef* USARTx)
{
	EncodeDisk_Data_Frame* data;
#if EN_USART1_RX
	if(USART1 == USARTx)
	{
		while(USART1_RX_STA !=0X8000);
		USART1_RX_STA=0;
		data = (EncodeDisk_Data_Frame *)USART1_RX_DATA;
		if((data->s_flag == 0x9a)&&(data->data_type == 0xc5))
		{
			return true;
		}
		else 
		{
			return false;
		}			
	}
#endif
#if EN_USART2_RX
	else if(USART2 == USARTx)
	{
		while(USART2_RX_STA !=0X8000);
		USART2_RX_STA=0;
		data = (EncodeDisk_Data_Frame *)USART2_RX_DATA;
		if((data->s_flag == 0x9a)&&(data->data_type == 0xc5))
		{
			return true;
		}
		else 
		{
			return false;
		}			
	}
#endif
	return false;

}

//_Bool use_spi_dma_rx_ImuData(IMU_Quart_or_Eul_DataFrame * data);
//_Bool use_uart_dma_rx_ImuData(IMU_Quart_or_Eul_DataFrame * data);
//_Bool use_spi_rx_ImuData(IMU_Quart_or_Eul_DataFrame * data);
bool use_uart_rx_ImuData(USART_TypeDef* USARTx)
{
	IMU_Quart_or_Eul_DataFrame * data;
#if EN_USART1_RX
	if(USART1 == USARTx)
	{
		while(USART1_RX_STA !=0X8000);
		USART1_RX_STA=0;
		data = (IMU_Quart_or_Eul_DataFrame *)USART1_RX_DATA;
		if((data->s_flag == 0x9a)&&(data->data_type == 0xa5))
		{
			return true;
		}
		else 
		{
			return false;
		}			
	}
#endif
#if EN_USART2_RX
	else if(USART2 == USARTx)
	{
		while(USART2_RX_STA !=0X8000);
		USART2_RX_STA=0;
		data = (IMU_Quart_or_Eul_DataFrame *)USART2_RX_DATA;
		if((data->s_flag == 0x9a)&&(data->data_type == 0xa5))
		{
			return true;
		}
		else 
		{
			return false;
		}			
	}
#endif
	return false;
}
