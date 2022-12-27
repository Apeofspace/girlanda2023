#include "main.h"


//void testfun(uint8_t* t)
//{
//	for (uint8_t i = 0; i<20;i++)
//	{
//		*t = i;
//		t++;
//	}
//}

int main(){
	
	for (uint32_t del = 0 ; del<3000000; del++); // задержка для того, чтобы контроллер успел войти в режим отладки, если вдруг гдето сильный баг
	
//	static uint8_t test[20];
//	uint8_t* p = test;
//	for (uint8_t i = 0; i<20;i++)
//	{
//		*p = i;
//		p++;
//	}
	
//	static uint8_t test[20];
//	testfun(test);
	
	init_CPU();
	init_SPI();
	init_TIMER1();
		
	while(1)
	{
		
	}
}
