/**
  ******************************************************************************
  * @file    main.c
  * @author  Vladimir Leonidov
  * @version V1.0.0
  * @date    15.11.2021
  * @brief   Лабораторная работа №3 - "USART, DMA"
  *			 Отладочная плата: STM32F103 Nucleo
  *
  *			 Реализованы отправка и приём данных по USART.
  *			 Разработан простейший обработчик команд.
  *
  ******************************************************************************
  */

#include "main.h"


char RxBuffer[RX_BUFF_SIZE];					//Буфер приёма USART
char TxBuffer[TX_BUFF_SIZE];					//Буфер передачи USART
bool ComReceived;								//Флаг приёма строки данных

/**
  * @brief  Обработчик прерывания от USART2
  * @param  None
  * @retval None
  */

int number = 0;

int abc = 0;






void USART2_IRQHandler(void)
{
	if ((USART2->SR & USART_SR_RXNE)!=0)		//Прерывание по приёму данных?
	{
		uint8_t pos = strlen(RxBuffer);			//Вычисляем позицию свободной ячейки

		RxBuffer[pos] = USART2->DR;				//Считываем содержимое регистра данных

		if (RxBuffer[pos]== 0x0D)							//Если это символ конца строки
		{
			ComReceived = true;					//- выставляем флаг приёма строки
			return;								//- и выходим
		}
	}
}



/**
  * @brief  Подпрограмма обработчика прерывания
  *			по переполнению тайемера TIM2
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;			//Сброс флага переполнения

	//Проверка нажата ли кнопка
			DELAY_VALUE;

			if(number < 9) {
				number++;

			}

}

/**
  * @brief  Подпрограмма обработчика прерывания
  *			по внешнему импульсу на выводах (EXTI15-EXTI10)
  *			Нас интересует EXTI13, там висит кнопка.
  * @param  None
  * @retval None
  */

/**
  * @brief  Инициализация портов ввода-вывода
  * @param  None
  * @retval None
  */
void initPorts(void)
{

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;  //включить тактирование GPIOA и альтернативных функций

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE0_1;		//PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE1_1;		//PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE4_1;		//PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE5_1;		//PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE6_1;		//PA5 (LD3), выход 2МГц


	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE7_1;		//PA5 (LD3), выход 2МГц


	//очистка полей
	GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
	//и конфигурация
	GPIOA->CRH |= GPIO_CRH_MODE8_1;		//PA5 (LD3), выход 2МГц




	  GPIOA->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_MODE11);
	  GPIOA->CRH |= GPIO_CRH_CNF11_1;
	  GPIOA->BSRR |= GPIO_BSRR_BR11;


	  GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
	  GPIOA->CRH |= GPIO_CRH_CNF10_1;
	  GPIOA->BSRR |= GPIO_BSRR_BR10;
}

/**
  * @brief  Инициализация прерывания от кнопки (PC13)
  * @param  None
  * @retval None
  */

/**
  * @brief  Инициализация таймера TIM6
  * @param  None
  * @retval None
  */
void initTIM2(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;			//Включить тактирование TIM6

	//Частота APB1 для таймеров = APB1Clk * 2 = 32МГц * 2 = 64МГц
	TIM2->PSC = 64000-1;						//Предделитель частоты (64МГц/64000 = 1кГц)
	TIM2->ARR = 1000-1;							//Модуль счёта таймера (1кГц/1000 = 1с)
	TIM2->DIER |= TIM_DIER_UIE;					//Разрешить прерывание по переполнению таймера

	NVIC_EnableIRQ(TIM2_IRQn);					//Рарзрешить прерывание от TIM2
	NVIC_SetPriority(TIM2_IRQn, 1);				//Выставляем приоритет
}


/**
  * @brief  Инициализация систем тактирования:
  * 		Источник тактирования: HSI
  * 		Частота: 64МГц
  * @param  None
  * @retval None
  */
void initClk(void)
{
	// Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY)){};

	// Enable Prefetch Buffer
	FLASH->ACR |= FLASH_ACR_PRFTBE;

	// Flash 2 wait state
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_2;

	// HCLK = SYSCLK
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	// PCLK2 = HCLK
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

	// PCLK1 = HCLK/2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

	// PLL configuration: PLLCLK = HSI/2 * 16 = 64 MHz
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;
	RCC->CFGR |= RCC_CFGR_PLLMULL16;

	// Enable PLL
	RCC->CR |= RCC_CR_PLLON;

	// Wait till PLL is ready
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {};

	// Select PLL as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait till PLL is used as system clock source
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL){};
}

/**
  * @brief  Инициализация USART2
  * @param  None
  * @retval None
  */
