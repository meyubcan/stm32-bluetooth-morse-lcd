#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"

// LCD pin tanımlamaları
#define LCD_RS_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_6

#define LCD_E_GPIO_Port GPIOA
#define LCD_E_Pin GPIO_PIN_7

#define LCD_D4_GPIO_Port GPIOA
#define LCD_D4_Pin GPIO_PIN_8

#define LCD_D5_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_9

#define LCD_D6_GPIO_Port GPIOA
#define LCD_D6_Pin GPIO_PIN_10

#define LCD_D7_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_4

// Fonksiyon prototipleri
void LCD_Init(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_SendString(char *str);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Clear(void);

#endif /* INC_LCD_H_ */
