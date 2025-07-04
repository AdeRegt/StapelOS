#include "../include/usb_hid.h"
#include "../include/usb.h"
#include "../include/memory.h"
#include "../include/string.h"

// https://www.usb.org/sites/default/files/hid1_11.pdf

uint8_t install_usb_hid(usb_interface_descriptor *desc,void *data){
    printk("Installing USB HID device\n");
    printk("USB-HID: Number of Endpoints: %d\n", desc->bNumEndpoints);
    if(desc->bInterfaceSubClass == 0x01) {
        printk("USB-HID: Boot Interface\n");
    }else{
        printk("USB-HID: Non-Boot Interface\n");
    }
    if(desc->bInterfaceProtocol==1){
        printk("USB-HID: Keyboard detected\n");
    }else if(desc->bInterfaceProtocol==2){
        printk("USB-HID: Mouse detected\n");
    }else{
        printk("USB-HID: Unknown Protocol: %d\n", desc->bInterfaceProtocol);
    }
    return 1;
}
