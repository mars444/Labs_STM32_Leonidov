#ifndef __MAIN_H
#define	__MAIN_H

#include "stm32f1xx.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"

/* Размеры буферов приёма и передачи */
#define	RX_BUFF_SIZE	256
#define TX_BUFF_SIZE	256

#define DELAY_VAL		1000000

/* Управление светодиодами */
#define	LED_ON()		GPIOA->BSRR = GPIO_BSRR_BS5
#define	LED_OFF()		GPIOA->BSRR = GPIO_BSRR_BR5
#define LED_SWAP()		GPIOA->BSRR = 0x1F30000;

/* Прототипы функций */
void initUSART2(void);
void txStr(char *str, bool crlf);
void ExecuteCommand(void);
void initClk(void);
void initPorts(void);
void initButton(void);
void initTIM2(void);
void delay(uint32_t takts);

void initButton_11(void);


#include "stm32f1xx.h"
#include "stdbool.h"

#define DELAY_VAL		1000000



/* Прототипы функций */
void initClk(void);
void initPorts(void);
void initButton(void);
void initTIM2(void);
void delay(uint32_t takts);


// Величина задержки между вкл/выкл светодиодов
#define DELAY_VALUE	delay(100000)

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

void initButton_10(void);
void initButton_9(void);

#endif
