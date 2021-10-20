#include "main.h"

int number = 0;

int main(void)
{
	port_configuration();

	loop();

	//Бесконечный цикл
}

void loop(void)
{

	while (1)
	{

		//Проверка нажата ли кнопка
		if (((GPIOA->IDR & GPIO_IDR_IDR9) != 0) && number < 9)
		{
			number++;
			DELAY_VALUE;

			func_onn(number);
		}

		else if (((GPIOA->IDR & GPIO_IDR_IDR10) != 0) && number > 0)
		{
			number--;

			DELAY_VALUE;
		}
		func_onn(number);
	}
}

void port_configuration(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //включить тактирование GPIOA

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE0_1; //PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE1_1; //PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE4_1; //PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE5_1; //PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE6_1; //PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE7_1; //PA5 (LD3), выход 2МГц

	//очистка полей
	GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
	//и конфигурация
	GPIOA->CRH |= GPIO_CRH_MODE8_1; //PA5 (LD3), выход 2МГц

	GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);

	GPIOA->CRH |= GPIO_CRH_CNF9_1;
	GPIOA->BSRR |= GPIO_BSRR_BR9;

	GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);

	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->BSRR |= GPIO_BSRR_BR10;
}

int func_onn(int number)
{

	RESET_NUMBER;

	switch (number)
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
	for (uint32_t i = 0; i < takts; i++)
	{
	};
}
