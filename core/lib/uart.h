#ifndef __UART_H
#define __UART_H


void uart1_init(void);


void uart_putc(char c);

void uart_puts(const char *s);


char uart_getc(void);


void uart_printf(const char *fmt,...);


void uart_log(const char *level,const char *msg);


#endif