/*
 * buttons.c
 * description: file to handle buttons
 *  Created on: 26-Apr-2023
 *      Author: Isha Sharma
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "buttons.h"
#include "fsl_debug_console.h"

#define NEXT_PIN 16  // PTA16 interfaced as the 'next' pin
#define ENTER_PIN 17  //PTA 17 interfaced as the 'enter' pin
#define BACK_PIN  12// PTA 12 interfaced as the 'back' pin

#define MASK(x) (1UL << (x)) //mask for shifting

#define FIFTY_MILLISECONDS 50003 //approximately counts to 50ms

uint8_t button_pressed = 0; // variable to keep track of button presses

/*
name: delay_50ms
description: function to generate delay
parameters: none
returns: none
 */
void delay_50ms(void)
{
    uint32_t i;
    for (i = 0; i < FIFTY_MILLISECONDS; i++);
}

/*
name: init_push_buttons
description: initializes the buttons as gpio
parameters: none
returns: none
 */
void init_push_buttons(void)
{
    // enable PORTA clock
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    // set up GPIO pins for push buttons
    //setting ps=0, pe=1
    PORTA->PCR[NEXT_PIN] &=~ PORT_PCR_MUX_MASK; //UP PIN
    PORTA->PCR[NEXT_PIN] |= PORT_PCR_MUX(1) |  PORT_PCR_PE(1) | PORT_PCR_PS(0); //pin normally pulled down, pulled up enabled when input
    PTA->PDDR &=~ MASK(NEXT_PIN);


    //setting ps=0, pe=1
    PORTA->PCR[ENTER_PIN] &=~ PORT_PCR_MUX_MASK; //UP PIN
    PORTA->PCR[ENTER_PIN] |= PORT_PCR_MUX(1) |  PORT_PCR_PE(1) | PORT_PCR_PS(0); //pin normally pulled down, pulled up enabled when input
    PTA->PDDR &=~ MASK(ENTER_PIN);

    PORTA->PCR[BACK_PIN] &=~ PORT_PCR_MUX_MASK; //DOWN PIN
    PORTA->PCR[BACK_PIN] |= PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(0); //pin normally pulled down, pulled up enabled when input
    PTA->PDDR &=~ MASK(BACK_PIN);

    //enabling interrupts
    PORTA->PCR[NEXT_PIN] |= PORT_PCR_IRQC(0x09);// interrupt triggered at rising edge
    PORTA->PCR[ENTER_PIN] |= PORT_PCR_IRQC(0x09);
    PORTA->PCR[BACK_PIN] |= PORT_PCR_IRQC(0x09);


    NVIC_SetPriority(PORTA_IRQn, 2); //set priority 2
    NVIC_ClearPendingIRQ(PORTA_IRQn);
    NVIC_EnableIRQ(PORTA_IRQn);


    PRINTF("Button press init done \n");

}

/*
name: button_flag_checker
description: checks the flag based on which button is pressed
parameters: none
returns: flag for which button was pressed
 */
int button_flag_checker(void)
{
	//disable irq
    NVIC_DisableIRQ(PORTA_IRQn);

	int current_button_state = 0;

    if (button_pressed == 1) //enter is pressed
    {
    	current_button_state = 1;
    	button_pressed = 0; // reset button_pressed variable

        PRINTF("\n\r ENTER PRESSED \n\r");
    }

    if (button_pressed == 2) //back is pressed
    {
    	current_button_state = 2;
    	 button_pressed = 0; // reset button_pressed variable

    	 PRINTF("\n\r BACK PRESSED \n\r");
    }

    if (button_pressed == 3) //next is pressed
    {
    	current_button_state = 3;
    	 button_pressed = 0; // reset button_pressed variable

    	 PRINTF("\n\r NEXT PRESSED \n\r");
    }

    //enable irq
      NVIC_EnableIRQ(PORTA_IRQn);

      return current_button_state;
}


/*
name: PORTA_IRQHandler
description: irq handler for buttons
parameters: none
returns: none
 */
void PORTA_IRQHandler(void)
{

    // disable irq
    NVIC_DisableIRQ(PORTA_IRQn);

    // check for interrupt and clear interrupt flags
    if (PORTA->ISFR & MASK(ENTER_PIN))
    {
    	delay_50ms(); // delay for debounce
        if (PORTA->ISFR & MASK(ENTER_PIN)) // check again after delay
        {
            button_pressed = 1; //enter pressed
        }
        PORTA->ISFR |= MASK(ENTER_PIN);
    }

    if (PORTA->ISFR & MASK(BACK_PIN))
    {
    	delay_50ms(); // delay for debounce
        if (PORTA->ISFR & MASK(BACK_PIN)) // check again after delay
        {
            button_pressed = 2; //back pressed
        }
        PORTA->ISFR |= MASK(BACK_PIN);
    }

    if (PORTA->ISFR & MASK(NEXT_PIN))
    {
    	delay_50ms(); // delay for debounce
        if (PORTA->ISFR & MASK(NEXT_PIN)) // check again after delay
        {
            button_pressed = 3; //next pressed
        }
        PORTA->ISFR |= MASK(NEXT_PIN);
    }

    // enable irq
    NVIC_EnableIRQ(PORTA_IRQn);
}

