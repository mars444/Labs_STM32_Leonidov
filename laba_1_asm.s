//start code  //start code   //start code  //start code  //start code

mov32	r0, PERIPH_BB_BASE+ \
				(RCC_APB2ENR-PERIPH_BASE)*32 + \
				2*4
										@ вычисляем адрес для BitBanding 2-го бита регистра RCC_APB2ENR
										@ BitAddress = BitBandBase + (RegAddr * 32) + BitNumber * 4
	mov		r1, #1						@ включаем тактирование порта D (в 2-й бит RCC_APB2ENR пишем '1`)
	str 	r1, [r0]					@ загружаем это значение



	MOV32	R0, GPIOA_CRL

    MOV32	R1, #0x33333333
	LDR		R2, [R0]
    BFI		R2, R1, #0, #31
    STR		R2, [R0]
					@ загрузить результат в регистр настройки порта

 			@ адрес порта выходных сигналов

			@ загружаем в порт


	MOV32	R0, GPIOA_CRH

    MOV32	R1, #0x3
	LDR		R2, [R0]
    BFI		R2, R1, #0, #4
    STR		R2, [R0]


  	mov32	r0, GPIOA_BSRR
		@ адрес порта выходных сигналов




loop:									@ Бесконечный цикл
	mov32 	r1, #0x1F2				@ устанавливаем вывод в '1'
	str 	r1, [r0]				@ загружаем в пор
	bl		delay						@ задержка
	bl      Reset_number


	mov32 	r1, #0xC0				@ устанавливаем вывод в '1'
	str 	r1, [r0]					@ загружаем в порт
	bl		delay						@ задержка
	bl      Reset_number


	mov32 	r1, #0x1B1				@ устанавливаем вывод в '1'
	str 	r1, [r0]				@ загружаем в порт
	bl		delay						@ задержка
	bl      Reset_number


	mov32 	r1, #0x1E1				@ устанавливаем вывод в '1'
	str 	r1, [r0]
	bl		delay						@ задержка
	bl      Reset_number

	mov32 	r1, #0xC3				@ устанавливаем вывод в '1'
	str 	r1, [r0]
	bl		delay						@ задержка
	bl      Reset_number

	mov32 	r1, #0x163				@ устанавливаем вывод в '1'
	str 	r1, [r0]
	bl		delay						@ задержка
	bl      Reset_number

	mov32 	r1, #0x173				@ устанавливаем вывод в '1'
	str 	r1, [r0]
	bl		delay						@ задержка
	bl      Reset_number

	mov32 	r1, #0x1C0				@ устанавливаем вывод в '1'
	str 	r1, [r0]
	bl		delay						@ задержка
	bl      Reset_number

	mov32 	r1, #0x1F3				@ устанавливаем вывод в '1'
	str 	r1, [r0]
	bl		delay						@ задержка
	bl      Reset_number


	mov32 	r1, #0xF1				@ устанавливаем вывод в '1'
	str 	r1, [r0]
	bl		delay						@ задержка
	bl      Reset_number


	b 		loop						@ возвращаемся к началу цикла

delay:									@ Подпрограмма задержки
	push	{r0}						@ Загружаем в стек R0, т.к. его значение будем менять
	mov32	r0, 0xFFFFF					@ псевдоинструкция Thumb (загрузить константу в регистр)
delay_loop:
	subs	r0, #1						@ SUB с установкой флагов результата
	it 		NE
	bne		delay_loop					@ переход, если Z==0 (результат вычитания не равен нулю)
	pop		{r0}						@ Выгружаем из стека R0
	bx     LR


	Reset_number:
	mov32	r1, #GPIO_BSRR_BR5			@ сбрасываем в '0'
	str 	r1, [r0]
	mov32 	r1, #GPIO_BSRR_BR0					@ устанавливаем вывод в '1'
	str 	r1, [r0]
	mov32 	r1, #GPIO_BSRR_BR1					@ устанавливаем вывод в '1'
	str 	r1, [r0]
	mov32 	r1, #GPIO_BSRR_BR4					@ устанавливаем вывод в '1'
	str 	r1, [r0]
	mov32	r1, #GPIO_BSRR_BR6			@ сбрасываем в '0'
	str 	r1, [r0]
	mov32 	r1, #GPIO_BSRR_BR7					@ устанавливаем вывод в '1'
	str 	r1, [r0]
	mov32 	r1, #GPIO_BSRR_BR8					@ устанавливаем вывод в '1'
	str 	r1, [r0]
	mov32 	r1, #GPIO_BSRR_BR9					@ устанавливаем вывод в '1'
	str 	r1, [r0]
	bx      lr

//end code  //end code  //end code //end code  //end code