#include "stm32l476xx.h"
#include "LCD.h"
#include <stdlib.h>
#include <string.h>

void delay(void);
void movingString(uint8_t* str, uint8_t len);

int main(void){
	LCD_Initialization();
	//char *test = "GAMING";
	
	//LCD_DisplayString(test);
	
	//LCD_Display_Name();
	while (1) {
		movingString((uint8_t *)"EE-14 is funz", 13);
	}
}

void delay(void) {
	for (int i = 0; i < 250000; i++) {
		asm ("nop");
	}
}

void movingString(uint8_t* str, uint8_t len) {
	uint8_t *spaces = "      ";
	uint8_t *str2 = malloc(len+12);
	memcpy(str2, spaces, 6);
	memcpy(str2+6, str, len);
	memcpy(str2+len+6, spaces, 6);
	uint8_t *print_str = malloc(6);
	for (int i = 0; i < (len+6); i++) {
		memcpy(print_str, str2+i, 6);
		LCD_DisplayString(print_str);
		delay();
	}
}
