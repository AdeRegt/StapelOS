#pragma once
#include <stdint.h>

#define PCI_MAX_BUS 255
#define PCI_MAX_SLOT 32
#define PCI_MAX_FUNCTION 8

#define PCI_ADDRESS 0xCF8
#define PCI_DATA 0xCFC

#define PCI_FIELDS_VENDOR 0
#define PCI_FIELDS_NO_VENDOR 0xFFFF
#define PCI_FIELDS_DEVICE 0xA
#define PCI_FIELDS_DEVICE_USB 0x0C03
#define PCI_FIELDS_INTERFACE 0x8
#define PCI_FIELDS_INTERRUPT 0x3C

void initialise_pci();
uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint32_t pciConfigReadDWord(uint8_t bus,uint8_t slot,uint8_t function,uint8_t offset);
uint8_t pciConfigReadByte(uint8_t bus,uint8_t slot,uint8_t function,uint8_t offset);
uint8_t pciConfigReadByteHi(uint8_t bus,uint8_t slot,uint8_t function,uint8_t offset);
void install_interrupt_from_pci(uint8_t bus,uint8_t slot,uint8_t function,void *callable);
void pciConfigWriteWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t value);
void pciConfigWriteDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value);