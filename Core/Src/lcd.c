#include "lcd.h"
#include "string.h"

static void LCD_Enable(void) {
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

static void LCD_Send4Bits(uint8_t data) {
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (data >> 0) & 0x01);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (data >> 3) & 0x01);
}

void LCD_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
    LCD_Send4Bits(cmd >> 4);
    LCD_Enable();
    LCD_Send4Bits(cmd & 0x0F);
    LCD_Enable();
    HAL_Delay(2);
}

void LCD_SendData(uint8_t data) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    LCD_Send4Bits(data >> 4);
    LCD_Enable();
    LCD_Send4Bits(data & 0x0F);
    LCD_Enable();
    HAL_Delay(2);
}

void LCD_SendString(char *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? 0x00 + col : 0x40 + col;
    LCD_SendCommand(0x80 | address);
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

void LCD_Init(void) {
    HAL_Delay(50);
    LCD_Send4Bits(0x03); LCD_Enable(); HAL_Delay(5);
    LCD_Enable(); HAL_Delay(1);
    LCD_Enable(); HAL_Delay(1);
    LCD_Send4Bits(0x02); LCD_Enable(); HAL_Delay(1);

    LCD_SendCommand(0x28); // 4-bit, 2-line
    LCD_SendCommand(0x0C); // Display ON, cursor OFF
    LCD_SendCommand(0x06); // Entry mode
    LCD_Clear();
}
