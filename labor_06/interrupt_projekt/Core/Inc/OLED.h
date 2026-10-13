#ifndef OLED_H_
#define OLED_H_

#include "main.h"

typedef enum {
    Font_7x10 = 0,
    Font_11x18 = 1,
    Font_16x26 = 2
} FontDef;

typedef enum {
    Black = 0x00,
    White = 0x01
} OLED_COLOR;

void OLED_Init(void);
void OLED_Fill(OLED_COLOR color);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_WriteString(char* str, FontDef Font, OLED_COLOR color);
void OLED_UpdateScreen(void);

#endif /* OLED_H_ */
