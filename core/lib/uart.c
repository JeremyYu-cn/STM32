#include "uart.h"
#include <stdarg.h>
#include <stdio.h>


#define USART1_BASE 0x40013800UL


#define USART1_SR   (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR   (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR  (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1  (*(volatile uint32_t *)(USART1_BASE + 0x0C))


#define RCC_BASE 0x40021000UL
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))


#define GPIOA_BASE 0x40010800UL
#define GPIOA_CRH (*(volatile uint32_t *)(GPIOA_BASE + 0x04))



void uart1_init(void)
{

    /*
     * GPIOA clock
     */
    RCC_APB2ENR |= (1 << 2);


    /*
     * USART1 clock
     */
    RCC_APB2ENR |= (1 << 14);



    /*
     * PA9 TX
     *
     * MODE = 11 50MHz
     * CNF  = 10 AF PP
     *
     * 1011
     */
    GPIOA_CRH &= ~(0xF << 4);
    GPIOA_CRH |=  (0xB << 4);



    /*
     * 72MHz / 115200
     */
    USART1_BRR = 0x0271;



    /*
     * UE
     * TE
     * RE
     */
    USART1_CR1 |= (1 << 13); // USART enable
    USART1_CR1 |= (1 << 3);  // TX enable
    USART1_CR1 |= (1 << 2);  // RX enable

}



void uart_putc(char c)
{
    while(!(USART1_SR & (1 << 7)))
    {
        // wait TXE
    }

    USART1_DR = c;
}



void uart_puts(const char *s)
{
    while(*s)
    {
        uart_putc(*s++);
    }
}



char uart_getc(void)
{

    /*
     * RXNE bit
     */
    while(!(USART1_SR & (1 << 5)))
    {

    }


    return (char)USART1_DR;

}



void uart_log(const char *level, const char *msg)
{

    uart_puts("[");
    uart_puts(level);
    uart_puts("] ");

    uart_puts(msg);

    uart_puts("\r\n");
}