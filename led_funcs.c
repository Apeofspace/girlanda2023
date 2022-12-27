#include "led_funcs.h"
#include "math.h"

void glow_white(double delta_time, uint8_t* data, uint16_t speed)
{
	// тупо макс яркость
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = MAX_BRIGHTNESS;
	}
}

void breath_colors1(double delta_time, uint8_t* data, uint16_t speed)
{
	// цвета меняют друг друга по очереди
	static uint8_t dir = 1;
	static uint8_t brightness = MAX_BRIGHTNESS;
	
	static COLORS color = 0;
	static uint8_t colors_array[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 1}, {0, 1, 1}};
	
	uint8_t step = (uint8_t)((double)speed/100 * MAX_BRIGHTNESS * (double)delta_time);
	
	if (brightness<step) 
	{
		dir = 0;
		color++;
		if (color>5) color = 0;
	}
	if (brightness>(MAX_BRIGHTNESS-step)) dir = 1;
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
	// красная фигня бегает
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = 0;
	}
	static uint16_t active_red = 0;
	data[active_red] = 0;
	data[active_red+1] = MAX_BRIGHTNESS;
	data[active_red+2] = 0;
	active_red+=3;
	if (active_red>LEDS_NUMBER*3) active_red=0;
}

void breath_colors2(double delta_time, uint8_t* data, uint16_t speed)
{
		// цвета меняют друг друга плавно
//	три синусоиды сдвинутые на 120 и если меньше 0 то 0
	
	static double bc2_k1 = 0; //это количество периодов для первой синусоиды
	double bc2_k2 = 0; // достаточно запомнить один, другие сдвинуты
	double bc2_k3 = 0; // достаточно запомнить один, другие сдвинуты

	bc2_k1 = bc2_k1 + delta_time * speed/300;
	bc2_k2 = bc2_k1 + 0.33;
	bc2_k3 = bc2_k1 + 0.66;
	
	
	/*Не важно если период больше 1*/
	while (bc2_k1>1) 
	{
		bc2_k1--;
		bc2_k2--;
		bc2_k3--;
	}
	
	double s1, s2, s3;
	s1 = MAX_BRIGHTNESS * sin(2 * M_PI * bc2_k1);
	s2 = MAX_BRIGHTNESS * sin(2 * M_PI * bc2_k2);
	s3 = MAX_BRIGHTNESS * sin(2 * M_PI * bc2_k3);
	if (s1 < 0) s1 = 0; // если синусоида меньше нуля, то обнуляем ее совсем.
	if (s2 < 0) s2 = 0;
	if (s3 < 0) s3 = 0;
	
//	//всяческая коррекция 
//	if (s1 > MAX_BRIGHTNESS/4) s1 = MAX_BRIGHTNESS/4;
//	if (s2 > MAX_BRIGHTNESS/4) s2 = MAX_BRIGHTNESS/4;
//	if (s3 > MAX_BRIGHTNESS/4) s3 = MAX_BRIGHTNESS/4;
	
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i+=3)
	{
		data[i] = (uint8_t)s1;
		data[i+1] = (uint8_t)s2; 
		data[i+2] = (uint8_t)s3; 
	}
	
}

void breath_white2(double delta_time, uint8_t* data, uint16_t speed)
{
	//дышит белым
	static uint8_t dir = 1;
	static uint8_t brightness = MAX_BRIGHTNESS;
	uint8_t step = (uint8_t)((double)speed/100 * MAX_BRIGHTNESS * (double)delta_time);
	
	if (brightness<step) dir = 0;
	if (brightness>(MAX_BRIGHTNESS-step)) dir = 1;
	brightness = (dir==0)? brightness+step : brightness-step;
	
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = brightness;
	}
}
