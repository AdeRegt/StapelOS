#pragma once
#include <stdint.h>

void outportb(uint16_t port, uint8_t value);
uint8_t inportb(uint16_t port);

void outportw(uint16_t port, uint16_t value);
uint16_t inportw(uint16_t port);

void outportl(uint16_t port, uint32_t value);
uint32_t inportl(uint16_t port);

uint64_t getCR0();
uint64_t getCR2();
uint64_t getCR3();
uint64_t getCR4();
void setCR0(uint64_t cr);
void setCR2(uint64_t cr);
void setCR3(uint64_t cr);
void setCR4(uint64_t cr);

int get_model(void);
int check_apic(void);
void cpuid(int code, uint32_t *a, uint32_t *d);
int cpuid_string(int code, uint32_t where[4]) ;
uint32_t get_cpu_info();
uint32_t get_cpu_feature_information();
