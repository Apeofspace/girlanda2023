#include "main.h"

void Timer1_IRQHandler()
{
	MDR_TIMER1->STATUS &= ~(TIMER_STATUS_CNT_ARR_EVENT);
	seconds++;	
	
	glow_white(0, leds_data_rgb);
	convert_array(leds_data_rgb, leds_data_corrected);
	update_leds();
	
}
