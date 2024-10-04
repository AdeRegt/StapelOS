#include "../include/string.h"
#include "../include/memory.h"
#include "../include/usb.h"
#include "../include/usb_msd.h"
#include "../include/usb_hid.h"
#include "../include/usb_xhci.h"
#include "../include/usb_ehci.h"

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
	case USB_IF_WIRELESS:
		printk("Wireless Controller :: ");
		switch(desc->bInterfaceSubClass){
		case 1:
			switch(desc->bInterfaceProtocol){
			case 1: printk("Bluetooth Programming Interface");break;
			case 2: printk("UWB Radio Control Interface");break;
			case 3: printk("Remote NDIS");break;
			case 4: printk("Bluetooth AMP Controller");break;
			}
			break;
		case 2:
			switch(desc->bInterfaceProtocol){
			case 1: printk("Host Wire Adapter Control/Data interface");break;
			case 2: printk("Device Wire Adapter Control/Data interface");break;
			case 3: printk("Device Wire Adapter Isochronous interface");break;
			}
			break;
		}
		break;
	case 0xEF: printk("Miscellaneous");break;
	case 0xFE: printk("Application Specific");break;
	case 0xFF: printk("Vendor specific");break;
	}
	printk("\n");
}

void usb_dump_device_descriptor(USBStandardDeviceDescriptor* desc){
	printk("USB Standard Device Descriptor\n");
	printk("- bLength            : %x \n",desc->bLength);
	printk("- bDescriptorType    : %x \n",desc->bDescriptorType);
	printk("- bcdUSB             : %x \n",desc->bcdUSB);
	printk("- bDeviceClass       : %x \n",desc->bDeviceClass);
	printk("- bDeviceSubClass    : %x \n",desc->bDeviceSubClass);
	printk("- bDeviceProtocol    : %x \n",desc->bDeviceProtocol);
	printk("- bMaxPacketSize0    : %x \n",desc->bMaxPacketSize0);
	printk("- idVendor           : %x \n",desc->idVendor);
	printk("- idProduct          : %x \n",desc->idProduct);
	printk("- bcdDevice          : %x \n",desc->bcdDevice);
	printk("- iManufacturer      : %x \n",desc->iManufacturer);
	printk("- iProduct           : %x \n",desc->iProduct);
	printk("- iSerialNumber      : %x \n",desc->iSerialNumber);
	printk("- bNumConfigurations : %x \n",desc->bNumConfigurations);
}

void usb_dump_device_type_from_interface(usb_interface_descriptor* desc){
	printk("interface descriptor\n");
	printk("- %s : %x \n","bLength",desc->bLength);
	printk("- %s : %x \n","bDescriptorType",desc->bDescriptorType);
	printk("- %s : %x \n","bInterfaceNumber",desc->bInterfaceNumber);
	printk("- %s : %x \n","bAlternateSetting",desc->bAlternateSetting);
	printk("- %s : %x \n","bNumEndpoints",desc->bNumEndpoints);
	printk("- %s : %x \n","bInterfaceClass",desc->bInterfaceClass);
	printk("- %s : %x \n","bInterfaceSubClass",desc->bInterfaceSubClass);
	printk("- %s : %x \n","bInterfaceProtocol",desc->bInterfaceProtocol);
	printk("- %s : %x \n","iInterface",desc->iInterface);
}

