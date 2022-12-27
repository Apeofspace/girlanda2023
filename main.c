#include "main.h"


int main(){
	
	for (uint32_t del = 0 ; del<3000000; del++); // задержка для того, чтобы контроллер успел войти в режим отладки, если вдруг гдето сильный баг
	
	init_CPU();
	init_SPI();
	
	alg_functions.currently_selected = 0;
	alg_functions.total_registered = 0;
	init_joystick();
	
	register_alg(running_red1);
	register_alg(breath_white1);
	
	init_TIMER1();
	init_TIMER2();	
	
	
	while(1)
	{
		switch (joystick_get_key())
		{
			case NOKEY:
				break;
			case SEL:
				clear_leds();
				update_leds();
			//doesnt do much
				break;
			case RIGHT:
				NVIC_DisableIRQ(Timer2_IRQn); //разрешить прерывания таймера	
				alg_functions.currently_selected++;
				if (alg_functions.currently_selected>alg_functions.total_registered-1) alg_functions.currently_selected = 0;
				NVIC_EnableIRQ(Timer2_IRQn); //разрешить прерывания таймера	
				break;
			case LEFT:
				NVIC_DisableIRQ(Timer2_IRQn); //разрешить прерывания таймера
				if (alg_functions.currently_selected == 0) alg_functions.currently_selected = alg_functions.total_registered-1;
				else if (alg_functions.total_registered > 1 )	alg_functions.currently_selected--;
				NVIC_EnableIRQ(Timer2_IRQn); //разрешить прерывания таймера	
				break;
			case UP:
				break;
			case DOWN:
				break;
			case MULTIPLE:
				break;
		}
	}
}
