#include "stm32l476xx.h"
#include "SysTick.h"
#include "LED.h"
#include "Draw.h"

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
	//resetTimer();
	//uint32_t timer;
	LCD_Initialization();
	Joystick_Init();
	int prevButton = 0;
	int currButton = 0;
	int jumping = 1;
	int obstaclePos = -1;
	while(1) {
		delay(1000);
		LCD_Clear();

		drawDinosaur(jumping);
		if(!jumping)
			jumping = 1;
		else
			jumping = 0;
		if (obstaclePos == -1)
			obstaclePos = 5;
		if (obstaclePos != -1) {
			if (obstaclePos == 1) {
				//if (!jumping)
				//	break;
				drawObstacle((uint8_t)obstaclePos, 1);
			} else
				drawObstacle((uint8_t)obstaclePos, 0);
			obstaclePos--;
		}
	}
	
	while(1) {};
}
