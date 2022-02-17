#include "main.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"

//Полная шкала АЦП
#define ADC_FS 0xFFF
//Напряжение при ADC_FS
#define V_REF 3.3
// Количество попугаев при 21ºC
#define DC_21 1922
//Наклон характеристики термодатчика
#define AVG_SLOPE 4.3e-3

/* Размеры буферов приёма и передачи */
#define TX_BUFF_SIZE    256

char RxBuffer[RX_BUFF_SIZE];					//Буфер приёма USART
char TxBuffer[TX_BUFF_SIZE];					//Буфер передачи USART
bool ComReceived;								//Флаг приёма строки данных

/**
  * @brief  Обработчик прерывания от USART2
  * @param  None
  * @retval None
  */

void initADC1_Regular() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;                    //Включить тактирование порта GPIOC
    GPIOC->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);    //PC4 на вход
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;                //Включить тактирование АЦП

    ADC1->CR1 = 0;                                        //Обнуляем конфигурационные регистры
    ADC1->CR2 = 0;                                        //...
    ADC1->SQR1 = 0;                                        //...
    ADC1->SQR2 = 0;                                        //...

    //Настройка времени преобразования каналов
    ADC1->SMPR1 |= ADC_SMPR1_SMP16;                        //Канал 16 - 239.5 тактов

    /**
     * ADC_CR2_TSVREFE - Подключить термодатчик к каналу ADC1_IN16
     * ADC_CR2_EXTSEL - Выбрать в качестве источника запуска SWSTART
     * ADC_CR2_EXTTRIG - Разрешить внешний запуск регулярного канала
     */

    ADC1->CR2 |= ADC_CR2_TSVREFE | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG;
    ADC1->CR2 |= ADC_CR2_ADON;                            //Включить АЦП
    //Тут хорошо бы вставить задержку перед калибровкой
    ADC1->CR2 |= ADC_CR2_CAL;                            //Запуск калибровки
    while (!(ADC1->CR2 & ADC_CR2_CAL)) {};                //Ожидание окончания калибровки
    //ацп может производить до 16 измерений. Используем только 1 измерение и указываем с какого именно канала будем его производить
    //выбираем нужный канал
    ADC1->SQR3 = 16;
}





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

		//запускаем измерение АЦП
		    ADC1->SR &= ~ADC_SR_EOC;                        //Сбрасываем флаг окончания преобразования
		    ADC1->CR2 |= ADC_CR2_SWSTART;
		    while ((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC);
		    float temp = ((ADC1->DR - DC_21) * V_REF/ADC_FS)/AVG_SLOPE + 21;
				sprintf(TxBuffer, "%.1f", temp);

	} else
		strcpy(TxBuffer,"Invalid Command");					//Если мы не знаем, чего от нас хотят, ругаемся в ответ

	txStr(TxBuffer,true);									//Отправляем буефер передачи с символами конца строки

	memset(RxBuffer,0,RX_BUFF_SIZE);						//Очистка буфера приёма

	ComReceived = false;									//Сбрасываем флаг приёма строки
}


void delay(uint32_t takts) {
	for (uint32_t i = 0; i < takts; i++) {};
}



int main(void) {
	/*Инициализации всякие*/
	initClk();
	initUSART2();


	/*Основной цикл*/
	while(true) {


			if (ComReceived == 1)				//Ждём приема строки
			ExecuteCommand();
	};


}
