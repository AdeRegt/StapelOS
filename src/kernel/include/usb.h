#pragma once
#include <stdint.h>

#define USB_IF_MSD 0x08
#define USB_IF_HID 0x03

typedef struct  {
    uint8_t bRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} USBCommand;

typedef struct __attribute__ ((packed)){
    unsigned char  bLength;
    unsigned char  bDescriptorType;

    unsigned short wTotalLength;
    unsigned char  bNumInterfaces;
    unsigned char  bConfigurationValue;
    unsigned char  iConfiguration;
    unsigned char  bmAttributes;
    unsigned char  bMaxPower;
}usb_config_descriptor ;

typedef struct __attribute__ ((packed)) {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint8_t  bInterfaceNumber;
    uint8_t  bAlternateSetting;
    uint8_t  bNumEndpoints;
    uint8_t  bInterfaceClass;
    uint8_t  bInterfaceSubClass;
    uint8_t  bInterfaceProtocol;
    uint8_t  iInterface;
}usb_interface_descriptor;

typedef struct __attribute__ ((packed)) {
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned char bEndpointAddress;
	unsigned char bmAttributes;
	unsigned short wMaxPacketSize;
  unsigned char udef;
}usb_endpoint;

typedef struct __attribute__ ((packed)) {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t bcdUSB;
  uint8_t bDeviceClass;
  uint8_t bDeviceSubClass;
  uint8_t bDeviceProtocol;
  uint8_t bMaxPacketSize0;
  uint16_t idVendor;
  uint16_t idProduct;
  uint16_t bcdDevice;
  uint8_t iManufacturer;
  uint8_t iProduct;
  uint8_t iSerialNumber;
  uint8_t bNumConfigurations;
}USBStandardDeviceDescriptor;

usb_endpoint* getUSBEndpoint(void* info,int type);
int usb_send_bulk(void* info,void* buffer,int size);
int usb_recieve_bulk(void* info,void* buffer,int size);
void usb_register_bulk_endpoints(void* info,usb_endpoint* ep1,usb_endpoint* ep2,void* ring1,void* ring2);
uint8_t usb_request_set_config(void *device,uint8_t configid);
void install_new_usb_device(usb_interface_descriptor* desc,void *info);
