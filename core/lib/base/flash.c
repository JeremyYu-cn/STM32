#include "flash.h"

bool flash_get_prefetch_buffer_status()
{
  return (FLASH_ACR & FLASH_BIT_PRFTBS) != 0;
};

void flash_init(const struct flash_init_config *cfg)
{
  flash_reset();

  if (cfg->hlfcya)
  {
    FLASH_ACR |= FLASH_BIT_HLFCYA;
  }

  if (cfg->prftbe)
  {
    FLASH_ACR |= FLASH_BIT_PRFTBE;
  }

  FLASH_ACR |= cfg->flash_latency;
};

void flash_reset()
{
  FLASH_ACR = FLASH_ACR_RESET_VALUE;
};
