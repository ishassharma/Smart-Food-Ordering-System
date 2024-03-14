/*
 * screens.c
 * description: file to handle screens of the statemachine
 *  Created on: 25-Apr-2023
 *      Author: Isha Sharma
*/

#include <string.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "buttons.h"
#include "fsl_debug_console.h"
#include "screens.h"
#include "LCD.h"

//lcd can take 16 entries in one line so lcd commands divided accordingly and printf is used for rest of the instructions

/*
name: welcome_screen
description: welcome screen page
parameters: none
returns: none
 */
void welcome_screen(void)
{
	PRINTF("\n\r\t\t\t WELCOME SCREEN \t\t\t\n\r");
	PRINTF("\n\r\t\t\t PRESS ENTER TO CONTINUE \t\t\t\n\r");
    clear_lcd();
	lcd_data_write("  FLAVOSPHERE  ", LCD_LINE1);
	lcd_data_write(" HELLO,WELCOME!", LCD_LINE2);

}

/*
name: cuisine_selection
description: cuisine selection screen page
parameters: none
returns: none
 */
void cuisine_selection(void)
{
	PRINTF("\n\r\t\t\t CUISINE SELECTION \n\r ");
	PRINTF("\n\r\t\t\tPRESS ENTER TO GO FORWARD WITH THE ORDERING \t\t\t\n\r");
	clear_lcd();
	lcd_data_write("CUISINES OFFERED", LCD_LINE1);
	lcd_data_write(".....", LCD_LINE2);
	clear_lcd();
	lcd_data_write("1) ITALIAN", LCD_LINE1);
	lcd_data_write("2) INDIAN", LCD_LINE2);

}

/*
name: italian_menu
description: italian menu screen page
parameters: none
returns: none
 */
void italian_menu(void)
{
	PRINTF("\n\r\t\t\t ITALIAN CUISINE \n\r ");
	PRINTF("\n\r\t\t\tPRESS ENTER TO CHOOSE ITALIAN\t\t\t\n\r");
	PRINTF("\n\r\t\t\tPRESS NEXT TO SEE NEXT CUISINE \t\t\t\n\r");

	clear_lcd();
	lcd_data_write("ITALIAN CUISINE: ", LCD_LINE1);
	lcd_data_write(".....", LCD_LINE2);
	clear_lcd();
	lcd_data_write("1) PIZZA", LCD_LINE1);
	lcd_data_write("2) PASTA", LCD_LINE2);

}

/*
name: pizza_italian
description: pizza italian screen page
parameters: none
returns: none
 */
void pizza_italian(void)
{
	PRINTF("\n\r\t\t\t PIZZA  \n\r ");
	PRINTF("\n\r\t\t\tPRESS ENTER TO GO FORWARD WITH THE ORDERING PIZZA \t\t\t\n\r");
	PRINTF("\n\r\t\t\tPRESS BACK TO GO BACK TO ITALIAN PAGE \t\t\t\n\r");
	PRINTF("\n\r\t\t\tPRESS NEXT TO CHOOSE PASTA \t\t\t\n\r");

	clear_lcd();
	lcd_data_write("SELECTED: ", LCD_LINE1);
	lcd_data_write("PIZZA", LCD_LINE2);

}

/*
name: pasta_italian
description: pasta italian screen page
parameters: none
returns: none
 */
void pasta_italian(void)
{
	PRINTF("\n\r\t\t\t PASTA  \n\r ");
	PRINTF("\n\r\t\t\tPRESS ENTER TO GO FORWARD WITH THE ORDERING PASTA \t\t\t\n\r");
	PRINTF("\n\r\t\t\tPRESS BACK TO GO BACK TO CHOOSE PIZZA \t\t\t\n\r");

	clear_lcd();
	lcd_data_write("SELECTED: ", LCD_LINE1);
	lcd_data_write("PASTA", LCD_LINE2);
	clear_lcd();

}

/*
name: indian_menu
description: indian menu screen page
parameters: none
returns: none
 */
void indian_menu(void)
{

	PRINTF("\n\r\t\t\t INDIAN CUISINE \n\r ");
	PRINTF("\n\r\t\t\tPRESS ENTER TO CHOOSE INDIAN\t\t\t\n\r");
	PRINTF("\n\r\t\t\tPRESS BACK TO GO BACK TO CUISINE SELECTION PAGE\t\t\t\n\r");

	clear_lcd();
	lcd_data_write("INDIAN CUISINE: ", LCD_LINE1);
	lcd_data_write(".....", LCD_LINE2);
	clear_lcd();
	lcd_data_write("1)BUTTER CHICKEN", LCD_LINE1);
	lcd_data_write("2) BIRYANI", LCD_LINE2);

}

/*
name: butter_chicken_indian
description: butter_chicken_indian screen page
parameters: none
returns: none
 */
void butter_chicken_indian(void)
{
	PRINTF("\n\r\t\t\t BUTTER CHICKEN  \n\r ");
	PRINTF("\n\r\t\t\tPRESS ENTER TO GO FORWARD WITH THE ORDERING BUTTER CHICKEN\t\t\t\n\r");
	PRINTF("\n\r\t\t\tPRESS BACK TO GO BACK TO INDIAN PAGE\t\t\t\n\r");
	PRINTF("\n\r\t\t\tPRESS NEXT TO CHOOSE BIRYANI \t\t\t\n\r");

	clear_lcd();
	lcd_data_write("SELECTED: ", LCD_LINE1);
	lcd_data_write("BUTTER CHICKEN", LCD_LINE2);

}

/*
name: biyrani_indian
description: biyrani indian screen page
parameters: none
returns: none
 */
void biyrani_indian(void)
{
	PRINTF("\n\r\t\t\t BIRYANI \n\r ");
	PRINTF("\n\r\t\t\tPRESS ENTER TO GO FORWARD WITH THE ORDERING BIRYANI\t\t\t\n\r");
	PRINTF("\n\r\t\t\tPRESS BACK TO GO BACK TO CHOOSE BUTTER CHICKEN \t\t\t\n\r");

	clear_lcd();
	lcd_data_write("SELECTED: ", LCD_LINE1);
	lcd_data_write("BIRYANI", LCD_LINE2);

}

/*
name: final_checkpoint
description: final checkpoint screen page that asks the user if he wants to confirm the order
parameters: none
returns: none
 */
void final_checkpoint(void)
{
	PRINTF("\n\r\t\t\t CONFIRM YOUR ORDER? \n\r ");
	PRINTF("\n\r\t\t\t PRESS BACK TO GO BACK \t\t\t\n\r");
	PRINTF("\n\r\t\t\t PRESS ENTER TO CONFIRM \t\t\t\n\r");
	clear_lcd();
	lcd_data_write("CONFIRM ORDER? ", LCD_LINE1);

}

/*
name: order_confirmation
description: orderconfirmation screen page
parameters: none
returns: none
 */
void order_confirmation(void)
{
	PRINTF("\n\r\t\t\t ORDER CONFIRMED \n\r ");
	PRINTF("\n\r\t\t\tPRESS ENTER TO FINISH \t\t\t\n\r");
	clear_lcd();
	lcd_data_write("ORDER CONFIRMED ", LCD_LINE1);
	lcd_data_write("PAY AT COUNTER", LCD_LINE2);
}

