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

void sleep(int timeout){
  timer_total = timeout;
  while(timer_total);
}

void sleep_seconds(int timeout){
  timer_total = timeout * 100;
  while(timer_total);
}

void initialise_timer(){
  int divisor = 1193180 / 100;       /* Calculate our divisor */
	outportb(0x43, 0x36);             /* Set our command byte 0x36 */
	outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
	outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
  setInterrupt (0, timer_int);
  outportb(0xA0,0x20);
	outportb(0x20,0x20);
}
