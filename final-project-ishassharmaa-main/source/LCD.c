/*
 * LCD.c
 * description: file to LCD
 *  Created on: 02-May-2023
 *      Author: Isha Sharma
 */


#include "lcd.h"

/*
name: delay
description: function to create delay
parameters: count for number (ns)
returns: none
 */
void delay(int cnt)
{
  int i,j;

	// 1 instruction takes 1/48000000 = 20nsec to execute
  	// at 48Mhz system clock
	for (j=0; j<5; j++)
	{
		for(i=0;i<cnt;i++);
	}
}

/*
name: lcd_init
description: function to initialise GPIOs for the lcd
parameters: none
returns: none
 */
void lcd_init(void){

	//Enable clock to PORTC
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);

	//Enable GPIO pins for LCD
	PORTC->PCR[10] |= PORT_PCR_MUX(1);			//Configure PTC10
	PORTC->PCR[7] |= PORT_PCR_MUX(1);			//Configure PTC7
	PORTC->PCR[6] |= PORT_PCR_MUX(1);			//Configure PTC6
	PORTC->PCR[5] |= PORT_PCR_MUX(1);			//Configure PTC5
	PORTC->PCR[4] |= PORT_PCR_MUX(1);			//Configure PTC4
	PORTC->PCR[3] |= PORT_PCR_MUX(1);			//Configure PTC3
	PORTC->PCR[0] |= PORT_PCR_MUX(1);			//Configure PTC0

	//Configure all the pins as output
	GPIOC->PDDR |= (LCD_DB7 | LCD_DB6 | LCD_DB5 | LCD_DB4 | LCD_E | LCD_RS | LCD_RW);
}

/*
name: lcd_init
description: function to write a nibble(4 bits) to the ddram
parameters: nibble to write
returns: none
 */
void write_nibble(uint8_t nibble)
{
		uint32_t gpio_temp;

		// store gpioc pdor
		gpio_temp = GPIOC->PDOR;

	  //update each data line one by one

		if (nibble & 0x80)//db7
		{
			gpio_temp |= LCD_DB7;
		}
		else
		{
			gpio_temp &= ~LCD_DB7;
		}

		if (nibble & 0x40)//db6
		{
			gpio_temp |= LCD_DB6;
		}
		else
		{
			gpio_temp &= ~LCD_DB6;
		}

		if (nibble & 0x20)
		{
			gpio_temp |= LCD_DB5;//db5
		}
		else
		{
			gpio_temp &= ~LCD_DB5;
		}

		if (nibble & 0x10)
		{
			gpio_temp |= LCD_DB4;//db4
		}
		else
		{
			gpio_temp &= ~LCD_DB4;
		}

		//update the pdor with calculated value
		GPIOC->PDOR = gpio_temp;
}

/*
name: lcd_Cmd
description: function to send command to lcd
parameters: command to write
returns: none
 */
void lcd_Cmd(uint8_t cmd)
{
		GPIOC->PDOR &= ~LCD_RS; // Select command register (RS=LOW)
		GPIOC->PDOR &= ~LCD_RW; // Select write operation  (RW=LOW)

		write_nibble(cmd & 0xF0); // Write Upper nibble

    // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_E;   // EN=HIGH
		delay(10000);           // Wait for ~1msec
		GPIOC->PDOR &= ~LCD_E;  // EN=LOW
		delay(10000);           // Wait for ~1msec

		write_nibble((cmd << 4) & 0xF0); // Write Lower nibble

    // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_E;   // EN=HIGH
		delay(10000);           // Wait for ~1msec
		GPIOC->PDOR &= ~LCD_E;  // EN=LOW
		delay(10000);           // Wait for ~1msec
}

/*
name: start_lcd
description: function to start lcd
parameters: none
returns: none
 */
void start_lcd(void)
{
	lcd_Cmd(0x02);  //cursor reset
	delay(100000);
	lcd_Cmd(0x28);  //  4-bit, 2 line, 5x7 dots mode for chars
	delay(100000);
	lcd_Cmd(0x0C);  // Display ON, Cursor OFF
	delay(100000);
	lcd_Cmd(0x01);  //clear lcd
	delay(100000);

}

/*
name: clear_lcd
description: function to clear lcd
parameters: none
returns: none
 */
void clear_lcd(void)
{
	lcd_Cmd(0x01); //clear lcd
	delay(10);
}

/*
name: lcd_string_write
description: function to write the string onto lcd
parameters: string to be written
returns: none
 */
uint8_t lcd_string_write(char **str)
{
	uint8_t cnt = 0; // Counting string length

	// Write until entire string (msg) is finished
	// (max 16 char per line)
	while (**str && cnt < 16)
	{
		GPIOC->PDOR |=  LCD_RS; // Select data register    (RS=HIGH)
		GPIOC->PDOR &= ~LCD_RW; // Select write operation  (RW=LOW)

		write_nibble(**str & 0xF0); // Write Upper nibble

    // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_E;   // EN=HIGH
		delay(10000);           // Wait for ~1msec
		GPIOC->PDOR &= ~LCD_E;  // EN=LOW
		delay(10000);           // Wait for ~1msec

		write_nibble((**str << 4) & 0xF0); // Write Lower nibble

    // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_E;   // EN=HIGH
		delay(10000);           // Wait for ~1msec
		GPIOC->PDOR &= ~LCD_E;  // EN=LOW
		delay(10000);           // Wait for ~1msec

		(*str)++; // Go to next character
		cnt++;     // Increment string length check count
		delay(100000);
	}

	return cnt;
}

/*
name: lcd_data_write
description: function to write a string that send the string generated to the lcd_string_write function
parameters: string to be written and which line of the lcd it should be printed on
returns: none
 */
void lcd_data_write(char *data, lcd_line line)
{
	uint8_t char_written; //data to be written
	char *temp = " "; //variable to dispal data and keep the rest of the lcd places as spaces

	if (line == LCD_LINE1)
	{
		lcd_Cmd(0x80);   // cursor to start of first line

	}
	else
	{
		lcd_Cmd(0xC0);   // cursor to start of second line

	}

	char_written = lcd_string_write(&data);
	//write data to lcd
	while(char_written < 16)
	{
		lcd_string_write(&temp);
		char_written++;
	}

}


