#include "../include/acpi.h"
#include "../include/string.h"
#include "../include/paging.h"
#include "../include/memory.h"

void *rsdp;
void *ioapic_base;

void *get_ioapic_base(){
    return ioapic_base;
}

void* acpi_scan_for_rsdp(){
    // Scan the BIOS memory area for the RSDP signature
    for(uintptr_t addr = BIOS_MEMORY_AREA_START; addr < BIOS_MEMORY_AREA_END; addr += 16){
        if(*(uint64_t*)addr == ROOT_SYSTEM_DESCRIPTION_POINTER_SIGNATURE){
            return (void*)addr;
        }
    }
    return 0; // RSDP not found
}

void acpi_dump_rsdp(RSDPDescriptor* rsdp){
    printk("====================[ RSDP Descriptor ]====================\n");
    printk("RSDP Address: %x\n", rsdp);
    printk("RSDP Signature: %c%c%c%c%c%c%c%c\n", rsdp->Signature[0], rsdp->Signature[1], rsdp->Signature[2], rsdp->Signature[3], rsdp->Signature[4], rsdp->Signature[5], rsdp->Signature[6], rsdp->Signature[7]);
    printk("Checksum: %x\n", rsdp->Checksum);
    printk("OEM ID: %x %x %x %x %x %x\n", rsdp->OEMID[0], rsdp->OEMID[1], rsdp->OEMID[2], rsdp->OEMID[3], rsdp->OEMID[4], rsdp->OEMID[5]);
    printk("Revision: %x\n", rsdp->Revision);
    printk("RSDT Address: %x\n", rsdp->RsdtAddress);
    printk("Extended Checksum: %x\n", rsdp->ExtendedChecksum);
    printk("XSDT Address: %x\n", rsdp->XsdtAddress);
    printk("Length: %d\n", rsdp->Length);
    printk("===========================================================\n");
}

void acpi_dump_xsdt(ACPISDTHeader* xsdt){
    printk("====================[ XSDT Header ]====================\n");
    printk("XSDT Address: %x\n", xsdt);
    printk("Signature: %c%c%c%c\n", xsdt->Signature[0], xsdt->Signature[1], xsdt->Signature[2], xsdt->Signature[3]);
    printk("Length: %d\n", xsdt->Length);
    printk("Revision: %d\n", xsdt->Revision);
    printk("Checksum: %x\n", xsdt->Checksum);
    printk("OEM ID: %x %x %x %x %x %x\n", xsdt->OEMID[0], xsdt->OEMID[1], xsdt->OEMID[2], xsdt->OEMID[3], xsdt->OEMID[4], xsdt->OEMID[5]);
    printk("OEM Table ID: %c%c%c%c%c%c%c%c\n", xsdt->OEMTableID[0], xsdt->OEMTableID[1], xsdt->OEMTableID[2], xsdt->OEMTableID[3], xsdt->OEMTableID[4], xsdt->OEMTableID[5], xsdt->OEMTableID[6], xsdt->OEMTableID[7]);
    printk("OEM Revision: %d\n", xsdt->OEMRevision);
    printk("Creator ID: %d\n", xsdt->CreatorID);
    printk("Creator Revision: %d\n", xsdt->CreatorRevision);
    printk("===========================================================\n");
}

ACPISDTHeader* parse_apic_table(ACPISDTHeader* xsdt, uint8_t* signature) {
    int entries = (xsdt->Length - sizeof(ACPISDTHeader)) / 8;
    uint64_t* table_ptrs = (uint64_t*)((uint8_t*)xsdt + sizeof(ACPISDTHeader));

    for (int i = 0; i < entries; i++) {
        ACPISDTHeader* hdr = (ACPISDTHeader*)(uintptr_t)table_ptrs[i];
        // Map the header page if needed
        if (hdr->Signature[0] == signature[0] && hdr->Signature[1] == signature[1] &&
            hdr->Signature[2] == signature[2] && hdr->Signature[3] == signature[3]) {
            // Found MADT
            return hdr;
        }
    }

    return (ACPISDTHeader*) 0;
}

void initialise_acpi(){
    rsdp = acpi_scan_for_rsdp();
    if(!rsdp){
        printk("ACPI RSDP not found!\n");
        return;
    }
    RSDPDescriptor* rsdpo = (RSDPDescriptor*)rsdp;
    if(rsdpo->Revision < 2){
        printk("ACPI version is too low: %d\n", rsdpo->Revision);
        return;
    }
    
    ACPISDTHeader* xsdt = (ACPISDTHeader*)(uintptr_t) rsdpo->XsdtAddress;

    define_linear_memory_block((void*)rsdpo->XsdtAddress);

    ACPISDTHeader *hdr = parse_apic_table(xsdt, "APIC");
    if(!hdr) {
        printk("ACPI MADT not found!\n");
        return;
    }
    
    uint8_t* madt_ptr = (uint8_t*)hdr + sizeof(ACPISDTHeader) + 8; // +8 for MADT header
    uint32_t madt_length = hdr->Length;
    int maxtries = 100;
    while (maxtries-- && madt_ptr < ((uint8_t*)hdr + madt_length)) {
        MADTEntry* entry = (MADTEntry*)madt_ptr;
        if (entry->Type == 1) { // IOAPIC
            ioapic_base = (void*)(uint64_t)*(uint32_t*)(madt_ptr + 4);
            define_linear_memory_block(ioapic_base);
            return;
        }
        madt_ptr += entry->Length;
    }
    printk("ACPI IOAPIC not found in MADT!\n");
    ioapic_base = 0; // Set to 0 if not found
    return;
}