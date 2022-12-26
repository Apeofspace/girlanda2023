#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_timer.h"            // Keil::Drivers:TIMER
#include "MDR32F9Qx_ssp.h"              // Keil::Drivers:SSP


#define SPI2_CLK PORT_Pin_5 
#define SPI2_RXD PORT_Pin_2
#define SPI2_TXD PORT_Pin_6
#define SPI2_PORT MDR_PORTD

/* Inits */
void init_CPU(void);
void init_TIMER1(void);
void init_SPI(void);

/* IRQs */
void Timer1_IRQHandler(void);


extern uint8_t testdata[2400];
