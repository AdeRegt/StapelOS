#include <stdint.h>

uint8_t msi_is_supported(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t msi_get_control(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t msi_write_message_address(uint8_t bus, uint8_t slot, uint8_t func, uint32_t address, uint8_t vector);
void msi_enable(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t msi_install(uint8_t bus, uint8_t slot, uint8_t func, uint16_t vector);