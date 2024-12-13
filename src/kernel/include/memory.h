#pragma once
#include <stdint.h>

#define MAX_SIZE_MEMORYTABLE 0x5000
#define MEMORY_TYPE_FREE 7
#define MEMORY_PAGE_SIZE 0x1000

typedef struct {
    uint32_t                          Type;           // Field size is 32 bits followed by 32 bit pad
    uint32_t                          Pad;
    uint64_t                        PhysicalStart;  // Field size is 64 bits
    uint64_t                        VirtualStart;   // Field size is 64 bits
    uint64_t                        NumberOfPages;  // Field size is 64 bits
    uint64_t                        Attribute;      // Field size is 64 bits
} MemoryDescriptor;

typedef struct{
  MemoryDescriptor* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
}MemoryInfo;

void initialise_memory(MemoryInfo* mem);
void markMemoryRegionUsed(void* from,void* to);
void *memset(void *s, char val, uint64_t count);
void* malloc(uint64_t requested_size);
void* calloc(uint64_t requested_size);
void *memclear(void *str,uint64_t n);
void* free(void* a);