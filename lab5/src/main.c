#include "stm32l476xx.h"
#include "SysTick.h"
#include "LED.h"
#include "Draw.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DINO_JUMP_TIME 60
#define DINO_JUMP_LAG 25
#define MAX_SPAWN_TIME 100

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
	time_t t;
	srand((unsigned) time(&t));
	int prevButton = 0;
	int currButton = 0;
	int jumping = 0;
	int obstaclePos = -1;
	int jumpTimer = 0;
	int jumpLagTimer = 0;
	uint64_t levelTimer = 1;
	int dinoJumpTime = DINO_JUMP_TIME;
	int dinoJumpLag = DINO_JUMP_LAG;
	int obstacleSpeed = 25;
	int obstacleTimer = obstacleSpeed;
	int obstacleSpawnTimer = 0;
	int level = 0;

	while(1) {
		delay(10);
		LCD_Clear();
		if (levelTimer % 1000 == 0) {
			obstacleSpeed-=5;
			dinoJumpTime-=5;
			dinoJumpLag-=5;
			level++;
		}
		drawBar(level);
		if (obstaclePos != -1) {
			if (obstaclePos == 1) {
				if (!jumping)
					break;
				drawObstacle((uint8_t)obstaclePos, 1);
			}
			else
				drawObstacle((uint8_t)obstaclePos, 0);
			if (obstacleTimer == 0) {
				obstaclePos--;
				obstacleTimer = obstacleSpeed;
			}
		}
		if (obstacleSpawnTimer != 0) {
			obstacleSpawnTimer--;
			if(obstacleSpawnTimer == 0) {
				obstaclePos = 5;
				obstacleTimer = obstacleSpeed;
			}
		}
		if (obstacleTimer != 0) {
			obstacleTimer--;
			if (obstaclePos == -1) {
				obstacleSpawnTimer = rand() % (MAX_SPAWN_TIME+1);
			}
		}
		
		currButton = GPIOA->IDR & 1U;

		if (currButton != prevButton) {
			prevButton = currButton;
			if(currButton == 1 && !jumping && jumpLagTimer == 0) {
				jumping = 1;
				jumpTimer = dinoJumpTime;
			}
		}
		drawDinosaur(jumping);
		if (jumpLagTimer != 0)
			jumpLagTimer--;
		if (jumpTimer != 0) {
			jumpTimer--;
			if (jumpTimer == 0) {
				jumping = 0;
				jumpLagTimer = dinoJumpLag;
			}
		}
		
		levelTimer++;
	}
	char *str = "Lose  ";
	LCD_DisplayString(str);
	while(1) {};
}
