#include "../include/string.h"
#include "../include/usb.h"
#include "../include/usb_msd.h"
#include "../include/xhci.h"

void usb_dump_descriptor(usb_interface_descriptor* desc){
	switch(desc->bInterfaceClass){
	case 0x00: printk("Use class information in the Interface Descriptors");break;
	case 0x01: printk("Audio");break;
	case 0x02: printk("Communications and CDC Control");break;
	case USB_IF_HID: printk("HID (Human Interface Device)");break;
	case 0x05: printk("Physical");break;
	case 0x06: printk("Image");break;
	case 0x07: printk("Printer");break;
	case USB_IF_MSD: printk("Mass Storage");break;
	case 0x09: printk("Hub");break;
	case 0x0A: printk("CDC-Data");break;
	case 0x0B: printk("Smart Card");break;
	case 0x0D: printk("Content Security");break;
	case 0x0E: printk("Video");break;
	case 0x0F: printk("Personal Healthcare");break;
	case 0x10: printk("Audio/Video Devices");break;
	case 0x11: printk("Billboard Device Class");break;
	case 0x12: printk("USB Type-C Bridge Class");break;
	case 0x13: printk("USB Bulk Display Protocol Device Class");break;
	case 0x14: printk("MCTP over USB Protocol Endpoint Device Class");break;
	case 0x3C: printk("I3C Device Class");break;
	case 0xDC: printk("Diagnostic Device");break;
	case 0xE0: printk("Wireless Controller");break;
	case 0xEF: printk("Miscellaneous");break;
	case 0xFE: printk("Application Specific");break;
	case 0xFF: printk("Vendor specific");break;
	}
	printk("\n");
}

usb_endpoint* getUSBEndpoint(void* info,int type){
	return xhci_get_endpoint(info,type);
}

int usb_send_bulk(void* info,void* buffer,int size){
	return xhci_send_bulk (((USBSocket*)info)->out,buffer,size);
}

int usb_recieve_bulk(void* info,void* buffer,int size){
	return xhci_recieve_bulk (((USBSocket*)info)->in,buffer,size);
}

void usb_register_bulk_endpoints(void* info,usb_endpoint* ep1,usb_endpoint* ep2,void* ring1,void* ring2){
	return xhci_register_bulk_endpoints (info, ep1, ep2, ring1, ring2);
}

uint8_t usb_request_set_config(void *device,uint8_t configid){
	return xhci_request_set_config (((USBSocket*)device)->control, configid);
}

void install_new_usb_device(usb_interface_descriptor* desc,void *info){
	if(desc->bInterfaceClass==USB_IF_MSD){
		install_usb_msd(desc,info);
	}else{
		usb_dump_descriptor(desc);
	}
}
