#pragma once
#include <stdint.h>

#define IOREGSEL 0x00
#define IOWIN    0x10

void ioapic_write(uint32_t reg, uint32_t value);
uint32_t ioapic_read(uint32_t reg);
void ioapic_set_redirection(uint8_t irq, uint8_t vector, uint8_t dest_apic_id, uint8_t flags);
uint8_t ioapic_is_enabled();