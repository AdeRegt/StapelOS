#include "../include/usb_ehci.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/pci.h"
#include "../include/cpu.h"
#include "../include/interrupts.h"
#include "../include/timer.h"
#include "../include/usb.h"

void *base_ehci_address;

__attribute__((interrupt)) void interrupt_ehci(interrupt_frame* frame){
	printk("ehciint %x \n",EHCI_USBSTS);
    EHCI_USBSTS = EHCI_USBSTS;
	outportb(0xA0,0x20);
	outportb(0x20,0x20);
}

void ehci_dump_hcsparams(){
    printk("HCSPARAMS Structural Parameters\n");
    printk("- N_PORTS                                            : %x \n",EHCI_HCSPARAMS_N_PORTS);
    printk("- Port Power Control (PPC)                           : %x \n",EHCI_HCSPARAMS_PPC);
    printk("- Port Routing Rules                                 : %x \n",EHCI_HCSPARAMS_PRR);
    printk("- Number of Ports per Companion Controller (N_PCC)   : %x \n",EHCI_HCSPARAMS_N_PCC);
    printk("- Number of Companion Controller (N_CC)              : %x \n",EHCI_HCSPARAMS_N_CC);
    printk("- Port Indicators (P_INDICATOR)                      : %x \n",EHCI_HCSPARAMS_P_INDICATOR);
    printk("- Debug Port Number                                  : %x \n",EHCI_HCSPARAMS_DPN);
}

void ehci_dump_hccparams(){
    printk("HCCPARAMS Capability Parameters\n");
    printk("- 64-bit Addressing Capability                       : %x \n",EHCI_HCCPARAMS_64B);
    printk("- Programmable Frame List Flag                       : %x \n",EHCI_HCCPARAMS_PFLF);
    printk("- Asynchronous Schedule Park Capability              : %x \n",EHCI_HCCPARAMS_ASPC);
    printk("- Isochronous Scheduling Threshold                   : %x \n",EHCI_HCCPARAMS_IST);
    printk("- EHCI Extended Capabilities Pointer (EECP)          : %x \n",EHCI_HCCPARAMS_EECP);
}

void ehci_dump_usblegsup(uint32_t reg){
    printk("USBLEGSUP USB Legacy Support Extended Capability %x \n",reg);
}

void ehci_dump_usbcmd(){
    printk("USBCMD USB Command Register \n");
    printk("- Run/Stop (RS)                          : %x \n",EHCI_USBCMD_RS );
    printk("- Host Controller Reset (HCRESET)        : %x \n",EHCI_USBCMD_HCRESET);
    printk("- Frame List Size                        : %x \n",EHCI_USBCMD_FLS);
    printk("- Periodic Schedule Enable               : %x \n",EHCI_USBCMD_PSE);
    printk("- Asynchronous Schedule Enable           : %x \n",EHCI_USBCMD_ASE);
    printk("- Interrupt on Async Advance Doorbell    : %x \n",EHCI_USBCMD_IAAD);
    printk("- Light Host Controller Reset            : %x \n",EHCI_USBCMD_LHCR);
    printk("- Asynchronous Schedule Park Mode Count  : %x \n",EHCI_USBCMD_ASPMC);
    printk("- Asynchronous Schedule Park Mode Enable : %x \n",EHCI_USBCMD_ASPME);
    printk("- Interrupt Threshold Control            : %x \n",EHCI_USBCMD_ITC);
}

