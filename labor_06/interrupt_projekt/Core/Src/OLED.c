#include "OLED.h"
extern I2C_HandleTypeDef hi2c2;

#define OLED_I2C &hi2c2
#define OLED_ADDRESS 0x78

static uint8_t OLED_Buffer[128 * 64 / 8];

void OLED_WriteCommand(uint8_t command) {
    HAL_I2C_Mem_Write(OLED_I2C, OLED_ADDRESS, 0x00, 1, &command, 1, 10);
}

void OLED_Init(void) {
    HAL_Delay(100);
    OLED_WriteCommand(0xAE); // Display off
    OLED_WriteCommand(0x20); // Set Memory Addressing Mode
    OLED_WriteCommand(0x10); // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    OLED_WriteCommand(0xB0); // Set Page Start Address for Page Addressing Mode, 0-7
    OLED_WriteCommand(0xC8); // Set COM Output Scan Direction
    OLED_WriteCommand(0x00); // Set low column address
    OLED_WriteCommand(0x10); // Set high column address
    OLED_WriteCommand(0x40); // Set start line address
    OLED_WriteCommand(0x81); // set contrast control register
    OLED_WriteCommand(0xFF);
    OLED_WriteCommand(0xA1); // Set segment re-map 0 to 127
    OLED_WriteCommand(0xA6); // Set normal display
    OLED_WriteCommand(0xA8); // Set multiplex ratio(1 to 64)
    OLED_WriteCommand(0x3F);
    OLED_WriteCommand(0xA4); // 0xa4,Output follows RAM content;0a5,Output ignores RAM content
    OLED_WriteCommand(0xD3); // set display offset
    OLED_WriteCommand(0x00); // not offset
    OLED_WriteCommand(0xD5); // set display clock divide ratio/oscillator frequency
    OLED_WriteCommand(0xF0);
    OLED_WriteCommand(0xD9); // set pre-charge period
    OLED_WriteCommand(0x22);
    OLED_WriteCommand(0xDA); // set com pins hardware configuration
    OLED_WriteCommand(0x12);
    OLED_WriteCommand(0xDB); // set vcomh
    OLED_WriteCommand(0x20);
    OLED_WriteCommand(0x8D); // set DC-DC enable
    OLED_WriteCommand(0x14);
    OLED_WriteCommand(0xAF); // Turn on OLED panel
    OLED_Fill(Black);
    OLED_UpdateScreen();
}

void OLED_Fill(OLED_COLOR color) {
    uint32_t i;
    for(i = 0; i < sizeof(OLED_Buffer); i++) {
        OLED_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
    }
}

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

void OLED_SetCursor(uint8_t x, uint8_t y) {
    cursor_x = x;
    cursor_y = y;
}

extern uint8_t Font7x10[];
extern uint8_t Font11x18[];
extern uint8_t Font16x26[];

void OLED_WriteString(char* str, FontDef Font, OLED_COLOR color) {
    while (*str) {
        str++;
    }
}

void OLED_UpdateScreen(void) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        OLED_WriteCommand(0xB0 + i);
        OLED_WriteCommand(0x00);
        OLED_WriteCommand(0x10);
        HAL_I2C_Mem_Write(OLED_I2C, OLED_ADDRESS, 0x40, 1, &OLED_Buffer[128 * i], 128, 100);
    }
}
