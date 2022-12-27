#include "led_funcs.h"

void glow_white(double delta_time, uint8_t* data, uint16_t speed)
{
	// тупо макс €ркость
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = 0xFF;
	}
}

void breath_colors1(double delta_time, uint8_t* data, uint16_t speed)
{
	// цвета мен€ют друг друга по очереди
	static uint8_t dir = 1;
	static uint8_t brightness = 255;
	
	static COLORS color = 0;
	static uint8_t colors_array[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 1}, {0, 1, 1}};
	
	uint8_t step = (uint8_t)((double)speed * (double)delta_time);
	
	if (brightness<step) 
	{
		dir = 0;
		color++;
		if (color>5) color = 0;
	}
	if (brightness>(255-step)) dir = 1;
	brightness = (dir==0)? brightness+step : brightness-step;
	
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i+=3)
	{
		data[i] = brightness * colors_array[color][0];
		data[i+1] = brightness * colors_array[color][1];
		data[i+2] = brightness * colors_array[color][2];
	}
}

void running_red1(double delta_time, uint8_t* data, uint16_t speed)
{
	// красна€ фигн€ бегает
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = 0;
	}
	static uint16_t active_red = 0;
	data[active_red] = 0;
	data[active_red+1] = 0xFF;
	data[active_red+2] = 0;
	active_red+=3;
	if (active_red>LEDS_NUMBER*3) active_red=0;
}

void breath_colors2(double delta_time, uint8_t* data, uint16_t speed)
{
		// цвета мен€ют друг друга плавно
//	static uint8_t dir = 1;
//	static uint8_t brightness = 255;
//	
//	static COLORS color = 0;
//	static uint8_t colors_array[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 1}, {0, 1, 1}};
//	
//	uint8_t step = (uint8_t)((double)speed * (double)delta_time);
//	
//	if (brightness<step) 
//	{
//		dir = 0;
//		color++;
//		if (color>5) color = 0;
//	}
//	if (brightness>(255-step)) dir = 1;
//	brightness = (dir==0)? brightness+step : brightness-step;
//	
//	for (uint16_t i = 0; i< LEDS_NUMBER*3; i+=3)
//	{
//		data[i] = brightness * colors_array[color][0];
//		data[i+1] = brightness * colors_array[color][1];
//		data[i+2] = brightness * colors_array[color][2];
//	}
}

void breath_white2(double delta_time, uint8_t* data, uint16_t speed)
{
	//дышит белым
	static uint8_t dir = 1;
	static uint8_t brightness = 255;
	uint8_t step = (uint8_t)((double)speed * (double)delta_time);
	
	if (brightness<step) dir = 0;
	if (brightness>(255-step)) dir = 1;
	brightness = (dir==0)? brightness+step : brightness-step;
	
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = brightness;
	}
}
