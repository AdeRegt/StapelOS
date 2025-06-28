#include "../include/usb_hid.h"
#include "../include/usb.h"
#include "../include/memory.h"
#include "../include/string.h"

uint8_t install_usb_hid(usb_interface_descriptor *desc,void *data){
    printk("Installing USB HID device\n");
    return 1;
}
