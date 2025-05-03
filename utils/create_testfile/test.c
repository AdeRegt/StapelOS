void exit(){
    asm volatile(
        "xorq %%rdi, %%rdi;"  /* return value */
        "movq $60, %%rax;"    /* syscall id (/asm/unistd_64.h   */
        "syscall;" 
        ::: "rdi", "rax"
        );
}

void main(){
    // asm volatile("cli");
    // asm volatile("hlt");

    exit();
}