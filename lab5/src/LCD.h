#ifndef __STM32L476G_DISCOVERY_LCD_H
#define __STM32L476G_DISCOVERY_LCD_H

#include <stdint.h>

#define bool _Bool

#define DINO 0
#define DINOJUMP 1
#define OBSTACLE 2
#define OBSTACLEDINO 3

void LCD_Initialization(void);
void LCD_bar(void);
void LCD_Clock_Init(void);
void LCD_PIN_Init(void);
void LCD_Configure(void);
void LCD_Clear(void);
void LCD_DisplayString(uint8_t* ptr);
void LCD_WriteChar(uint8_t* ch, bool point, bool colon, uint8_t position);
static void LCD_Conv_Char_Seg(uint8_t* c,bool point,bool colon, uint8_t* digit);
void LCD_DisplayTime(uint32_t millis);
void LCD_WriteObject(uint8_t position, uint8_t object);
void LCD_Display_Bar(int bar0, int bar1, int bar2, int bar3);
void LCD_DisplayScore(uint32_t num);

#endif /* __STM32L476G_DISCOVERY_LCD_H */
