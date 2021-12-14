#include "main.h"

int number = 0;
int main(void) {

	port_configuration();
	initTIM2();
	initButton_10();
	initButton_11();




	while(1) {
		func_onn(number);

	}

}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;			//Сброс флага переполнения

	//Проверка нажата ли кнопка
			DELAY_VALUE;

			if(number < 9) {
				number++;

			}




}

void initTIM2(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;		//Включить тактирование TIM6

	//Частота APB1 для таймеров = APB1Clk * 2 = 32МГц * 2 = 64МГц
	TIM2->PSC = 8000-1;					//Предделитель частоты (64МГц/64000 = 1кГц)
	TIM2->ARR = 1000-1;						//Модуль счёта таймера (1кГц/1000 = 1с)
	TIM2->DIER |= TIM_DIER_UIE;				//Разрешить прерывание по переполнению таймера

	NVIC_EnableIRQ(TIM2_IRQn);				//Рарзрешить прерывание от TIM2
	NVIC_SetPriority(TIM2_IRQn, 1);			//Выставляем приоритет
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

				TIM2->CR1 ^= TIM_CR1_CEN;		//Инвертируем состояние таймера

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


/**
  * @brief  Подпрограмма задержки
  * @param  takts - Кол-во тактов
  * @retval None
  */
void delay(uint32_t takts)
{
	for (uint32_t i = 0; i < takts; i++) {};
}


