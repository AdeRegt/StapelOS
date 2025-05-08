#include <stdint.h>


#define GDT_ENTRIES 5

// GDT entry structure
typedef struct {
    uint16_t limit_low;  // Lower 16 bits of the limit
    uint16_t base_low;   // Lower 16 bits of the base
    uint8_t base_middle; // Next 8 bits of the base
    uint8_t access;      // Access flags
    uint8_t granularity; // Granularity and limit flags
    uint8_t base_high;   // Last 8 bits of the base
} __attribute__((packed)) GDTEntry;

// GDTR structure
typedef struct {
    uint16_t limit; // Size of the GDT
    uint64_t base;  // Address of the GDT
} __attribute__((packed)) GDTR;

void initialize_gdt();
extern void gdt_flush();