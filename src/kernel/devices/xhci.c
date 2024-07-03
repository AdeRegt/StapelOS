#include "../include/xhci.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/pci.h"
#include "../include/cpu.h"
#include "../include/interrupts.h"
#include "../include/timer.h"
#include "../include/usb.h"

void *base_xhci_address;
void* dcbaap_items;
void *commandring;
void *eventring;
int command_ring_pointer;

__attribute__((interrupt)) void interrupt_xhci(interrupt_frame* frame){
	printk("xhciint %x \n",USBSTS);
	IMAN(0) = 3;
	USBSTS = USBSTS;
	outportb(0xA0,0x20);
	outportb(0x20,0x20);
}

void xhci_dump_caplength(){
	printk("Capability Registers Length (CAPLENGTH) : %x \n",CAPLENGTH);
}

void xhci_dump_hciversion(){
	printk("Host Controller Interface Version Number (HCIVERSION) : %x \n",HCIVERSION);
}

void xhci_dump_hcsparams1(){
	printk("Structural Parameters 1 (HCSPARAMS1) : %x \n",HCSPARAMS1);
	printk("- Number of Device Slots (MaxSlots)  : %x \n",HCSPARAMS1_MaxSlots);
	printk("- Number of Interrupters (MaxIntrs)  : %x \n",HCSPARAMS1_MaxIntrs);
	printk("- Number of Ports (MaxPorts)         : %x \n",HCSPARAMS1_MaxPorts);
}

void xhci_dump_hcsparams2(){
	printk("Structural Parameters 2 (HCSPARAMS2)             : %x \n",HCSPARAMS2);
	printk("- Isochronous Scheduling Threshold (IST)         : %x \n",HCSPARAMS2_IST);
	printk("- Event Ring Segment Table Max (ERST Max)        : %x \n",HCSPARAMS2_ERST_Max);
	printk("- Max Scratchpad Buffers (Max Scratchpad Bufs Hi): %x \n",HCSPARAMS2_Scratchpad_Bufs_Hi);
	printk("- Scratchpad Restore (SPR)                       : %x \n",HCSPARAMS2_SPR);
	printk("- Max Scratchpad Buffers (Max Scratchpad Bufs Lo): %x \n",HCSPARAMS2_Scratchpad_Bufs_Lo);
}

void xhci_dump_hcsparams3(){
	printk("Structural Parameters 3 (HCSPARAMS3) : %x \n",HCSPARAMS3);
	printk("- U1 Device Exit Latency             : %x \n",HCSPARAMS3_U1);
	printk("- U2 Device Exit Latency             : %x \n",HCSPARAMS3_U2);
}

void xhci_dump_hccparams1(){
	printk("Capability Parameters 1 (HCCPARAMS1)             : %x \n",HCCPARAMS1);
	printk("- 64-bit Addressing Capability (AC64)            : %s\n",(HCCPARAMS1_AC64)?"yes":"no");
	printk("- BW Negotiation Capability (BNC)                : %s\n",(HCCPARAMS1_BNC)?"yes":"no");
	printk("- Context Size (CSZ)                             : %s\n",(HCCPARAMS1_CSZ)?"yes":"no");
	printk("- Port Power Control (PPC)                       : %s\n",(HCCPARAMS1_PPC)?"yes":"no");
	printk("- Port Indicators (PIND)                         : %s\n",(HCCPARAMS1_PIND)?"yes":"no");
	printk("- Light HC Reset Capability (LHRC)               : %s\n",(HCCPARAMS1_LHRC)?"yes":"no");
	printk("- Latency Tolerance Messaging Capability (LTC)   : %s\n",(HCCPARAMS1_LTC)?"yes":"no");
	printk("- No Secondary SID Support (NSS)                 : %s\n",(HCCPARAMS1_NSS)?"yes":"no");
	printk("- Parse All Event Data (PAE)                     : %s\n",(HCCPARAMS1_PAE)?"yes":"no");
	printk("- Stopped - Short Packet Capability (SPC)        : %s\n",(HCCPARAMS1_SPC)?"yes":"no");
	printk("- Stopped EDTLA Capability (SEC)                 : %s\n",(HCCPARAMS1_SEC)?"yes":"no");
	printk("- Contiguous Frame ID Capability (CFC)           : %s\n",(HCCPARAMS1_CFC)?"yes":"no");
	printk("- Maximum Primary Stream Array Size (MaxPSASize) : %x\n",HCCPARAMS1_MaxPSASize);
	printk("- xHCI Extended Capabilities Pointer (xECP)      : %x\n",HCCPARAMS1_xECP);
}

void xhci_dump_dboff(){
	printk("Doorbell Offset (DBOFF) : %x \n",DBOFF);
}

void xhci_dump_rtsoff(){
	printk("Runtime Register Space Offset (RTSOFF) : %x \n",RTSOFF);
}

