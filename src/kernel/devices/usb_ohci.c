#include "../include/usb_ohci.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/pci.h"
#include "../include/cpu.h"
#include "../include/interrupts.h"
#include "../include/timer.h"
#include "../include/usb.h"

uint64_t ohci_base_address;
void *hcca;

void ohci_reset(){
    // Reset the OHCI controller by setting the HCR bit in HcCommandStatus
    *(volatile uint32_t *)(ohci_base_address + OHCI_HCCOMMANDSTATUS_OFFSET) = 1;

    // Wait for the HCR bit to clear, indicating that the reset is complete
    while (*(volatile uint32_t *)(ohci_base_address + OHCI_HCCOMMANDSTATUS_OFFSET) & 1);
    
    printk("OHCI controller reset complete\n");
}


void ohci_init_hcca() {
    // Allocate 256 bytes aligned to 256 bytes
    hcca = calloc(0x1000);
    *((volatile uint32_t *)(ohci_base_address + OHCI_HCHCCA_OFFSET)) = (uint32_t) (uint64_t) hcca;
    printk("HCCA allocated at address %x\n", hcca);


}

void ohci_disable_interrupts() {
    *((volatile uint32_t *)(ohci_base_address + OHCI_HCINTERRUPTDISABLE_OFFSET)) = 0xFFFFFFFF;
}

void ohci_set_operational() {
    uint32_t hccontrol = 0;
    hccontrol |= OHCI_CONTROL_CBSR_1_1;
    hccontrol |= OHCI_CONTROL_CLE; // Enable control list
    hccontrol |= OHCI_CONTROL_BLE; // Enable bulk list
    hccontrol |= OHCI_CONTROL_PLE; // Enable periodic list
    hccontrol |= OHCI_CONTROL_HCFS_OPERATIONAL; // Set to operational state

    *((volatile uint32_t *)(ohci_base_address + OHCI_HCCONTROL_OFFSET)) = hccontrol;
    printk("OHCI controller set to operational state\n");
    ohci_disable_interrupts();
}

OHCIEndpointDescriptor *ohci_create_endpoint_descriptor(uint32_t control, uint32_t tail_td, uint32_t head_td, uint32_t next_ed) {
    OHCIEndpointDescriptor *ed = (OHCIEndpointDescriptor *)calloc(0x1000);
    ed->control = control;
    ed->tail_td = tail_td;
    ed->head_td = head_td;
    ed->next_ed = next_ed;
    return ed;
}

OHCITansferDescriptor *ohci_create_transfer_descriptor(uint32_t control, uint32_t curr_buffer_ptr, uint32_t next_td, uint32_t buffer_end) {
    OHCITansferDescriptor *td = (OHCITansferDescriptor *)calloc(0x1000);
    td->control = control;
    td->curr_buffer_ptr = curr_buffer_ptr;
    td->next_td = next_td;
    td->buffer_end = buffer_end;
    return td;
}

__attribute__((interrupt)) void interrupt_ohci(interrupt_frame* frame){
	printk("ohciint\n");
}

void ohci_bus_reset() {
    // Set Port Reset Status (PRS) bit
    *((volatile uint32_t *)(ohci_base_address + OHCI_HCRHPORTSTATUS_OFFSET)) = OHCI_RH_PORT_RESET;

    // Wait for reset to complete (PRS bit clears)
    while (*((volatile uint32_t *)(ohci_base_address + OHCI_HCRHPORTSTATUS_OFFSET)) & OHCI_RH_PORT_RESET);

    printk("USB bus reset complete\n");
}

uint32_t ohci_read_port_status(uint32_t i) {
    return *((volatile uint32_t *)(ohci_base_address + OHCI_HCRHPORTSTATUS_OFFSET + (4*i)));
}

void ohci_write_port_status(uint32_t i,uint32_t value) {
    *((volatile uint32_t *)(ohci_base_address + OHCI_HCRHPORTSTATUS_OFFSET + (4*i))) = value;
}

int ohci_is_operational() {
    uint32_t hccontrol = *((volatile uint32_t *)(ohci_base_address + OHCI_HCCONTROL_OFFSET));
    return (hccontrol & OHCI_HCFS_MASK) == OHCI_HCFS_OPERATIONAL;
}

void wait_for_transfer_complete(OHCITansferDescriptor *last_td) {
    // Wait for the DoneHead in HCCA to point to our last TD
    volatile uint32_t *done_head = &((volatile uint32_t *)hcca)[1]; // DoneHead is at offset 4 in HCCA
    printk("Waiting for transfer to complete... done_head:%x last_td:%x epiloog: %x oper: %d \n", done_head, last_td,((volatile uint32_t *)hcca)[1],ohci_is_operational());
    while (*done_head != (uint32_t)(uint64_t)last_td) {
        // Optionally add a timeout or yield/sleep here
        // printk("Waiting for transfer to complete... %x %x \n",done_head, last_td);
        done_head = &((volatile uint32_t *)hcca)[1]; // DoneHead is at offset 4 in HCCA
    }

    // Optionally, check the condition code in the TD
    if ((last_td->control & 0xF) != 0) { // Condition code is lowest 4 bits
        printk("Transfer failed, condition code: %x\n", last_td->control & 0xF);
    } else {
        printk("Transfer completed successfully\n");
    }
}

