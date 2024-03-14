/*
 * i2c.h
 *
 *  Created on: 01-May-2023
 *      Author: Isha Sharma
 */

#ifndef I2C_H_
#define I2C_H_

#include "MKL25Z4.h"
#include <stdio.h>

void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
uint8_t i2c_repeated_read(uint8_t last_read_flag);
void i2c_read_setup(uint8_t dev, uint8_t address);
void i2c_start(void);
void i2c_wait(void);
void i2c_busy(void);
void i2c_init(void);


#endif /* I2C_H_ */
