#include "../include/memory.h"
#include "../include/string.h"

MemoryBlockDescriptor memoryblock[MAX_SIZE_MEMORYTABLE];
uint64_t freememorypointer = 0;

MemoryInfo* memory_info;

void initialise_memory(MemoryInfo* mem){
  memory_info = mem;
  uint64_t memoryitemcount = mem->mMapSize / mem->mMapDescSize;
  for(uint64_t i = 0 ; i < memoryitemcount ; i++){
    MemoryDescriptor *desc = (MemoryDescriptor*) ( ((uint64_t)mem->mMap) + ( i * mem->mMapDescSize ));
    if(desc->Type==7&&desc->PhysicalStart){
      freememorypointer = desc->PhysicalStart;
    }
  }
}

void *memset(void *str, int c, uint64_t n){
  for(uint64_t i = 0 ; i < n ; i++){
    ((int*)str)[i] = c;
  }
  return str;
}

void *memclear(void *str,uint64_t n){
  return memset(str,0,n);
}

void* malloc(uint64_t requested_size){
  uint64_t memoryitemcount = memory_info->mMapSize / memory_info->mMapDescSize;
  for(uint64_t i = 0 ; i < memoryitemcount ; i++){
    MemoryDescriptor *desc = (MemoryDescriptor*) ( ((uint64_t)memory_info->mMap) + ( i * memory_info->mMapDescSize ));
    if(desc->Type==7&&desc->PhysicalStart){
      if((desc->PhysicalStart+requested_size)<=(desc->PhysicalStart+(desc->NumberOfPages*0x1000))){
        uint64_t r = desc->PhysicalStart;
        desc->PhysicalStart += requested_size;
        return (void*)r;
      }
    }
  }
  printk("__fatal: out of memory\n");for(;;);
  return 0;
}

void* calloc(uint64_t requested_size){
  void* dat = malloc(requested_size);
  memclear(dat,requested_size);
  return dat;
}

void* free(void* a){
  return a;
}
