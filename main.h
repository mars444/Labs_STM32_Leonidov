#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f1xx.h"

// Величина задержки между вкл/выкл светодиодов
#define DELAY_VAL	100000

#define ON_NUMBER_0  GPIOA->BSRR = 0x1F2
#define ON_NUMBER_1  GPIOA->BSRR = 0xC0
#define ON_NUMBER_2  GPIOA->BSRR = 0x1B1
#define ON_NUMBER_3  GPIOA->BSRR = 0x1E1
#define ON_NUMBER_4  GPIOA->BSRR = 0xC3
#define ON_NUMBER_5  GPIOA->BSRR = 0x163
#define ON_NUMBER_6  GPIOA->BSRR = 0x173
#define ON_NUMBER_7  GPIOA->BSRR = 0x1C0
#define ON_NUMBER_8  GPIOA->BSRR = 0x1F3
#define ON_NUMBER_9  GPIOA->BSRR = 0xF1


/* Прототипы функций */
void delay(uint32_t takts);
int func_onn(int number);

#endif /* MAIN_H_ */
