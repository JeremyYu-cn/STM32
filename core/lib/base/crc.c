#include "./crc.h"
#include <stdint.h>

void crc_init()
{
  // TODO Turn on crc clock
}

uint32_t crc_calulate(uint32_t *data, int len)
{
  // Reset CRC Claculation
  CRC_CR = CRC_RESET;

  for (int i = 0; i < len; i++)
  {
    CRC_DR = data[i];
  }

  return CRC_DR;
}

void crc_close()
{
  // TODO Turn off crc clock
}
