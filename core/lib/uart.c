#include "uart.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>


#define USART1_BASE 0x40013800UL


#define USART1_SR   (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR   (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR  (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1  (*(volatile uint32_t *)(USART1_BASE + 0x0C))
#define USART1_CR2  (*(volatile uint32_t *)(USART1_BASE + 0x10))
#define USART1_CR3  (*(volatile uint32_t *)(USART1_BASE + 0x14))


#define RCC_BASE 0x40021000UL

#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))


#define GPIOA_BASE 0x40010800UL

#define GPIOA_CRH (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))



/*
 * USART1 init
 *
 * STM32F103
 *
 * Clock:
 * SYSCLK 72MHz
 * APB2   72MHz
 *
 * Baud:
 * 115200
 *
 */
void uart1_init(void)
{

    /*
     * Enable:
     * AFIO
     * GPIOA
     * USART1
     */
    RCC_APB2ENR |= (1 << 0);
    RCC_APB2ENR |= (1 << 2);
    RCC_APB2ENR |= (1 << 14);



    /*
     * PA9 TX
     *
     * MODE = 11
     * CNF  = 10
     *
     * 1011
     */
    GPIOA_CRH &= ~(0xF << 4);
    GPIOA_CRH |=  (0xB << 4);



    /*
     * PA10 RX
     *
     * MODE = 00
     * CNF  = 10
     *
     * 1000
     */
    GPIOA_CRH &= ~(0xF << 8);
    GPIOA_CRH |=  (0x8 << 8);


    /*
     * RX pull-up
     */
    GPIOA_ODR |= (1 << 10);



    /*
     * Reset USART config
     */
    USART1_CR1 = 0;
    USART1_CR2 = 0;
    USART1_CR3 = 0;



    /*
     * 72MHz
     *
     * Baud = 115200
     *
     * BRR = 0x0271
     */
    USART1_BRR = 0x0271;



    /*
     * Enable USART
     *
     * UE
     * TE
     * RE
     */
    USART1_CR1 |= (1 << 13);
    USART1_CR1 |= (1 << 3);
    USART1_CR1 |= (1 << 2);

}



/*
 * send one char
 */
void uart_putc(char c)
{

    /*
     * convert \n to \r\n
     */
    if(c == '\n')
    {
        while(!(USART1_SR & (1 << 7)));

        USART1_DR = '\r';
    }



    /*
     * wait TX empty
     */
    while(!(USART1_SR & (1 << 7)))
    {

    }


    USART1_DR = (uint32_t)c;



    /*
     * wait transmission complete
     */
    while(!(USART1_SR & (1 << 6)))
    {

    }

}



/*
 * send string
 */
void uart_puts(const char *s)
{

    while(*s)
    {
        uart_putc(*s++);
    }

}



/*
 * receive char
 */
char uart_getc(void)
{

    while(!(USART1_SR & (1 << 5)))
    {

    }


    return (char)USART1_DR;

}

static void uart_put_uint(uint32_t num)
{
    char buf[11];
    int i = 0;


    if(num == 0)
    {
        uart_putc('0');
        return;
    }


    while(num)
    {
        buf[i++] = '0' + (num % 10);
        num /= 10;
    }


    while(i--)
    {
        uart_putc(buf[i]);
    }
}



static void uart_put_int(int32_t num)
{

    if(num < 0)
    {
        uart_putc('-');
        num = -num;
    }


    uart_put_uint((uint32_t)num);

}



/*
 * printf style output
 */
void uart_printf(const char *fmt,...)
{

    va_list args;

    va_start(args,fmt);


    while(*fmt)
    {

        if(*fmt != '%')
        {
            uart_putc(*fmt++);
            continue;
        }


        fmt++;


        switch(*fmt)
        {

            case 'd':
            {
                int value = va_arg(args,int);
                uart_put_int(value);
                break;
            }


            case 'u':
            {
                uint32_t value = va_arg(args,uint32_t);
                uart_put_uint(value);
                break;
            }


            case 's':
            {
                char *str = va_arg(args,char *);
                uart_puts(str);
                break;
            }


            case 'c':
            {
                char c = (char)va_arg(args,int);
                uart_putc(c);
                break;
            }


            case '%':
            {
                uart_putc('%');
                break;
            }


            default:
                break;

        }


        fmt++;

    }


    va_end(args);
}



/*
 * log output
 *
 * example:
 *
 * uart_log("INFO","system start");
 *
 * output:
 *
 * [INFO] system start
 *
 */
void uart_log(const char *level,const char *msg)
{

    uart_puts("[");

    uart_puts(level);

    uart_puts("] ");


    uart_puts(msg);


    uart_puts("\r\n");

}