#define PIT_COMMAND_MODE_REGISTER 0x43
#define PIT_CHANNEL0_DATA_REGISTER 0x40

#define PIT_TIMER_SLEEP_APIC 0x00200000
#define PIT_TIMER_SLEEP_PIC 0x800

void initialise_timer();
void sleep(int timeout);
