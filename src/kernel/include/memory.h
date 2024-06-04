#pragma once
#include <stdint.h>

#define MAX_SIZE_MEMORYTABLE 500

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

typedef struct{
  uint64_t start;
  uint64_t end;
  uint8_t valid;
} MemoryBlockDescriptor;

void initialise_memory(MemoryInfo* mem);
void *memset(void *str, int c, uint64_t n);
void* malloc(uint64_t requested_size);
void* calloc(uint64_t requested_size);
