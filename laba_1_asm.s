///start code  //start code   //start code  //start code  //start code
// Включаем тактирование порта А с момощью BitBanding (см лекции)
	mov32	r0, PERIPH_BB_BASE + \
		(RCC_APB2ENR-PERIPH_BASE) * 32 + 2 * 4
										@ вычисляем адрес для BitBanding 2-го бита регистра RCC_APB2ENR
										@ BitAddress = BitBandBase + (RegAddr * 32) + BitNumber * 4
	mov		r1, #1						@ включаем тактирование порта A (в 2-й бит RCC_APB2ENR пишем '1`)
	str 	r1, [r0]					@ загружаем это значение



	// Настравиваем ноги PA0,PA1, PA4-PA7  на выход push-pull, загрузив 0011, что равно 3 в хексе
	MOV32	R0, GPIOA_CRL
    MOV32	R1, #0x33330033
	LDR		R2, [R0]
    BFI		R2, R1, #0, #31 //отступаем 0 бит и в след 31 бит записываем 0011
    STR		R2, [R0]

	// Настравиваем ногу PA8 на выход push-pull, загрузив 0011, что равно 3 в хексе
	MOV32	R0, GPIOA_CRH
    MOV32	R1, #0x3
	LDR		R2, [R0]
    BFI		R2, R1, #0, #4  //отступаем 0 бит и в след 4 бит записываем 0011
    STR		R2, [R0]

	// Настравиваем ноги PA9, PA10 (кнопки) на вход, загрузив 1000, что равно 8 в хексе
	MOV32	R0, GPIOA_CRH
    MOV32	R0, GPIOA_CRH
    MOV32	R1, #0x88
	LDR		R2, [R0]
    BFI		R2, R1, #4, #8  //отступаем 4 бит и в след 8 бит записываем 0011
    STR		R2, [R0]


	MOV R5,   #0    // Записыаает первое число, котрое хотим увидеть на семисегментнике


main:	  // НАчало основного цикла, аналоги ф-ции main в Си

    MOV32   R0, GPIOA_BSRR
    BL      LED_ON     // Вызывает подпрорамму LED_ON

buttons:
button_increment_pa9:
    push	{r2,r3}
 	MOV32	R3, GPIOA_IDR
	LDR		R2, [R3]
	AND     R2, #0x200
	CMP     R2, #0
	pop		{r2,r3}
	IT      EQ
	BEQ     button_decrement_pa10

	bl  delay

	CMP     R5, #9
	ITE     EQ
	MOVEQ   R5, #9
	ADDNE   R5, #1

button_decrement_pa10:
	push	{r2,r3}
 	MOV32	R3, GPIOA_IDR
	LDR		R2, [R3]
	AND     R2, #0x400
	CMP     R2, #0
	pop		{r2,r3}
	IT      EQ
	BEQ     main

	bl  delay

	CMP     R5, #0
	ITE     EQ
	MOVEQ   R5, #0
	SUBNE   R5, #1


	B 		main						// переходим по метке main


LED_ON:

    PUSH	{R0, R1}


Reset_number:
	MOV32	R0, GPIOA_BSRR
	mov32		r1, #0x1F30000 // загружаем в оегистр бсрр 1111100110000000000000000 чтобы сбросить в 0 ноги pa1,pa2,pa4-pa8
	str 	r1, [r0]




	TBB [PC, R5] //R5 is the index, PC is the base address of the branch table
BranchTable:
    .byte     ((Dest0-BranchTable)/2)
	.byte     ((Dest1-BranchTable)/2)
	.byte     ((Dest2-BranchTable)/2)
	.byte     ((Dest3-BranchTable)/2)
	.byte     ((Dest4-BranchTable)/2)
	.byte     ((Dest5-BranchTable)/2)
	.byte     ((Dest6-BranchTable)/2)
	.byte     ((Dest7-BranchTable)/2)
	.byte     ((Dest8-BranchTable)/2)
	.byte     ((Dest9-BranchTable)/2)
Dest0:
	MOV 	R1, #0x1F2					// R1 = 0x1F2// это маска, которая позволит отобразить цифру 0 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
Dest1:
	MOV 	R1, #0xC0					// R1 = 0xС0// это маска, которая позволит отобразить цифру 0 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
Dest2:
	MOV 	R1, #0x1B1					//  и так далеее
	STR 	R1, [R0]
	B       DestEnd
Dest3:
	MOV 	R1, #0x1E1
	STR 	R1, [R0]
	B       DestEnd
Dest4:
	MOV 	R1, #0xC3
	STR 	R1, [R0]
	B       DestEnd
Dest5:
	MOV 	R1, #0x163
	STR 	R1, [R0]
	B       DestEnd
Dest6:
	MOV 	R1, #0x173
	STR 	R1, [R0]
	B       DestEnd
Dest7:
	MOV 	R1, #0x1C0
	STR 	R1, [R0]
	B       DestEnd
Dest8:
	MOV 	R1, #0x1F3
	STR 	R1, [R0]
	B       DestEnd
Dest9:
	MOV 	R1, #0x1E3
	STR 	R1, [R0]
	B       DestEnd
DestEnd:
    POP		{R0, R1}				    // Выгружаем из стека значения регистров R0 и R1, тем самым возвращая им те значения,
										//которые у них были при сохранении в стек
    b     buttons						// Перехд к метке buttons

delay:									@ Подпрограмма задержки
	push	{r0}						@ Загружаем в стек R0, т.к. его значение будем менять
	mov32	r0, 0x5FFFF					@ псевдоинструкция Thumb (загрузить константу в регистр)
delay_loop:
	subs	r0, #1						@ SUB с установкой флагов результата
	it 		NE
	bne		delay_loop					@ переход, если Z==0 (результат вычитания не равен нулю)
	pop		{r0}						@ Выгружаем из стека R0
	bx     LR

//end code  //end code  //end code //end code  //end code