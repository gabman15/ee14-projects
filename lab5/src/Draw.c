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

void drawBar(int level) {
    int bar0=0;
    int bar1=0;
    int bar2=0;
    int bar3=0;
    if(level > 0) {
        bar0 = 1;
        if (level > 1) {
            bar1 = 1;
            if (level > 2) {
                bar2 = 1;
                if (level > 3) {
                    bar3 = 1;
                }
            }
        }
    }
    LCD_Display_Bar(bar0, bar1, bar2, bar3);
}