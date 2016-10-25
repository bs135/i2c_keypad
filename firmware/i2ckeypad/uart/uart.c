/*
* uart.c
*
* Created: 09/10/2016 10:43:47 AM
*  Author: BS135
*/

#include "../config.h"
#include <avr/io.h>
#include <util/setbaud.h>
#include "uart.h"

#ifdef UART_DEBUG
FILE uart_output = FDEV_SETUP_STREAM(uart_stream_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_stream_getchar, _FDEV_SETUP_READ);
#endif // UART_DEBUG

void uart_init(){
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	#if USE_2X
	UCSR0A |= _BV(U2X0);
	#else
	UCSR0A &= ~(_BV(U2X0));
	#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

void uart_putchar(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
	UDR0 = c;
	loop_until_bit_is_set(UCSR0A, TXC0); /* Wait until transmission ready. */
}

char uart_getchar(void) {
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
	return UDR0;
}


#ifdef UART_DEBUG
int uart_stream_putchar(char c, FILE *stream) {
	if (c == '\n') {
		uart_stream_putchar('\r', stream);
	}
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	
	return 0;
}

int uart_stream_getchar(FILE *stream) {
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}
#endif // UART_DEBUG