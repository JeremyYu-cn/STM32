#include <stdint.h>

#define CRC_BASE 0x40023000UL
#define CRC_DR (*(volatile uint32_t *)(CRC_BASE + 0x08UL))
#define CRC_IDR (*(volatile uint32_t *)(CRC_BASE + 0x04UL))
#define CRC_CR (*(volatile uint32_t *)(CRC_BASE + 0x08UL))
#define CRC_RESET 1UL << 0

void crc_init();
uint32_t crc_calulate(uint32_t *data, int len);
void crc_close();
