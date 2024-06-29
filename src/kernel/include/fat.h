#pragma once
#include <stdint.h>

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

typedef struct {
	uint8_t 		bootjmp[3];
	uint8_t 		oem_name[8];
	uint16_t 	    bytes_per_sector;
	uint8_t		    sectors_per_cluster;
	uint16_t		reserved_sector_count;
	uint8_t		    table_count;
	uint16_t		root_entry_count;
	uint16_t		total_sectors_16;
	uint8_t		    media_type;
	uint16_t		table_size_16;
	uint16_t		sectors_per_track;
	uint16_t		head_side_count;
	uint32_t 		hidden_sector_count;
	uint32_t 		total_sectors_32;

	//this will be cast to it's specific type once the driver actually knows what type of FAT this is.
	unsigned char		extended_section[54];

}__attribute__((packed)) FATBootBlock;

typedef struct{
  uint32_t sectors_per_fat;
  uint16_t flags;
  uint16_t fat_version;
  uint32_t cluster_num_root;
}__attribute__((packed)) FAT32BootBlock;

typedef struct {
	uint8_t filename[11];
	uint8_t attributes;
	uint8_t rsvd;
	uint8_t creation_time;
	uint16_t created_at_time;
	uint16_t created_at_date;
	uint16_t lastaccess_at_date;
	uint16_t cluster_high;
	uint16_t modified_at_time;
	uint16_t modified_at_date;
	uint16_t cluster_low;
	uint32_t size;
}__attribute__((packed)) FATFileDefinition;

typedef struct{
  FATFileDefinition fs[16];
}__attribute__((packed)) FATFileTemplate;

void detect_fat();
