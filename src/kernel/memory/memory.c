#include "../include/memory.h"
#include "../include/string.h"

MemoryBlockDescriptor memoryblock[MAX_SIZE_MEMORYTABLE];
uint64_t freememorypointer = 0;

void initialise_memory(MemoryInfo* mem){
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
  for(int i = 0 ; i < MAX_SIZE_MEMORYTABLE ; i++){
    if(memoryblock[i].valid==0){
      memoryblock[i].valid = 1;
      memoryblock[i].start = freememorypointer;
      freememorypointer += requested_size;
      memoryblock[i].end = freememorypointer;
      return (void*) memoryblock[i].start;
    }
  }
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
