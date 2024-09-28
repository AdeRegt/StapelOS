#include "../include/string.h"
#include "../include/cpu.h"
#include "../include/timer.h"
#include "../include/interrupts.h"

static int timer_total = 0;

__attribute__((interrupt)) void timer_int(interrupt_frame* frame){
  if(timer_total){
    timer_total--;
  }
  outportb(0xA0,0x20);
	outportb(0x20,0x20);
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
  resetTimer();
  set_pit_count(timeout*0x800);
  while(get_pit_count()!=1);
}

void sleep_seconds(int timeout){
  timer_total = timeout * 100;
  while(timer_total);
}

void initialise_timer(){
  resetTimer();
  setInterrupt (0, timer_int);
  outportb(0xA0,0x20);
	outportb(0x20,0x20);
}
