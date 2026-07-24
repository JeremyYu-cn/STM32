#pragma once

#include <stdint.h>
#include "common.h"

// Basic RCC Address
#define RCC_BASE 0x40021000
#define RCC_CR (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_AHBENR (*(volatile uint32_t *)(RCC_BASE + 0x14))
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x1C))

#define RCC_APB2RST (*(volatile uint32_t *)(RCC_BASE + 0x0C))
#define RCC_APB1RST (*(volatile uint32_t *)(RCC_BASE + 0x10))

// CR Clock control register
#define RCC_CR_HSION (1 << 0)
#define RCC_CR_HSIRDY (1 << 1) // Read Only
#define RCC_CR_HSICAL (255 << 8) // Read Only

// AHB clock enable register
#define RCC_AHBENR_DMA1 (1 << 0)
#define RCC_AHBENR_DMA2 (1 << 1)
#define RCC_AHBENR_SRAM (1 << 2)
#define RCC_AHBENR_FLITF (1 << 4)
#define RCC_AHBENR_CRC (1 << 6)
#define RCC_AHBENR_FSMC (1 << 8)
#define RCC_AHBENR_SDIO (1 << 10)

// APB2 peripheral clock enable register
#define RCC_APB2ENR_AFIO (1 << 0)
#define RCC_APB2ENR_IOPA (1 << 2)
#define RCC_APB2ENR_IOPB (1 << 3)
#define RCC_APB2ENR_IOPC (1 << 4)
#define RCC_APB2ENR_IOPD (1 << 5)
#define RCC_APB2ENR_IOPE (1 << 6)
#define RCC_APB2ENR_IOPF (1 << 7)
#define RCC_APB2ENR_IOPG (1 << 8)
#define RCC_APB2ENR_ADC1 (1 << 9)
#define RCC_APB2ENR_ADC2 (1 << 10)
#define RCC_APB2ENR_TIM1 (1 << 11)
#define RCC_APB2ENR_SPI1 (1 << 12)
#define RCC_APB2ENR_TIM8 (1 << 13)
#define RCC_APB2ENR_USART1 (1 << 14)
#define RCC_APB2ENR_ADC3 (1 << 15)
#define RCC_APB2ENR_TIM9 (1 << 19)
#define RCC_APB2ENR_TIM10 (1 << 20)
#define RCC_APB2ENR_TIM11 (1 << 21)

// APB1 peripheral clock enable register
#define RCC_APB1ENR_TIM2 (1 << 0)
#define RCC_APB1ENR_TIM3 (1 << 1)
#define RCC_APB1ENR_TIM4 (1 << 2)
#define RCC_APB1ENR_TIM5 (1 << 3)
#define RCC_APB1ENR_TIM6 (1 << 4)
#define RCC_APB1ENR_TIM7 (1 << 5)
#define RCC_APB1ENR_TIM12 (1 << 6)
#define RCC_APB1ENR_TIM13 (1 << 7)
#define RCC_APB1ENR_TIM14 (1 << 8)
#define RCC_APB1ENR_WWDG (1 << 11)
#define RCC_APB1ENR_SPI2 (1 << 14)
#define RCC_APB1ENR_SPI3 (1 << 15)
#define RCC_APB1ENR_USART2 (1 << 17)
#define RCC_APB1ENR_USART3 (1 << 18)
#define RCC_APB1ENR_UART4 (1 << 19)
#define RCC_APB1ENR_UART5 (1 << 20)
#define RCC_APB1ENR_I2C1 (1 << 21)
#define RCC_APB1ENR_I2C2 (1 << 22)
#define RCC_APB1ENR_USB (1 << 23)
#define RCC_APB1ENR_CAN (1 << 25)
#define RCC_APB1ENR_BKP (1 << 27)
#define RCC_APB1ENR_PWR (1 << 28)
#define RCC_APB1ENR_DAC (1 << 29)

struct rcc_enable_peripheral_config {
    volatile uint32_t *rcc_base; /* Base address of the RCC register (RCC_APB2ENR or RCC_APB1ENR or RCC_AHBENR) */
    /* Peripheral to enable (RCC_APB2ENR_* or RCC_APB1ENR_* or RCC_AHBENR_*) */
    uint32_t peripheral;
};

// Enables the clock for a specific peripheral on the APB1 or APB2 bus.
void rcc_enable_peripheral(struct rcc_enable_peripheral_config *config);

// Disables the clock for a specific peripheral on the APB1 or APB2 bus.
void rcc_disable_peripheral(struct rcc_enable_peripheral_config *config);

// Resets a specific peripheral on the APB1 or APB2 bus.
void rcc_reset_peripheral(struct rcc_enable_peripheral_config *config);

// Returns the peripheral enable status for a specific peripheral on the APB1 or APB2 bus.
STM_STATUS rcc_is_peripheral_enabled(struct rcc_enable_peripheral_config *config);