void initUSART2(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;						//включить тактирование альтернативных ф-ций портов
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;					//включить тактирование UART2

	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);		//PA2 на выход
	GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1);

	GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);		//PA3 - вход
	GPIOA->CRL |= GPIO_CRL_CNF3_0;

	/*****************************************
	Скорость передачи данных - 115200     9600
	Частота шины APB1 - 32МГц

	1. USARTDIV = 32'000'000/(16*115200) = 17.4     208,3
	2. 17 = 0x11                                    208   D0
	3. 16*0.4 = 6	                                16*0,3 = 4,8 ~ 5
	4. Итого 0xd05
	*****************************************/
	USART2->BRR = 0xd05;

	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	USART2->CR1 |= USART_CR1_RXNEIE;						//разрешить прерывание по приему байта данных

	NVIC_EnableIRQ(USART2_IRQn);
}


/**
  * @brief  Передача строки по USART2 без DMA
  * @param  *str - указатель на строку
  * @param  crlf - если true, перед отправкой добавить строке символы конца строки
  * @retval None
  */
void txStr(char *str, bool crlf) {

	if (crlf)												//если просят,
		strcat(str,"\r");									//добавляем символ конца строки

	for (size_t i = 0; i < strlen(str); i++) {
		USART2->DR = str[i];								//передаём байт данных
		while ((USART2->SR & USART_SR_TC)==0) {};			//ждём окончания передачи
	}
}

/**
  * @brief  Обработчик команд
  * @param  None
  * @retval None
  */
void ExecuteCommand(void) {
//	txStr(RxBuffer, false);
	memset(TxBuffer,0,sizeof(TxBuffer));					//Очистка буфера передачи

	/* Обработчик команд */
	if (strncmp(RxBuffer,"*IDN?",5) == 0)					//Это команда "*IDN?"
	{
		strcpy(TxBuffer,"PAMUZHAK, MAKAROV  IU4-71");					//Она самая, возвращаем строку идентификации
	}


	else if (strncmp(RxBuffer,"START",5) == 0)				//Команда запуска таймера?
	{


			TIM2->CR1 |= TIM_CR1_CEN;

			strcpy(TxBuffer, "OK");
		}






	else if (strncmp(RxBuffer,"PAUSE",4) == 0)				//Команда остановки таймера?
	{


		TIM2->CR1 &= ~TIM_CR1_CEN;

		strcpy(TxBuffer, "OK");

	}


	else if(strncmp(RxBuffer,"SET",3) == 0) {  // Если в RxBuffer первые 3 символа равны "SET"

      int set_number = 0;

      sscanf(RxBuffer,"%*s %d", &set_number);

      if (set_number >= 0 && set_number <= 9) {
        number = set_number;
        strcpy(TxBuffer,"OK");          // То в буфер передачи помещаем "OK"
      } else {

    	  strcpy(TxBuffer,"Invalid parameter");
      }
    } else if(strncmp(RxBuffer,"GET", 3) == 0)   // Если в RxBuffer лежит команда "GET?
    {
      sprintf(TxBuffer, "%x", number);

    } else
		strcpy(TxBuffer,"Invalid Command");					//Если мы не знаем, чего от нас хотят, ругаемся в ответ

	txStr(TxBuffer,true);									//Отправляем буефер передачи с символами конца строки

	memset(RxBuffer,0,RX_BUFF_SIZE);						//Очистка буфера приёма

	ComReceived = false;									//Сбрасываем флаг приёма строки
}

/**
  * @brief  Основная программа
  * @param  None
  * @retval None
  */


/**
  * @brief  Подпрограмма задержки
  * @param  takts - Кол-во тактов
  * @retval None
  */
void delay(uint32_t takts) {
	for (uint32_t i = 0; i < takts; i++) {};
}


void initButton_10(void){

/* Настройка самого прерывания */

	// Настройка альтернативных фукнций портов.
	// Настройки портов с 12 по 15 хранятся в регистре AFIO_EXTICR4.

	// с 8 по 11 хранятся в AFIO_EXTICR3
	// Регистры объединены в массив AFIO->EXTICR, нумерация массива начинается с нулевого элемента.
	// Поэтому настройки AFIO_EXTICR4 хранятся в AFIO->EXTICR[3]
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PA;
	//регистры EXTICR находятся в масссимке, поэтому для использования EXTICR нужно взять 3 элемент массива EXTICR[3]


	//EXTI->FTSR |= EXTI_FTSR_TR10;			//Прерывание по спаду импульса (при отпускании на кнопку)
	EXTI->RTSR |= EXTI_FTSR_TR10;			//Прерывание по фронту импульса (при нажатии на кнопку)
	EXTI->IMR |= EXTI_IMR_MR10;				//Выставляем маску - EXTI13 (разрешить прерывание именно только на 13 ноге )

	NVIC_EnableIRQ(EXTI15_10_IRQn);			//Разрешаем прерывание ( на всех )   это функции cmsis
	NVIC_SetPriority(EXTI15_10_IRQn, 2);	//Выставляем приоритет    это функции cmsis
}

