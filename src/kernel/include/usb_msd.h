#include "usb.h"

typedef struct {
    uint32_t signature;
    uint32_t tag;
    uint32_t data_residue;
    uint8_t status;
} __attribute__ ((packed)) CommandStatusWrapper;

typedef struct {
    uint32_t signature;
    uint32_t tag;
    uint32_t transferlength;
    uint8_t flags;
    uint8_t lun;
    uint8_t command_len;
    uint8_t data[16];
} __attribute__ ((packed)) CommandBlockWrapper;

void install_usb_msd(usb_interface_descriptor* desc,void *data);
