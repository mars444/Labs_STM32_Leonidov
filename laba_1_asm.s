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


	MOV32	R0, GPIOA_CRH
    MOV32	R1, #0x333
	LDR		R2, [R0]
    BFI		R2, R1, #0, #4
    STR		R2, [R0]

    MOV32	R0, GPIOA_CRH
    MOV32	R1, #0x88
	LDR		R2, [R0]
    BFI		R2, R1, #4, #8
    STR		R2, [R0]


	MOV R5,   #3


loop:									// Бесконечный цикл

    MOV32   R0, GPIOA_BSRR              // R0 = адрес регистра GPIOA_BSRR

    BL      semseg
button:
    push	{r2,r3}
 	MOV32	R3, GPIOA_IDR
	LDR		R2, [R3]
	AND     R2, #0x200
	CMP     R2, #0
	pop		{r2,r3}
	IT      EQ
	BEQ     button2

	bl  delay

	CMP     R5, #9                    // сравниваем R5 и 20 (20 - максимальное значение, достигнув которого мы должны изменить напрвдение счета)
	ITE     EQ                          // если они равны
	MOVEQ   R5, #9                      // то R5 = 0
	ADDNE   R5, #1                      // иначе R5 = R5 + 1

button2:
	push	{r2,r3}
 	MOV32	R3, GPIOA_IDR
	LDR		R2, [R3]
	AND     R2, #0x400
	CMP     R2, #0
	pop		{r2,r3}
	IT      EQ
	BEQ     loop

	bl  delay

	CMP     R5, #0                    // сравниваем R5 и 20 (20 - максимальное значение, достигнув которого мы должны изменить напрвдение счета)
	ITE     EQ                          // если они равны
	MOVEQ   R5, #0                      // то R5 = 0
	SUBNE   R5, #1                      // иначе R5 = R5 - 1


	B 		loop						// переходим по метке loop, что начнет все операции заново


semseg:                         // Подпрограмма для отображения на семисегментнике числа, которое хранится в регистре R7
    // При вызове подпрограммы ожидается, что какие значение у регистров были при вызове подпрограммы, такие и останутся после её окончания
    // Совсем не трогать регистры не получится, поэтому временно сохраням значения регистров в стеке, чтобы затем, в конце, считать их оттуда
    PUSH	{R0, R1}						// Сохраняем значения R0 и R1 в стек
    bl delay

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



	TBB [PC, R5] //R1 is the index, R0 is the base address of the branch table
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
	MOV 	R1, #0x1F2
	STR 	R1, [R0]
	B       DestEnd
Dest1:
	MOV 	R1, #0xC0
	STR 	R1, [R0]
	B       DestEnd
Dest2:
	MOV 	R1, #0x1B1
	STR 	R1, [R0]
	B       DestEnd
Dest3:
	MOV 	R1, #0x1E1                 // R1 = 0x9E// это маска, которая позволит отобразить цифру 3 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
Dest4:
	MOV 	R1, #0xC3               // R1 = 0xCC// это маска, которая позволит отобразить цифру 4 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
Dest5:
	MOV 	R1, #0x163                   // R1 = 0xDA// это маска, которая позволит отобразить цифру 5 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
Dest6:
	MOV 	R1, #0x173                  // R1 = 0xFA// это маска, которая позволит отобразить цифру 6 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
Dest7:
	MOV 	R1, #0x1C0                   // R1 = 0x0E// это маска, которая позволит отобразить цифру 7 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
Dest8:
	MOV 	R1, #0x1F3                  // R1 = 0xFE// это маска, которая позволит отобразить цифру 8 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
Dest9:
	MOV 	R1, #0x1E3               // R1 = 0xDE// это маска, которая позволит отобразить цифру 9 на семесегментнике
	STR 	R1, [R0]
	B       DestEnd
DestEnd:
    POP		{R0, R1}				    // Выгружаем из стека значения регистров R0 и R1, тем самым возвращая им те значения, которые у них были при сохранении в стек
    b     button
  					// выход из подпрограммы - переход по адресу LR (LR - регистр, который содержит адрес строки порограммы, когда в последний раз вызывалась команда BL)


delay:									@ Подпрограмма задержки
	push	{r0}						@ Загружаем в стек R0, т.к. его значение будем менять
	mov32	r0, 0xFFFC				@ псевдоинструкция Thumb (загрузить константу в регистр)
delay_loop:
	subs	r0, #1						@ SUB с установкой флагов результата
	it 		NE
	bne		delay_loop					@ переход, если Z==0 (результат вычитания не равен нулю)
	pop		{r0}						@ Выгружаем из стека R0
	bx     LR






//end code  //end code  //end code //end code  //end code