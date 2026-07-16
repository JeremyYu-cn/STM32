#include "./led.h"
#include <stdint.h>

#define RCC_BASE 0x40021000UL
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))

#define GPIOC_BASE 0x40011000UL
#define GPIOC_ODR (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))
#define GPIOC_13 13

void high_led()
{
  GPIOC_ODR |= GPIOC_13;
}

void low_led()
{
  GPIOC_ODR &= GPIOC_13;
}