#include <stdint.h>
#include "lib/base/flash.h"
#include "lib/base/rcc.h"

#define RCC_BASE 0x40021000

#define RCC_CR (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_CFGR (*(volatile uint32_t *)(RCC_BASE + 0x04))

#define FLASH_ACR (*(volatile uint32_t *)0x40022000)

// TODO Use rcc lib to init clock
void SystemInit(void)
{

    /*
     * HSE ON
     */
    struct rcc_enable_peripheral_config rcc_cr_cfg = {
        .rcc_base = RCC_CR,
        .peripheral = RCC_CR
    };
    RCC_CR |= (1 << 16);

    while (!(RCC_CR & (1 << 17)));

    /*
     * FLASH INIT
     */
    struct flash_init_config flash_cfg = {
        .flash_latency = FLASH_LATENCY_2WS
    };
    flash_init(&flash_cfg);

    /*
     * AHB = SYSCLK
     */
    RCC_CFGR &= ~(0xF << 4);

    /*
     * APB1 = HCLK/2
     */
    RCC_CFGR &= ~(7 << 8);
    RCC_CFGR |= (4 << 8);

    /*
     * PLL source HSE
     */
    RCC_CFGR |= (1 << 16);

    /*
     * PLL x9
     */
    RCC_CFGR &= ~(0xF << 18);
    RCC_CFGR |= (7 << 18);

    /*
     * PLL enable
     */
    RCC_CR |= (1 << 24);

    while (!(RCC_CR & (1 << 25)));

    /*
     * switch SYSCLK PLL
     */
    RCC_CFGR &= ~(3 << 0);
    RCC_CFGR |= (2 << 0);

    while ((RCC_CFGR & (3 << 2)) != (2 << 2));
}