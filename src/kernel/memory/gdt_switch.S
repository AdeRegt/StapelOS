.global gdt_flush
gdt_flush:
    movw $0x10, %ax       # Load data segment selector
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    pushq $0x08           # Push code segment selector (64-bit)
    lea next(%rip), %rax  # Load the address of 'next' into RAX
    pushq %rax            # Push the address onto the stack
    lretq                 # Long return to switch segments
next:
    ret