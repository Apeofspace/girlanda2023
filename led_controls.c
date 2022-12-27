#include "main.h"

uint8_t leds_data_rgb[LEDS_NUMBER*3];
uint8_t leds_data_corrected[LEDS_NUMBER*24];
uint32_t seconds = 0;
alg_functions_t alg_functions;


void convert_array(uint8_t* arr, uint8_t* result)
{
	uint16_t i = 0;
	int j = 0;
	uint8_t temp = 0;
	while(i<LEDS_NUMBER*3)
	{
		temp = arr[i];
		j = 7;
		while (j>=0)
		{		
			*result = ((temp>>j)&0x1)? ONE : ZERO;
			result++;
			j--;
		}
		i++;
	}
}

void clear_leds()
{
	for (uint16_t i = 0; i>(sizeof(leds_data_corrected)/sizeof(leds_data_corrected[0]));i++)
	{
		leds_data_corrected[i] = ZERO;
	}
}

void update_leds()
{
	for (uint32_t i = 0; i < LEDS_NUMBER*24; i++)
	{
		while (!(MDR_SSP2->SR&SSP_FLAG_TFE)){}
		SSP_SendData(MDR_SSP2, leds_data_corrected[i]);
	}
}

void reset_time()
{
		seconds = 0;
}

cur_time_t get_time()
{
	double onefiftythou = MDR_TIMER1->CNT;
	return (double)seconds + onefiftythou/50000;
}

void register_alg(void alg(cur_time_t time, uint8_t* data))
{
	alg_functions.funcs[alg_functions.total_registered] = alg;
	alg_functions.total_registered++;
}