void usb_dump_device_endpoint(usb_endpoint *dev){
	char* usage_type = "unknown";
	char* synchronisation_type = "unknown";
	char* transfer_type = "unknown";

	if(((dev->bmAttributes>>4)&0b11)==0b00){usage_type="Data endpoint";}
	if(((dev->bmAttributes>>4)&0b11)==0b01){usage_type="Feedback endpoint";}
	if(((dev->bmAttributes>>4)&0b11)==0b10){usage_type="Implicit feedback data endpoint";}
	if(((dev->bmAttributes>>4)&0b11)==0b11){usage_type="Reserved endpoint";}

	if(((dev->bmAttributes>>2)&0b11)==0b00){synchronisation_type="No synchronization";}
	if(((dev->bmAttributes>>2)&0b11)==0b01){synchronisation_type="Asynchronous";}
	if(((dev->bmAttributes>>2)&0b11)==0b10){synchronisation_type="Adaptive";}
	if(((dev->bmAttributes>>2)&0b11)==0b11){synchronisation_type="Synchronous";}

	if(((dev->bmAttributes)&0b11)==0b00){transfer_type="Control";}
	if(((dev->bmAttributes)&0b11)==0b01){transfer_type="Isochronous";}
	if(((dev->bmAttributes)&0b11)==0b10){transfer_type="Bulk";}
	if(((dev->bmAttributes)&0b11)==0b11){transfer_type="Interrupt";}

	printk("interface descriptor endpoint\n");
	printk("- %s : %x \n","bLength",dev->bLength);
	printk("- %s : %x \n","bDescriptorType",dev->bDescriptorType);
	printk("- %s : %x dir:%x num:%x \n","bEndpointAddress",dev->bEndpointAddress,(dev->bEndpointAddress >> 7)&1,dev->bEndpointAddress & 0xF);
	printk("- %s : %x %s %s %s \n","bmAttributes",dev->bmAttributes,usage_type,synchronisation_type,transfer_type);
	printk("- %s : %x \n","wMaxPacketSize",dev->wMaxPacketSize);
}

usb_endpoint* getUSBEndpoint(void* info,int type){
	if(((USBSocket*)info)->usbver==3){
		return xhci_get_endpoint(info,type);
	}else if(((USBSocket*)info)->usbver==2){
		return ehci_get_endpoint(info,type);
	}else{
		printk("called %s but it is not supported!\n",__func__);for(;;);
	}
}

int usb_send_bulk(void* info,void* buffer,int size){
	if(((USBSocket*)info)->usbver==3){
		return xhci_send_bulk (((USBSocket*)info)->out,buffer,size);
	}else if(((USBSocket*)info)->usbver==2){
		return ehci_send_bulk (((USBSocket*)info)->out,buffer,size);
	}else{
		printk("called %s but it is not supported!\n",__func__);for(;;);
	}
}

int usb_recieve_bulk(void* info,void* buffer,int size){
	if(((USBSocket*)info)->usbver==3){
		return xhci_recieve_bulk (((USBSocket*)info)->in,buffer,size);
	}else if(((USBSocket*)info)->usbver==2){
		return ehci_recieve_bulk (((USBSocket*)info)->in,buffer,size);
	}else{
		printk("called %s but it is not supported!\n",__func__);for(;;);
	}
}

uint8_t usb_register_bulk_endpoints(void* info,usb_endpoint* ep1,usb_endpoint* ep2,void* ring1,void* ring2){
	if(((USBSocket*)info)->usbver==3){
		return xhci_register_bulk_endpoints (info, ep1, ep2, ring1, ring2);
	}else if(((USBSocket*)info)->usbver==2){
		return ehci_register_bulk_endpoints (info, ep1, ep2, ring1, ring2);
	}else{
		printk("called %s but it is not supported!\n",__func__);for(;;);
	}
}

uint8_t usb_request_set_config(void *info,uint8_t configid){
	if(((USBSocket*)info)->usbver==3){
		return xhci_request_set_config (((USBSocket*)info)->control, configid);
	}else if(((USBSocket*)info)->usbver==2){
		return ehci_request_set_config (((USBSocket*)info)->control, configid);
	}else{
		printk("called %s but it is not supported!\n",__func__);for(;;);
	}
}

void install_new_usb_device(usb_interface_descriptor* desc,void *info){
	if(desc->bInterfaceClass==USB_IF_MSD){
		install_usb_msd(desc,info);
	}else if(desc->bInterfaceClass==USB_IF_HID){
		install_usb_hid(desc,info);
	}else{
		usb_dump_descriptor(desc);
	}
}

USBCommand *usb_generate_command_structure(uint8_t request, uint8_t dir, uint8_t type, uint8_t recieve, uint16_t windex,uint16_t wlength, uint16_t wvalue)
{
    USBCommand *command = (USBCommand*) calloc(0x1000);
    command->bRequest = request; // set address
    command->bRequestType = 0;
    command->bRequestType |= dir; // dir is out
    command->bRequestType |= (type<<5); // type is standard
    command->bRequestType |= recieve; // recieve 
    command->wIndex = windex; 
    command->wLength = wlength;
    command->wValue = wvalue;
    return command;
}