void xhci_dump_capability_registers(){
	// see page 381 of specification
	printk("---XHCI Capability Registers---\n");
	xhci_dump_caplength();
	xhci_dump_hciversion();
	xhci_dump_hcsparams1();
	xhci_dump_hcsparams2();
	xhci_dump_hcsparams3();
	xhci_dump_hccparams1();
	xhci_dump_dboff();
	xhci_dump_rtsoff();
	// printk("Capability Parameters 2 (HCCPARAMS2) : %x \n",HCCPARAMS2);
	// printk("Virtualization Based Trusted IO Register Space Offset (VTIOSOFF) : %x \n",VTIOSOFF);
}

void xhci_dump_usbcmd(){
	printk("USB Command Register (USBCMD)             : %x \n",USBCMD);
	printk("- Run/Stop (R/S)                          : %s \n",USBCMD_RS?"yes":"no");
	printk("- Host Controller Reset (HCRST)           : %s \n",USBCMD_HCRST?"yes":"no");
	printk("- Interrupter Enable (INTE)               : %s \n",USBCMD_INTE?"yes":"no");
	printk("- Host System Error Enable (HSEE)         : %s \n",USBCMD_HSEE?"yes":"no");
	printk("- Light Host Controller Reset (LHCRST)    : %s \n",USBCMD_LHCRST?"yes":"no");
	printk("- Controller Save State (CSS)             : %s \n",USBCMD_CSS?"yes":"no");
	printk("- Controller Restore State (CRS)          : %s \n",USBCMD_CRS?"yes":"no");
	printk("- Enable Wrap Event (EWE)                 : %s \n",USBCMD_EWE?"yes":"no");
	printk("- Enable U3 MFINDEX Stop (EU3S)           : %s \n",USBCMD_EU3S?"yes":"no");
	printk("- CEM Enable (CME)                        : %s \n",USBCMD_CME?"yes":"no");
	printk("- Extended TBC Enable (ETE)               : %s \n",USBCMD_ETE?"yes":"no");
	printk("- Extended TBC TRB Status Enable (TSC_EN) : %s \n",USBCMD_TSC_EN?"yes":"no");
	printk("- VTIO Enable (VTIOE)                     : %s \n",USBCMD_VTIOE?"yes":"no");
}

void xhci_dump_usbsts(){
	printk("USB Command Register (USBSTS) : %x \n",USBSTS);
	printk("- HCHalted (HCH)              : %s \n",USBSTS_HCH?"yes":"no");
	printk("- Host System Error (HSE)     : %s \n",USBSTS_HSE?"yes":"no");
	printk("- Event Interrupt (EINT)      : %s \n",USBSTS_EINT?"yes":"no");
	printk("- Port Change Detect (PCD)    : %s \n",USBSTS_PCD?"yes":"no");
	printk("- Save State Status (SSS)     : %s \n",USBSTS_SSS?"yes":"no");
	printk("- Restore State Status (RSS)  : %s \n",USBSTS_RSS?"yes":"no");
	printk("- Save/Restore Error (SRE)    : %s \n",USBSTS_SRE?"yes":"no");
	printk("- Controller Not Ready (CNR)  : %s \n",USBSTS_CNR?"yes":"no");
	printk("- Host Controller Error (HCE) : %s \n",USBSTS_HCE?"yes":"no");
}

void xhci_dump_page_size(){
	printk("Page Size Register (PAGESIZE) : %x \n",PAGESIZE);
}

void xhci_dump_device_notification_control_register(){
	printk("Device Notification Control Register (DNCTRL) : %x \n",DNCTRL);
}

void xhci_dump_config(){
	printk("Configure Register (CONFIG) : %x \n",CONFIG);
}

void xhci_dump_operational_registers(){
	printk("--XHCI Operational Registers---\n");
	xhci_dump_usbcmd();
	xhci_dump_usbsts();
	xhci_dump_page_size();
	xhci_dump_device_notification_control_register();
	xhci_dump_config();
}

void xhci_dump_ports(){
	for(int i = 0 ; i < HCSPARAMS1_MaxPorts ;i++){
		printk("device %d : %x \n",i,PORTSC(i));
	}
}

void xhci_dump_slot_context(XHCISlotContext* slot){
	printk("RouteString       : %x \n",slot->RouteString);
	printk("Speed             : %x \n",slot->Speed);
	printk("MTT               : %x \n",slot->MTT);
	printk("Hub               : %x \n",slot->Hub);
	printk("ContextEntries    : %x \n",slot->ContextEntries);
	printk("MaxExitLatency    : %x \n",slot->MaxExitLatency);
	printk("RootHubPortNumber : %x \n",slot->RootHubPortNumber);
	printk("NumberOfPorts     : %x \n",slot->NumberOfPorts);
	printk("ParentHubSlotID   : %x \n",slot->ParentHubSlotID);
	printk("ParentPortNumber  : %x \n",slot->ParentPortNumber);
	printk("TTT               : %x \n",slot->TTT);
	printk("InterrupterTarget : %x \n",slot->InterrupterTarget);
	printk("USBDeviceAddress  : %x \n",slot->USBDeviceAddress);
	printk("SlotState         : %x \n",slot->SlotState);
}

