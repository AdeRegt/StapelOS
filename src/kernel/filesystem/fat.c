#include "../include/string.h"
#include "../include/fat.h"
#include "../include/filesystem.h"
#include "../include/memory.h"

typedef struct{
	uint8_t attributes;
	uint8_t chs_start[3];
	uint8_t type;
	uint8_t chs_end[3];
	uint32_t lba_start;
	uint32_t sectors;
}__attribute__((packed)) Partition;

typedef struct{
	uint8_t code[440];
	uint32_t unique_disk_id;
	uint16_t reserved;
	Partition partition1;
	Partition partition2;
	Partition partition3;
	Partition partition4;
	uint16_t signature;
}__attribute__((packed)) MBRTemplate;

void fat_dump_mbr_entry(Partition part){
	printk("Attr: %x sectors:%d type:%x LBA:%x \n",part.attributes,part.sectors,part.type,part.lba_start);
}

void fat_dump_mbr(MBRTemplate* template){
	printk("UDid: %x Sign: %x \n",template->unique_disk_id,template->signature);
	fat_dump_mbr_entry(template->partition1);
	fat_dump_mbr_entry(template->partition2);
	fat_dump_mbr_entry(template->partition3);
	fat_dump_mbr_entry(template->partition4);
}

void detect_fat(){
	MBRTemplate* template = read_sectors (0 , 1);
	fat_dump_mbr(template);

}
