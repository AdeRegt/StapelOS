// 0x8E
#define IDT_TA_InterruptGate    0b10001110
// 0x8C
#define IDT_TA_CallGate         0b10001100
// 0x8F
#define IDT_TA_TrapGate         0b10001111
#define IDT_MAX_DESCRIPTORS     251
#define GDT_CODE_SEGMENT 0x08

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define PIC_OFFSET 0x20

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
void IRQ_clear_mask(unsigned char IRQline);
void disable_pic();
void interrupts_disable();
void interrupts_enable();