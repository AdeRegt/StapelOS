#include "../include/memory.h"
#include "../include/string.h"

MemoryInfo* memory_info;
int free_blocks = 0;

uint64_t getMemoryInfoBlockCount(){
  return memory_info->mMapSize / memory_info->mMapDescSize;
}

void memory_region_dump(){
  for(uint64_t i = 0 ; i < getMemoryInfoBlockCount() ; i++){
    MemoryDescriptor *desc = (MemoryDescriptor*) ( ((uint64_t)memory_info->mMap) + ( i * memory_info->mMapDescSize ));
    printk("@ %d < %x - %x > \n",desc->Type,desc->PhysicalStart,desc->PhysicalStart+(desc->NumberOfPages*MEMORY_PAGE_SIZE));
  }
}

uint8_t memorymap[MAX_SIZE_MEMORYTABLE];

void initialise_memory(MemoryInfo* mem){
  memory_info = mem;
  
  memclear(memorymap,MAX_SIZE_MEMORYTABLE);
  
}

// thanks https://github.com/nelsoncole/sirius-x86-64/blob/main/boot/stage2/lib/string.c
void *memset(void *s, char val, uint64_t count)
{
	uint64_t _count = count;
    unsigned char *tmp = (unsigned char *)s;
    for(; _count != 0; _count--) *tmp++ = val;
    return s;

}

// thanks https://github.com/nelsoncole/sirius-x86-64/blob/main/boot/stage2/lib/string.c
void *memcpy(void * restrict s1, const void * restrict s2, uint64_t n)
{
	uint64_t p    = n;
	char *p_dest = (char*)s1;
	char *p_src  = (char*)s2;

	while(p--)
	*p_dest++ = *p_src++;
	return s1;
}

void *memclear(void *str,uint64_t n){
  return memset(str,0,n);
}

void* malloc(uint64_t requested_size){

  //
  // calculate memory requirements
  int neededmemoryregions = 0;
  uint64_t t = 0;
  while(1){
    if(t>=requested_size){
      break;
    }
    neededmemoryregions++;
    t += MEMORY_PAGE_SIZE;
  }
  
  //
  // calculate rigt
  if(neededmemoryregions!=1){
    printk("malloc: unexpected size: requested: %d calculated: %d \n",requested_size,neededmemoryregions);
    for(;;);
  }

  int ews = 0;
  for(uint64_t i = 0 ; i < getMemoryInfoBlockCount() ; i++){
    MemoryDescriptor *desc = (MemoryDescriptor*) ( ((uint64_t)memory_info->mMap) + ( i * memory_info->mMapDescSize ));
    if( desc->Type==MEMORY_TYPE_FREE &&desc->PhysicalStart ){
      for(uint64_t u = 0 ; u < desc->NumberOfPages ; u++){
        if(memorymap[ews]==0){
          memorymap[ews] = 1;
          void* cv = (void*) ( desc->PhysicalStart + ( u * MEMORY_PAGE_SIZE ) );
          // printk("-> %x \n",cv);
          return cv;
        }
        ews++;
      }
    }
  }

  printk("__out of memory\n");for(;;);
}

void markMemoryRegionUsed(void* from,void* to){
  // printk("--#-start:%x end:%x total:%x \n",from,to,(to-from)/MEMORY_PAGE_SIZE);
  // first check if our chunk is free
  int memmaptablepointer = 0;
  int memteb = 0;
  for(uint64_t i = 0 ; i < getMemoryInfoBlockCount() ; i++){
    MemoryDescriptor *desc = (MemoryDescriptor*) ( ((uint64_t)memory_info->mMap) + ( i * memory_info->mMapDescSize ));
    if( desc->Type==MEMORY_TYPE_FREE &&desc->PhysicalStart){
      for(uint64_t u = 0 ; u < desc->NumberOfPages ; u++){
        if( memteb==0 && (desc->PhysicalStart+(u*MEMORY_PAGE_SIZE)) <= ((uint64_t)from) && ((desc->PhysicalStart+(u*MEMORY_PAGE_SIZE))+(desc->NumberOfPages*MEMORY_PAGE_SIZE)) >= ((uint64_t)from) && ((desc->PhysicalStart+(u*MEMORY_PAGE_SIZE))+(desc->NumberOfPages*MEMORY_PAGE_SIZE)) >= ((uint64_t)to) ){
          memteb = memmaptablepointer;
        }
        memmaptablepointer++;
      }
    }
  }

  for(int i = 0 ; i < ((to-from)/MEMORY_PAGE_SIZE) ; i++){
    memorymap[memteb+i] = 1;
  }
}

void* calloc(uint64_t requested_size){
  void* dat = malloc(requested_size);
  memclear(dat,requested_size);
  return dat;
}

void* free(void* a){
  return a;
}
