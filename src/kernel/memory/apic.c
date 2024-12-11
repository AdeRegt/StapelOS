#include "../include/apic.h"
#include "../include/cpu.h"
#include "../include/string.h"

void *get_apic_base(){
    uint32_t eax, edx;
    cpu_get_specific_registers(IA32_APIC_BASE_MSR, &eax, &edx);
    return (void*) ((uint64_t)((eax & 0xfffff000) | (((uint64_t)edx & 0x0f) << 32)));
}

// void cpu_set_apic_base(uintptr_t apic) {
//    uint32_t edx = 0;
//    uint32_t eax = (apic & 0xfffff0000) | IA32_APIC_BASE_MSR_ENABLE;
//    edx = (apic >> 32) & 0x0f;
//    cpu_set_specific_registers(IA32_APIC_BASE_MSR, eax, edx);
// }

void initialise_apic(){
    void* apicbase = get_apic_base();
    printk("APIC: base of APIC: %lx \n",apicbase);
    // cpu_set_apic_base(apicbase);
}