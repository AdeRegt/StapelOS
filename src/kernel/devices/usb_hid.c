#include "../include/string.h"
#include "../include/usb.h"
#include "../include/usb_hid.h"
#include "../include/memory.h"

void install_usb_hid(usb_interface_descriptor* desc,void *data){
	printk("subclass: %x protocol: %x \n",desc->bInterfaceSubClass,desc->bInterfaceProtocol);
}
