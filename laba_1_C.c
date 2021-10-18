#include "main.h"


int number = 0;

int func_onn(int number){

	  switch(number)
	  {
			case 0:
					LED_ON_1;
					LED_ON_4;
					LED_ON_5;
					LED_ON_6;
					LED_ON_7;
					LED_ON_8;
					LED_OFF_0;

				break;
			case 1:
					LED_ON_6;
					LED_ON_7;
					LED_OFF_0;

					LED_OFF_1;
					LED_OFF_5;
					LED_OFF_4;
					LED_OFF_8;


				break;
			case 2:
					LED_ON_0;
					LED_ON_4;
					LED_ON_5;
					LED_ON_8;
					LED_ON_7;


					LED_OFF_1;
					LED_OFF_6;


				break;
			case 3:
					LED_ON_0;
					LED_ON_5;
					LED_ON_6;
					LED_ON_7;
					LED_ON_8;


					LED_OFF_1;
					LED_OFF_4;



				break;
			case 4:
					LED_ON_0;
					LED_ON_1;
					LED_ON_6;
					LED_ON_7;


					LED_OFF_4;
					LED_OFF_5;
					LED_OFF_8;


				break;
			case 5:
					LED_ON_0;
					LED_ON_1;
					LED_ON_5;
					LED_ON_6;
					LED_ON_8;


					LED_OFF_4;
					LED_OFF_7;


				break;
			case 6:
					LED_ON_0;
					LED_ON_1;
					LED_ON_4;
					LED_ON_5;
					LED_ON_6;
					LED_ON_8;

					LED_OFF_7;


				break;
			case 7:
					LED_ON_6;
					LED_ON_7;
					LED_ON_8;

					LED_OFF_0;
					LED_OFF_1;
					LED_OFF_4;
					LED_OFF_5;

				break;
			case 8:
					LED_ON_0;
					LED_ON_1;
					LED_ON_4;
					LED_ON_5;
					LED_ON_6;
					LED_ON_7;
					LED_ON_8;

				break;
			case 9:
					LED_ON_0;
					LED_ON_1;
					LED_ON_5;
					LED_ON_6;
					LED_ON_7;
					LED_ON_8;

					LED_OFF_4;

				break;
		}
	  return 0;
	}




int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	//включить тактирование GPIOA

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




		GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);

	  GPIOA->CRH |= GPIO_CRH_CNF9_1;
	  GPIOA->BSRR |= GPIO_BSRR_BS9;


		GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);

	  GPIOA->CRH |= GPIO_CRH_CNF10_1;
	  GPIOA->BSRR |= GPIO_BSRR_BS10;









	//Бесконечный цикл
	while(1) {


	    //Проверка нажата ли кнопка
			if(((GPIOA->IDR & GPIO_IDR_IDR9) == 0) && number < 9)
	    {
				number++;


	      delay(200000);
			func_onn(number);

	    }




			else if(((GPIOA->IDR & GPIO_IDR_IDR10) == 0) && number > 0)
		    {
					number--;




		      delay(200000);

		    }
				func_onn(number);






	}
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
