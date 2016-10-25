/*
* i2ckeypad.c
*
* Created: 29/08/2016 4:07:06 PM
* Author : BS135
*/

#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "main.h"
#include "uart/uart.h"
#include "i2c/i2c_master.h"
#include "i2c_keymatrix/i2c_keymatrix.h"


int main(void)
{

	uart_init();
	i2c_init();
	
	#ifdef UART_DEBUG
	stdout = &uart_output;
	stdin  = &uart_input;
	#endif // UART_DEBUG

	#ifdef UART_DEBUG
	char input;
	uint16_t portRead;
	uint8_t row;
	uint8_t col;
	uint8_t col_val;
	
	puts("Hello world!");
	puts("Welcome to i2ckeypad project.");
	
	while(1) {
		input = getchar();
		printf("%c\n", input);
		
		switch (input)
		{
			case 'w':// write
			puts("I2C_WRITE");
			i2c_keymatrix_write(0xbe, 0xef);
			break;
			
			case 'r':
			puts("I2C_READ");
			portRead = 0x0000;
			portRead=i2c_keymatrix_read();
			printf("%x\n", portRead);
			break;
			
			case '1':
			puts("Select row 1");
			i2c_keymatrix_write(0xff, ~_BV(0));
			break;
			
			case '2':
			puts("Select row 2");
			i2c_keymatrix_write(0xff, ~_BV(1));
			break;
			
			case '3':
			puts("Select row 3");
			i2c_keymatrix_write(0xff, ~_BV(2));
			break;
			
			case '4':
			puts("Select row 4");
			i2c_keymatrix_write(0xff, ~_BV(3));
			break;
			
			case '5':
			puts("Select row 5");
			i2c_keymatrix_write(0xff, ~_BV(4));
			break;
			
			case 's':
			puts("Scan result:");

			for (row = 0; row < 5; row++)
			{
				i2c_keymatrix_unselect_rows();
				i2c_keymatrix_select_row(row);
				col_val = i2c_keymatrix_read_cols();
				for (col = 0; col < 4; col++)
				{
					if (col_val & _BV(col))
					{
						putchar('1');
					}
					else
					{
						putchar('0');
					}
				}
				putchar('\n');
			}
			
			break;
			
			default:
			puts("Hello All!");
			break;
		}
	}
	#endif // UART_DEBUG
	
	DDRB |= _BV(DDB5);	// PB5=Out
	PORTB  &= ~_BV(PORTB5);
	while (1)
	{
		PORTB  &= ~_BV(PORTB5);
		_delay_ms(200);
		PORTB  |= _BV(PORTB5);
		_delay_ms(100);
	}
	

	return 0;
}

