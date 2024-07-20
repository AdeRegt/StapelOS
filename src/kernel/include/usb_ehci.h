#pragma once
#include <stdint.h>
#include "usb.h"

#define EHCI_CAPLENGTH ((uint8_t*)( base_ehci_address + 0x00))[0]
#define EHCI_HCIVERSION ((uint16_t*)( base_ehci_address + 0x02))[0]
#define EHCI_HCSPARAMS ((uint32_t*)( base_ehci_address + 0x04))[0]
#define EHCI_HCSPARAMS_N_PORTS      ( ( EHCI_HCSPARAMS & 0b00000000000000000000000000001111 ) >> 0 )
#define EHCI_HCSPARAMS_PPC          ( ( EHCI_HCSPARAMS & 0b00000000000000000000000000010000 ) >> 4 )
#define EHCI_HCSPARAMS_PRR          ( ( EHCI_HCSPARAMS & 0b00000000000000000000000010000000 ) >> 7 )
#define EHCI_HCSPARAMS_N_PCC        ( ( EHCI_HCSPARAMS & 0b00000000000000000000111100000000 ) >> 8 )
#define EHCI_HCSPARAMS_N_CC         ( ( EHCI_HCSPARAMS & 0b00000000000000001111000000000000 ) >> 12 )
#define EHCI_HCSPARAMS_P_INDICATOR  ( ( EHCI_HCSPARAMS & 0b00000000000000010000000000000000 ) >> 16 )
#define EHCI_HCSPARAMS_DPN          ( ( EHCI_HCSPARAMS & 0b00000000111100000000000000000000 ) >> 20 )
#define EHCI_HCCPARAMS ((uint32_t*)( base_ehci_address + 0x08))[0]
#define EHCI_HCCPARAMS_64B          ( ( EHCI_HCCPARAMS & 0b00000000000000000000000000000001 ) >> 0 )
#define EHCI_HCCPARAMS_PFLF         ( ( EHCI_HCCPARAMS & 0b00000000000000000000000000000010 ) >> 1 )
#define EHCI_HCCPARAMS_ASPC         ( ( EHCI_HCCPARAMS & 0b00000000000000000000000000000100 ) >> 2 )
#define EHCI_HCCPARAMS_IST          ( ( EHCI_HCCPARAMS & 0b00000000000000000000000011110000 ) >> 4 )
#define EHCI_HCCPARAMS_EECP         ( ( EHCI_HCCPARAMS & 0b00000000000000001111111100000000 ) >> 8 )
#define EHCI_USBCMD ((uint32_t*)( base_ehci_address + EHCI_CAPLENGTH + 0))[0]
#define EHCI_USBCMD_RS              ( ( EHCI_USBCMD & 0b00000000000000000000000000000001 ) >> 0 )
#define EHCI_USBCMD_HCRESET         ( ( EHCI_USBCMD & 0b00000000000000000000000000000010 ) >> 1 )
#define EHCI_USBCMD_FLS             ( ( EHCI_USBCMD & 0b00000000000000000000000000001100 ) >> 2 )
#define EHCI_USBCMD_PSE             ( ( EHCI_USBCMD & 0b00000000000000000000000000010000 ) >> 4 )
#define EHCI_USBCMD_ASE             ( ( EHCI_USBCMD & 0b00000000000000000000000000100000 ) >> 5 )
#define EHCI_USBCMD_IAAD            ( ( EHCI_USBCMD & 0b00000000000000000000000001000000 ) >> 6 )
#define EHCI_USBCMD_LHCR            ( ( EHCI_USBCMD & 0b00000000000000000000000010000000 ) >> 7 )
#define EHCI_USBCMD_ASPMC           ( ( EHCI_USBCMD & 0b00000000000000000000001100000000 ) >> 8 )
#define EHCI_USBCMD_ASPME           ( ( EHCI_USBCMD & 0b00000000000000000000010000000000 ) >> 11 )
#define EHCI_USBCMD_ITC             ( ( EHCI_USBCMD & 0b00000000011111111000000000000000 ) >> 16 )
#define EHCI_USBSTS ((uint32_t*)( base_ehci_address + EHCI_CAPLENGTH + 0x04 ))[0]
#define EHCI_USBSTS_USBINT          ( ( EHCI_USBSTS & 0b00000000000000000000000000000001 ) >> 00 )
#define EHCI_USBSTS_USBERRINT       ( ( EHCI_USBSTS & 0b00000000000000000000000000000010 ) >> 01 )
#define EHCI_USBSTS_PCD             ( ( EHCI_USBSTS & 0b00000000000000000000000000000100 ) >> 02 )
#define EHCI_USBSTS_FLR             ( ( EHCI_USBSTS & 0b00000000000000000000000000001000 ) >> 03 )
#define EHCI_USBSTS_HSE             ( ( EHCI_USBSTS & 0b00000000000000000000000000010000 ) >> 04 )
#define EHCI_USBSTS_IAA             ( ( EHCI_USBSTS & 0b00000000000000000000000000100000 ) >> 05 )
#define EHCI_USBSTS_HCHalted        ( ( EHCI_USBSTS & 0b00000000000000000001000000000000 ) >> 12 )
#define EHCI_USBSTS_Reclamation     ( ( EHCI_USBSTS & 0b00000000000000000010000000000000 ) >> 13 )
#define EHCI_USBSTS_PSS             ( ( EHCI_USBSTS & 0b00000000000000000100000000000000 ) >> 14 )
#define EHCI_USBSTS_ASS             ( ( EHCI_USBSTS & 0b00000000000000001000000000000000 ) >> 15 )
#define EHCI_USBINTR ((uint32_t*)( base_ehci_address + EHCI_CAPLENGTH + 0x08 ))[0]
#define EHCI_PERIODICLISTBASE ((uint32_t*)( base_ehci_address + EHCI_CAPLENGTH + 0x14 ))[0]
#define EHCI_ASYNCLISTADDR ((uint32_t*)( base_ehci_address + EHCI_CAPLENGTH + 0x18 ))[0]
#define EHCI_CONFIGFLAG ((uint32_t*)( base_ehci_address + EHCI_CAPLENGTH + 0x40 ))[0]
#define EHCI_PORTSC(i) ((uint32_t*)( base_ehci_address + EHCI_CAPLENGTH + 0x44 + (4*i) ))[0]
#define EHCI_PORTSC_CCS(i)         ( ( EHCI_PORTSC(i) & 0b00000000000000000000000000000001 ) >> 00 )
#define EHCI_PORTSC_CSC(i)         ( ( EHCI_PORTSC(i) & 0b00000000000000000000000000000010 ) >> 01 )
#define EHCI_PORTSC_PE(i)          ( ( EHCI_PORTSC(i) & 0b00000000000000000000000000000100 ) >> 02 )
#define EHCI_PORTSC_PEC(i)         ( ( EHCI_PORTSC(i) & 0b00000000000000000000000000001000 ) >> 03 )
#define EHCI_PORTSC_OA(i)          ( ( EHCI_PORTSC(i) & 0b00000000000000000000000000010000 ) >> 04 )
#define EHCI_PORTSC_OC(i)          ( ( EHCI_PORTSC(i) & 0b00000000000000000000000000100000 ) >> 05 )
#define EHCI_PORTSC_FPR(i)         ( ( EHCI_PORTSC(i) & 0b00000000000000000000000001000000 ) >> 06 )
#define EHCI_PORTSC_Suspend(i)     ( ( EHCI_PORTSC(i) & 0b00000000000000000000000010000000 ) >> 07 )
#define EHCI_PORTSC_PR(i)          ( ( EHCI_PORTSC(i) & 0b00000000000000000000000100000000 ) >> 8 )
#define EHCI_PORTSC_LS(i)          ( ( EHCI_PORTSC(i) & 0b00000000000000000000110000000000 ) >> 10 )
#define EHCI_PORTSC_PP(i)          ( ( EHCI_PORTSC(i) & 0b00000000000000000001000000000000 ) >> 12 )
#define EHCI_PORTSC_PO(i)          ( ( EHCI_PORTSC(i) & 0b00000000000000000010000000000000 ) >> 13 )
#define EHCI_PORTSC_PIC(i)         ( ( EHCI_PORTSC(i) & 0b00000000000000001100000000000000 ) >> 14 )
#define EHCI_PORTSC_PTC(i)         ( ( EHCI_PORTSC(i) & 0b00000000000011110000000000000000 ) >> 16 )
#define EHCI_PORTSC_WKCNNT_E(i)    ( ( EHCI_PORTSC(i) & 0b00000000000100000000000000000000 ) >> 20 )
#define EHCI_PORTSC_WKDSCNNT_E(i)  ( ( EHCI_PORTSC(i) & 0b00000000001000000000000000000000 ) >> 21 )
#define EHCI_PORTSC_WKOC_E(i)      ( ( EHCI_PORTSC(i) & 0b00000000010000000000000000000000 ) >> 22 )

