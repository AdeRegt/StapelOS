#include "../include/pic.h"
#include "../include/cpu.h"
#include "../include/string.h"

void reset_pic(uint8_t oldpic1,uint8_t oldpic2){
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
}

void initialise_pic(){
  uint8_t oldpic1 = inportb(PIC1_DATA);
  uint8_t oldpic2 = inportb(PIC2_DATA);
  reset_pic(oldpic1,oldpic2);
}

void pic_eoi(){
  outportb(0xA0,0x20);
  outportb(0x20,0x20);
}

uint8_t pic_get_interrupt_number(){
    return 0;
}

void disable_pic(){
  uint8_t oldpic1 = inportb(PIC1_DATA);
  uint8_t oldpic2 = inportb(PIC2_DATA);
  if(!(oldpic1==0xFF&&oldpic2==0xFF)){
    reset_pic(0xFF,0xFF);
  }
}