void ehci_dump_portsc(int i){
    printk("PORTSC<%d> - Port Status and Control\n",i+1);
    printk("- Current Connect Status                    : %x \n",EHCI_PORTSC_CCS(i));
    printk("- Connect Status Change                     : %x \n",EHCI_PORTSC_CSC(i));
    printk("- Port Enabled/Disabled                     : %x \n",EHCI_PORTSC_PE(i));
    printk("- Port Enable/Disable Change                : %x \n",EHCI_PORTSC_PEC(i));
    printk("- Over-current Active                       : %x \n",EHCI_PORTSC_OA(i));
    printk("- Over-current Change                       : %x \n",EHCI_PORTSC_OC(i));
    printk("- Force Port Resume                         : %x \n",EHCI_PORTSC_FPR(i));
    printk("- Suspend                                   : %x \n",EHCI_PORTSC_Suspend(i));
    printk("- Port Reset                                : %x \n",EHCI_PORTSC_PR(i));
    printk("- Line Status                               : %x \n",EHCI_PORTSC_LS(i));
    printk("- Port Power                                : %x \n",EHCI_PORTSC_PP(i));
    printk("- Port Owner                                : %x \n",EHCI_PORTSC_PO(i));
    printk("- Port Indicator Control                    : %x \n",EHCI_PORTSC_PIC(i));
    printk("- Port Test Control                         : %x \n",EHCI_PORTSC_PTC(i));
    printk("- Wake on Connect Enable (WKCNNT_E)         : %x \n",EHCI_PORTSC_WKCNNT_E(i));
    printk("- Wake on Disconnect Enable (WKDSCNNT_E)    : %x \n",EHCI_PORTSC_WKDSCNNT_E(i));
    printk("- Wake on Over-current Enable (WKOC_E)      : %x \n",EHCI_PORTSC_WKOC_E(i));
}

void ehci_reset_controller(){
    // stop running controller
    if(EHCI_USBCMD_RS){
        printk("ehci is already running!\n");
    }

    // reset controller
    EHCI_USBCMD |= 2;
    sleep(2);
    while(EHCI_USBCMD_HCRESET);
}

void ehci_demand_ownership(uint8_t bus, uint8_t slot, uint8_t func){
    // demand ownership
    uint8_t capreg = EHCI_HCCPARAMS_EECP;
    pciConfigWriteDWord(bus,slot,func,capreg + 0x00, (1<<24));
    while(!(pciConfigReadDWord(bus,slot,func,capreg + 0x00)&(1<<24))){
        sleep(10);
    }
}

EhciTransferDescriptor *ehci_generate_transfer_descriptor(uint32_t nextlink,uint8_t type,uint16_t size,uint8_t toggle,uint32_t data)
{
    EhciTransferDescriptor *command = (EhciTransferDescriptor*) calloc(0x1000);
    command->nextlink = nextlink;
    command->altlink = 1;
    command->token = 0;
    command->token |= (1<<7); // actief
    command->token |= (type<<8); 
    command->token |= (3<<10); // maxerror
    command->token |= (size<<16);
    command->token |= (toggle<<31);
    command->buffer[0] = data;
    return command;
}

EhciQueueHead *ehci_generate_queue_head(uint32_t next_link,uint8_t eps,uint8_t dtc,uint8_t t,uint16_t mplen,uint8_t device,uint32_t capabilities,uint32_t token,uint8_t endpointid)
{
    EhciQueueHead *command = (EhciQueueHead*) calloc(0x1000);
    command->altlink = 1;
    command->nextlink = next_link;
    command->curlink = 0;
    command->characteristics = 0;
    command->characteristics |= (eps<<12);
    command->characteristics |= (dtc<<14);
    command->characteristics |= (t<<15);
    command->characteristics |= (mplen<<16);
    command->characteristics |= (endpointid<<8);
    command->characteristics |= (device);
    command->capabilities = capabilities;
    command->token = token;
    return command;
}

