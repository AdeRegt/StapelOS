#include "../include/string.h"
#include "../include/fat.h"
#include "../include/filesystem.h"
#include "../include/memory.h"

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

void fat_dump_file(FATFileDefinition tmp){
	if(tmp.attributes!=0x20){
		return;
	}
	printk("cluster: %x %x attr:%x size: %d filename:",tmp.cluster_high,tmp.cluster_low,tmp.attributes,tmp.size);
	for(int i = 0 ; i < 11 ; i++){
		printk("%c",tmp.filename[i]);
	}
	printk("\n");
}

void fat_dump_filesystem(FATFileTemplate* tmp){
	for(int i = 0 ; i < (16*2) ; i++){
		fat_dump_file(tmp->fs[i]);
	}
}

void fat_dump_boot_block(FATBootBlock* ee){
	printk("- %s : %x %x %x \n","bootjmp              ",ee->bootjmp[0],ee->bootjmp[1],ee->bootjmp[2]);
	printk("- %s : %c %c %c %c %c %c %c %c \n","oem_name             ",ee->oem_name[0],ee->oem_name[1],ee->oem_name[2],ee->oem_name[3],ee->oem_name[4],ee->oem_name[5],ee->oem_name[6],ee->oem_name[7]);
	printk("- %s : %d \n","bytes_per_sector     ",ee->bytes_per_sector);
	printk("- %s : %d \n","sectors_per_cluster  ",ee->sectors_per_cluster);
	printk("- %s : %d \n","reserved_sector_count",ee->reserved_sector_count);
	printk("- %s : %d \n","table_count          ",ee->table_count);
	printk("- %s : %d \n","root_entry_count     ",ee->root_entry_count);
	printk("- %s : %d \n","total_sectors_16     ",ee->total_sectors_16);
	printk("- %s : %d \n","media_type           ",ee->media_type);
	printk("- %s : %d \n","table_size_16        ",ee->table_size_16);
	printk("- %s : %d \n","sectors_per_track    ",ee->sectors_per_track);
	printk("- %s : %d \n","head_side_count      ",ee->head_side_count);
	printk("- %s : %d \n","hidden_sector_count  ",ee->hidden_sector_count);
	printk("- %s : %d \n","total_sectors_32     ",ee->total_sectors_32);
	if(ee->total_sectors_32!=0){
		FAT32BootBlock* bb = (FAT32BootBlock*) &ee->extended_section;
		printk("- %s : %d \n","sectors_per_fat      ",bb->sectors_per_fat);
		printk("- %s : %x \n","flags                ",bb->flags);
		printk("- %s : %d \n","fat_version          ",bb->fat_version);
		printk("- %s : %d \n","cluster_num_root     ",bb->cluster_num_root);
	}
}

FATFileTemplate *filesystembuffer;

void fat_initialise_fat(Partition part){
	FATBootBlock *bpb = (FATBootBlock*) read_sectors (part.lba_start , 1);
	FAT32BootBlock* bb = (FAT32BootBlock*) &bpb->extended_section;
	uint32_t root_directory_index = bpb->reserved_sector_count + ( bpb->table_count * bb->sectors_per_fat );
	filesystembuffer = (FATFileTemplate*) read_sectors (part.lba_start + root_directory_index , 5);
}

void fat_handle_partition(Partition part){
	if(part.type==11){
		fat_initialise_fat (part);
	}
}

void detect_fat(){
	MBRTemplate* template = read_sectors (0 , 1);
	fat_handle_partition (template->partition1);
	fat_handle_partition (template->partition2);
	fat_handle_partition (template->partition3);
	fat_handle_partition (template->partition4);

}
