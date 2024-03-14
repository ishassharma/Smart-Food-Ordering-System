/*
 * buttons.h
 *
 *  Created on: 26-Apr-2023
 *      Author: Isha Sharma
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

void delay_50ms(void) ;
void init_push_buttons(void) ;
int button_flag_checker(void);
void PORTA_IRQHandler(void);

#endif /* BUTTONS_H_ */
