/*
 * i2c.c
 * description: file to i2c protocol
 *  Created on: 01-May-2023
 *      Author: Isha Sharma
 */

#include "i2c.h"

int lock_detect = 0;
int i2c_lock = 0;

/*
name: i2c_init
description: function to initialise pins for i2c
parameters: none
returns: none
 */
void i2c_init(void)
{

	//clock i2c0 peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Set pins to I2C functionality
	PORTE->PCR[24] |= PORT_PCR_MUX(5);	// I2C0_SCL
	PORTE->PCR[25] |= PORT_PCR_MUX(5);	// I2C0_SDA

	//set to 100k baud
	//baud = bus freq/(scl_div+mul)
 	//~400k = 24M/(64); icr=0x12 sets scl_div to 64
	I2C0->F = (I2C_F_MULT(0) | I2C_F_ICR(0X10));

	//Enable I2C and set it to master mode
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	//Select high drive mode
	I2C0->C2 |= I2C_C2_HDRS_MASK;
}

/*
name: i2c_busy
description: function to check for i2c being busy or not
parameters: none
returns: none
 */
void i2c_busy(void)
{
	lock_detect = 0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_TX_MASK;		//transmit
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	//write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK;	//Set Master mode
	I2C0->C1 |= I2C_C1_TX_MASK;		//Set tx mode
	I2C0->D = 0xFF;
	while((I2C0->S & I2C_S_IICIF_MASK) == 0U)
	{
	}								// wait interrupt
	I2C0->S |= I2C_S_IICIF_MASK;	// clear interrupt bit

	I2C0->S |= I2C_S_ARBL_MASK;		//Clear arbitration error flag

	I2C0->C1 &= ~I2C_C1_IICEN_MASK;	//Send start
	I2C0->C1 |= I2C_C1_TX_MASK;		//set tx mode
	I2C0->C1 |= I2C_C1_MST_MASK;	//Start signal generated

	I2C0->C1 |= I2C_C1_IICEN_MASK;

	I2C0->C1 &= ~I2C_C1_IICEN_MASK; //wait till start is ready
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Set to slave mode
	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set rx mode
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;		//Clear arbitration and interrupt flag
	lock_detect=0;
	i2c_lock = 1;
}

/*
name: i2c_wait
description: function to wait till i2c line is cleared, completed
parameters: none
returns: none
 */
void i2c_wait(void)
{
	lock_detect = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK) == 0) & (lock_detect < 200)){
		lock_detect++;
	}
	if(lock_detect >= 200){
		i2c_busy();
	}
	I2C0->S |= I2C_S_IICIF_MASK;
}

/*
name: i2c_start
description: function to start i2c protocol
parameters: none
returns: none
 */
void i2c_start(void)
{
	I2C0->C1 |= I2C_C1_TX_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
}

/*
name: i2c_read_setup
description: function to setup registers to read device and register addresses
parameters: device address, register address
returns: none
 */
void i2c_read_setup(uint8_t dev, uint8_t address)
{
	I2C0->D = dev;					//send device address
	i2c_wait();						// Wait for completion
	I2C0->D = address;				//send read address
	i2c_wait();						// Wait for completion
	I2C0->C1 |= I2C_C1_RSTA_MASK;	//repeated start
	I2C0->D = (dev|0x1);			//send device address for value to read
	i2c_wait();						// wait for completition
	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set to receive mode
}

/*
name: i2c_repeated_read
description: function to configure i2c repeated start logic
parameters: last read flag
returns: data read from register
 */
uint8_t i2c_repeated_read(uint8_t last_read_flag)
{
	uint8_t data;
	lock_detect = 0;

	if(last_read_flag){
		I2C0->C1 |= I2C_C1_TXAK_MASK; //NACK
	}
	else{
		I2C0->C1 &= ~I2C_C1_TXAK_MASK; //ACK
	}

	data = I2C0->D;					//dummy read
	i2c_wait();						//wait for completion

	if(last_read_flag){
		I2C0->C1 &= ~I2C_C1_MST_MASK; //send stop
	}
	data = I2C0->D;					//read data

	return data;
}

/*
name: i2c_read_byte
description: function to read byte using i2c D register
parameters: device address, address for i2c D rgister
returns:  data read from register
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C0->C1 |= I2C_C1_TX_MASK;		//Set to transmit mode
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;	//Send start
	I2C0->D = dev;					//Send device address
	i2c_wait();						// wait for completion

	I2C0->D = address;				//Send read address
	i2c_wait();						// wait for completion

	I2C0->C1 |= I2C_C1_RSTA_MASK;	//Repeated start
	I2C0->D = (dev|0x1);			//Send development address - read
	i2c_wait();						// wait for completion

	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set to receive mode
	I2C0->C1 |= I2C_C1_TXAK_MASK;	//NACK

	data = I2C0->D;					//Read backup
	i2c_wait();						// wait for completion

	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Send stop
	data = I2C0->D;					//Read data

	return data;
}

/*
name: i2c_write_byte
description: function to write byte using i2c D register
parameters: device address, address for D register, data to be written
returns: none
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{
	I2C0->C1 |= I2C_C1_TX_MASK;		//Set to transmit mode
	I2C0->C1 |= I2C_C1_MST_MASK;	//Send start
	I2C0->D = dev;					//Send device address
	i2c_wait();						// wait for completion

	I2C0->D = address;				//Send write address
	i2c_wait();						// wait for completion

	I2C0->D = data;					//Send data
	i2c_wait();						// wait for completion
	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Send stop bit
}
