#include "rcc.h"
#include <stdint.h>

void rcc_enable_peripheral(struct rcc_enable_peripheral_config *config) {
    *(config->rcc_base) |= config->peripheral;
}

void rcc_reset_peripheral(struct rcc_enable_peripheral_config *config) {
    *(config->rcc_base) |= config->peripheral;
    *(config->rcc_base) &= ~config->peripheral;
}

void rcc_disable_peripheral(struct rcc_enable_peripheral_config *config) {
    *(config->rcc_base) &= ~config->peripheral;
}

STM_STATUS rcc_is_peripheral_enabled(struct rcc_enable_peripheral_config *config) {
        return (*(config->rcc_base) & config->peripheral)
        ? STM_STATUS_OK
        : STM_STATUS_FAIL;
}