uint8_t ehci_wait_for_completion(volatile EhciTransferDescriptor *status)
{
    uint8_t lstatus = 1;
    while(1)
    {
        sleep(5);
        volatile uint32_t tstatus = (volatile uint32_t)status->token;
        if(tstatus & (1 << 4))
        {
            // not anymore active and failed miserably
            printk("Transmission failed due babble error\n");
            lstatus = 0;
            break;
        }
        if(tstatus & (1 << 3))
        {
            // not anymore active and failed miserably
            printk("Transmission failed due transaction error\n");
            lstatus = 0;
            break;
        }
        if(tstatus & (1 << 6))
        {
            // not anymore active and failed miserably
            printk("Transmission failed due serious error\n");
            lstatus = 0;
            break;
        }
        if(tstatus & (1 << 5))
        {
            // not anymore active and failed miserably
            printk("Transmission failed due data buffer error\n");
            lstatus = 0;
            break;
        }
        if(!(tstatus & (1 << 7)))
        {
            // not anymore active and succesfull ended
            // printk("Transaction succeed\n");
            // printk("\n");
            lstatus = 1;
            break;
        }
    }
    return lstatus;
}

uint8_t ehci_offer_queuehead_to_ring(uint32_t qh,EhciTransferDescriptor *stat)
{
    EHCI_ASYNCLISTADDR = (uint32_t) qh;
    EHCI_USBCMD = EHCI_USBCMD | 0b100000;
    uint8_t res = ehci_wait_for_completion(stat);
    EHCI_USBCMD &= ~0b100000;
    EHCI_ASYNCLISTADDR = 1;
    return res;
}

uint8_t ehci_request_device_addr(uint8_t wantedaddress){
    USBCommand* command = usb_generate_command_structure(USB2_REQUEST_SET_ADDRESS,0,0,0,0,0,wantedaddress);
    EhciTransferDescriptor *status = ehci_generate_transfer_descriptor(1,1,0,1,0);
    EhciTransferDescriptor *transfercommand = ehci_generate_transfer_descriptor((uint32_t)(uint64_t)status,2,8,0,(uint32_t)(uint64_t)command);
    EhciQueueHead *head1 = ehci_generate_queue_head(1,0,0,1,0,0,0,0x40,0);
    EhciQueueHead *head2 = ehci_generate_queue_head((uint32_t)(uint64_t)transfercommand,2,1,0,64,0,0x40000000,0,0);
    head1->horizontal_link_pointer = ((uint32_t)(uint64_t)head2) | 2;
    head2->horizontal_link_pointer = ((uint32_t)(uint64_t)head1) | 2;
    uint8_t res = ehci_offer_queuehead_to_ring((uint32_t)(uint64_t)head1,status);
    free(command);
    free(status);
    free(transfercommand);
    free(head1);
    free(head2);
    return res;
}

void *ehci_request_device_descriptor(uint8_t address,uint8_t type,uint8_t index,uint8_t size)
{
    void *buffer = calloc(0x1000);
    USBCommand *command = usb_generate_command_structure(USB2_REQUEST_GET_DESCRIPTOR,0,4,0,0,size,(type << 8) | index);                                                          // OK
    EhciTransferDescriptor *status = ehci_generate_transfer_descriptor(1,0,0,1,0);                                                                      // OK
    EhciTransferDescriptor *transfercommand = ehci_generate_transfer_descriptor((uint32_t)(uint64_t)status,1,size,1,(uint32_t)(uint64_t)buffer);    // OK
    EhciTransferDescriptor *td = ehci_generate_transfer_descriptor((uint32_t)(uint64_t)transfercommand,2,8,0,(uint32_t)(uint64_t)command);       // OK 8
    EhciQueueHead *head1 = ehci_generate_queue_head(1,0,0,1,0,0,0,0x40,0);
    EhciQueueHead *head2 = ehci_generate_queue_head((uint32_t)(uint64_t)td,2,1,0,64,address,0x40000000,0,0);
    head1->horizontal_link_pointer = ((uint32_t)(uint64_t)head2) | 2;
    head2->horizontal_link_pointer = ((uint32_t)(uint64_t)head1) | 2;
    uint8_t res = ehci_offer_queuehead_to_ring((uint32_t)(uint64_t)head1,status);
    free(command);
    free(status);
    free(transfercommand);
    free(td);
    free(head1);
    free(head2);
    if(res){
        return buffer;
    }else{
        return 0;
    }
}