#define EHCI_PCI_INFO_REG           0x60
#define EHCI_PROTOCOL_VER           0x20
#define EHCI_HCI_VER                0x100
#define EHCI_PERIODIC_FRAME_SIZE    1024

typedef struct __attribute__ ((packed)) {
    uint32_t nextlink;
    uint32_t altlink;
    uint32_t token;
    uint32_t buffer[5];
    uint32_t extbuffer[5];
} EhciTransferDescriptor;

typedef struct __attribute__ ((packed)) {
    uint32_t horizontal_link_pointer;
    uint32_t characteristics;
    uint32_t capabilities;
    uint32_t curlink;

    uint32_t nextlink;
    uint32_t altlink;
    uint32_t token;
    uint32_t buffer[5];
    uint32_t extbuffer[5];
}EhciQueueHead;

void initialise_ehci(uint8_t bus, uint8_t slot, uint8_t func);
usb_endpoint* ehci_get_endpoint(USBSocket* info,int type);
void ehci_register_bulk_endpoints(USBSocket* socket,usb_endpoint* ep1,usb_endpoint* ep2,void* ring1,void* ring2);
uint8_t ehci_request_set_config(USBRing *device,uint8_t configid);
uint8_t ehci_send_bulk(USBRing *device,void *data,int size);
uint8_t ehci_recieve_bulk(USBRing *device,void *data,int size);