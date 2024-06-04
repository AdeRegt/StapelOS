#include <stdint.h>
#include "../include/interrupts.h"
#include "../include/cpu.h"
#include "../include/string.h"

static IDTR idtr;
__attribute__ ((aligned(0x10))) static IDTDescEntry idt[256];

void interrupt_eoi(){
  outportb(0xA0,0x20);
	outportb(0x20,0x20);
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

void IRQ_set_mask(unsigned char IRQline) {
  uint16_t port;
  uint8_t value;

  if(IRQline < 8) {
      port = PIC1_DATA;
  } else {
      port = PIC2_DATA;
      IRQline -= 8;
  }
  value = inportb(port) | (1 << IRQline);
  outportb(port, value);
}

void IRQ_clear_mask(unsigned char IRQline) {
  uint16_t port;
  uint8_t value;

  if(IRQline < 8) {
      port = PIC1_DATA;
  } else {
      port = PIC2_DATA;
      IRQline -= 8;
  }
  value = inportb(port) & ~(1 << IRQline);
  outportb(port, value);
}

void initialise_interrupts(){
  uint8_t oldpic1 = inportb(PIC1_DATA);
  uint8_t oldpic2 = inportb(PIC2_DATA);
  outportb(PIC1, 0x11);
  outportb(PIC2, 0x11);
  outportb(PIC1_DATA, PIC_OFFSET);
  outportb(PIC2_DATA, PIC_OFFSET + 8);
  outportb(PIC1_DATA, ICW1_INTERVAL4);
  outportb(PIC2_DATA, ICW1_SINGLE);
  outportb(PIC1_DATA, ICW1_ICW4);
  outportb(PIC2_DATA, ICW1_ICW4);
  outportb(PIC1_DATA, 0x0);
  outportb(PIC2_DATA, 0x0);
  outportb(PIC1_DATA,oldpic1);
  outportb(PIC2_DATA,oldpic2);

   idtr.Offset = (uintptr_t)&idt[0];
    idtr.Limit = (uint16_t)sizeof(IDTDescEntry) * IDT_MAX_DESCRIPTORS - 1;

    IDTDescEntry *idtentries = (IDTDescEntry*) idtr.Offset;
    for(uint16_t i = 0 ; i < idtr.Limit ; i++){
        setRawInterrupt(i,NakedInterruptHandler);
    }
    for(uint16_t i = 0 ; i < PIC_OFFSET ; i++){
        setRawInterrupt(i,GeneralFault_Handler);
    }
    asm volatile ("lidt %0" : : "m"(idtr));
    asm volatile ("sti");
}