void setup_control_transfer_for_get_descriptor(){

    // Example buffer for device descriptor (should be at least 18 bytes)
    uint8_t device_desc_buf[18] = {0};

    // 1. Prepare setup packet
    USBCommand *setup = (USBCommand *)calloc(0x1000);
    setup->bRequestType  = 0x80; // Device-to-host, Standard, Device
    setup->bRequest      = 0x06; // GET_DESCRIPTOR
    setup->wValue        = 0x0100; // Descriptor Type (Device) << 8 | Descriptor Index (0)
    setup->wIndex        = 0x0000;
    setup->wLength       = 18;    // Device descriptor size

    // 2. Allocate and initialize TDs for setup, data, and status stages
    OHCITansferDescriptor *td_setup = ohci_create_transfer_descriptor(
        /*control=*/0x00000000, // SETUP PID, etc. (fill as needed)
        /*curr_buffer_ptr=*/(uint32_t)(uint64_t)setup,
        /*next_td=*/0,
        /*buffer_end=*/(uint32_t)(uint64_t)setup + sizeof( USBCommand) - 1
    );

    OHCITansferDescriptor *td_data = ohci_create_transfer_descriptor(
        /*control=*/0x00000000, // IN PID, etc. (fill as needed)
        /*curr_buffer_ptr=*/(uint32_t)(uint64_t)device_desc_buf,
        /*next_td=*/0,
        /*buffer_end=*/(uint32_t)(uint64_t)device_desc_buf + 17
    );

    OHCITansferDescriptor *td_status = ohci_create_transfer_descriptor(
        /*control=*/0x00000000, // OUT PID, etc. (fill as needed)
        /*curr_buffer_ptr=*/0,
        /*next_td=*/0,
        /*buffer_end=*/0
    );

    // Link the TDs
    td_setup->next_td = (uint32_t)(uint64_t)td_data;
    td_data->next_td = (uint32_t)(uint64_t)td_status;
    td_status->next_td = 0;

    // 3. Create an ED for endpoint 0
    uint32_t ed_control = ED_CONTROL_FA(0) | ED_CONTROL_EN(0) | ED_CONTROL_D(2) | ED_CONTROL_S | ED_CONTROL_K | ED_CONTROL_F | ED_CONTROL_MPS(8);
    OHCIEndpointDescriptor *ed = ohci_create_endpoint_descriptor(
        ed_control,
        (uint32_t)(uint64_t)td_status, // Tail points to dummy/status TD
        (uint32_t)(uint64_t)td_setup,  // Head points to first TD
        0
    );

    // 4. Set HcControlHeadED to the ED
    *((volatile uint32_t *)(ohci_base_address + OHCI_HCCONTROLHEADED_OFFSET)) = (uint32_t)(uint64_t)ed;

    // 5. The controller will now process the control transfer when the control list is enabled and the controller is operational.
    //    You should poll for completion or handle it in your interrupt handler by checking the DoneHead in the HCCA.
    sleep(5);
    printk("setup %x data %x status %x ed %x\n",
           td_setup, td_data, td_status, ed);
    wait_for_transfer_complete(td_status);
}


void initialise_ohci(uint8_t bus, uint8_t slot, uint8_t func){
    printk("initialising ohci controller\n");
    printk("pci bus %d slot %d func %d\n",bus,slot,func);
    ohci_base_address = pciConfigReadDWord(bus, slot, func, 0x10);
    printk("base address %x\n",ohci_base_address);

	// enable busmastering if needed
	pci_enable_busmastering(bus, slot, func);

    install_interrupt_from_pci(bus,slot,func,interrupt_ohci);

    ohci_reset();
    ohci_init_hcca();

    uint32_t control = ED_CONTROL_FA(0) | ED_CONTROL_EN(0) | ED_CONTROL_D(2) | ED_CONTROL_S | (1 << 14) | ED_CONTROL_F | ED_CONTROL_MPS(8);
    OHCITansferDescriptor *dummy_td = ohci_create_transfer_descriptor(0, 0, 0, 0);
    OHCIEndpointDescriptor *ed = ohci_create_endpoint_descriptor(control, (uint32_t) (uint64_t) dummy_td, (uint32_t) (uint64_t) dummy_td, 0);
    *((volatile uint32_t *)(ohci_base_address + OHCI_HCCONTROLHEADED_OFFSET)) = (uint32_t) (uint64_t) (ed);
    printk("control %x\n",dummy_td);
    ohci_set_operational();
    ohci_bus_reset();

    // while (!(ohci_read_port_status(0) & PORT_CONNECTION_BIT)) {}

    if (!(ohci_read_port_status(0) & PORT_ENABLE_BIT)) {
        printk("Enabling port 0\n");
        ohci_write_port_status(0,PORT_ENABLE_BIT);
    }

    setup_control_transfer_for_get_descriptor();
}
