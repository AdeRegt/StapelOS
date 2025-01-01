#pragma once
#include <stdint.h>

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100 // Processor is a BSP
#define IA32_APIC_BASE_MSR_ENABLE 0x800

#define EXPECTED_APIC_BASE 0xFEE00000

void initialise_apic();
void apic_eoi();
void set_apic_timer_values(uint32_t vals);