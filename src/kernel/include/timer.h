#define PIT_COMMAND_MODE_REGISTER 0x43
#define PIT_CHANNEL0_DATA_REGISTER 0x40

void initialise_timer();
void sleep(int timeout);
void sleep_seconds(int timeout);
