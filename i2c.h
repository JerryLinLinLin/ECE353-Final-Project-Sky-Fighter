/*
 * i2c.h
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
 */

#ifndef I2C_H_
#define I2C_H_

#include "msp.h"
#include <stdint.h>

/**********************************************************************************************
 * Initialize I2C
 **********************************************************************************************/
void i2c_init(void);

/**********************************************************************************************
 * Read an I2C device
 **********************************************************************************************/
uint16_t i2c_read_16(uint8_t subordinate_address, uint8_t reg_address);

/**********************************************************************************************
 * Write an I2C device
 **********************************************************************************************/
void i2c_write_16(uint8_t subordinate_address, uint8_t reg_address, uint16_t data);



#endif /* I2C_H_ */