usb_endpoint* ehci_get_endpoint(USBSocket* info,int type){
    return (usb_endpoint*)(((unsigned long)info->descriptors)+sizeof(usb_config_descriptor)+sizeof(usb_interface_descriptor)+(sizeof(usb_endpoint)*type));
}

void ehci_register_bulk_endpoints(USBSocket* socket,usb_endpoint* ep1,usb_endpoint* ep2,void* ring1,void* ring2){

	USBRing *ringbulkout = (USBRing*) calloc(0x1000);
	ringbulkout->ring = ring1;
	ringbulkout->pointer = 0;
	ringbulkout->stat = 1;
	ringbulkout->doorbelid = ep1->bEndpointAddress;
	ringbulkout->deviceaddr = socket->control->deviceaddr;

	USBRing *ringbulkin = (USBRing*) calloc(0x1000);
	ringbulkin->ring = ring2;
	ringbulkin->pointer = 0;
	ringbulkin->stat = 1;
	ringbulkin->doorbelid = ep2->bEndpointAddress;
	ringbulkin->deviceaddr = socket->control->deviceaddr;

	socket->out = ringbulkout;
	socket->in = ringbulkin;
}

uint8_t ehci_request_set_config(USBRing *device,uint8_t configid){
    USBCommand *command = usb_generate_command_structure(USB2_REQUEST_SET_CONFIGURATION,0,0,0,0,0,configid);
    EhciTransferDescriptor *status = ehci_generate_transfer_descriptor(1,1,0,1,0);
    EhciTransferDescriptor *transfercommand = ehci_generate_transfer_descriptor((uint32_t)(uint64_t)status,2,8,0,(uint32_t)(uint64_t)command);
    EhciQueueHead *head1 = ehci_generate_queue_head(1,0,0,1,0,0,0,0x40,0);
    EhciQueueHead *head2 = ehci_generate_queue_head((uint32_t)(uint64_t)transfercommand,2,1,0,64,device->deviceaddr,0x40000000,0,0);
    head1->horizontal_link_pointer = ((uint32_t)(uint64_t)head2) | 2;
    head2->horizontal_link_pointer = ((uint32_t)(uint64_t)head1) | 2;
    uint8_t res = ehci_offer_queuehead_to_ring((uint32_t)(uint64_t)head1,status);
    free(command);
    free(status);
    free(transfercommand);
    free(head1);
    free(head2);
    return res;
}

uint8_t ehci_send_bulk(USBRing *device,void *data,int size)
{
    EhciTransferDescriptor *status2 = ehci_generate_transfer_descriptor(1,0,0,1,0);
    EhciTransferDescriptor *status = ehci_generate_transfer_descriptor((uint32_t)(uint64_t)status2,0,size,0,(uint32_t)(uint64_t)data);
    EhciQueueHead *head1 = ehci_generate_queue_head(1,0,0,1,0,0,0,0x40,0);
    EhciQueueHead *head2 = ehci_generate_queue_head((uint32_t)(uint64_t)status,2,1,0,512,device->deviceaddr,0x40000000,0,device->doorbelid);
    head1->horizontal_link_pointer = ((uint32_t)(uint64_t)head2) | 2;
    head2->horizontal_link_pointer = ((uint32_t)(uint64_t)head1) | 2;
    uint8_t res = ehci_offer_queuehead_to_ring((uint32_t)(uint64_t)head1,status);
    free(status);
    free(head1);
    free(head2);
    return res;
}

