;******************** (C) Yifeng ZHU *******************************************
; @file    main.s
; @author  Yifeng Zhu
; @date    May-17-2015
; @note
;           This code is for the book "Embedded Systems with ARM Cortex-M 
;           Microcontrollers in Assembly Language and C, Yifeng Zhu, 
;           ISBN-13: 978-0982692639, ISBN-10: 0982692633
; @attension
;           This code is provided for education purpose. The author shall not be 
;           held liable for any direct, indirect or consequential damages, for any 
;           reason whatever. More information can be found from book website: 
;           http:;www.eece.maine.edu/~zhu/book
;*******************************************************************************

	INCLUDE core_cm4_constants.s		; Load Constant Definitions
	INCLUDE stm32l476xx_constants.s      

	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	ENTRY			
				
__main	PROC
	
    ; Enable the clock to GPIO Ports B and E and A	
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR] ;load addresses of the reset and clock control registers
	                           ;then offsets by clock enable register
	ORR r1, r1, #RCC_AHB2ENR_GPIOBEN ;port b
	ORR r1, r1, #RCC_AHB2ENR_GPIOEEN ;port e
	ORR r1, r1, #RCC_AHB2ENR_GPIOAEN ;port a
	STR r1, [r0, #RCC_AHB2ENR] ;stores back to memory 
	
	;confifure the GPIO (General Purpose IO) port mode register
	; set input mode of joystick 
	; MODE: 00: Input mode, 01: General purpose output mode
    ;       10: Alternate function mode, 11: Analog mode (reset state)
	
	LDR r0, =GPIOA_BASE ;load gpioa joystick base adress
	LDR r1, [r0, #GPIO_MODER] ; offset this by mode register
	BIC r1, r1,  #(0x3) ;no shifting at all, set to 0 "Pa0"
	STR r1, [r0, #GPIO_MODER]
	
	LDR r0, =GPIOB_BASE ;load gpiob red led base adress
	LDR r1, [r0, #GPIO_MODER] ; offset this by mode register
	BIC r1, r1,  #(0x3<<4) ; perform bitwise clear; shifted by 4 = 2 * 2 bc 2 bits
	ORR r1, r1,  #(0x1<<4)
	STR r1, [r0, #GPIO_MODER] ; store back to memory 
	
	LDR r0, =GPIOE_BASE ;load gpioe green led base adress
	LDR r1, [r0, #GPIO_MODER] ; offset this by mode register
	BIC r1, r1,  #(0x3<<0x10) ; shifted by 16 = 0x10 = 8 (PE'8') * 2 bc 2 bits
	ORR r1, r1,  #(0x1<<0x10)
	STR r1, [r0, #GPIO_MODER] ; store back to memory 
	
	; extra code that makes ONLY the red LED turn once board is flashed
	; both LEDS would toggle at the same time without this 
	LDR r0, =GPIOB_BASE
	LDR r1, [r0, #GPIO_ODR]
	ORR r1, r1,  #(0x1<<2)
	STR r1, [r0, #GPIO_ODR]
	
loop
	; check joystick (PA0)
	LDR r0, =GPIOA_BASE
	LDR r1, [r0, #GPIO_IDR] ; offset joystick's (gpioa) base adresss by input data register;
	                        ; last digit of r1 is 1 when button is pressed
	AND r4, r1, #1 ; and r1 $ #1; returns 0x00000001 if button is pressed to r4. returns 0 if not. 
	CMP r4, r5 ; compare/subtract the state r5 was before to r4; r4 and r5 arent equal so the zero flag is 0 when button is pressed
	BEQ loop ;branch if equal allows us to get out of loop until zero flag is set to 0
	MOV r5, r4
	; loop until button pushed
	CMP r5, #0 ;zero flag is 0 when button is pressed
	BEQ loop

	; toggle RED LED (PB2)
	LDR r0, =GPIOB_BASE
	LDR r1, [r0, #GPIO_ODR] ; offset led base adress with output register
	EOR r1, r1,  #(0x1<<2) ; use eor to toggile bits
	STR r1, [r0, #GPIO_ODR] ; store back in memory 
	
	; toggle GREEN LED (PE8) 
	LDR r0, =GPIOE_BASE
	LDR r1, [r0, #GPIO_ODR]
	EOR r1, r1,  #(0x1<<8)
	STR r1, [r0, #GPIO_ODR]
	
	
	B loop
  
;stop 	B 		stop     		; dead loop & program hangs here

	ENDP
					
	ALIGN			

	AREA    myData, DATA, READWRITE
	ALIGN
array	DCD   1, 2, 3, 4
	END
