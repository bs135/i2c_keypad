/*
 * i2c_keymatrix.h
 *
 * Created: 19/10/2016 1:34:28 AM
 *  Author: Hai
 */ 


#ifndef I2C_KEYMATRIX_H_
#define I2C_KEYMATRIX_H_


// PCF8575 address
#define I2C_SLAVE_ADDR	0x40

uint8_t i2c_keymatrix_write(uint8_t port0, uint8_t port1);
uint16_t i2c_keymatrix_read(void);
void i2c_keymatrix_unselect_rows(void);
void i2c_keymatrix_select_row(uint8_t row);
uint8_t i2c_keymatrix_read_cols(void);
//uint32_t i2c_keymatrix_scan(void);

#endif /* I2C_KEYMATRIX_H_ */