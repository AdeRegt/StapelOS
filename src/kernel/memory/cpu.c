#include <stdint.h>
#include <cpuid.h>

void outportb(uint16_t port, uint8_t value){
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

uint8_t inportb(uint16_t port){
    uint8_t returnVal;
    asm volatile ("inb %1, %0"
    : "=a"(returnVal)
    : "Nd"(port));
    return returnVal;
}

void outportw(uint16_t port, uint16_t value){
    asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

uint16_t inportw(uint16_t port){
    uint16_t returnVal;
    asm volatile ("inw %1, %0"
    : "=a"(returnVal)
    : "Nd"(port));
    return returnVal;
}

void outportl(uint16_t port, uint32_t value){
    asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

uint32_t inportl(uint16_t port){
    uint32_t returnVal;
    asm volatile ("inl %1, %0"
    : "=a"(returnVal)
    : "Nd"(port));
    return returnVal;
}

uint64_t getCR0(){
    uint64_t cr;
    __asm__ __volatile__ (
            "mov %%cr0, %%rax\n\t"
            "mov %%eax, %0\n\t"
        : "=m" (cr)
        : /* no input */
        : "%rax"
    );
    return cr;
}

uint64_t getCR2(){
    uint64_t cr;
    __asm__ __volatile__ (
            "mov %%cr2, %%rax\n\t"
            "mov %%eax, %0\n\t"
        : "=m" (cr)
        : /* no input */
        : "%rax"
    );
    return cr;
}

uint64_t getCR3(){
    uint64_t cr;
    __asm__ __volatile__ (
            "mov %%cr3, %%rax\n\t"
            "mov %%eax, %0\n\t"
        : "=m" (cr)
        : /* no input */
        : "%rax"
    );
    return cr;
}

uint64_t getCR4(){
    uint64_t cr;
    __asm__ __volatile__ (
            "mov %%cr4, %%rax\n\t"
            "mov %%eax, %0\n\t"
        : "=m" (cr)
        : /* no input */
        : "%rax"
    );
    return cr;
}

void setCR0(uint64_t cr){
    __asm__ __volatile__ (
            "mov %0, %%rax\n\t"
            "mov %%rax, %%cr0\n\t"
        : /* no output */
        : "m" (cr)
        : "%rax"
    );
}

void setCR2(uint64_t cr){
    __asm__ __volatile__ (
            "mov %0, %%rax\n\t"
            "mov %%rax, %%cr2\n\t"
        : /* no output */
        : "b" (cr)
        : "%rax"
    );
}

void setCR3(uint64_t cr){
    __asm__ __volatile__ (
            "mov %0, %%rax\n\t"
            "mov %%rax, %%cr3\n\t"
        : /* no output */
        : "b" (cr)
        : "%rax"
    );
}

void setCR4(uint64_t cr){
    __asm__ __volatile__ (
            "mov %0, %%rax\n\t"
            "mov %%rax, %%cr4\n\t"
        : /* no output */
        : "b" (cr)
        : "%rax"
    );
}

void cli(){
    __asm__ __volatile__ ("cli");
}

void sti(){
    __asm__ __volatile__ ("cli");
}

// https://en.wikipedia.org/wiki/CPUID


/* Example: Get CPU's model number */
int get_model(void){
    int ebx, unused;
    __cpuid(0, unused, ebx, unused, unused);
    return ebx;
}

/* Example: Check for builtin local APIC. */
int check_apic(void){
    unsigned int eax, unused, edx;
    __get_cpuid(1, &eax, &unused, &unused, &edx);
    return edx & (1 << 9);
}

void cpuid(int code, uint32_t *a, uint32_t *d) {
  asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}

int cpuid_string(int code, uint32_t where[4]) {
  asm volatile("cpuid":"=a"(*where),"=b"(*(where+1)),
               "=c"(*(where+2)),"=d"(*(where+3)):"a"(code));
  return (int)where[0];
}

uint32_t get_cpu_info(){
    uint32_t unused, infoslot;
    cpuid(1,&infoslot,&unused);
    return infoslot;
}

uint32_t get_cpu_feature_information(){
  int code = 1;
  uint32_t infoslot;
  asm volatile("cpuid":"=d"(*&infoslot):"a"(code):"ecx","ebx");
  return infoslot;
}

void __stack_chk_fail(){
    for(;;);
}

void __stack_chk_fail_local(){
    for(;;);
}
