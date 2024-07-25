#include "../include/string.h"
#include "../include/usb.h"
#include "../include/usb_msd.h"
#include "../include/memory.h"
#include "../include/fat.h"

uint32_t usbtagpointer = 1;

CommandBlockWrapper* usb_stick_generate_pointer()
{
    CommandBlockWrapper *ep = (CommandBlockWrapper*) calloc(0x1000);
    memset(ep,0,sizeof(CommandBlockWrapper));
    ep->signature = 0x43425355;
    ep->tag = usbtagpointer++;
    return ep;
}

void *usb_stick_one_read(void *data, uint64_t sector, uint32_t counter,void* out)
{
    CommandBlockWrapper *ep = usb_stick_generate_pointer();
    ep->transferlength = 512 * counter;
    ep->flags = 0x80;
    ep->command_len = 10;
    // command READ(0x12)
    ep->data[0] = 0x28;
    // reserved
    ep->data[1] = 0;
    // lba
    ep->data[2] = (uint8_t) ((sector >> 24) & 0xFF);
    ep->data[3] = (uint8_t) ((sector >> 16) & 0xFF);
    ep->data[4] = (uint8_t) ((sector >> 8) & 0xFF);
    ep->data[5] = (uint8_t) ((sector) & 0xFF);
    // counter
    ep->data[6] = 0;
    ep->data[7] = (uint8_t) ((counter >> 8) & 0xFF);
    ep->data[8] = (uint8_t) ((counter) & 0xFF);

    usb_send_bulk (data, ep, sizeof(CommandBlockWrapper));

	usb_recieve_bulk(data,out,sizeof(CommandStatusWrapper) + (512*counter));

	CommandStatusWrapper *csw = (CommandStatusWrapper*) (out + (512*counter));
	if(csw->signature!=0x53425355){
		printk("usb_msd: invalid signature!\n");
		printk("status: %x residue: %x tag: %x signature: %x \n",csw->status,csw->data_residue,csw->tag,csw->signature);
		return 0;
	}
	return out;
}

void *rsb;

void *read_sectors(uint64_t sector, uint32_t counter,void* out){
	return usb_stick_one_read (rsb,sector,counter,out);
}

void install_usb_msd(usb_interface_descriptor* desc,void *data){
	// only support MSD
	if(desc->bInterfaceClass != 0x08)
	{
		return;
	}

	// check number of endpoins
	if(desc->bNumEndpoints != 2)
	{
		printk("Number of endpoints is not 2!\n");
		return;
	}

	if(desc->bInterfaceSubClass != 6)
	{
		printk("Interface Sub Class is not 6!\n");
		return;
	}

	if(desc->bInterfaceProtocol != 0x50)
	{
		printk("Interface Protocol is not 0x50!\n");
		return;
	}

	usb_endpoint *ep1 = getUSBEndpoint(data,0);
  	usb_endpoint *ep2 = getUSBEndpoint(data,1);

	void *localoutring = calloc(0x1000);
	void *localinring = calloc(0x1000);

	usb_register_bulk_endpoints(data,ep1,ep2,localoutring,localinring);

	usb_request_set_config(data,1);

	rsb = data;
	detect_fat();
}
