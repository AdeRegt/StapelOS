#pragma once
#include <stdint.h>

void *read_sectors(uint64_t sector, uint32_t counter,void* out);
char* fat_dir();
int fat_open(char* filename);
uint32_t fat_read(int filepointer,void* where);
