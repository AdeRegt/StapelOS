#include "../include/syscall.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/paging.h"
#include "../include/cpu.h"

uint64_t syscall_rax;
uint64_t syscall_rbx;
uint64_t syscall_rcx;
uint64_t syscall_rdx;
uint64_t syscall_rsi;
uint64_t syscall_rdi;
uint64_t syscall_rsp;
uint64_t syscall_rbp;
uint64_t syscall_exstack;
uint64_t syscall_r8;
uint64_t syscall_r9;
uint64_t syscall_r10;
uint64_t syscall_r11;
uint64_t syscall_r12;
uint64_t syscall_r13;
uint64_t syscall_r14;
uint64_t syscall_r15;

 void syscallprobe(){
    #ifdef DEBUGSYSCALL
    printk("SYSCALL\n");
    printk("- rax %x \n",syscall_rax);
    printk("- rbx %x \n",syscall_rbx);
    printk("- rcx %x \n",syscall_rcx);
    printk("- rdx %x \n",syscall_rdx);
    printk("- rsi %x \n",syscall_rsi);
    printk("- rdi %x \n",syscall_rdi);
    printk("- rsp %x \n",syscall_rsp);
    printk("- rbp %x \n",syscall_rbp);
    #endif 
    if(syscall_rax==1){
        if(syscall_rdi!=1){
            printk("syscall: print to something else then screen!\n");
            return;
        }
        #ifdef DEBUGSYSCALL
        printk("write: rdx: %x , rsi: %x\n",syscall_rdx,syscall_rsi);
        #endif 
        for(uint64_t i = 0 ; i < syscall_rdx ; i++){
            #ifdef DEBUGSYSCALL
            printk("write x: i: %x , c: %x \n",i,((uint8_t*)syscall_rsi)[i]);
            #endif 
            printk("%c",((uint8_t*)syscall_rsi)[i]);
        }
    }else{
        #ifndef DEBUGSYSCALL
        printk("SYSCALL\n");
        printk("- rax %x \n",syscall_rax);
        printk("- rbx %x \n",syscall_rbx);
        printk("- rcx %x \n",syscall_rcx);
        printk("- rdx %x \n",syscall_rdx);
        printk("- rsi %x \n",syscall_rsi);
        printk("- rdi %x \n",syscall_rdi);
        printk("- rsp %x \n",syscall_rsp);
        printk("- rbp %x \n",syscall_rbp);
        #endif 
        cli();
        hlt();
    }
    // printk((char*) syscall_rsi);
}

extern void syscallentrypoint();

void syscall_enable(){
    uint32_t alpha;
    uint32_t beta;
    cpu_get_specific_registers(IA32_EFER,&alpha,&beta);
    if(!(alpha & 1)){
        alpha |= 1;
        cpu_set_specific_registers(IA32_EFER,alpha,beta);
    }
}

void syscall_set_segments(uint8_t from,uint8_t to){
    uint32_t alpha;
    uint32_t beta;
    alpha = 0;
    beta = from | ( to << 16 );
    cpu_set_specific_registers(SYSCALL_REG_STAR,alpha,beta);
}

void syscall_set_entry_point(uint64_t ent){
    uint32_t alpha;
    uint32_t beta;
    alpha = (uint32_t)(ent);
    beta = 0;
    cpu_set_specific_registers(SYSCALL_REG_LSTAR,alpha,beta);
}

void syscall_set_mask(uint32_t mask){
    uint32_t alpha = mask;
    uint32_t beta = 0;
    cpu_set_specific_registers(0xC0000084,alpha,beta);
}

void initialise_syscall(){
    // https://wiki.osdev.org/SYSENTER
    syscall_enable();
    syscall_set_segments(0x8,0x18);
    syscall_set_entry_point((uint64_t)&syscallentrypoint);
    syscall_set_mask(0x202);

    // syscall_exstack = ( (uint64_t) malloc(0x1000) ) - 0x1000;
}