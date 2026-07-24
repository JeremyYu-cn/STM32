#include "gpio.h"
#include <stdint.h>

void gpio_init(struct gpio_config *config) {
    // Set the mode for the specified pin
    volatile uint32_t *gpio_cfg_addr;

    if(config->pin < 8)
    {
        gpio_cfg_addr = &GPIO_CFG_CRL(config->gpio_base);
    }
    else
    {
        gpio_cfg_addr = &GPIO_CFG_CRH(config->gpio_base);
    }


    // Reset register and bit reset for the specified pin
    GPIO_BRR(config->gpio_base) = (1 << config->pin);
    GPIO_BSRR(config->gpio_base) = (1 << (config->pin + 16));

    // Set configuration for the specified pin
    uint32_t shift = GPIO_CFG_POS(config->pin); // Each pin has 4 bits in the configuration register

    // Clear the existing mode bits for the pin
    *gpio_cfg_addr &= ~(0xF << shift);
    
    // Set the new mode bits for the pin
    *gpio_cfg_addr |= (config->mode << shift);

    // Set the pin low
    GPIO_BSRR(config->gpio_base) = (1 << (config->pin +16));
}

void gpio_set_pin(GPIO_BASE_TYPE gpio_base, GPIO_PIN_TYPE pin, GPIO_BIT_MODE mode) {
    if(mode == GPIO_BIT_HIGH)
    {
        GPIO_BSRR(gpio_base) = (1 << pin);
    }
    else
    {
        GPIO_BSRR(gpio_base) = (1 << (pin + 16));
    }
}
