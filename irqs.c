#include "main.h"

void Timer1_IRQHandler()
{
	MDR_TIMER1->STATUS &= ~(TIMER_STATUS_CNT_ARR_EVENT);
//	GS.time.new_time.seconds++;
	
	static uint32_t max = sizeof(testdata)/sizeof(testdata[0]);	
	
	for (uint32_t i = 0; i < max; i++)
	{
		while (!(MDR_SSP2->SR&SSP_FLAG_TFE)){}
		SSP_SendData(MDR_SSP2, testdata[i]);
	}
	
}

