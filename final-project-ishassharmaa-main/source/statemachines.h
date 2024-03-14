/*
 * statemachines.h
 *
 *  Created on: 26-Apr-2023
 *      Author: Isha Sharma
 */

#ifndef STATEMACHINES_H_
#define STATEMACHINES_H_

//enum for different states
typedef enum
{
    welcomescreen,
	cuisineselection,
	italian,
	pizza,
	pasta,
	indian,
	butter_chicken,
	biryani,
	finalcheckpoint,
	orderconfirmation
} States;

void statemachine(void);

#endif /* STATEMACHINES_H_ */