char* xhci_get_port_link_state(int n){
	int i = PORTSC_PLS(n);
	if(i == XHCI_PORT_LINK_U0){
		return "Link is in the U0 State";
	}
	if(i == XHCI_PORT_LINK_U1){
		return "Link is in the U1 State";
	}
	if(i == XHCI_PORT_LINK_U2){
		return "Link is in the U2 State";
	}
	if(i == XHCI_PORT_LINK_U3){
		return "Link is in the U3 State (Device Suspended)";
	}
	if(i == XHCI_PORT_LINK_DISABLED){
		return "Link is in the Disabled State";
	}
	if(i == XHCI_PORT_LINK_RXDETECT){
		return "Link is in the RxDetect State";
	}
	if(i == XHCI_PORT_LINK_INACTIVE_STATE){
		return "Link is in the Inactive State";
	}
	if(i == XHCI_PORT_LINK_POLLING_STATE){
		return "Link is in the Polling State";
	}
	if(i == XHCI_PORT_LINK_RECOVERY_STATE){
		return "Link is in the Recovery State";
	}
	if(i == XHCI_PORT_LINK_HOT_RESET_STATE){
		return "Link is in the Hot Reset State";
	}
	if(i == XHCI_PORT_LINK_COMPLIANCE_MODE_STATE){
		return "Link is in the Compliance Mode State";
	}
	if(i == XHCI_PORT_LINK_TEST_STATE){
		return "Link is in the Test Mode89 State";
	}
	if(i == XHCI_PORT_LINK_RESUME_STATE){
		return "Link is in the Resume State";
	}
	return "unknown";
}

char* xhci_get_port_speed(int n){
	if(PORTSC_Port_Speed (n) == XHCI_SPEED_SUPER){
		return "Superspeed";
	}else if(PORTSC_Port_Speed (n) == XHCI_SPEED_FULL){
		return "Fullspeed";
	}else if(PORTSC_Port_Speed (n) == XHCI_SPEED_LOW){
		return "Lowspeed";
	}else if(PORTSC_Port_Speed (n) == XHCI_SPEED_HI){
		return "Hispeed";
	}
	return "Unknown";
}

void xhci_dump_usbport(int n){
	printk("Port Status and Control Register (PORTSC) : %x \n",PORTSC(n));
	printk("- Current Connect Status (CCS)       : %x \n",PORTSC_CCS(n));
	printk("- Port Enabled/Disabled (PED)        : %x \n",PORTSC_PED(n));
	printk("- Over-current Active (OCA)          : %x \n",PORTSC_OCA(n));
	printk("- Port Reset (PR)                    : %x \n",PORTSC_PR(n));
	printk("- Port Link State (PLS)              : %s \n",xhci_get_port_link_state(n));
	printk("- Port Power (PP)                    : %x \n",PORTSC_PP(n));
	printk("- Port Speed (Port Speed)            : %s \n",xhci_get_port_speed(n));
	printk("- Port Indicator Control (PIC)       : %x \n",PORTSC_PIC(n));
	printk("- Port Link State Write Strobe (LWS) : %x \n",PORTSC_LWS(n));
	printk("- Connect Status Change (CSC)        : %x \n",PORTSC_CSC(n));
	printk("- Port Enabled/Disabled Change (PEC) : %x \n",PORTSC_PEC(n));
	printk("- Warm Port Reset Change (WRC)       : %x \n",PORTSC_WRC(n));
	printk("- Over-current Change (OCC)          : %x \n",PORTSC_OCC(n));
	printk("- Port Reset Change (PRC)            : %x \n",PORTSC_PRC(n));
	printk("- Port Link State Change (PLC)       : %x \n",PORTSC_PLC(n));
	printk("- Port Config Error Change (CEC)     : %x \n",PORTSC_CEC(n));
	printk("- Cold Attach Status (CAS)           : %x \n",PORTSC_CAS(n));
	printk("- Wake on Connect Enable (WCE)       : %x \n",PORTSC_WCE(n));
	printk("- Wake on Disconnect Enable (WDE)    : %x \n",PORTSC_WDE(n));
	printk("- Wake on Over-current Enable (WOE)  : %x \n",PORTSC_WOE(n));
	printk("- Device Removable (DR)              : %x \n",PORTSC_DR(n) );
	printk("- Warm Port Reset (WPR)              : %x \n",PORTSC_WPR(n));
}

