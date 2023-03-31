#include "stm32l476xx.h"
#include "LCD.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void delay(void);
void movingString(uint8_t* str, uint8_t len);

int main(void){
	LCD_Initialization();
	while (1) {
		movingString((uint8_t *)"EE-14 is fuNz", 13);
	}
}

int wait_loop0 = 750;
int wait_loop1 = 600;

void delay(void) {
	int i,j;
	for (i = 0; i < wait_loop0; i++) {
		for (j = 0; j < wait_loop1; j++) {
			int volatile t = 120 * i * j;
			t = t + 5;
		}
	}
}

void movingString(uint8_t* str, uint8_t len) {
	char *spaces = "      ";
	uint8_t *str2 = malloc(len+12);
	uint8_t *str3 = malloc(6);
	int i;
	memcpy(str2, spaces, 6);
	memcpy(str2+6, str, len);
	memcpy(str2+len+6, spaces, 6);
	for (i = 0; i < (len+6); i++) {
		memcpy(str3, str2+i, 6);
		LCD_DisplayString(str3);
		delay();
	}
}
