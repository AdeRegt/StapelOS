#include "../include/elf.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/paging.h"
#include "../include/cpu.h"

uint64_t uprogstart;
uint64_t usermode_eflags = USERMODE_EFLAGS;
extern void jump_usermode();

int load_elf_segment(void* reference,ELFProgramHeader* ph){
    if(ph->p_memsz>PAGE_GAP_SIZE){
        return 1;
    }
    if(!(ph->p_vaddr&PAGE_AND)){
        // maybe we need to allocate a new page?
        uint32_t toyaddr = ph->p_vaddr >> 21;
        if((toyaddr%2)==0){
            // yes, we need to allocate a new page!
            void *freepage = malloc_whole_page();
            define_seperate_memory_block((void*)ph->p_vaddr,freepage);
        }
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
    uprogstart = header->e_entry;
    #ifdef USE_USERMODE
    jump_usermode();
    #else
    void (*ProgramStart)() = ((__attribute__((sysv_abi)) void (*)() ) uprogstart);
    ProgramStart();
    #endif 
}

void load_test_executable(){
    #include "./../../../utils/create_testfile/testfile.c"
    load_elf_executable((void*)&buffer);
}