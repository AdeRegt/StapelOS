#include "../include/elf.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/paging.h"
#include "../include/cpu.h"

uint32_t uprogstart;
extern void jump_usermode();

int load_elf_segment(void* reference,ELFProgramHeader* ph){
    if(ph->p_memsz>0x200000){
        return 1;
    }
    memcpy((void*)ph->p_vaddr,(void*)(((uint64_t)reference) + ph->p_offset),ph->p_filesz);
    return 0;
}

void load_elf_executable(void* buffer){
    ELFHeader* header = (ELFHeader*) buffer;
    if(!(header->magic[0]==EI_MAG0||header->magic[1]==EI_MAG1||header->magic[2]==EI_MAG2||header->magic[3]==EI_MAG3)){
        printk("elf: invalid magic!\n");
        return;
    }
    if(header->bitver!=EFI_TARGET_BIT){
        printk("elf: not 64bit elf!\n");
        return;
    }
    if(header->indian!=EFI_TARGET_INDIAN){
        printk("elf: invalid endian!\n");
        return;
    }
    if(header->elfver!=EFI_TARGET_ELF){
        printk("elf: invalid elf version!\n");
        return;
    }
    if(header->type!=EFI_TARGET_EXEC){
        printk("elf: elf is not executable!\n");
        return;
    }
    if(header->e_phoff!=EFI_TARGET_OFF){
        printk("elf: invalid elf offset\n");
        return;
    }
    if(header->e_ehsize!=EFI_TARGET_OFF){
        printk("elf: wrong headersize \n");
        return;
    }
    void *freepage = malloc_whole_page();
    define_seperate_memory_block((void*)0x400000,freepage);
    void* ks = (void*)0;
    for(uint16_t i = 0 ; i < header->e_phnum ; i++){
        uint64_t adu = ((uint64_t)buffer) + header->e_phoff + (i*header->e_phentsize);
        ELFProgramHeader* ph = (ELFProgramHeader*) adu;
        if(ph->p_type==PT_LOAD){
            int ts = load_elf_segment(buffer,ph);
            if(ts){
                printk("elf: invalid segment \n");
                return;
            }
        }
    }
    uprogstart = (uint32_t)(uint64_t)header->e_entry;
    #ifdef USE_USERMODE
    jump_usermode();
    #else
    void (*ProgramStart)() = ((__attribute__((sysv_abi)) void (*)() ) (uint64_t)header->e_entry);
    ProgramStart();
    #endif 
}

void load_test_executable(){
    #include "./../../../utils/create_testfile/testfile.c"
    load_elf_executable((void*)&buffer);
}