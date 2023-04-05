#include "Draw.h"

void drawDinosaur(int jumping) {
    if (jumping)
        LCD_WriteObject(1, DINOJUMP);
    else
        LCD_WriteObject(1, DINO);
}

void drawObstacle(uint8_t pos, int dino) {
    if(dino)
        LCD_WriteObject(pos, OBSTACLEDINO);
    else
        LCD_WriteObject(pos, OBSTACLE);
}