void xhci_dump_device_descriptor(USBStandardDeviceDescriptor* desc){
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

void xhci_dump_device_type_from_interface(usb_interface_descriptor* desc){
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

void xhci_dump_device_endpoint(usb_endpoint *dev){
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

void xhci_stop(){
	// Do we still run?
	if(USBCMD_RS){
		// yes, we do run!
		// we probably have a bios or uefi who booted us
		USBCMD = 0;
		sleep(10);
		// now wait until we have come to a full stop
		while(USBSTS_HCH==0);
	}
}

void xhci_reset(){
	USBCMD = USBCMD | USBCMD_MASK_HCRST;
	sleep(10);
	while(USBCMD_HCRST);
}

void xhci_wait_for_controller_is_ready(){
	while(USBSTS_CNR){
		sleep(10);
	}
}

uint8_t xhci_command_ring_get_switch()
{
		return 1;
}

DefaultTRB *xhci_request_free_command_trb(uint8_t inc)
{
		DefaultTRB *dtrb = (DefaultTRB*) (commandring + (sizeof(DefaultTRB)*command_ring_pointer));
		memset(dtrb,0,sizeof(DefaultTRB));
		if(inc)
		{
				command_ring_pointer++;
		}
		return dtrb;
}

volatile CommandCompletionEventTRB *xhci_ring_and_wait(uint32_t doorbell_offset,uint32_t doorbell_value,uint32_t checkvalue)
{
		DOORBELL[doorbell_offset] = doorbell_value;
		sleep(5);
		while((IMAN(0)&1)==0)
		{
				sleep(5);
		}
		int timeout = 5;
		again:
		sleep(5);
		for(int i = 0 ; i < XHCI_EVENT_RING_SIZE ; i++)
		{
				volatile CommandCompletionEventTRB *to = (volatile CommandCompletionEventTRB*)&((volatile CommandCompletionEventTRB*)(eventring+(i*sizeof(CommandCompletionEventTRB))))[0];
				if(to->DataBufferPointerLo==checkvalue)
				{
						return to;
				}
		}
		timeout--;
		if(timeout){
			goto again;
		}
		return 0;
}

uint8_t xhci_resultcode_explained(volatile CommandCompletionEventTRB* res)
{
		const char * cc[] = {
				"Invalid",
				"Success",
				"Data Buffer Error",
				"Babble Detected Error",
				"USB Transaction Error",
				"TRB Error",
				"Stall Error",
				"Resource Error",
				"Bandwidth Error",
				"No Slots Available Error",
				"Invalid Stream Type Error",
				"Slot Not Enabled Error",
				"Endpoint Not Enabled Error",
				"Short Packet",
				"Ring Underrun",
				"Ring Overrun",
				"VF Event Ring Full Error",
				"Parameter Error",
				"Bandwidth Overrun Error",
				"Context State Error",
				"No Ping Response Error",
				"Event Ring Full Error",
				"Incompatible Device Error",
				"Missed Service Error",
				"Command Ring Stopped",
				"Command Aborted",
				"Stopped",
				"Stopped - Length Invalid",
				"Stopped - Short Packet",
				"Max Exit Latency Too Large Error",
				"Reserved",
				"Isoch Buffer Overrun",
				"Event Lost Error",
				"Undefined Error",
				"Invalid Stream ID Error",
				"Secondary Bandwidth Error",
				"Split Transaction Error"
		};
		printk("(%x) %s \n",res->CompletionCode,cc[res->CompletionCode]);
		return res->CompletionCode;
}

uint8_t xhci_request_device_address(uint8_t device_id,void* data,uint8_t bsr )
{
		// Enable slot TRB
		SetAddressCommandTRB *trb1 = (SetAddressCommandTRB*) xhci_request_free_command_trb(1);
		trb1->CycleBit = xhci_command_ring_get_switch();
		trb1->TRBType = 11;
		trb1->BSR = bsr;
		trb1->DataBufferPointerLo = (uint32_t) (uint64_t) data;
		trb1->DataBufferPointerHi = 0;
		trb1->SlotID = device_id;

		SetAddressCommandTRB *trb2 = (SetAddressCommandTRB*) xhci_request_free_command_trb(0);
		trb2->CycleBit = xhci_command_ring_get_switch()==0?1:0;

		volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(0,0,(uint32_t)(uint64_t)trb1);
		if(res)
		{
			if(res->CompletionCode!=1){
				return xhci_resultcode_explained(res);
			}
			return 1;
		}
		else
		{
				printk("coulden`t get xhci datatoken\n");
				return 0;
		}
}

int xhci_get_device_id(){
	// Enable slot TRB
	EnableSlotCommandTRB *trb1 = (EnableSlotCommandTRB*) xhci_request_free_command_trb(1);
	trb1->CycleBit = xhci_command_ring_get_switch();
	trb1->TRBType = 9;

	EnableSlotCommandTRB *trb2 = (EnableSlotCommandTRB*) xhci_request_free_command_trb(0);
	trb2->CycleBit = xhci_command_ring_get_switch()==0?1:0;

	volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(0,0,(uint32_t)(uint64_t)trb1);
	if(res)
	{
			if(res->CompletionCode!=1)
			{
					return xhci_resultcode_explained(res);
			}
			return res->SlotID;
	}
	else
	{
			printk("coulden`t get xhci datatoken\n");
			return 0;
	}
}

uint8_t xhci_request_ring_test(USBRing *device,int deviceaddr){
	DefaultTRB *trb3 = (DefaultTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
	trb3->Cyclebit = device->stat;
	trb3->TRBType = 8;
	trb3->InterruptOnCompletion = 1;

	StatusStageTRB *trb4 = (StatusStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer];
	trb4->Cyclebit = 0;

	volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(deviceaddr,device->doorbelid,(uint32_t)(uint64_t)trb3);
	if(res)
	{
			if(res->CompletionCode!=1){
				return xhci_resultcode_explained(res);
			}
			return 1;
	}
	else
	{
			printk("coulden`t get xhci datatoken\n");
			return 0;
	}
}



uint8_t xhci_request_device_update(uint8_t device_id,void* data )
{
		// Enable slot TRB
		SetAddressCommandTRB *trb1 = (SetAddressCommandTRB*) xhci_request_free_command_trb(1);
		trb1->CycleBit = xhci_command_ring_get_switch();
		trb1->TRBType = 12;
		trb1->DataBufferPointerLo = (uint32_t) (uint64_t) data;
		trb1->DataBufferPointerHi = 0;
		trb1->SlotID = device_id;

		SetAddressCommandTRB *trb2 = (SetAddressCommandTRB*) xhci_request_free_command_trb(0);
		trb2->CycleBit = xhci_command_ring_get_switch()==0?1:0;

		volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(0,0,(uint32_t)(uint64_t)trb1);
		if(res)
		{
			if(res->CompletionCode!=1){
				return xhci_resultcode_explained(res);
			}
			return 1;
		}
		else
		{
				printk("coulden`t get xhci datatoken\n");
				return 0;
		}
}

void *xhci_request_device_configuration(USBRing *device,int deviceaddr)
{
		uint32_t expectedsize = sizeof(usb_config_descriptor) + sizeof(usb_interface_descriptor) +(sizeof(usb_endpoint)*2);
		void* data = calloc(0x1000);

		SetupStageTRB *trb1 = (SetupStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
		trb1->usbcmd.bRequestType = 0x80;
		trb1->usbcmd.bRequest = 6;
		trb1->usbcmd.wValue = 0x200;
		trb1->usbcmd.wIndex = 0;
		trb1->usbcmd.wLength = expectedsize;
		trb1->TRBTransferLength = 8;
		trb1->InterrupterTarget = 0;
		trb1->Cyclebit = 1;
		trb1->ImmediateData = 1;
		trb1->TRBType = 2;
		trb1->TRT = 3;
		trb1->InterruptOnCompletion = 1;

		DataStageTRB *trb2 = (DataStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
		trb2->Address1 = (uint32_t)(uint64_t) data;
		trb2->Address2 = 0;
		trb2->TRBTransferLength = expectedsize;
		trb2->Cyclebit = 1;
		trb2->TRBType = 3;
		trb2->Direction = 1;
		trb2->InterruptOnCompletion = 1;

		StatusStageTRB *trb3 = (StatusStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
		trb3->Cyclebit = 1;
		trb3->InterruptOnCompletion = 1;
		trb3->Direction = 0;
		trb3->TRBType = 4;

		StatusStageTRB *trb4 = (StatusStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer];
		trb4->Cyclebit = 0;

		volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(deviceaddr,1,(uint32_t)(uint64_t)trb3);
		if(res)
		{
				if(res->CompletionCode!=1)
				{
						xhci_resultcode_explained(res);
						return 0;
				}
				return data;
		}
		else
		{
				printk("coulden`t get xhci datatoken\n");
				return 0;
		}
}

void *xhci_request_device_descriptor(USBRing *device,int deviceaddr)
{
		void* data = calloc(0x1000);

		SetupStageTRB *trb1 = (SetupStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
		trb1->usbcmd.bRequestType = 0x80;
		trb1->usbcmd.bRequest = 6;
		trb1->usbcmd.wValue = 0x100;
		trb1->usbcmd.wIndex = 0;
		trb1->usbcmd.wLength = 8;
		trb1->TRBTransferLength = 8;
		trb1->InterrupterTarget = 0;
		trb1->Cyclebit = 1;
		trb1->ImmediateData = 1;
		trb1->TRBType = 2;
		trb1->TRT = 3;

		DataStageTRB *trb2 = (DataStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
		trb2->Address1 = (uint32_t)(uint64_t) data;
		trb2->Address2 = 0;
		trb2->TRBTransferLength = 8;
		trb2->Cyclebit = 1;
		trb2->TRBType = 3;
		trb2->Direction = 1;

		StatusStageTRB *trb3 = (StatusStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
		trb3->Cyclebit = 1;
		trb3->InterruptOnCompletion = 1;
		trb3->Direction = 0;
		trb3->TRBType = 4;

		StatusStageTRB *trb4 = (StatusStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer];
		trb4->Cyclebit = 0;

		volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(deviceaddr,1,(uint32_t)(uint64_t)trb3);
		if(res)
		{
				if(res->CompletionCode!=1)
				{
						xhci_resultcode_explained(res);
						return 0;
				}
				return data;
		}
		else
		{
				printk("coulden`t get xhci datatoken\n");
				return 0;
		}
}

uint8_t xhci_request_set_config(USBRing *device,uint8_t configid)
{
    SetupStageTRB *trb1 = (SetupStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
    trb1->usbcmd.bRequest = 9;
    trb1->usbcmd.wValue = configid;
    trb1->usbcmd.wIndex = 0;
    trb1->usbcmd.wLength = 0;
    trb1->TRBTransferLength = 8;
    trb1->InterrupterTarget = 0;
    trb1->Cyclebit = 1;
    trb1->ImmediateData = 1;
    trb1->TRBType = 2;
    trb1->TRT = 3;

    StatusStageTRB *trb3 = (StatusStageTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
    trb3->Cyclebit = 1;
    trb3->InterruptOnCompletion = 1;
    trb3->Direction = 1;
    trb3->TRBType = 4;

    volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(device->deviceaddr,device->doorbelid,(uint32_t)(uint64_t)trb3);
    if(res)
    {
        if(res->CompletionCode!=1)
        {
            return xhci_resultcode_explained(res);
        }
        return 1;
    }
    else
    {
        printk("coulden`t get xhci datatoken\n");
        return 0;
    }
}

uint8_t xhci_recieve_bulk(USBRing *device,void *data,int size)
{
    TransferTRB *trb1 = (TransferTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
    trb1->DataBufferPointerLo = (uint32_t)((uint64_t)data);
    trb1->DataBufferPointerHi = 0;
    trb1->BlockEventInterrupt = 0;
    trb1->Chainbit = 0;
    trb1->Cyclebit = 1;
    trb1->EvaluateNextTRB = 0;
    trb1->ImmediateData = 0;
    trb1->InterrupterTarget = 0;
    trb1->TDSize = 0;
    trb1->TRBTransferLength = size;
    trb1->TRBType = 1;
    trb1->InterruptOnCompletion = 1;

    EventDataTRB *trb3 = (EventDataTRB*) & ((DefaultTRB*)device->ring)[device->pointer];
    trb3->Cyclebit = 0;

    volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(device->deviceaddr,device->doorbelid,(uint32_t)(uint64_t)trb1);
    if(res)
    {
        if(res->CompletionCode!=1)
        {
            return xhci_resultcode_explained(res);
        }
        return 1;
    }
    else
    {
        printk("coulden`t get xhci datatoken\n");
        return 0;
    }
}

uint8_t xhci_send_bulk(USBRing *device,void *data,int size)
{
    TransferTRB *trb1 = (TransferTRB*) & ((DefaultTRB*)device->ring)[device->pointer++];
    trb1->DataBufferPointerLo = (uint32_t)((uint64_t)data);
    trb1->DataBufferPointerHi = 0;
    trb1->BlockEventInterrupt = 0;
    trb1->Chainbit = 0;
    trb1->Cyclebit = 1;
    trb1->EvaluateNextTRB = 0;
    trb1->ImmediateData = 0;
    trb1->InterrupterTarget = 0;
    // trb1->NoSnoop = 1;
    trb1->TDSize = 0;
    trb1->TRBTransferLength = size;
    trb1->TRBType = 1;
    trb1->InterruptOnCompletion = 1;

    EventDataTRB *trb3 = (EventDataTRB*) & ((DefaultTRB*)device->ring)[device->pointer];
    trb3->Cyclebit = 0;

    volatile CommandCompletionEventTRB *res = xhci_ring_and_wait(device->deviceaddr,device->doorbelid,(uint32_t)(uint64_t)trb1);
    if(res)
    {
        if(res->CompletionCode!=1)
        {
            return xhci_resultcode_explained(res);
        }
        return 1;
    }
    else
    {
        printk("coulden`t get xhci datatoken\n");
        return 0;
    }
}

void xhci_fill_endpoint(USBSocket* socket,usb_endpoint* ep,void* ring,int id,int eptype){
	memclear((void*)&socket->dataset->epx[id],sizeof(XHCIEndpointContext));
	socket->dataset->epx[id].EPType = eptype;
	socket->dataset->epx[id].MaxPacketSize = ep->wMaxPacketSize;
	socket->dataset->epx[id].Cerr = 3;
	socket->dataset->epx[id].TRDequeuePointerLow = ((uint32_t) (uint64_t) ring)>>4 ;
	socket->dataset->epx[id].TRDequeuePointerHigh = 0;
	socket->dataset->epx[id].DequeueCycleState = 1;
}

void xhci_register_bulk_endpoints(USBSocket* socket,usb_endpoint* ep1,usb_endpoint* ep2,void* ring1,void* ring2){
	//
	// OUT endpoint direction
	xhci_fill_endpoint(socket,ep1,ring1,0,2);

	//
	// IN endpoint direction
	xhci_fill_endpoint(socket,ep2,ring2,1,6);

	socket->dataset->icc.Aregisters = 0b1111;
	socket->dataset->slotcontext.ContextEntries = 3;

	xhci_request_device_update(socket->control->deviceaddr,socket->dataset);

	USBRing *ringbulkout = (USBRing*) calloc(0x1000);
	ringbulkout->ring = ring1;
	ringbulkout->pointer = 0;
	ringbulkout->stat = 1;
	ringbulkout->doorbelid = 2;
	ringbulkout->deviceaddr = socket->control->deviceaddr;

	USBRing *ringbulkin = (USBRing*) calloc(0x1000);
	ringbulkin->ring = ring2;
	ringbulkin->pointer = 0;
	ringbulkin->stat = 1;
	ringbulkin->doorbelid = 3;
	ringbulkin->deviceaddr = socket->control->deviceaddr;

	socket->out = ringbulkout;
	socket->in = ringbulkin;
}

usb_endpoint* xhci_get_endpoint(USBSocket* info,int type){
	return (usb_endpoint*)(((unsigned long)info->descriptors)+sizeof(usb_config_descriptor)+sizeof(usb_interface_descriptor)+(sizeof(usb_endpoint)*type));
}

void xhci_initialise_port(int portno)
{
	// is there something connected?
	if(PORTSC_CCS(portno)==0)
	{
		return;
	}
	// is it enabled?
	if(PORTSC_PED (portno)==0)
	{
		PORTSC(portno) = PORTSC (portno) | 0x10;
		sleep(7);
	}
	// and now?
	if(PORTSC_PED (portno)==0)
	{
		return;
	}

	uint8_t portspeed = PORTSC_Port_Speed (portno);
	uint16_t calculatedportspeed = 0;
	if(portspeed==XHCI_SPEED_SUPER)
	{
			calculatedportspeed = 512;
	}
	else if(portspeed==XHCI_SPEED_HI)
	{
			calculatedportspeed = 64;
	}
	else if(portspeed==XHCI_SPEED_LOW)
	{
			calculatedportspeed = 8;
	}
	else if(portspeed==XHCI_SPEED_FULL)
	{
			calculatedportspeed = 64;return;
	}
	else
	{
			return;
	}

	// now get a device id
	int deviceid = xhci_get_device_id();
	if(deviceid==0)
	{
		return;
	}

	//
	// Setup the other structures
	void *localring = calloc(0x1000);
	XHCIInputContextBuffer *infostructures = (XHCIInputContextBuffer*) calloc(0x1000);
	infostructures->icc.Aregisters = 0b11;
	infostructures->slotcontext.RootHubPortNumber = portno + 1;
	infostructures->slotcontext.ContextEntries = 1;
	infostructures->slotcontext.Speed = portspeed;
	infostructures->epc.LSA = 0;
	infostructures->epc.EPType = 4;
	infostructures->epc.Cerr = 3;
	infostructures->epc.MaxPacketSize = calculatedportspeed;
	infostructures->epc.TRDequeuePointerLow = ((uint32_t) (uint64_t) localring)>>4 ;
	infostructures->epc.TRDequeuePointerHigh = 0;
	infostructures->epc.DequeueCycleState = 1;

	((uint32_t*)dcbaap_items)[(deviceid*2)+0] = ((uint32_t)(uint64_t)(infostructures+64));
	((uint32_t*)dcbaap_items)[(deviceid*2)+1] = 0;

	uint8_t res = xhci_request_device_address(deviceid,infostructures,0);
	if(res!=1)
	{
		res = xhci_request_device_address(deviceid,infostructures,1);
		if(res!=1)
		{
			return;
		}
	}

	USBRing *ringinfo = (USBRing*) calloc(0x1000);
	ringinfo->ring = localring;
	ringinfo->pointer = 0;
	ringinfo->stat = 1;
	ringinfo->doorbelid = 1;
	ringinfo->deviceaddr = deviceid;

	xhci_request_ring_test(ringinfo,deviceid);

	USBStandardDeviceDescriptor* devdesc = (USBStandardDeviceDescriptor*) xhci_request_device_descriptor(ringinfo,deviceid);
	if(portspeed==XHCI_SPEED_FULL&&devdesc->bMaxPacketSize0!=64){
			printk("We have a fullspeed here! different maxpackagesize: %d \n",devdesc->bMaxPacketSize0);
			return;
	}

	uint8_t* cinforaw = (uint8_t*)xhci_request_device_configuration(ringinfo,deviceid);
	usb_interface_descriptor* desc = (usb_interface_descriptor*)(((unsigned long)cinforaw)+sizeof(usb_config_descriptor));

	USBSocket *socket = (USBSocket*) calloc(0x1000);
	socket->control = ringinfo;
	socket->dataset = infostructures;
	socket->descriptors = cinforaw;

	install_new_usb_device(desc,socket);
}

void initialise_xhci(uint8_t bus, uint8_t slot, uint8_t func)
{
	// get interrupt
	install_interrupt_from_pci(bus,slot,func,interrupt_xhci);

	// get the base address of xhci
	base_xhci_address = 0;
	base_xhci_address += pciConfigReadDWord (bus, slot, func, 0x10) & 0xFFFFFFF0;
	command_ring_pointer = 0;

	//
	// check the capabilities to stop the system
	uint32_t capapointer = (((uint32_t*)(base_xhci_address+0x10))[0]>>16)<<2;
	void *cappointer = capapointer + base_xhci_address;
	int captimeout = 100;
	while(1)
	{
			volatile uint32_t reg = ((volatile uint32_t*)cappointer)[0];
			uint8_t capid = reg & 0xFF;
			uint8_t capoffset = (reg>>8) & 0xFF;
			if(capid==0)
			{
					break;
			}
			if( capid==1 && reg & 0x10000 )
			{
					((volatile uint32_t*)cappointer)[0] |= 0x1000000;
					sleep(1);
					captimeout--;
					if(captimeout==0)
					{
							break;
					}
					continue;
			}
			if(capoffset==0)
			{
					break;
			}
			cappointer += capoffset * sizeof(uint32_t);
	}

	// stop xhci if it is still running
	xhci_stop ();

	//
	// After Chip Hardware Reset 6 wait until the Controller Not Ready (CNR) flag
	// in the USBSTS is ‘0’ before writing any xHC Operational or Runtime
	// registers.

	// reset controller
	xhci_reset ();

	// wait until ready
	xhci_wait_for_controller_is_ready ();

	CONFIG |= 5;

	dcbaap_items = calloc(0x1000);
	DCBAAP_L = (uint32_t) ((uint64_t) dcbaap_items);
	DCBAAP_H = (uint32_t) 0;

	void* scratchpad_items = calloc(0x1000);
	((uint32_t*)dcbaap_items)[0] = (uint32_t)(uint64_t)scratchpad_items;
	((uint32_t*)dcbaap_items)[1] = (uint32_t)(uint64_t)0;

	for(int i = 0 ; i < 2 ; i++)
	{
		((uint32_t*)scratchpad_items)[ 0 + ( i * 2 ) ] = (uint32_t)(uint64_t)calloc(0x1000);
		((uint32_t*)scratchpad_items)[ 1 + ( i * 2 ) ] = (uint32_t)(uint64_t)0;
	}

	commandring = calloc(0x1000);
	CRCR_L = ((uint32_t)((uint64_t)commandring))|1;
	CRCR_H = 0;

	eventring = calloc(0x1000);
	XHCIEventRingSegmentTable *segmenttable = (XHCIEventRingSegmentTable*)calloc(0x1000);
	segmenttable->ring_segment_base_address_low = ((uint32_t)((uint64_t)eventring));
	segmenttable->ring_segment_base_address_high = 0;
	segmenttable->ring_segment_size = XHCI_EVENT_RING_SIZE;

	ERSTSZ(0) = 1;

	ERDP_L (0) = ((uint32_t)((uint64_t)eventring));
	ERDP_H (0) = 0;

	ERSTBA_L (0) = ((uint32_t)((uint64_t)segmenttable));
	ERSTBA_H (0) = 0;

	IMOD (0) = 0x00100FA0;

	IMAN (0) = 2;

	USBCMD = USBCMD | USBCMD_MASK_RS;

	sleep(5);

	for(int i = 0 ; i < HCSPARAMS1_MaxPorts ;i++)
	{
		if(PORTSC(i) & 1)
		{
			xhci_initialise_port(i);
		}
	}
}


