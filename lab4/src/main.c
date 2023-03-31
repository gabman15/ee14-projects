#include "stm32l476xx.h"
#include "SysTick.h"
#include "LED.h"
#include "LCD.h"

void System_Clock_Init(void){
	
	RCC->CR |= RCC_CR_MSION; 
	
	// Select MSI as the clock source of System Clock
	RCC->CFGR &= ~RCC_CFGR_SW; 
	
	// Wait until MSI is ready
	while ((RCC->CR & RCC_CR_MSIRDY) == 0); 	
	
	// MSIRANGE can be modified when MSI is OFF (MSION=0) or when MSI is ready (MSIRDY=1). 
	RCC->CR &= ~RCC_CR_MSIRANGE; 
	RCC->CR |= RCC_CR_MSIRANGE_7;  // Select MSI 8 MHz	
 
	// The MSIRGSEL bit in RCC-CR select which MSIRANGE is used. 
	// If MSIRGSEL is 0, the MSIRANGE in RCC_CSR is used to select the MSI clock range.  (This is the default)
	// If MSIRGSEL is 1, the MSIRANGE in RCC_CR is used. 
	RCC->CR |= RCC_CR_MSIRGSEL; 
	
	// Enable MSI and wait until it's ready	
	while ((RCC->CR & RCC_CR_MSIRDY) == 0); 		
}

void Joystick_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	GPIOA->MODER &= ~(3U);
}


int main(void){
	//System Clock Initialization
	System_Clock_Init();

	//LED Initialization
	LED_Init();

	//SysTick Initialization
	SysTick_Init();
	resetTimer();
	uint32_t timer;
	LCD_Initialization();
	Joystick_Init();
	int prevButton = 0;
	int currButton = 0;
	while(1) {
		//delay of 10 mSec
		delay(10);

		currButton = GPIOA->IDR & 1U;
		if (currButton != prevButton) {
			prevButton = currButton;

			if(currButton == 1)
				toggleTimer();
		}

		timer = getTimer();
		LCD_DisplayTime(timer);

	}
	
	
	while (1);
}