void initButton_11(void){

/* Настройка самого прерывания */

	// Настройка альтернативных фукнций портов.
	// Настройки портов с 12 по 15 хранятся в регистре AFIO_EXTICR4.

	// с 8 по 11 хранятся в AFIO_EXTICR3
	// Регистры объединены в массив AFIO->EXTICR, нумерация массива начинается с нулевого элемента.
	// Поэтому настройки AFIO_EXTICR4 хранятся в AFIO->EXTICR[3]
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI11_PA;
	//регистры EXTICR находятся в масссимке, поэтому для использования EXTICR нужно взять 3 элемент массива EXTICR[3]


	//EXTI->FTSR |= EXTI_FTSR_TR10;			//Прерывание по спаду импульса (при отпускании на кнопку)
	EXTI->RTSR |= EXTI_FTSR_TR11;			//Прерывание по фронту импульса (при нажатии на кнопку)
	EXTI->IMR |= EXTI_IMR_MR11;				//Выставляем маску - EXTI13 (разрешить прерывание именно только на 13 ноге )

	NVIC_EnableIRQ(EXTI15_10_IRQn);			//Разрешаем прерывание ( на всех )   это функции cmsis
		NVIC_SetPriority(EXTI15_10_IRQn, 2);

}


void EXTI15_10_IRQHandler(void) {
	// Т.к. этот обработчик вызывается, если произшло одно из прерываний EXTI15-EXI10,
	// нужно проверить, кто из них его вызвал.
	if (EXTI->PR & EXTI_PR_PR10) {	// нас интересует EXTI13

		EXTI->PR |= EXTI_PR_PR10;

		number = 0;



			//Инвертируем состояние таймера
	}

	if (EXTI->PR & EXTI_PR_PR11) {	// нас интересует EXTI13

		EXTI->PR |= EXTI_PR_PR11;

				DELAY_VALUE;		 //Задержка для защиты от дребезга контактов

				if(abc == 0) {
					abc = 1;

				} else if (abc == 1){
					abc =0;
				}

				if(abc ==0) {
					TIM2->CR1 &= ~TIM_CR1_CEN;
				} else {
					TIM2->CR1 |= TIM_CR1_CEN;
				}



				//Инвертируем состояние таймера
		}
}










void port_configuration(void){

			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;  //включить тактирование GPIOA и альтернативных функций

			//очистка полей
			GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
			//и конфигурация
			GPIOA->CRL |= GPIO_CRL_MODE0_1;		//PA5 (LD3), выход 2МГц

			//очистка полей
			GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
			//и конфигурация
			GPIOA->CRL |= GPIO_CRL_MODE1_1;		//PA5 (LD3), выход 2МГц

			//очистка полей
			GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
			//и конфигурация
			GPIOA->CRL |= GPIO_CRL_MODE4_1;		//PA5 (LD3), выход 2МГц

			//очистка полей
			GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
			//и конфигурация
			GPIOA->CRL |= GPIO_CRL_MODE5_1;		//PA5 (LD3), выход 2МГц

			//очистка полей
			GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
			//и конфигурация
			GPIOA->CRL |= GPIO_CRL_MODE6_1;		//PA5 (LD3), выход 2МГц


			//очистка полей
			GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
			//и конфигурация
			GPIOA->CRL |= GPIO_CRL_MODE7_1;		//PA5 (LD3), выход 2МГц


			//очистка полей
			GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
			//и конфигурация
			GPIOA->CRH |= GPIO_CRH_MODE8_1;		//PA5 (LD3), выход 2МГц




			  GPIOA->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_MODE11);
			  GPIOA->CRH |= GPIO_CRH_CNF11_1;
			  GPIOA->BSRR |= GPIO_BSRR_BR11;


			  GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
			  GPIOA->CRH |= GPIO_CRH_CNF10_1;
			  GPIOA->BSRR |= GPIO_BSRR_BR10;

	}

int func_onn(int number){
	DELAY_VALUE;
	RESET_NUMBER;

	  switch(number)
	  {
			case 0:
				ON_NUMBER_0;
				break;

			case 1:
				ON_NUMBER_1;
				break;

			case 2:
				ON_NUMBER_2;
				break;

			case 3:
				ON_NUMBER_3;
				break;

			case 4:
				ON_NUMBER_4;
				break;

			case 5:
				ON_NUMBER_5;
				break;

			case 6:
				ON_NUMBER_6;
				break;

			case 7:
				ON_NUMBER_7;
				break;

			case 8:
				ON_NUMBER_8;
				break;

			case 9:
				ON_NUMBER_9;
				break;

			default:
				ON_NUMBER_0;
				break;
		}
	  return 0;
	}



int main(void) {
	/*Инициализации всякие*/
	initClk();
	initPorts();
	initTIM2();
	initUSART2();

	initButton_10();
	initButton_11();

	/*Основной цикл*/
	while(true) {


			if (ComReceived == 1)				//Ждём приема строки
			ExecuteCommand();
		func_onn(number);
	};


}
