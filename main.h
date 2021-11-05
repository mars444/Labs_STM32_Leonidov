#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f1xx.h"

// Величина задержки между вкл/выкл светодиодов
#define DELAY_VALUE	delay(200000)

#define ON_NUMBER_0  GPIOA->BSRR = 0x1F2
#define ON_NUMBER_1  GPIOA->BSRR = 0xC0
#define ON_NUMBER_2  GPIOA->BSRR = 0x1B1
#define ON_NUMBER_3  GPIOA->BSRR = 0x1E1
#define ON_NUMBER_4  GPIOA->BSRR = 0xC3
#define ON_NUMBER_5  GPIOA->BSRR = 0x163
#define ON_NUMBER_6  GPIOA->BSRR = 0x173
#define ON_NUMBER_7  GPIOA->BSRR = 0x1C0
#define ON_NUMBER_8  GPIOA->BSRR = 0x1F3
#define ON_NUMBER_9  GPIOA->BSRR = 0x1E3

#define RESET_NUMBER GPIOA->BSRR = 0x1F30000;


/* Прототипы функций */
void delay(uint32_t takts);
int func_onn(int number);
void Reset_number(void);
void port_configuration(void);
void loop(void);

#endif /* MAIN_H_ */
