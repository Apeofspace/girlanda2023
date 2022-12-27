#include "main.h"

void Timer1_IRQHandler()
{
	/*������� ������*/
	MDR_TIMER1->STATUS &= ~(TIMER_STATUS_CNT_ARR_EVENT);
	seconds++;	
}

void Timer2_IRQHandler()
{
	/*����������*/
	MDR_TIMER2->STATUS &= ~(TIMER_STATUS_CNT_ARR_EVENT);
	
	alg_functions.funcs[alg_functions.currently_selected](get_time(), leds_data_rgb); // ����� ������� ���������
	convert_array(leds_data_rgb, leds_data_corrected); // ����������� �������
	update_leds(); // ��������� �� ��������
}
