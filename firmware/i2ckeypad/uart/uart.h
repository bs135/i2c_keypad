/*
 * uart.h
 *
 * Created: 09/10/2016 10:41:35 AM
 *  Author: BS135
 */ 

#include <stdio.h>

#ifndef UART_H_
#define UART_H_


void uart_init();
void uart_putchar(char c);
char uart_getchar(void);

#ifdef UART_DEBUG
int uart_stream_putchar(char c, FILE *stream);
int uart_stream_getchar(FILE *stream);

extern FILE uart_output;
extern FILE uart_input;
#endif // UART_DEBUG

#endif /* UART_H_ */