/* 
Миландровская библиотека переписанная так, чтобы на неё не так страшно было смотреть
Ловит нажатия кнопочек на платочке от LDM
*/

#include "joystick.h"


void init_joystick(void) {
		PORT_InitTypeDef GPIO_user_init;
		
//		GPIO_user_init.PORT_OE        = PORT_OE_OUT;
//		GPIO_user_init.PORT_PULL_UP   = PORT_PULL_UP_OFF;
//		GPIO_user_init.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
//		GPIO_user_init.PORT_PD_SHM    = PORT_PD_SHM_OFF;
//		GPIO_user_init.PORT_PD        = PORT_PD_DRIVER;
//		GPIO_user_init.PORT_GFEN      = PORT_GFEN_OFF;
//		GPIO_user_init.PORT_SPEED     = PORT_SPEED_MAXFAST;		
		GPIO_user_init.PORT_FUNC      = PORT_FUNC_MAIN;
		GPIO_user_init.PORT_MODE      = PORT_MODE_DIGITAL;	
		
		
		GPIO_user_init.PORT_Pin       = (PORT_Pin_5|PORT_Pin_6);
		RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
		PORT_Init(MDR_PORTB, &GPIO_user_init);
	
		GPIO_user_init.PORT_Pin       = (PORT_Pin_2);
		RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
		PORT_Init(MDR_PORTC, &GPIO_user_init);
		
		GPIO_user_init.PORT_Pin       = (PORT_Pin_1|PORT_Pin_3);
		RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);
		PORT_Init(MDR_PORTE, &GPIO_user_init);
}

/* Определение "кода" по нажатым кнопкам */
KeyCode joystick_get_key(void) {
    uint32_t i, sKey;
    static uint32_t data[5];
	
//		// костыль чтобы на всякий случай забить массив нулями, ибо я не доверяю миландру
//		static enum {first_launch, not_first_launch} first_launch_kostil = first_launch; 
//		if (first_launch_kostil == first_launch){
//			for(i=0;i<5;i++) data[i]=1;
//			first_launch_kostil = not_first_launch;
//		}

		//сдвигаем все буферы на 1 влево
		for(i=0;i<5;i++) data[i] = (data[i]<<1); 
		
		// Собираем данные с кнопок в массив с инверсией  значений (1 - нажата, 0 - не нажата)
    if(!(MDR_PORTC->RXTX & (1<<2))) data[0] = (data[0]|=0x1UL);   /* SEL      PC2*/
    if(!(MDR_PORTB->RXTX & (1<<6))) data[1] = (data[1]|=0x1UL);   /* RIGHT    PB6*/
    if(!(MDR_PORTE->RXTX & (1<<3))) data[2] = (data[2]|=0x1UL);   /* LEFT     PE3*/
    if(!(MDR_PORTB->RXTX & (1<<5))) data[3] = (data[3]|=0x1UL);   /* UP       PB5*/
    if(!(MDR_PORTE->RXTX & (1<<1))) data[4] = (data[4]|=0x1UL);   /* DOWN     PE1*/
		
				//Устроняем дребезг
		uint32_t jitter_mask = 0x1F;
		uint32_t actual_data[5];
		for(i=0;i<5;i++){			
			if (data[i]==jitter_mask) actual_data[i] = 1;
			else actual_data[i] = 0;
		}
		
    // Суммируем состояния кнопок
    sKey=0;
    for(i=0;i<5;i++) sKey = sKey + actual_data[i];

    if(sKey == 0) return NOKEY;/* NOKEY    */ 
    else if (sKey > 1) return MULTIPLE;/* MULTIPLE */
		
    for(i=0;i<5;i++) if(actual_data[i] == 1) return ((KeyCode)(i+1)); // Если нажата только одна кнопка, то распознаем её
}
