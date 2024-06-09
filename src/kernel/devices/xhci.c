#include "../include/xhci.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/pci.h"
#include "../include/cpu.h"
#include "../include/interrupts.h"

void *base_xhci_address;

__attribute__((interrupt)) void interrupt_xhci(interrupt_frame* frame){
  printk("xhciint\n");
  outportb(0xA0,0x20);
	outportb(0x20,0x20);
}

void xhci_dump_caplength(){
  printk("Capability Registers Length (CAPLENGTH) : %x \n",CAPLENGTH);
}

void xhci_dump_hciversion(){
  printk("Host Controller Interface Version Number (HCIVERSION) : %x \n",HCIVERSION);
}

void xhci_dump_hcsparams1(){
  printk("Structural Parameters 1 (HCSPARAMS1) : %x \n",HCSPARAMS1);
  printk("- Number of Device Slots (MaxSlots)  : %x \n",HCSPARAMS1_MaxSlots);
  printk("- Number of Interrupters (MaxIntrs)  : %x \n",HCSPARAMS1_MaxIntrs);
  printk("- Number of Ports (MaxPorts)         : %x \n",HCSPARAMS1_MaxPorts);
}

void xhci_dump_hcsparams2(){
  printk("Structural Parameters 2 (HCSPARAMS2)             : %x \n",HCSPARAMS2);
  printk("- Isochronous Scheduling Threshold (IST)         : %x \n",HCSPARAMS2_IST);
  printk("- Event Ring Segment Table Max (ERST Max)        : %x \n",HCSPARAMS2_ERST_Max);
  printk("- Max Scratchpad Buffers (Max Scratchpad Bufs Hi): %x \n",HCSPARAMS2_Scratchpad_Bufs_Hi);
  printk("- Scratchpad Restore (SPR)                       : %x \n",HCSPARAMS2_SPR);
  printk("- Max Scratchpad Buffers (Max Scratchpad Bufs Lo): %x \n",HCSPARAMS2_Scratchpad_Bufs_Lo);
}

void xhci_dump_hcsparams3(){
  printk("Structural Parameters 3 (HCSPARAMS3) : %x \n",HCSPARAMS3);
  printk("- U1 Device Exit Latency             : %x \n",HCSPARAMS3_U1);
  printk("- U2 Device Exit Latency             : %x \n",HCSPARAMS3_U2);
}

void xhci_dump_hccparams1(){
  printk("Capability Parameters 1 (HCCPARAMS1)             : %x \n",HCCPARAMS1);
  printk("- 64-bit Addressing Capability (AC64)            : %s\n",(HCCPARAMS1_AC64)?"yes":"no");
  printk("- BW Negotiation Capability (BNC)                : %s\n",(HCCPARAMS1_BNC)?"yes":"no");
  printk("- Context Size (CSZ)                             : %s\n",(HCCPARAMS1_CSZ)?"yes":"no");
  printk("- Port Power Control (PPC)                       : %s\n",(HCCPARAMS1_PPC)?"yes":"no");
  printk("- Port Indicators (PIND)                         : %s\n",(HCCPARAMS1_PIND)?"yes":"no");
  printk("- Light HC Reset Capability (LHRC)               : %s\n",(HCCPARAMS1_LHRC)?"yes":"no");
  printk("- Latency Tolerance Messaging Capability (LTC)   : %s\n",(HCCPARAMS1_LTC)?"yes":"no");
  printk("- No Secondary SID Support (NSS)                 : %s\n",(HCCPARAMS1_NSS)?"yes":"no");
  printk("- Parse All Event Data (PAE)                     : %s\n",(HCCPARAMS1_PAE)?"yes":"no");
  printk("- Stopped - Short Packet Capability (SPC)        : %s\n",(HCCPARAMS1_SPC)?"yes":"no");
  printk("- Stopped EDTLA Capability (SEC)                 : %s\n",(HCCPARAMS1_SEC)?"yes":"no");
  printk("- Contiguous Frame ID Capability (CFC)           : %s\n",(HCCPARAMS1_CFC)?"yes":"no");
  printk("- Maximum Primary Stream Array Size (MaxPSASize) : %x\n",HCCPARAMS1_MaxPSASize);
  printk("- xHCI Extended Capabilities Pointer (xECP)      : %x\n",HCCPARAMS1_xECP);
}

void xhci_dump_dboff(){
  printk("Doorbell Offset (DBOFF) : %x \n",DBOFF);
}

void xhci_dump_rtsoff(){
  printk("Runtime Register Space Offset (RTSOFF) : %x \n",RTSOFF);
}

void xhci_dump_capability_registers(){
  // see page 381 of specification
  printk("---XHCI Capability Registers---\n");
  xhci_dump_caplength();
  xhci_dump_hciversion();
  xhci_dump_hcsparams1();
  xhci_dump_hcsparams2();
  xhci_dump_hcsparams3();
  xhci_dump_hccparams1();
  xhci_dump_dboff();
  xhci_dump_rtsoff();
  // printk("Capability Parameters 2 (HCCPARAMS2) : %x \n",HCCPARAMS2);
  // printk("Virtualization Based Trusted IO Register Space Offset (VTIOSOFF) : %x \n",VTIOSOFF);
}

void initialise_xhci(uint8_t bus, uint8_t slot, uint8_t func){
  // get interrupt
  install_interrupt_from_pci(bus,slot,func,interrupt_xhci);
  // get the base address of xhci
  base_xhci_address = 0;
  base_xhci_address += pciConfigReadDWord (bus, slot, func, 0x10) & 0xFFFFFFF0;
  // dump host controller information
  xhci_dump_capability_registers();
}