uint8_t ehci_recieve_bulk(USBRing *device,void *command,int size)
{
    EhciTransferDescriptor *status = 0;
    EhciTransferDescriptor *current = 0;
    EhciTransferDescriptor *lastone = 0;
    
    uint32_t pointer = 0;
    uint16_t packagel = 0;
    uint16_t i = 0;
    uint8_t toggle = 1;
    while(1)
    {
        packagel = size-pointer;
        if(packagel>512){
            packagel = 512;
        }
        current = ehci_generate_transfer_descriptor(1,1,packagel,toggle,(uint32_t)(uint64_t)command + pointer);
        if(status==0)
        {
            status = current;
        }
        if(lastone!=0)
        {
            lastone->nextlink = (uint32_t)(uint64_t)current;
        }
        toggle = toggle==0;
        lastone = current;
        pointer += packagel;
        if(pointer==size)
        {
            break;
        }
        i++;
    }

    EhciQueueHead *head1 = ehci_generate_queue_head(1,0,0,1,0,0,0,0x40,0);
    EhciQueueHead *head2 = ehci_generate_queue_head((uint32_t)(uint64_t)status,2,1,0,512,device->deviceaddr,0x40000000,0,device->doorbelid);
    head1->horizontal_link_pointer = ((uint32_t)(uint64_t)head2) | 2;
    head2->horizontal_link_pointer = ((uint32_t)(uint64_t)head1) | 2;
    uint8_t res = ehci_offer_queuehead_to_ring((uint32_t)(uint64_t)head1,status);
    free(status);
    free(head1);
    free(head2);
    if(res==0){
        return 0;
    }else{
        return 1;
    }
}

uint8_t ehci_address_count = 1;

void ehci_probe_port(int i){
    if(!EHCI_PORTSC_CCS(i)){
        return;
    }
    EHCI_PORTSC(i) = EHCI_PORTSC(i);
    EHCI_PORTSC(i) |= (1<<8);
    sleep(3);
    EHCI_PORTSC(i) &= ~ (1<<8);
    sleep(3);

    uint8_t device_address = ehci_address_count++;
    
    // tell system to use our device address
    uint8_t res = ehci_request_device_addr(device_address);
    if(res!=1){
        return;
    }
    // get device desciptors
    void *devicedescriptor = ehci_request_device_descriptor(device_address,USB2_DESCRIPTOR_TYPE_DEVICE,0,8);
    // get config desciptors 
    devicedescriptor = ehci_request_device_descriptor(device_address,USB2_DESCRIPTOR_TYPE_CONFIGURATION,0,sizeof(usb_config_descriptor) + sizeof(usb_interface_descriptor) +(sizeof(usb_endpoint)*2));
    // more device specific data
    USBRing *ringinfo = (USBRing*) calloc(0x1000);
	ringinfo->ring = 0;
	ringinfo->pointer = 0;
	ringinfo->stat = 1;
	ringinfo->doorbelid = 1;
	ringinfo->deviceaddr = device_address;

    usb_interface_descriptor* desc = (usb_interface_descriptor*)(((unsigned long)devicedescriptor)+sizeof(usb_config_descriptor));
	USBSocket *socket = (USBSocket*) calloc(0x1000);
	socket->control = ringinfo;
	socket->dataset = 0;
	socket->descriptors = devicedescriptor;
	socket->usbver = 2;

	install_new_usb_device(desc,socket);
}

void ehci_probe_ports(){
    for(int i = 0 ; i < EHCI_HCSPARAMS_N_PORTS ; i++){
        ehci_probe_port(i);
    }
}

void initialise_ehci(uint8_t bus, uint8_t slot, uint8_t func){
    // get interrupt
	install_interrupt_from_pci(bus,slot,func,interrupt_ehci);

	// get the base address of xhci
	base_ehci_address = 0;
	base_ehci_address += pciConfigReadDWord (bus, slot, func, 0x10) & 0xFFFFFFF0;
    
    ehci_demand_ownership(bus,slot,func);

    ehci_reset_controller();

    // EHCI_USBINTR |= 7;

    EHCI_USBCMD = 1;
    sleep(10);
    EHCI_CONFIGFLAG |= 1;
    sleep(10);
    ehci_probe_ports();
}