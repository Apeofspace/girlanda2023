#include "main.h"

void Timer1_IRQHandler()
{
	MDR_TIMER1->STATUS &= ~(TIMER_STATUS_CNT_ARR_EVENT);
	seconds++;	
	
	breath_white1(0, leds_data_rgb);
	convert_array(leds_data_rgb, leds_data_corrected);
	update_leds();
	
}
