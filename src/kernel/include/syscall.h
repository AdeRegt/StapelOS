#pragma once
#include <stdint.h>

#define SYSCALL_REG_STAR 0xC0000081
#define SYSCALL_REG_LSTAR 0xC0000082
#define SYSCALL_REG_CSTAR 0xC0000083
#define IA32_EFER 0xC0000080

void initialise_syscall();