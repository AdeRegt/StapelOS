#include <stdint.h>

asm ("jmp main");

void syscall(int64_t a,int64_t b,int64_t c,int64_t d,int64_t e,int64_t f){
    register int64_t rax __asm__ ("rax") = a;
    register int64_t rbx __asm__ ("rbx") = b;
    register int64_t rcx __asm__ ("rcx") = c;
    register int64_t rdx __asm__ ("rdx") = d;
    register int64_t rsi __asm__ ("rsi") = e;
    register int64_t rdi __asm__ ("rdi") = f;
    __asm__ __volatile__ (
        "syscall"
        : 
        "+r" (rax),
        "+r" (rbx),
        "+r" (rcx),
        "+r" (rdx),
        "+r" (rsi),
        "+r" (rdi)
        : "r" (rdi)
        :  
    );
}

void exit(uint64_t res){
    syscall(70,res,0,0,0,0);
}

int strlen(char* str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

void write_string(char* message){
    syscall(1,0,0,strlen(message),(uint64_t)message,1);
}

void main(){
    write_string("This message is send from Usermode!\n\n");
    exit(0);
    asm volatile("cli\nhlt");
}