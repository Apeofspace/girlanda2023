#include "main.h"

uint8_t testdata[2400];

int main(){
	
	for (uint32_t del = 0 ; del<3000000; del++); // задержка для того, чтобы контроллер успел войти в режим отладки, если вдруг гдето сильный баг
	
	init_CPU();
	init_SPI();
	

	uint16_t i = 0;
	while (i < 2400)
	{
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		
			
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		
		
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;
		testdata[i++]=0xC0;

		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
		testdata[i++]=0xF0;
	}

	init_TIMER1();
	

	
	while(1)
	{
		
	}
}
