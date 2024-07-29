#include "../include/string.h"
#include "../include/pci.h"
#include "../include/cpu.h"
#include "../include/usb_xhci.h"
#include "../include/usb_ehci.h"
#include "../include/interrupts.h"

void pciConfigWriteWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t value) {
    unsigned long address;
 
    /* create configuration address as per Figure 1 */
    address = (unsigned long)((bus << 16) | (slot << 11) |
              (func << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));
 
    /* write out the address */
    outportw(PCI_ADDRESS, address);
    outportw(PCI_DATA,value);
}

void pciConfigWriteDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value){
	unsigned long address;
 
    /* create configuration address as per Figure 1 */
    address = (unsigned long)((bus << 16) | (slot << 11) |
              (func << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));
 
    /* write out the address */
    outportl(PCI_ADDRESS, address);
    outportl(PCI_DATA,value);
}

uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;

    /* create configuration address as per Figure 1 */
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

    /* write out the address */
    outportl(PCI_ADDRESS, address);
    /* read in the data */
    /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
    tmp = (uint16_t)((inportl(PCI_DATA) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
}

uint32_t pciConfigReadDWord(uint8_t bus,uint8_t slot,uint8_t function,uint8_t offset){
	uint32_t result = 0;
	uint32_t partA = pciConfigReadWord(bus,slot,function,offset);
	uint32_t partB = pciConfigReadWord(bus,slot,function,offset+2);
	result = ((partB<<16) | ((partA) & 0xffff));
	return result;
}

uint8_t pciConfigReadByte(uint8_t bus,uint8_t slot,uint8_t function,uint8_t offset){
  return pciConfigReadWord (bus, slot, function, offset) & 0xFF;
}

uint8_t pciConfigReadByteHi(uint8_t bus,uint8_t slot,uint8_t function,uint8_t offset){
  return ( pciConfigReadWord (bus, slot, function, offset) >> 8 ) & 0xFF;
}

void install_interrupt_from_pci(uint8_t bus,uint8_t slot,uint8_t function,void *callable){
  uint8_t interrupt_line = pciConfigReadWord(bus,slot,function,PCI_FIELDS_INTERRUPT) & 0xFF;
  setInterrupt(interrupt_line,callable);
}

void check_pci_entry_for_usb(uint8_t bus,uint8_t slot,uint8_t function){
  uint8_t interface = pciConfigReadByteHi(bus,slot,function,PCI_FIELDS_INTERFACE);
  if(interface==0x00||interface==0x10){
    // printk("USB1.0 found\n");
  }else if(interface==0x20){
    initialise_ehci (bus, slot, function);
  }else if(interface==0x30){
    initialise_xhci (bus, slot, function);
  }else{
    printk("error: unknown USB type\n");
  }
}

void check_pci_entry(uint8_t bus,uint8_t slot,uint8_t function){
  uint16_t vendor = pciConfigReadWord(bus,slot,function,PCI_FIELDS_VENDOR);
  if(vendor==PCI_FIELDS_NO_VENDOR){
    return;
  }
  uint16_t device = pciConfigReadWord(bus,slot,function,PCI_FIELDS_DEVICE);
  if(device==PCI_FIELDS_DEVICE_USB){
    check_pci_entry_for_usb(bus,slot,function);
  }
}

void initialise_pci(){
  for(uint8_t bus = 0 ; bus < PCI_MAX_BUS ; bus++){
    for(uint8_t slot = 0 ; slot < PCI_MAX_SLOT ; slot++){
      for(uint8_t function = 0 ; function < PCI_MAX_FUNCTION ; function++){
        check_pci_entry(bus,slot,function);
      }
    }
  }
}
