#include "include/vga.h"
#include "include/string.h"
#include "include/interrupts.h"
#include "include/memory.h"
#include "include/paging.h"
#include "include/pci.h"
#include "include/timer.h"
#include "include/fat.h"
#include "include/filesystem.h"
#include "include/stapelbridge.h"
#include "include/ps2_keyboard.h"
#include "include/serial.h"
#include "include/cpu.h"
#include "include/gdt.h"

/**
 * @brief Bootinfo structure given by the program that booted us
 *
 */
typedef struct{

	/**
	 * @brief Graphicsinfo from the current device, like screensize, bytes per pixel, etc
	 *
	 */
	GraphicsInfo* graphics_info;

	/**
	 * @brief Fontfile that is used by the bootloader
	 *
	 */
	void* font;

	/**
	 * @brief Memoryinfo with memorymap of the free memory which is present
	 *
	 */
	MemoryInfo* memory_info;

	/**
	 * @brief Information table of which devices are present on this system
	 *
	 */
	void *rsdp;
} BootInfo;

void kernel_main(BootInfo* bi){
  initialise_graphics_driver(bi->graphics_info);
  printk("StapelOS64 bit\n");
  printk("Loading essentials...\n");
  initialise_gdt();
  initialise_memory(bi->memory_info);
  initialise_paging();
  initialise_interrupts();
  initialise_timer();
  initialise_serial();
  clearFatDetection();
  initialise_pci();
  initialise_ps2_keyboard();
  printk("Ready.\n");
  if(fat_filesystem_is_enabled()){
	printk("Filesystem is enabled!\n");
	char *dir = fat_dir();
	if(dir){
		printk("Root directory: %s \n",dir);
		load_stapel_tutorial();
	}else{
		printk("Oops: something went wrong while loading the root directory!\n");
	}
  }
  printk("System is finished\n");
  for(;;);
}
