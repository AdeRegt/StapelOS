#include <stdint.h>
#include "../include/interrupts.h"
#include "../include/cpu.h"
#include "../include/string.h"
#include "../include/pic.h"
#include "../include/apic.h"

static IDTR idtr;
__attribute__ ((aligned(0x10))) static IDTDescEntry idt[256];

void interrupt_eoi(){
  if(check_apic()){
    apic_eoi();
  }else{
    pic_eoi();
  }
}

__attribute__((interrupt)) void MasterInteruptHandler00(interrupt_frame* frame){
  printk("Interrupt 00 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler01(interrupt_frame* frame){
  printk("Interrupt 01 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler02(interrupt_frame* frame){
  printk("Interrupt 02 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler03(interrupt_frame* frame){
  printk("Interrupt 03 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler04(interrupt_frame* frame){
  printk("Interrupt 04 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler05(interrupt_frame* frame){
  printk("Interrupt 05 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler06(interrupt_frame* frame){
  printk("Interrupt 06 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler07(interrupt_frame* frame){
  printk("Interrupt 07 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler08(interrupt_frame* frame){
  printk("Interrupt 08 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler09(interrupt_frame* frame){
  printk("Interrupt 09 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0a(interrupt_frame* frame){
  printk("Interrupt 0a fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0b(interrupt_frame* frame){
  printk("Interrupt 0b fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0c(interrupt_frame* frame){
  printk("Interrupt 0c fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0d(interrupt_frame* frame){
  printk("Interrupt 0d fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0e(interrupt_frame* frame){
  printk("Interrupt 0e fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0f(interrupt_frame* frame){
  printk("Interrupt 0f fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler10(interrupt_frame* frame){
  printk("Interrupt 10 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler11(interrupt_frame* frame){
  printk("Interrupt 11 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler12(interrupt_frame* frame){
  printk("Interrupt 12 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler13(interrupt_frame* frame){
  printk("Interrupt 13 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler14(interrupt_frame* frame){
  printk("Interrupt 14 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler15(interrupt_frame* frame){
  printk("Interrupt 15 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler16(interrupt_frame* frame){
  printk("Interrupt 16 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler17(interrupt_frame* frame){
  printk("Interrupt 17 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler18(interrupt_frame* frame){
  printk("Interrupt 18 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler19(interrupt_frame* frame){
  printk("Interrupt 19 fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler1a(interrupt_frame* frame){
  printk("Interrupt 1a fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler1b(interrupt_frame* frame){
  printk("Interrupt 1b fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler1c(interrupt_frame* frame){
  printk("Interrupt 1c fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler1d(interrupt_frame* frame){
  printk("Interrupt 1d fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler1e(interrupt_frame* frame){
  printk("Interrupt 1e fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler1f(interrupt_frame* frame){
  printk("Interrupt 1f fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void GeneralFault_Handler(interrupt_frame* frame){
  printk("\nInterrupt: error cs:%x flags:%x ip:%x sp:%x ss:%x\n",frame->cs,frame->flags,frame->ip,frame->sp,frame->ss);
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void NakedInterruptHandler(interrupt_frame* frame){
	interrupt_eoi();
}

void interrupt_set_offset(IDTDescEntry* int_PageFault,uint64_t offset){
  int_PageFault->offset0 = (uint16_t)(offset & 0x000000000000ffff);
  int_PageFault->offset1 = (uint16_t)((offset & 0x00000000ffff0000) >> 16);
  int_PageFault->offset2 = (uint32_t)((offset & 0xffffffff00000000) >> 32);
}

void setRawInterrupt(int offset,void *fun){
  IDTDescEntry* int_PageFault = (IDTDescEntry*)(idtr.Offset + ((offset) * sizeof(IDTDescEntry)));
  interrupt_set_offset(int_PageFault,(uint64_t)fun);
  int_PageFault->type_attr = IDT_TA_TrapGate;
  int_PageFault->selector = GDT_CODE_SEGMENT;
}

void setInterrupt(int offset,void *fun){
  setRawInterrupt(INT_OFFSET+offset+(check_apic()?1:0),fun);
}

void interrupts_disable(){
  asm volatile ("cli");
}

void interrupts_enable(){
  asm volatile ("sti");
}

void initialise_interrupts(){

  //
  // if we have APIC, use APIC, otherwise use PIC
  if(check_apic()){
	  disable_pic();
	  initialise_apic();
  }else{
	  initialise_pic();
  }

  idtr.Offset = (uintptr_t)&idt[0];
  idtr.Limit = (uint16_t)sizeof(IDTDescEntry) * IDT_MAX_DESCRIPTORS - 1;

  IDTDescEntry *idtentries = (IDTDescEntry*) idtr.Offset;
  setRawInterrupt(0x00,MasterInteruptHandler00);
  setRawInterrupt(0x01,MasterInteruptHandler01);
  setRawInterrupt(0x02,MasterInteruptHandler02);
  setRawInterrupt(0x03,MasterInteruptHandler03);
  setRawInterrupt(0x04,MasterInteruptHandler04);
  setRawInterrupt(0x05,MasterInteruptHandler05);
  setRawInterrupt(0x06,MasterInteruptHandler06);
  setRawInterrupt(0x07,MasterInteruptHandler07);
  setRawInterrupt(0x08,MasterInteruptHandler08);
  setRawInterrupt(0x09,MasterInteruptHandler09);
  setRawInterrupt(0x0A,MasterInteruptHandler0a);
  setRawInterrupt(0x0B,MasterInteruptHandler0b);
  setRawInterrupt(0x0C,MasterInteruptHandler0c);
  setRawInterrupt(0x0D,MasterInteruptHandler0d);
  setRawInterrupt(0x0E,MasterInteruptHandler0e);
  setRawInterrupt(0x0F,MasterInteruptHandler0f);
  setRawInterrupt(0x10,MasterInteruptHandler10);
  setRawInterrupt(0x11,MasterInteruptHandler11);
  setRawInterrupt(0x12,MasterInteruptHandler12);
  setRawInterrupt(0x13,MasterInteruptHandler13);
  setRawInterrupt(0x14,MasterInteruptHandler14);
  setRawInterrupt(0x15,MasterInteruptHandler15);
  setRawInterrupt(0x16,MasterInteruptHandler16);
  setRawInterrupt(0x17,MasterInteruptHandler17);
  setRawInterrupt(0x18,MasterInteruptHandler18);
  setRawInterrupt(0x19,MasterInteruptHandler19);
  setRawInterrupt(0x1A,MasterInteruptHandler1a);
  setRawInterrupt(0x1B,MasterInteruptHandler1b);
  setRawInterrupt(0x1C,MasterInteruptHandler1c);
  setRawInterrupt(0x1D,MasterInteruptHandler1d);
  setRawInterrupt(0x1E,MasterInteruptHandler1e);
  setRawInterrupt(0x1F,MasterInteruptHandler1f);
  for(int z = 0x20 ; z < 0xFF ; z++){
    setRawInterrupt(z,MasterInteruptHandler1f);
  }
  asm volatile ("lidt %0" : : "m"(idtr));
  interrupts_enable();
}

