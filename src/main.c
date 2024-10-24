#include "main.h"

//TODO: нормальные докстринги.
//TODO: ридми
//TODO: более нормальное название и структура алгоритмов.
//TODO: избавиться от статиков, пусть память выделяется динамично. в этом не должно быть проблем, так как одновременно запущен только 1 алоритм.
//TODO: больше красивых цветастых


static void joystick_poll_loop() {
  static uint8_t pause = 0;
  switch (joystick_get_key()) {
  case NOKEY:
    break;
  case SEL:
    if (pause == 0) {
      pause = 1;
      NVIC_DisableIRQ(Timer2_IRQn); //разрешить прерывания таймера
    } else {
      pause = 0;
      reset_time();
      NVIC_EnableIRQ(Timer2_IRQn);
    }
    break;
  case RIGHT:
    NVIC_DisableIRQ(Timer2_IRQn); //разрешить прерывания таймера
    alg_functions.currently_selected++;
    if (alg_functions.currently_selected > alg_functions.total_registered - 1)
      alg_functions.currently_selected = 0;
    NVIC_EnableIRQ(Timer2_IRQn); //разрешить прерывания таймера
    break;
  case LEFT:
    NVIC_DisableIRQ(Timer2_IRQn); //разрешить прерывания таймера
    if (alg_functions.currently_selected == 0)
      alg_functions.currently_selected = alg_functions.total_registered - 1;
    else if (alg_functions.total_registered > 1 )
      alg_functions.currently_selected--;
    NVIC_EnableIRQ(Timer2_IRQn); //разрешить прерывания таймера
    break;
  case UP:
    if (alg_functions.speed < 400)
      alg_functions.speed += 20;
    break;
  case DOWN:
    if (alg_functions.speed > 20)
      alg_functions.speed -= 20;
    break;
  case MULTIPLE:
    break;
  case NUM_KEY_CODES:
    break;
  }
}

int main() {

  for (uint32_t del = 0 ; del < 3000000;
       del++); // задержка для того, чтобы контроллер успел войти в режим отладки, если вдруг гдето сильный баг

  init_CPU();
  init_SPI();

  alg_functions.currently_selected = 0;
  alg_functions.total_registered = 0;
  alg_functions.speed = 100; //1Hz
  init_joystick();

  /*!!Регистрация алгоритмов!!*/
  register_alg(running_color2);
  register_alg(running_color3);
  register_alg(breath_colors3);
  // register_alg(running_color4);
  register_alg(breath_colors2);
//	register_alg(running_red1);
  register_alg(breath_colors1);
  /*--------------------------*/

  init_TIMER1();
  init_TIMER2();

  while (1) {
    joystick_poll_loop();
  }
}

