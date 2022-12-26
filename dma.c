#include "main.h"


//-----------------------------------------------------------------------
	DMA_CtrlDataInitTypeDef DMA_PriCtrlStr_TX =
{
	0,
	0,
	DMA_SourceIncByte,
	DMA_DestIncNo,
	DMA_MemoryDataSize_Byte,
	DMA_Mode_Basic,
	1,
	DMA_Transfers_1,
	DMA_SourcePrivileged,
	DMA_DestPrivileged
};
//-----------------------------------------------------------------------	
	DMA_ChannelInitTypeDef DMA_InitStr_TX =
{
	&DMA_PriCtrlStr_TX,
	&DMA_PriCtrlStr_TX,
	DMA_AHB_Privileged,
	DMA_Priority_High, 
	DMA_BurstClear, 
	DMA_CTRL_DATA_PRIMARY
};
//-----------------------------------------------------------------------
void SEND_DATA_SPI2_DMA(uint8_t* SourceBuffer, uint32_t Length)
{
	DMA_PriCtrlStr_TX.DMA_SourceBaseAddr 	= (uint32_t) SourceBuffer;
	DMA_PriCtrlStr_TX.DMA_DestBaseAddr 		= (uint32_t) (&(MDR_SSP2->DR));
	DMA_PriCtrlStr_TX.DMA_CycleSize = Length;

	DMA_Init(DMA_Channel_SSP2_TX, &DMA_InitStr_TX);
	
	SSP_DMACmd(MDR_SSP2, SSP_DMA_TXE, ENABLE);
	DMA_Cmd(DMA_Channel_SSP2_TX, ENABLE);
}
//-----------------------------------------------------------------------
