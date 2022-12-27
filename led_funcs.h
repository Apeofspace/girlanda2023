#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK

#define LEDS_NUMBER 100
typedef enum {R, G, B, RG, RB, GB}COLORS;

#define MAX_BRIGHTNESS 255

/*Algorythms*/
void glow_white(double delta_time, uint8_t* data, uint16_t speed);
void running_red1(double delta_time, uint8_t* data, uint16_t speed);
void breath_colors1(double delta_time, uint8_t* data, uint16_t speed);
void breath_white2(double delta_time, uint8_t* data, uint16_t speed);
