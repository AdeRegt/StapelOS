#include <stdint.h>
#include "../include/msi.h"
#include "../include/cpu.h"
#include "../include/string.h"
#include "../include/interrupts.h"
#include "../include/apic.h"
#include "../include/pci.h"

uint8_t msi_is_supported(uint8_t bus, uint8_t slot, uint8_t func){
    if(!pci_has_capabilities(bus,slot,func)){
        return 0;
    }
    uint8_t cap_pointer = pci_get_capability_pointer(bus,slot,func);
    while(cap_pointer){
        uint8_t cap_id = pciConfigReadByte(bus,slot,func,cap_pointer);
        if(cap_id==0x05){
            return cap_pointer;
        }
        cap_pointer = pciConfigReadByte(bus,slot,func,cap_pointer+1);
    }
    return 0;
}

uint16_t msi_get_control(uint8_t bus, uint8_t slot, uint8_t func){
    uint8_t cap_pointer = msi_is_supported(bus,slot,func);
    if(!cap_pointer){
        return 0;
    }
    return pciConfigReadWord(bus,slot,func,cap_pointer+2);
}

uint8_t msi_write_message_address(uint8_t bus, uint8_t slot, uint8_t func, uint32_t address, uint8_t vector){
    uint8_t cap_pointer = msi_is_supported(bus,slot,func);
    if(!cap_pointer){
        return 0;
    }
    uint16_t control = pciConfigReadWord(bus,slot,func,cap_pointer+2);
    if(control & (1<<7)){
        // 64 bit
        pciConfigWriteDWord(bus,slot,func,cap_pointer+4,address);
        pciConfigWriteDWord(bus,slot,func,cap_pointer+12,vector);
        return 1;
    }else{
        // 32 bit
        pciConfigWriteDWord(bus,slot,func,cap_pointer+4,address);
        pciConfigWriteDWord(bus,slot,func,cap_pointer+8,vector);
        return 1;
    }
    return 0;
}

void msi_enable(uint8_t bus, uint8_t slot, uint8_t func){
    uint8_t cap_pointer = msi_is_supported(bus,slot,func);
    if(!cap_pointer){
        return;
    }
    uint16_t control = pciConfigReadWord(bus,slot,func,cap_pointer+2);
    control |= 1; // enable
    pciConfigWriteWord(bus,slot,func,cap_pointer+2,control);
}

uint8_t msi_install(uint8_t bus, uint8_t slot, uint8_t func, uint16_t vector){
    uint8_t capa = msi_is_supported(bus, slot, func);
    if(capa){
        msi_write_message_address(bus, slot, func, 0xFEE00000 | (0<<12), vector);
        msi_enable(bus, slot, func);
        return 1;
    }
    return 0;
}