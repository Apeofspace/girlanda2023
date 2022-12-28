#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "time.h"
#include "stdlib.h"

#define LEDS_NUMBER 100
typedef enum {R, G, B, RG, RB, GB}COLORS;
typedef enum {PHASE_UP,PHASE_DOWN} phase_t;

#define MAX_BRIGHTNESS 100
#define M_PI 3.14159265358979323846

/*Algorythms*/
void glow_white(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness);
void running_red1(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness);
void breath_colors1(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness);
void breath_white2(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness);
void breath_colors2(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness);
void running_color2(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness);
void running_color3(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness);
void running_color4(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness);
