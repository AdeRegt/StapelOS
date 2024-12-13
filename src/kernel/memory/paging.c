#include "../include/memory.h"
#include "../include/paging.h"
#include "../include/string.h"

PageTable *master_page_table;

void *memreg = (void*)PAGE_LOCATOR;

PageLookupResult page_map_indexer(uint64_t virtual_address){
    PageLookupResult plr;
    virtual_address >>= 12;
    plr.page_table_index = virtual_address & 0x1ff;
    virtual_address >>= 9;
    plr.page_directory_table_index = virtual_address & 0x1ff;
    virtual_address >>= 9;
    plr.page_directory_pointer_table_index = virtual_address & 0x1ff;
    virtual_address >>= 9;
    plr.page_map_level_4_table_index = virtual_address & 0x1ff;
    return plr;
}

void map_memory(void* pml4mem, void *virtualmemory,void* physicalmemory){
    PageLookupResult lookup = page_map_indexer((uint64_t)virtualmemory);
    PageTable* PLM4 = (PageTable*) pml4mem;
    Page PDE = PLM4->pages[lookup.page_map_level_4_table_index];
    PageTable *PDP;
    if(!PDE.present){
        PDP = (PageTable*) memreg;
        memreg += 0x1000;
        memset(PDP, 0, 0x1000);
        PDE.address = (uint64_t)PDP >> 12;
        PDE.present = 1;
        PDE.readwrite = 1;
        PLM4->pages[lookup.page_map_level_4_table_index] = PDE;
    }else{
        PDP = (PageTable*)((uint64_t)PDE.address<<12);
    }

    PDE = PDP->pages[lookup.page_directory_pointer_table_index];
    PageTable *PD;
    if(!PDE.present){
        PD = (PageTable*) memreg;
        memreg += 0x1000;
        memset(PD, 0, 0x1000);
        PDE.address = (uint64_t)PD >> 12;
        PDE.present = 1;
        PDE.readwrite = 1;
        PDP->pages[lookup.page_directory_pointer_table_index] = PDE;
    }else{
        PD = (PageTable*)((uint64_t)PDE.address<<12);
    }

    PDE = PD->pages[lookup.page_directory_table_index];
    PageTable *PE;
    PDE.address     = (uint64_t)physicalmemory>>12;//PE >> 12;
    PDE.present     = 1;
    PDE.readwrite   = 1;
    PDE.largepages  = 1;
    PD->pages[lookup.page_directory_table_index] = PDE;
}

void define_linear_memory_block(void *address){
  map_memory(master_page_table,address,address);
}

void initialise_paging(){
  master_page_table = (PageTable*) calloc(sizeof(PageTable));
  for(uint64_t valve = 0 ; valve < (0xFFFFF000/PAGE_GAP_SIZE) ; valve++){
      define_linear_memory_block((void*)(valve*PAGE_GAP_SIZE));
  }
  asm volatile ("mov %0, %%cr3" : : "r" (master_page_table));
  markMemoryRegionUsed((void*)PAGE_LOCATOR,memreg);
}
