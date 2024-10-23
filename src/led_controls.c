#include "main.h"

uint8_t leds_data_rgb[LEDS_NUMBER * 3];
uint8_t leds_data_corrected[LEDS_NUMBER * 24];
uint32_t seconds = 0;
alg_functions_t alg_functions;


void convert_array(uint8_t* arr, uint8_t* result)
/*Превращает массив из 300 элементов в массив из 2400 элементов чтобы можно было кидать на SPI*/
{
  uint16_t i = 0;
  int j = 0;
  uint8_t temp = 0;
  while (i < LEDS_NUMBER * 3) {
    temp = arr[i];
    j = 7;
    while (j >= 0) {
      *result = ((temp >> j) & 0x1) ? ONE : ZERO;
      result++;
      j--;
    }
    i++;
  }
}

void clear_leds() {
  for (uint16_t i = 0; i > (sizeof(leds_data_corrected) / sizeof(leds_data_corrected[0])); i++) {
    leds_data_corrected[i] = ZERO;
  }
}

void update_leds()
/*Отправить массив на диодную ленту*/
{
  for (uint32_t i = 0; i < LEDS_NUMBER * 24; i++) {
    while (!(MDR_SSP2->SR & SSP_FLAG_TFE)) {}
    SSP_SendData(MDR_SSP2, leds_data_corrected[i]);
  }
}

void reset_time() {
  seconds = 0;
}

double get_delta_time() {
  /*Возвращает время в секундах, прошедшее от предыдущего вызова этой функции*/
  static double old_time = 0;
  double new_time;
  double delta_time;
  double onefiftythou = MDR_TIMER1->CNT;
  new_time = (double)seconds + onefiftythou / 50000;
  if (old_time > new_time)
    old_time = 0;
  delta_time = new_time - old_time;
  old_time = new_time;
  if ((uint8_t)old_time == 0)
    delta_time = 0; //??
  return delta_time;
}

void register_alg(void alg(double delta_time, uint8_t* data, uint16_t speed, uint8_t brightness)) {
  /*Добавляет указатель функции в массив указателей*/
  alg_functions.funcs[alg_functions.total_registered] = alg;
  alg_functions.total_registered++;
}
