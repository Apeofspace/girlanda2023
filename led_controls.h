#include "main.h"

#define LEDS_NUMBER 100

#define ONE 0xF0
#define ZERO 0xC0


/*Funcs*/
void register_alg(void alg(void));
void update_leds(void);
void clear_leds(void);
uint8_t* convert_array(uint8_t* arr);


/*Time*/
typedef double cur_time_t;

cur_time_t get_time(void);
void reset_time(void);


/*DATA ARRAYS*/
extern uint8_t leds_data[LEDS_NUMBER*3];
extern uint8_t leds_data_corrected[LEDS_NUMBER*24];
extern void (*alg_functions[10])(cur_time_t time);
