#include "../include/stapelbridge.h"
#include "../include/filesystem.h"
#include "../include/memory.h"
#include "../include/string.h"

void load_stapel_file_singletasking(char* path){
	int z = fat_open(path);
	void *find = calloc(0x1000);
	int len = fat_read(z,find);
	StapelMultitaskingInstance* cv = insert_stapel_cardridge (find);
	while(1)
  {
      handle_next_instruction(cv);
  }
}

void load_stapel_tutorial(){
	load_stapel_file_singletasking ("EXAMPLE.ST");
}
