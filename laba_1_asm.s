//start code  //start code   //start code  //start code  //start code

// тактирование порта а

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



	mov32 	r1, #0xC3				@ устанавливаем вывод в '1'
	str 	r1, [r0]					@ загружаем в порт

//end code  //end code  //end code //end code  //end code