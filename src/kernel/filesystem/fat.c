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

FATFileTemplate *filesystembuffer = 0;
FATInformation* information;

uint8_t fat_filesystem_is_enabled(){
	return filesystembuffer!=0;
}

uint32_t fat_read(int filepointer,void* where){
	if(filepointer){
		FATFileDefinition defo = filesystembuffer->fs[filepointer-1];
		FAT32BootBlock* bb = (FAT32BootBlock*) &information->bootblock->extended_section;
		uint32_t lol = ( information->base + (information->root_directory_index + ( defo.cluster_low * information->bootblock->sectors_per_cluster )) ) - ( bb->cluster_num_root * information->bootblock->sectors_per_cluster );
		char* tt = (char*) read_sectors (lol , ( defo.size/512 ) + 1, where);
		return defo.size;
	}else{
		return 0;
	}
}

int fat_compare_filenames(char* filename,char* original){
	int original_a = 0;
	int filename_a = 0;
	char buffer[13];
	for(int i = 0 ; i < 13 ; i++){
		buffer[i]=0;
	}
	int bufferi = 0;
	for(int i = 0 ; i < 8 ; i++){
		if(filename[i]==' '){
			continue;
		}
		buffer[bufferi++] = filename[i];
	}
	buffer[bufferi++] = '.';
	for(int i = 0 ; i < 3 ; i++){
		if(filename[8+i]==' '){
			continue;
		}
		buffer[bufferi++] = filename[8+i];
	}
	for(int i = 0 ; i < 12 ; i++){
		if(original[i]==0){
			break;
		}
		if(buffer[i]!=original[i]){
			return 0;
		}
	}
	return 1;
}

int fat_open(char* filename){
	for(int i = 0 ; i < (16*2) ; i++){
		if(filesystembuffer->fs[i].attributes==0x20){
			if(fat_compare_filenames ((char*) &filesystembuffer->fs[i].filename, filename)==1){
				return i+1;
			}
		}
	}
	return 0;
}

char* fat_dir(){
	char* buffer = (char*) calloc(0x1000);
	int bufferi = 0;
	int bufferz = 0;
	for(int i = 0 ; i < (16*2) ; i++){
		if(filesystembuffer->fs[i].attributes==0x20){
			if(bufferi!=0){
				buffer[bufferi++] = ';';
			}
			for(int z = 0 ; z < 8 ; z++){
				if(filesystembuffer->fs[i].filename[z]!=' '){
					buffer[bufferi++] = filesystembuffer->fs[i].filename[z];
				}
			}
			buffer[bufferi++] = '.';
			for(int z = 0 ; z < 3 ; z++){
				if(filesystembuffer->fs[i].filename[z]!=' '){
					buffer[bufferi++] = filesystembuffer->fs[i].filename[8+z];
				}
			}
		}
	}
	return buffer;
}

void fat_initialise_fat(Partition part){
	FATBootBlock *bpb = (FATBootBlock*) calloc(0x1000);
	read_sectors (part.lba_start , 1, bpb);
	FAT32BootBlock* bb = (FAT32BootBlock*) &bpb->extended_section;
	uint32_t root_directory_index = bpb->reserved_sector_count + ( bpb->table_count * bb->sectors_per_fat );
	filesystembuffer = (FATFileTemplate*) calloc(0x1000);
	read_sectors (part.lba_start + root_directory_index , 5, filesystembuffer);
	information = (FATInformation*) calloc(0x1000);
	information->bootblock = bpb;
	information->template = filesystembuffer;
	information->root_directory_index = root_directory_index;
	information->base = part.lba_start;
	// fat_dump_boot_block(bpb);
	printk("FAT32 Filesystem discovered!\n");
}

void fat_handle_partition(Partition part){
	if(part.type==11){
		fat_initialise_fat (part);
	}
}

void detect_fat(){
	MBRTemplate* template = calloc(0x1000);
	read_sectors (0 , 1, template);
	fat_handle_partition (template->partition1);
	fat_handle_partition (template->partition2);
	fat_handle_partition (template->partition3);
	fat_handle_partition (template->partition4);
}
