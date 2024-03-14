/*
 * statemachines.c
 * description: file for the main state machine
 *  Created on: 26-Apr-2023
 *      Author: Isha Sharma
 */

#include "screens.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "buttons.h"
#include "fsl_debug_console.h"
#include "screens.h"
#include "statemachines.h"
#include "LCD.h"

/*
name: statemachine
description: state machine for screens
parameters: none
returns: none
 */
void statemachine(void)
{
	States state = welcomescreen; //default state is welcome_screen
	States prevstate = welcomescreen; //previous state
	int button_state=0; //variable to keep track of current button stae for state machine
	while(1)
	{
		button_state=0;
	// switch case to determine state machine
		switch (state)
	{
	            case welcomescreen:
	            	PRINTF("\n\r STATE: WELCOME SCREEN \n\r");
	            	welcome_screen();
	            	button_state = button_flag_checker();
	            	while(button_state == 0)
	            	{
	            		button_state = button_flag_checker();
	            	}
	                if (button_state==1)
	                {
	                    state = cuisineselection; //change state to cuisine selection if enter is pressed
	                }

	               break;


	            case cuisineselection:
	            	PRINTF("\n\r STATE: CUISINE SCREEN \n\r");
	            	cuisine_selection();
	            	button_state = button_flag_checker();
	            	while(button_state == 0)
					{
						button_state = button_flag_checker();
					}

	                if (button_state==1)
					{
						state = italian; //change state to italian if enter is pressed
						prevstate= cuisineselection;
					}
	                else if (button_state == 2)
					{
						state = welcomescreen; //change state to welcome if back is pressed
					}

	                break;

	            case italian:
	            	PRINTF("\n\r STATE: ITALIAN \n\r");
	            	italian_menu();
	            	button_state = button_flag_checker();
	            	while(button_state == 0)
					{
						button_state = button_flag_checker();
					}

	            	if (button_state==1)
					{
						state = pizza; //change state to pizza if enter is pressed
						prevstate = italian;
					}
					else if (button_state == 3)
					{
						state = indian; //change state to indian if next is pressed
						prevstate = italian;
					}
	                break;

	            case pizza:
	            	PRINTF("\n\r STATE: PIZZA \n\r");
	            	pizza_italian();
	            	button_state = button_flag_checker();
	            	while(button_state == 0)
	            	{
	            		button_state = button_flag_checker();
	            	}

	            	if (button_state == 1)
					{
						state = finalcheckpoint; //change state to final checkpoint for order confirmation if enter is pressed
						prevstate = pizza;
					}
					else if (button_state == 2)
					{
						state = italian; //change state to italian if back is pressed
						prevstate = pizza;
					}
					else if (button_state == 3)
					{
						state = pasta; //change state to pasta if next is pressed
						prevstate = pizza;
					}

	                break;

	            case pasta:
	            	PRINTF("\n\r STATE: PASTA \n\r");
	            	pasta_italian();
	            	button_state = button_flag_checker();
	            	while(button_state == 0)
	            	{
	            		button_state = button_flag_checker();
	            	}

	            	if (button_state == 1)
					{
						state = finalcheckpoint;  //change state to final checkpoint for order confirmation if enter is pressed
						prevstate = pasta;
					}
					else if (button_state == 2)
					{
						state = pizza; //change state to pizza if back is pressed
						prevstate = pasta;
					}

	                break;

	            case indian:
	            	PRINTF("\n\r STATE: INDIAN \n\r");
	            	indian_menu();
	            	button_state = button_flag_checker();
	            	while(button_state == 0)
	            	{
	            		button_state = button_flag_checker();
	            	}

	            	if (button_state==1)
					{
						state = butter_chicken; //change state to butter_chicken if enter is pressed
						prevstate = indian;
					}
	            	else if(button_state==2)
					{
						state = italian; //change state to pizza if back is pressed
						prevstate = indian;
					}
	                break;

	            case butter_chicken:
	            	PRINTF("\n\r STATE: BUTTER CHICKEN \n\r");
	            	butter_chicken_indian();
	            	button_state = button_flag_checker();
	            	while(button_state == 0)
	            	{
	            		button_state = button_flag_checker();
	            	}

	            	if (button_state == 1)
					{
						state = finalcheckpoint; //change state to final checkpoint for order confirmation if enter is pressed
						prevstate = butter_chicken;
					}
					else if (button_state == 2)
					{
						state = indian; //change state to indian if back is pressed
						prevstate = butter_chicken;
					}
					else if (button_state == 3)
					{
						state = biryani; //change state to indian if next is pressed
						prevstate = butter_chicken;
					}

	                break;

	            case biryani:
	            	PRINTF("\n\r STATE: BIRYANI \n\r");
	            	biyrani_indian();
	            	button_state = button_flag_checker();
	            	while(button_state == 0)
	            	{
	            		button_state = button_flag_checker();
	            	}

	            	if (button_state == 1)
					{
						state = finalcheckpoint; //change state to final checkpoint for order confirmation if enter is pressed
						prevstate = biryani;
					}
					else if (button_state == 2) // "previous" button
					{
						state = butter_chicken; //change state to previous if back is pressed
						prevstate = biryani;
					}

	                break;

	            case finalcheckpoint:
	                PRINTF("\n\r STATE: FIANL CHECKPOINT \n\r");
	                final_checkpoint();
	                button_state = button_flag_checker();
	            	while(button_state == 0)
	            	{
	            		button_state = button_flag_checker();
	            	}

	                if(button_state==1) // "enter" button
	                {
	                    state = orderconfirmation; //change state to order confirmation for finishing if enter is pressed
	                    prevstate = finalcheckpoint;
	                }
	                else if(button_state==2) // if back is pressed go to whichever was the last state
	                {
	                    if(prevstate == pizza)
	                    {
	                        state = pizza;
	                    }
	                    else if(prevstate == pasta)
	                    {
	                        state = pasta;
	                    }
	                    else if(prevstate == butter_chicken)
	                    {
	                        state = butter_chicken;
	                    }
	                    else if(prevstate == biryani)
						{
							state = biryani;
						}
	                }
	                break;

	            case orderconfirmation:
	            	order_confirmation();
	            	button_state = button_flag_checker();
					while(button_state == 0)
					{
						button_state = button_flag_checker();
					}

					if(button_state==1) // "enter" button
					{
						state = welcomescreen; //reset states
						prevstate = welcomescreen;
					}
					break;
	        }
}
}
