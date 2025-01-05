#pragma once
#include <stdint.h>

#define PAGE_GAP_SIZE 0x200000
#define PAGE_LOCATOR 0xF00000

typedef struct{
    uint8_t present: 1;
    uint8_t readwrite: 1;
    uint8_t usersuper: 1;
    uint8_t writetrough: 1;
    uint8_t cachedisabled: 1;
    uint8_t accessed: 1;
    uint8_t ignore1: 1;
    uint8_t largepages: 1;
    uint8_t ignore2: 1;
    uint8_t available: 3;
    uint64_t address: 52;
}Page;

typedef struct{
    Page pages[512];
}PageTable;

typedef struct{
    uint64_t page_map_level_4_table_index;
    uint64_t page_directory_pointer_table_index;
    uint64_t page_directory_table_index;
    uint64_t page_table_index;
}PageLookupResult;

void initialise_paging();
void define_linear_memory_block(void *address);