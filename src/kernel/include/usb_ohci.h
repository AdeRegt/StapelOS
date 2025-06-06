#pragma once
#include <stdint.h>
#include "usb.h"

#define OHCI_HCCOMMANDSTATUS_OFFSET 0x08
#define OHCI_HCCONTROL_OFFSET 0x04
#define OHCI_HCHCCA_OFFSET 0x18
#define OHCI_HCCONTROLHEADED_OFFSET 0x20
#define OHCI_HCRHPORTSTATUS_OFFSET 0x54
#define OHCI_HCINTERRUPTDISABLE_OFFSET 0x14

#define OHCI_HCFS_MASK        (3 << 6)
#define OHCI_HCFS_OPERATIONAL (2 << 6)


#define OHCI_CONTROL_CBSR_1_1      (0x0 << 0) // Control/Bulk Service Ratio 1:1
#define OHCI_CONTROL_PLE           (1 << 2)   // Periodic List Enable
#define OHCI_CONTROL_CLE           (1 << 4)   // Control List Enable
#define OHCI_CONTROL_BLE           (1 << 5)   // Bulk List Enable
#define OHCI_CONTROL_HCFS_OPERATIONAL (0x2 << 6) // Host Controller Functional State: Operational

#define OHCI_RH_PORT_RESET        (1 << 4)

#define ED_CONTROL_FA(addr)      ((addr & 0x7F) << 0)   // Function Address
#define ED_CONTROL_EN(ep)        ((ep & 0xF) << 7)      // Endpoint Number
#define ED_CONTROL_D(dir)        ((dir & 0x3) << 11)    // Direction (0=OUT, 1=IN, 2=From TD)
#define ED_CONTROL_S             (0 << 13)              // Speed (0=Full, 1=Low)
#define ED_CONTROL_K             (0 << 14)              // Skip (0=Active, 1=Skip)
#define ED_CONTROL_F             (0 << 15)              // Format (0=Control, 1=Isochronous)
#define ED_CONTROL_MPS(mps)      ((mps & 0x7FF) << 16)  // Max Packet Size

#define PORT_CONNECTION_BIT 0x00000001
#define PORT_ENABLE_BIT 0x00000002

typedef struct{
    uint32_t control;
    uint32_t tail_td;
    uint32_t head_td;
    uint32_t next_ed;
} OHCIEndpointDescriptor;

typedef struct {
    uint32_t control;
    uint32_t curr_buffer_ptr;
    uint32_t next_td;
    uint32_t buffer_end;
} OHCITansferDescriptor;

void initialise_ohci(uint8_t bus, uint8_t slot, uint8_t func);