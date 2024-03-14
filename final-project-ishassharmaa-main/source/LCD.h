/*
 * OLED.h
 *
 *  Created on: 02-May-2023
 *      Author: Isha Sharma
 */

#ifndef LCD_H_
#define LCD_H_

#include "MKL25Z4.h"

 // LCD to GPIO pin configuration interface
#define PTC7 7
#define PTC0 0
#define PTC3 3
#define PTC4 4
#define PTC5 5
#define PTC6 6
#define PTC10 10

#define LCD_DB7  ((uint32_t)1 << PTC7)  // PTC7
#define LCD_DB6  ((uint32_t)1 << PTC0)  // PTC0
#define LCD_DB5  ((uint32_t)1 << PTC3)  // PTC3
#define LCD_DB4  ((uint32_t)1 << PTC4)  // PTC4

#define LCD_E    ((uint32_t)1 << PTC5)  // PTC5
#define LCD_RW   ((uint32_t)1 << PTC6)  // PTC6
#define LCD_RS   ((uint32_t)1 << PTC10) // PTC10

//enum to define first or second row of the lcd
typedef enum
{
	LCD_LINE1,
	LCD_LINE2,
}lcd_line;

void delay(int cnt);
void lcd_init(void);
void write_nibble(uint8_t nibble);
void lcd_Cmd(uint8_t cmd);
void start_lcd(void);
void clear_lcd(void);
uint8_t lcd_string_write(char **str);
void lcd_data_write(char *data, lcd_line line);

#endif /* LCD_H_ */
