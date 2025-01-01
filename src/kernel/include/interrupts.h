// 0x8E
#define IDT_TA_InterruptGate    0b10001110
// 0x8C
#define IDT_TA_CallGate         0b10001100
// 0x8F
#define IDT_TA_TrapGate         0b10001111
#define IDT_MAX_DESCRIPTORS     251
#define GDT_CODE_SEGMENT 0x08

#define INT_OFFSET 0x20

typedef struct {
    uint16_t offset0;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset1;
    uint32_t offset2;
    uint32_t ignore;
}IDTDescEntry;

typedef struct __attribute__((packed)) {
    uint16_t Limit;
    uint64_t Offset;
} IDTR;

typedef struct{
    uint64_t ip;
    uint64_t cs;
    uint64_t flags;
    uint64_t sp;
    uint64_t ss;
}interrupt_frame;

struct stackframe {
  struct stackframe* ebp;
  uint32_t eip;
};

void initialise_interrupts();
void setInterrupt(int offset,void *fun);
void interrupts_disable();
void interrupts_enable();
void interrupt_eoi();