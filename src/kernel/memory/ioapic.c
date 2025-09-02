#include "../include/ioapic.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/paging.h"
#include "../include/acpi.h"

uint8_t ioapic_is_enabled() {
    // Check if the IOAPIC base address is set
    return get_ioapic_base() != 0;
}

void ioapic_write(uint32_t reg, uint32_t value) {
    *(volatile uint32_t*)(get_ioapic_base() + IOREGSEL) = reg;
    *(volatile uint32_t*)(get_ioapic_base() + IOWIN) = value;
}

uint32_t ioapic_read(uint32_t reg) {
    *(volatile uint32_t*)(get_ioapic_base() + IOREGSEL) = reg;
    return *(volatile uint32_t*)(get_ioapic_base() + IOWIN);
}

// Set up a redirection entry for a given IRQ
void ioapic_set_redirection(uint8_t irq, uint8_t vector, uint8_t dest_apic_id, uint8_t flags) {
    // flags: bitmask for delivery mode, polarity, trigger, mask, etc.
    uint32_t low = vector | flags; // vector and flags
    uint32_t high = dest_apic_id << 24; // destination APIC ID
    
    // Write low dword
    ioapic_write(0x10 + irq * 2, low);
    // Write high dword
    ioapic_write(0x10 + irq * 2 + 1, high);
}

void ioapic_dump_redirection_table(int max_irq) {
    for (int irq = 0; irq < max_irq; irq++) {
        uint32_t low = ioapic_read(0x10 + irq * 2);
        uint32_t high = ioapic_read(0x10 + irq * 2 + 1);
        printk("IRQ %d: LOW=%x HIGH=%x\n", irq, low, high);
    }
}