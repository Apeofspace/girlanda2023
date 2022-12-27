#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_timer.h"            // Keil::Drivers:TIMER
#include "MDR32F9Qx_ssp.h"              // Keil::Drivers:SSP
#include "joystick.h"


#define SPI2_CLK PORT_Pin_5 
#define SPI2_RXD PORT_Pin_2
#define SPI2_TXD PORT_Pin_6
#define SPI2_PORT MDR_PORTD

#define LEDS_NUMBER 100

#define ONE 0xF0
#define ZERO 0xC0

typedef enum {R, G, B, RG, RB, GB}COLORS;

/* Inits */
void init_CPU(void);
void init_TIMER1(void);
void init_TIMER2(void);
void init_SPI(void);

/* IRQs */
void Timer1_IRQHandler(void);
void Timer2_IRQHandler(void);

/*Time*/
typedef double cur_time_t;
extern uint32_t seconds;
cur_time_t get_delta_time(void);
void reset_time(void);

/*Funcs*/
void register_alg(void alg(cur_time_t delta_time, uint8_t* data, uint16_t speed));
void update_leds(void);
void clear_leds(void);
void convert_array(uint8_t* arr, uint8_t* result);

/*DATA ARRAYS*/
extern uint8_t leds_data_rgb[LEDS_NUMBER*3];
extern uint8_t leds_data_corrected[LEDS_NUMBER*24];
typedef struct
{
	void (*funcs[20])(cur_time_t delta_time, uint8_t* data, uint16_t speed);
	uint8_t total_registered;
	uint8_t currently_selected;
	uint16_t speed;
} alg_functions_t;
extern alg_functions_t alg_functions;


/*Algorythms*/
void glow_white(cur_time_t delta_time, uint8_t* data, uint16_t speed);
void running_red1(cur_time_t delta_time, uint8_t* data, uint16_t speed);
void breath_colors1(cur_time_t delta_time, uint8_t* data, uint16_t speed);
void breath_white2(cur_time_t delta_time, uint8_t* data, uint16_t speed);
