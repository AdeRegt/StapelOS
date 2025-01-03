#include "../include/stapelbridge.h"
#include "../include/filesystem.h"
#include "../include/memory.h"
#include "../include/string.h"

void load_stapel_file_singletasking(char* path){
	int z = fat_open(path);
	if(z==0){
		return;
	}
	void *find = calloc(0x1000);
	int len = fat_read(z,find);
	if(len==0){
		return;
	}
	StapelMultitaskingInstance* cv = insert_stapel_cardridge (find);
	if(cv){
		while(handle_next_instruction(cv));
	}
}

void load_stapel_tutorial(){
	load_stapel_file_singletasking ("EXAMPLE.ST");
}
