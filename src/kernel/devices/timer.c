#include "../include/string.h"
#include "../include/cpu.h"
#include "../include/timer.h"
#include "../include/interrupts.h"
#include "../include/apic.h"

static int timer_total = 0;

__attribute__((interrupt)) void timer_int(interrupt_frame* frame){
  if(check_apic()){
    timer_total++;
  }else{
    if(timer_total){
      timer_total--;
    }
  }
  interrupt_eoi();
}

void set_pit_count(uint16_t value){
  cli();
  outportb(PIT_CHANNEL0_DATA_REGISTER,value&0xFF);		// Low byte
	outportb(PIT_CHANNEL0_DATA_REGISTER,(value&0xFF00)>>8);	// High byte
  sti();
}

uint16_t get_pit_count(){
  cli();
  uint16_t count = 0;
	outportb(PIT_COMMAND_MODE_REGISTER,0b0000000);
	count = inportb(PIT_CHANNEL0_DATA_REGISTER);		// Low byte
	count |= inportb(PIT_CHANNEL0_DATA_REGISTER)<<8;		// High byte
  sti();
	return count;
}

void resetTimer(){
  int divisor = 1193180 / 100;       /* Calculate our divisor */
	outportb(PIT_COMMAND_MODE_REGISTER, 0x3C);             /* Set our command byte 0x36 */
	outportb(PIT_CHANNEL0_DATA_REGISTER, divisor & 0xFF);   /* Set low byte of divisor */
	outportb(PIT_CHANNEL0_DATA_REGISTER, divisor >> 8);     /* Set high byte of divisor */
}

void sleep(int timeout){
  if(check_apic()){
    timer_total = 0;
    set_apic_timer_values(PIT_TIMER_SLEEP_APIC);
    while(timer_total!=2);
  }else{
    resetTimer();
    set_pit_count(timeout*PIT_TIMER_SLEEP_PIC);
    while(get_pit_count()!=1);
  }
}

void initialise_timer(){
  if(!check_apic()){
    resetTimer();
  }
  setInterrupt (0, timer_int);
}
