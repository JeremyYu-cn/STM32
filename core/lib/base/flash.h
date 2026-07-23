#pragma once

#include <stdint.h>
#include <stdbool.h>

#define FLASH_LATENCY_TYPE uint32_t

#define FLASH_ACR (*(volatile uint32_t *)0x40022000)
#define FLASH_ACR_LATENCY_MASK 0x07U
#define FLASH_ACR_RESET_VALUE 0x00000030U

#define FLASH_BIT_PRFTBS (1 << 5)
#define FLASH_BIT_PRFTBE (1 << 4)
#define FLASH_BIT_HLFCYA (1 << 3)

// SYSCLK <= 24 MHz
#define FLASH_LATENCY_0WS 0x00U
// SYSCLK <= 48 MHz
#define FLASH_LATENCY_1WS 0x01U
// SYSCLK <= 72 MHz
#define FLASH_LATENCY_2WS 0x02U

struct flash_init_config
{
  bool hlfcya;
  bool prftbe;
  FLASH_LATENCY_TYPE flash_latency;
};

// Prefetch buffer status
bool flash_get_prefetch_buffer_status();
void flash_init(const struct flash_init_config *);
void flash_reset();
