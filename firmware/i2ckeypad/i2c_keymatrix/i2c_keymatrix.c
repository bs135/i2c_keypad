/*
* i2c_keymatrix.c
*
* Created: 19/10/2016 1:34:18 AM
*  Author: Hai
*/

#include <avr/io.h>
#include "i2c_keymatrix.h"
#include "../i2c/i2c_master.h"

uint8_t i2c_keymatrix_write(uint8_t port0, uint8_t port1)
{
	if (i2c_start(I2C_SLAVE_ADDR | I2C_WRITE)) return 1;
	if (i2c_write(port0)) return 1;
	if (i2c_write(port1)) return 1;
	i2c_stop();
	return 0;
}

uint16_t i2c_keymatrix_read(void)
{
	uint8_t port0;
	uint8_t port1;

	if (i2c_start(I2C_SLAVE_ADDR | I2C_READ)) return 1;
	
	port0 = i2c_read_ack();
	port1 = i2c_read_nack();
	i2c_stop();

	return (port0 << 8) | port1;
}

void i2c_keymatrix_unselect_rows(void)
{
	i2c_keymatrix_write(0xff, 0xff);
}

void i2c_keymatrix_select_row(uint8_t row)
{
	i2c_keymatrix_write(0xff, ~_BV(row));
}

uint8_t i2c_keymatrix_read_cols(void)
{
	uint8_t port0;

	if (i2c_start(I2C_SLAVE_ADDR | I2C_READ)) return 1;
	
	port0 = i2c_read_ack();
	i2c_read_nack();//port1 
	i2c_stop();

	return ~(port0 & 0x0f);
}

//uint32_t i2c_keymatrix_scan(void)
//{
	//uint8_t row;
	//uint8_t col;
	//uint8_t col_val;
	//uint32_t matrix = 0;
	//for (row = 0; row < 5; row++)
	//{
		//i2c_keymatrix_unselect_rows();
		//i2c_keymatrix_select_row(row);
		//col_val = i2c_keymatrix_read_cols();
		//for (col = 0; col < 4; col++)
		//{
			//matrix = matrix<<1;
			//if (col_val & _BV(col))
			//{
				//matrix = matrix | 1;
			//}
		//}
	//}
	//
	//return matrix;
//}