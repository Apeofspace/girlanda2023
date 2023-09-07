#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK


/* "Коды клавиш" */
typedef enum {
    NOKEY      = 0,
    SEL        = 1,
    RIGHT      = 2,
    LEFT       = 3,
    UP         = 4,
    DOWN       = 5,
    MULTIPLE   = 6,
    NUM_KEY_CODES
} KeyCode;

void init_joystick(void);

/* Определение "кода" по нажатым кнопкам */
KeyCode joystick_get_key(void);

#define KEY_PRESSED(x)              (GetKey() == x)
#define WAIT_UNTIL_KEY_PRESSED(x)   while(!KEY_PRESSED(x)){}
#define WAIT_UNTIL_KEY_RELEASED(x)  while(KEY_PRESSED(x)){}
#define WAIT_UNTIL_ANY_KEY          while(GetKey() == NOKEY){}

