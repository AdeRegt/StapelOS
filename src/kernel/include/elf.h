#pragma once
#include <stdint.h>

#define EI_MAG0 0x7F
#define EI_MAG1 0x45 
#define EI_MAG2 0x4c
#define EI_MAG3 0x46 

#define EFI_TARGET_BIT 2
#define EFI_TARGET_INDIAN 1
#define EFI_TARGET_ELF 1
#define EFI_TARGET_EXEC 2
#define EFI_TARGET_OFF 0x40
#define PT_LOAD 0x00000001



typedef struct {
    uint8_t magic[4];
    uint8_t bitver;
    uint8_t indian;
    uint8_t elfver;
    uint8_t osabi;
    uint8_t abiver;
    uint8_t padding[7];
    uint16_t type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
}__attribute__((packed)) ELFHeader;

typedef struct {
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
}__attribute__((packed)) ELFProgramHeader;

void load_elf_executable(void* buffer);
void load_test_executable();