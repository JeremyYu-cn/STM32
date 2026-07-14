#include <stdint.h>


#define RCC_BASE    0x40021000

#define RCC_CR      (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_CFGR    (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x1C))

#define FLASH_ACR   (*(volatile uint32_t *)0x40022000)


void SystemInit(void)
{

    /*
     * HSE ON
     */
    RCC_CR |= (1<<16);

    while(!(RCC_CR & (1<<17)));


    /*
     * FLASH 2WS
     */
    FLASH_ACR &= ~0x7;
    FLASH_ACR |= 0x2;


    /*
     * AHB = SYSCLK
     */
    RCC_CFGR &= ~(0xF<<4);


    /*
     * APB1 = HCLK/2
     */
    RCC_CFGR &= ~(7<<8);
    RCC_CFGR |= (4<<8);


    /*
     * PLL source HSE
     */
    RCC_CFGR |= (1<<16);


    /*
     * PLL x9
     */
    RCC_CFGR &= ~(0xF<<18);
    RCC_CFGR |= (7<<18);


    /*
     * PLL enable
     */
    RCC_CR |= (1<<24);

    while(!(RCC_CR&(1<<25)));


    /*
     * switch SYSCLK PLL
     */
    RCC_CFGR &= ~(3<<0);
    RCC_CFGR |= (2<<0);


    while((RCC_CFGR&(3<<2))!=(2<<2));

}