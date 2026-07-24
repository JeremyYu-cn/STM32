#pragma once
#include <stdint.h>

#define GPIO_PIN_TYPE uint32_t
#define GPIO_MODE_TYPE uint32_t
#define GPIO_SPEED_TYPE uint32_t
#define GPIO_BASE_TYPE uint32_t
#define GPIO_PIN_MODE uint32_t
#define GPIO_BIT_MODE uint32_t

// GPIO Base Addresses
#define GPIOA_ADDR 0x40010800
#define GPIOB_ADDR 0x40010C00
#define GPIOC_ADDR 0x40011000
#define GPIOD_ADDR 0x40011400
#define GPIOE_ADDR 0x40011800
#define GPIOF_ADDR 0x40011C00
#define GPIOG_ADDR 0x40012000
#define AFIO_ADDR 0x40010000

// GPIO CFG Register Offsets
#define GPIO_CFG_CRL(gpio_base) (*(volatile uint32_t *)((gpio_base) + 0x00)) // Configuration register base address
#define GPIO_CFG_CRH(gpio_base) (*(volatile uint32_t *)((gpio_base) + 0x04)) // Configuration register base address

// GPIO Bit Register
#define GPIO_BSRR(gpio_base) (*(volatile uint32_t *)((gpio_base) + 0x10)) // Bit set/reset register base address
#define GPIO_BRR(gpio_base) (*(volatile uint32_t *)((gpio_base) + 0x14)) // Bit reset register base address

// GPIO_PIN
#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5
#define GPIO_PIN_6 6
#define GPIO_PIN_7 7
#define GPIO_PIN_8 8
#define GPIO_PIN_9 9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13              
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15

// GPIOA_CFG_POS
#define GPIO_CFG_POS(pin) ((pin & 0x07) * 4)

#define GPIO_MODE_INPUT 0x00
#define GPIO_MODE_OUTPUT_10MHZ 0x01
#define GPIO_MODE_OUTPUT_2MHZ 0x02
#define GPIO_MODE_OUTPUT_50MHZ 0x03

#define GPIO_BIT_HIGH 1
#define GPIO_BIT_LOW 0

struct gpio_config {
    GPIO_BASE_TYPE gpio_base; /* Base address of the GPIO register (GPIOA_BASE, GPIOB_BASE, etc.) */
    GPIO_PIN_TYPE pin;       /* Pin number (0-15) */
    GPIO_MODE_TYPE mode;      /* Mode configuration (00: Input, 01: Output 50MHz, 10: Alternate function, 11: Analog) */
};

void gpio_init(struct gpio_config *config);

void gpio_set_pin(GPIO_BASE_TYPE gpio_base, GPIO_PIN_TYPE pin, GPIO_BIT_MODE mode);
