#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f1xx.h"

// Величина задержки между вкл/выкл светодиодов
#define DELAY_VAL	100000

/* Управление светодиодами */
#define	LED_ON_5	GPIOA->BSRR = GPIO_BSRR_BS5
#define	LED_OFF_5	GPIOA->BSRR = GPIO_BSRR_BR5

#define	LED_ON_0	GPIOA->BSRR = GPIO_BSRR_BS0
#define	LED_OFF_0	GPIOA->BSRR = GPIO_BSRR_BR0

#define	LED_ON_1	GPIOA->BSRR = GPIO_BSRR_BS1
#define	LED_OFF_1	GPIOA->BSRR = GPIO_BSRR_BR1

#define	LED_ON_4	GPIOA->BSRR = GPIO_BSRR_BS4
#define	LED_OFF_4	GPIOA->BSRR = GPIO_BSRR_BR4

#define	LED_ON_6	GPIOA->BSRR = GPIO_BSRR_BS6
#define	LED_OFF_6	GPIOA->BSRR = GPIO_BSRR_BR6

#define	LED_ON_7	GPIOA->BSRR = GPIO_BSRR_BS7
#define	LED_OFF_7	GPIOA->BSRR = GPIO_BSRR_BR7

#define	LED_ON_8	GPIOA->BSRR = GPIO_BSRR_BS8
#define	LED_OFF_8	GPIOA->BSRR = GPIO_BSRR_BR8


#define	BUTTON_1_SET_1	GPIOA->BSRR = GPIO_BSRR_BS9
#define	BUTTON_1_SET_0	GPIOA->BSRR = GPIO_BSRR_BR9


#define	BUTTON_2_SET_1	GPIOA->BSRR = GPIO_BSRR_BS9
#define	BUTTON_2_SET_0	GPIOA->BSRR = GPIO_BSRR_BR9




/* Прототипы функций */
void delay(uint32_t takts);
int func_onn(int number);

#endif /* MAIN_H_ */
