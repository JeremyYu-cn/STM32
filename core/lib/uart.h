#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart1_init(void);

void uart_putc(char c);
void uart_puts(const char *s);

char uart_getc(void);

void uart_log(const char *level, const char *msg);

#endif