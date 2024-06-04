#include "include/vga.h"
#include "include/string.h"
#include "include/interrupts.h"
#include "include/memory.h"

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
  initialise_memory (bi->memory_info);
  initialise_interrupts();
  printk("StapelOS64 bit\n");
  for(;;);
}
