#pragma once
#include <stdint.h>

#define BIOS_MEMORY_AREA_START 0x000E0000
#define BIOS_MEMORY_AREA_END 0x000FFFFF
#define ROOT_SYSTEM_DESCRIPTION_POINTER_SIGNATURE 0x2052545020445352 // "RSD PTR "

typedef struct {
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision; 
    uint32_t RsdtAddress;
    // ... (ACPI 2.0+ fields follow)
    uint32_t Length;
    uint64_t XsdtAddress; // 64-bit address for XSDT
    uint8_t ExtendedChecksum;
    uint8_t Reserved[3];
} __attribute__((packed)) RSDPDescriptor;

typedef struct {
    char Signature[4];
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
    // Followed by array of 64-bit pointers
} __attribute__((packed)) ACPISDTHeader;

typedef struct {
    uint8_t Type;
    uint8_t Length;
    // ...fields depending on type
} __attribute__((packed)) MADTEntry;

typedef struct {
    MADTEntry Header;
    uint8_t IOAPICId;
    uint8_t Reserved;
    uint32_t IOAPICAddress; // 32-bit address of the IOAPIC
    uint32_t GlobalSystemInterruptBase; // Base for global system interrupts
} __attribute__((packed)) MADTEntryType1;

void initialise_acpi(void* rsdp_address_from_bootloader_arg);
void *get_ioapic_base();