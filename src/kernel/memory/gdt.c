#include <stdint.h>
#include "../include/gdt.h"
#include "../include/memory.h"

// GDT and GDTR
static GDTEntry gdt[GDT_ENTRIES];
static GDTR gdtr;

// Function to set a GDT entry
void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].granularity = (limit >> 16) & 0x0F;

    gdt[index].granularity |= granularity & 0xF0;
    gdt[index].access = access;
}

void set_tss_descriptor(int index, uint64_t base, uint32_t limit) {
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].granularity = (limit >> 16) & 0x0F;

    gdt[index].granularity |= 0x80;  // Set the "Present" bit
    gdt[index].access = 0x89;       // TSS descriptor type
}

TSS tss;

void x64_load_ltr(int tr)
{
    asm volatile ( \
        " movw %w0, %%ax; \
          ltrw %%ax;     "\
        :: "a"(tr) );
}

// Function to initialize the GDT
void initialize_gdt() {
    memset(gdt,0,(sizeof(GDTEntry) * GDT_ENTRIES) - 1);

    // Null descriptor
    set_gdt_entry(0, 0, 0, 0, 0);

    // Code segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xA0);

    // Data segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xA0);

    // User mode code segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xA0);

    // User mode data segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xA0);

    // tss gdt entry
    set_tss_descriptor(5,0,0);

    memset ( (void*) &tss, 0, sizeof(TSS) );

    uint8_t kernel_stack[4096];
    tss.rsp0 = (uint64_t)&kernel_stack[4095];

    // Load the GDTR
    gdtr.limit = (sizeof(GDTEntry) * GDT_ENTRIES) - 1;
    gdtr.base = (uint64_t)&gdt;

    asm volatile("lgdt %0" : : "m"(gdtr));

    gdt_flush();
    x64_load_ltr(GDT_TSS);
}