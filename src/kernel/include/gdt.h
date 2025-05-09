#include <stdint.h>


#define GDT_ENTRIES 32

#define GDT_NULL 0x00
#define GDT_KERNEL_CODE_SEGMENT 0x08
#define GDT_KERNEL_DATA_SEGMENT 0x10
#define GDT_USER_CODE_SEGMENT 0x18
#define GDT_USER_DATA_SEGMENT 0x20
#define GDT_TSS 0x28

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

typedef struct {

    unsigned int reserved;
    
    unsigned long rsp0; 
    unsigned long rsp1; 
    unsigned long rsp2;

    unsigned int reserved2[2];

    unsigned long ist1; 
    unsigned long ist2; 
    unsigned long ist3; 
    unsigned long ist4; 
    unsigned long ist5; 
    unsigned long ist6; 
    unsigned long ist7;

    unsigned int reserved3[2];

    unsigned short reserved4;
    unsigned short IOPB_offset;

} __attribute__((packed)) TSS;

void initialize_gdt();
extern void gdt_flush();