#include "main.h"



int main(){
	uint8_t pause = 0;
	
	for (uint32_t del = 0 ; del<3000000; del++); // �������� ��� ����, ����� ���������� ����� ����� � ����� �������, ���� ����� ����� ������� ���
	
	init_CPU();
	init_SPI();
	
	alg_functions.currently_selected = 0;
	alg_functions.total_registered = 0;
	alg_functions.speed = 100;
	init_joystick();
	
	srand(12568);
	
	/*!!����������� ����������!!*/
//	register_alg(breath_colors3);
	register_alg(running_color2);
	register_alg(breath_colors2);
	register_alg(running_red1);
	register_alg(breath_colors1);
//	register_alg(breath_white2);
	/*--------------------------*/
	
	init_TIMER1();
	init_TIMER2();	
	
	while(1)
	{
		switch (joystick_get_key())
		{
			case NOKEY:
				break;
			case SEL:	
				if (pause == 0)
				{
					pause = 1;
					NVIC_DisableIRQ(Timer2_IRQn); //��������� ���������� �������
				}
				else
				{
					pause = 0;
					reset_time();
					NVIC_EnableIRQ(Timer2_IRQn);
				}
				break;
			case RIGHT:
				NVIC_DisableIRQ(Timer2_IRQn); //��������� ���������� �������	
				alg_functions.currently_selected++;
				if (alg_functions.currently_selected>alg_functions.total_registered-1) alg_functions.currently_selected = 0;
				NVIC_EnableIRQ(Timer2_IRQn); //��������� ���������� �������	
				break;
			case LEFT:
				NVIC_DisableIRQ(Timer2_IRQn); //��������� ���������� �������
				if (alg_functions.currently_selected == 0) alg_functions.currently_selected = alg_functions.total_registered-1;
				else if (alg_functions.total_registered > 1 )	alg_functions.currently_selected--;
				NVIC_EnableIRQ(Timer2_IRQn); //��������� ���������� �������	
				break;
			case UP:
				if (alg_functions.speed<400) alg_functions.speed+=20;
				break;
			case DOWN:
				if (alg_functions.speed>20)	alg_functions.speed-=20;
				break;
			case MULTIPLE:
				break;
			case NUM_KEY_CODES:
				break;
		}
	}
}
