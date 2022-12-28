#include "led_funcs.h"
#include "math.h"

/*
----------------------------------------
��� ����� ��� ��������� ��� ������
������� ��������� �����, ������ � ������� ��� ����� �������� � ��������
������ �������� ���: 300 ������������ ��������: 100 ����� �� 3. ������ ������ �� ��� ��� ��� ����� �� 0 �� 255(�����, �������, �������)
����� ������� ���� ��������� � ������ ������������, �� ���������� ���������������� ����� register_alg
----------------------------------------
*/
//-----------------------------------------------------------------------
void clear(double delta_time, uint8_t* data, uint16_t speed)
{
	// ������� ������ ������ ��� �������� ��� ������ ����������
		for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = 0;
	}
}
//-----------------------------------------------------------------------
void glow_white(double delta_time, uint8_t* data, uint16_t speed)
{
	// ���� ���� �������
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = MAX_BRIGHTNESS;
	}
}
//-----------------------------------------------------------------------
void breath_colors1(double delta_time, uint8_t* data, uint16_t speed)
{
	// ����� ������ ���� ����� �� �������
	static uint8_t dir = 1;
	static uint8_t brightness = MAX_BRIGHTNESS;
	
	static COLORS color = 0;
	static uint8_t bc1_colors_array[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 1}, {0, 1, 1}};
	
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
		data[i] = brightness * bc1_colors_array[color][0];
		data[i+1] = brightness * bc1_colors_array[color][1];
		data[i+2] = brightness * bc1_colors_array[color][2];
	}
}
//-----------------------------------------------------------------------
void running_red1(double delta_time, uint8_t* data, uint16_t speed)
{
	// ������� ����� ������ ����������� ������� �������
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i++)
	{
		data[i] = 0;
	}
	static uint16_t rr_active_red = 0;
	data[rr_active_red] = 0; //�����
	data[rr_active_red+1] = MAX_BRIGHTNESS; //�������
	data[rr_active_red+2] = 0; //�������
	rr_active_red+=3;
	if (rr_active_red>LEDS_NUMBER*3) rr_active_red=0;
}
//-----------------------------------------------------------------------
void breath_colors2(double delta_time, uint8_t* data, uint16_t speed)
{
		// ����� ������ ���� ����� ������

	static double bc2_k1 = 0; //��� ���������� �������� ��� ������ ���������
	static double bc2_k2 = 0.33; // ���������� ��������� ����, ������ ��������
	static double bc2_k3 = 0.66; // ���������� ��������� ����, ������ ��������

	double temp = delta_time * speed/300;
	bc2_k1 = bc2_k1 + temp;
	bc2_k2 = bc2_k2 + temp;
	bc2_k3 = bc2_k3 + temp;
	
	/*�� ����� ���� ������ ������ 1*/
	while (bc2_k1>1) bc2_k1--;
	while (bc2_k2>1) bc2_k2--;
	while (bc2_k3>1) bc2_k3--;
	
	double s1, s2, s3;
	s1 = MAX_BRIGHTNESS/3 * sin(2 * M_PI * bc2_k1)+MAX_BRIGHTNESS/2;
	s2 = MAX_BRIGHTNESS * sin(2 * M_PI * bc2_k2)+MAX_BRIGHTNESS/2;
	s3 = MAX_BRIGHTNESS/2 * sin(2 * M_PI * bc2_k3)+MAX_BRIGHTNESS/2;
	
	if (s1 < 0) s1 = 0; // ���� ��������� ������ ����, �� �������� �� ������.
	if (s2 < 0) s2 = 0;
	if (s3 < 0) s3 = 0;
	
	for (uint16_t i = 0; i< LEDS_NUMBER*3; i+=3)
	{
		data[i] = (uint8_t)s1;
		data[i+1] = (uint8_t)s2; 
		data[i+2] = (uint8_t)s3; 
	}
	
}
//-----------------------------------------------------------------------
void breath_white2(double delta_time, uint8_t* data, uint16_t speed)
{
	//����� �����
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
//-----------------------------------------------------------------------
void running_color(double delta_time, uint8_t* data, uint16_t speed)
{
	// ������ � ��� ������� � ��������
	// �� ������� ���������� ������, ����� ������������ ������ ������
	static uint8_t rc_color_array[10][3] = {
		{0,MAX_BRIGHTNESS/2,0},//������ �
		{MAX_BRIGHTNESS/4,MAX_BRIGHTNESS,0}, //� + ������ �
		{MAX_BRIGHTNESS, MAX_BRIGHTNESS,0}, //�
		{MAX_BRIGHTNESS,0, MAX_BRIGHTNESS}, //�
		{MAX_BRIGHTNESS, 20, 20}, //� + ������ �����
		{MAX_BRIGHTNESS, 20, 20}, //� + ������ �����
		{MAX_BRIGHTNESS,0, MAX_BRIGHTNESS}, //�
		{MAX_BRIGHTNESS, MAX_BRIGHTNESS,0}, //�
		{MAX_BRIGHTNESS/4,MAX_BRIGHTNESS,0}, //� + ������ �
		{0,MAX_BRIGHTNESS/2,0}//������ �
	};

	static uint8_t rc_phase = PHASE_UP;
	static double rc_k = 0;
	double rc_scratch_threshold=0.65;
	uint8_t rc_scratch_reset_value = 7;
	static uint8_t rc_scratch_countdown = 0;	
	static uint8_t rc_scratching_now = 4;
	static uint16_t rc_speed_temp;
	
	if (rc_k>1) 
	{
		rc_phase=PHASE_DOWN;
		rc_k=1;
		if (rc_scratch_countdown>0) rc_scratch_countdown--;
	}
	if (rc_k<0) 
	{
		rc_phase=PHASE_UP;
		rc_k=0;
		if (rc_scratch_countdown>0) rc_scratch_countdown--;
	}
	
	if (rc_scratch_countdown==0) // ������ ����!
	{
		if ((rc_phase==PHASE_UP)&(rc_k>rc_scratch_threshold))
		{
			rc_phase=PHASE_DOWN;
			if (rc_scratching_now==0) rc_speed_temp*=2;
			rc_scratching_now++;
			
		}
		if ((rc_phase==PHASE_DOWN)&(rc_k<(1-rc_scratch_threshold)))
		{
			rc_phase=PHASE_UP;
			if (rc_scratching_now==0) rc_speed_temp*=2;
			rc_scratching_now++;
		}
		if (rc_scratching_now>=4) // ������ ��� =(
		{
			rc_scratch_countdown = rc_scratch_reset_value;
			rc_scratching_now = 0;
			rc_speed_temp=speed;
		}
	}
	
	
	if (rc_phase==PHASE_UP)	rc_k += delta_time*rc_speed_temp/100;
	else rc_k -= delta_time*rc_speed_temp/100;
	
	int ind = (int)(floor(rc_k * 100));

	for (uint16_t i = 0; i<10;i++)
	{
		int z = (ind+i)*3;
		if (!(z<LEDS_NUMBER*3))
		{
			//z ������ 297. ������ �������
			data[LEDS_NUMBER*3-3] = 0;
			data[LEDS_NUMBER*3-2] = MAX_BRIGHTNESS;
			data[LEDS_NUMBER*3-1] = 0;
		}
		else if (!(z>0))
		{
			//z �������������. ����� �������
			data[0] = 0;
			data[1] = MAX_BRIGHTNESS;
			data[2] = 0;
		}
		else
		{
			//�� ���������
			data[z] = rc_color_array[i][0];
			data[z+1] = rc_color_array[i][1];
			data[z+2] = rc_color_array[i][2];
		}
	}
}
//-----------------------------------------------------------------------
void running_color2(double delta_time, uint8_t* data, uint16_t speed)
{
	clear(delta_time, data, speed);
	running_color(delta_time, data, speed);
	
}
//-----------------------------------------------------------------------
void running_color3(double delta_time, uint8_t* data, uint16_t speed)
{
	breath_colors2(delta_time, data, speed/2);
	running_color(delta_time,data,speed);
}
//-----------------------------------------------------------------------
void running_color4(double delta_time, uint8_t* data, uint16_t speed)
{
	breath_colors1(delta_time, data, speed/2);
	running_color(delta_time,data,speed);
}
//-----------------------------------------------------------------------
