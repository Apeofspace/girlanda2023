#include "main.h"

void glow_white(cur_time_t time, uint8_t* data)
{
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = 0xFF;
	}
}

void breath_white1(cur_time_t time, uint8_t* data)
{
	static uint8_t dir = 1;
	static uint8_t step = 30;
	static uint8_t brightness = 255;
	
	if (brightness<step) dir = 0;
	if (brightness>(255-step)) dir = 1;
	brightness = (dir==0)? brightness+step : brightness-step;
	
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = brightness;
	}
}

void running_red1(cur_time_t time, uint8_t* data)
{
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = 0x0F;
	}
	static uint16_t active_red = 0;
	data[active_red] = 0;
	data[active_red+1] = 0xFF;
	data[active_red+2] = 0;
	active_red+=3;
	if (active_red>LEDS_NUMBER*3) active_red=0;
}

//uint32_t* breathing_color_wave