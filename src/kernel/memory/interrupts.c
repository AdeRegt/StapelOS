#include <stdint.h>
#include "../include/interrupts.h"
#include "../include/cpu.h"
#include "../include/string.h"
#include "../include/pic.h"
#include "../include/apic.h"
#include "../include/timer.h"
#include "../include/gdt.h"
#include "../include/reflection.h"

static IDTR idtr;
__attribute__ ((aligned(0x10))) static IDTDescEntry idt[256];

void interrupt_eoi(){
  if(check_apic()){
    apic_eoi();
  }else{
    pic_eoi();
  }
}

uint8_t interrupt_get_int_number(){
  if(check_apic()){
    return apic_get_interrupt_number();
  }else{
    return pic_get_interrupt_number();
  }
}

void print_callstack(interrupt_frame* frame, int max_depth) {
    uintptr_t* rbp;
    uintptr_t rip;
    int depth = 0;

    // On interrupt, rbp is not always saved in the frame, but sp points to the stack at interrupt time.
    // If you save rbp in your interrupt_frame, use that. Otherwise, try to read from stack.
    rbp = (uintptr_t*)__builtin_frame_address(0);

    printk("Call stack:\n");
    while (rbp && depth < max_depth) {
        rip = *(rbp + 1); // Return address is right above rbp
        printk("  [%d] %s\n", depth, getSymbolnameForAddress(rip));
        rbp = (uintptr_t*)(*rbp); // Next rbp
        depth++;
    }
}

static void showInterruptRegis(interrupt_frame* frame,unsigned long int error){
  printk("cs: %x , flags:%x , ip:%x , sp:%x , ss:%x , error:%x \n",frame->cs,frame->flags,frame->ip,frame->sp,frame->ss,error);
  printk("currently we are in ring %x but the process was in ring %x \n",cpu_get_current_ring(),cpu_get_ring_from_cs(frame->cs));
  printk("IP contains code from %s \n",getSymbolnameForAddress(frame->ip));
  print_callstack(frame,10);
}

__attribute__((interrupt)) void MasterInteruptHandler00(interrupt_frame* frame){
  printk("Interrupt 00 Division Error fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler01(interrupt_frame* frame){
  printk("Interrupt 01 Debug fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler02(interrupt_frame* frame){
  printk("Interrupt 02 Non-maskable Interrupt fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler03(interrupt_frame* frame){
  printk("Interrupt 03 Breakpoint fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler04(interrupt_frame* frame){
  printk("Interrupt 04 Overflow fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler05(interrupt_frame* frame){
  printk("Interrupt 05 Bound Range Exceeded fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler06(interrupt_frame* frame){
  printk("Interrupt 06 Invalid Opcode fired!\n");
  showInterruptRegis(frame,0);
  asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler07(interrupt_frame* frame){
  printk("Interrupt 07 Device Not Available fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler08(interrupt_frame* frame){
  printk("Interrupt 08 Double Fault fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler09(interrupt_frame* frame){
  printk("Interrupt 09 Coprocessor Segment Overrun fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0a(interrupt_frame* frame){
  printk("Interrupt 0a Invalid TSS fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0b(interrupt_frame* frame){
  printk("Interrupt 0b Segment Not Present fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0c(interrupt_frame* frame){
  printk("Interrupt 0c Stack-Segment Fault fired!\n");
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0d(interrupt_frame* frame,unsigned long int error){
  printk("Interrupt 0d General Protection Fault fired!\n");
  showInterruptRegis(frame,error);
	asm volatile("cli\nhlt");
}

__attribute__((interrupt)) void MasterInteruptHandler0e(interrupt_frame* frame,unsigned long int error){
  printk("Interrupt 0e Page Fault fired!\n");
  showInterruptRegis(frame,error);
  if(error & 0b00000000000000000000000000000001){
    printk("- was caused by a page-protection violation\n");
  }else{
    printk("- was caused by a non-present page\n");
  }
  if(error & 0b00000000000000000000000000000010){
    printk("- was caused by a write access\n");
  }else{
    printk("- was caused by a read access\n");
  }
  if(error & 0b00000000000000000000000000000100){
    printk("- was caused while CPL = 3. This does not necessarily mean that the page fault was a privilege violation\n");
  }
  if(error & 0b00000000000000000000000000001000){
    printk("- one or more page directory entries contain reserved bits which are set to 1. This only applies when the PSE or PAE flags in CR4 are set to 1\n");
  }
  if(error & 0b00000000000000000000000000010000){
    printk("- was caused by an instruction fetch. This only applies when the No-Execute bit is supported and enabled.\n");
  }
  if(error & 0b00000000000000000000000000100000){
    printk("- was caused by a protection-key violation. The PKRU register (for user-mode accesses) or PKRS MSR (for supervisor-mode accesses) specifies the protection key rights\n");
  }
  if(error & 0b00000000000000000000000001000000){
    printk("- was caused by a shadow stack access\n");
  }
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
  printk("Interrupt %x fired!\n",interrupt_get_int_number());
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
  int_PageFault->selector = GDT_KERNEL_CODE_SEGMENT;
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
    setRawInterrupt(z,NakedInterruptHandler);
  }
  asm volatile ("lidt %0" : : "m"(idtr));
  interrupts_enable();
  interrupt_eoi();
  if(check_apic()){
    set_apic_timer_values(PIT_TIMER_SLEEP_APIC);
  }
}

