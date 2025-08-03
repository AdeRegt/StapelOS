#include <stdint.h>
#include "../include/reflection.h" 

char* getSymbolnameForAddress(uint64_t input){
	char* res;
	extern void pciConfigWriteWord();
	if(input>=((uint64_t)&pciConfigWriteWord)){
		res = "pciConfigWriteWord";
	}
	extern void pciConfigWriteDWord();
	if(input>=((uint64_t)&pciConfigWriteDWord)){
		res = "pciConfigWriteDWord";
	}
	extern void pciConfigReadWord();
	if(input>=((uint64_t)&pciConfigReadWord)){
		res = "pciConfigReadWord";
	}
	extern void pciConfigReadDWord();
	if(input>=((uint64_t)&pciConfigReadDWord)){
		res = "pciConfigReadDWord";
	}
	extern void pciConfigReadByte();
	if(input>=((uint64_t)&pciConfigReadByte)){
		res = "pciConfigReadByte";
	}
	extern void pciConfigReadByteHi();
	if(input>=((uint64_t)&pciConfigReadByteHi)){
		res = "pciConfigReadByteHi";
	}
	extern void install_interrupt_from_pci();
	if(input>=((uint64_t)&install_interrupt_from_pci)){
		res = "install_interrupt_from_pci";
	}
	extern void check_pci_entry_for_usb();
	if(input>=((uint64_t)&check_pci_entry_for_usb)){
		res = "check_pci_entry_for_usb";
	}
	extern void pci_enable_busmastering();
	if(input>=((uint64_t)&pci_enable_busmastering)){
		res = "pci_enable_busmastering";
	}
	extern void check_pci_entry();
	if(input>=((uint64_t)&check_pci_entry)){
		res = "check_pci_entry";
	}
	extern void initialise_pci();
	if(input>=((uint64_t)&initialise_pci)){
		res = "initialise_pci";
	}
	extern void ps2_read_status_register();
	if(input>=((uint64_t)&ps2_read_status_register)){
		res = "ps2_read_status_register";
	}
	extern void ps2_read_data_port();
	if(input>=((uint64_t)&ps2_read_data_port)){
		res = "ps2_read_data_port";
	}
	extern void ps2_write_data_port();
	if(input>=((uint64_t)&ps2_write_data_port)){
		res = "ps2_write_data_port";
	}
	extern void ps2_write_command_register();
	if(input>=((uint64_t)&ps2_write_command_register)){
		res = "ps2_write_command_register";
	}
	extern void ps2_chip_echo();
	if(input>=((uint64_t)&ps2_chip_echo)){
		res = "ps2_chip_echo";
	}
	extern void ps2_chip_reset();
	if(input>=((uint64_t)&ps2_chip_reset)){
		res = "ps2_chip_reset";
	}
	extern void ps2_chip_set_default_parameters();
	if(input>=((uint64_t)&ps2_chip_set_default_parameters)){
		res = "ps2_chip_set_default_parameters";
	}
	extern void ps2_chip_get_current_scancode_set();
	if(input>=((uint64_t)&ps2_chip_get_current_scancode_set)){
		res = "ps2_chip_get_current_scancode_set";
	}
	extern void ps2_chip_enablescanning();
	if(input>=((uint64_t)&ps2_chip_enablescanning)){
		res = "ps2_chip_enablescanning";
	}
	extern void getKeymapFor();
	if(input>=((uint64_t)&getKeymapFor)){
		res = "getKeymapFor";
	}
	extern void scancode_to_char();
	if(input>=((uint64_t)&scancode_to_char)){
		res = "scancode_to_char";
	}
	extern void irq_keyboard();
	if(input>=((uint64_t)&irq_keyboard)){
		res = "irq_keyboard";
	}
	extern void getch();
	if(input>=((uint64_t)&getch)){
		res = "getch";
	}
	extern void initialise_ps2_keyboard();
	if(input>=((uint64_t)&initialise_ps2_keyboard)){
		res = "initialise_ps2_keyboard";
	}
	extern void serialportnumber_to_address();
	if(input>=((uint64_t)&serialportnumber_to_address)){
		res = "serialportnumber_to_address";
	}
	extern void enable_serial_port();
	if(input>=((uint64_t)&enable_serial_port)){
		res = "enable_serial_port";
	}
	extern void initialise_serial();
	if(input>=((uint64_t)&initialise_serial)){
		res = "initialise_serial";
	}
	extern void load_stapel_file_singletasking();
	if(input>=((uint64_t)&load_stapel_file_singletasking)){
		res = "load_stapel_file_singletasking";
	}
	extern void load_stapel_tutorial();
	if(input>=((uint64_t)&load_stapel_tutorial)){
		res = "load_stapel_tutorial";
	}
	extern void timer_int();
	if(input>=((uint64_t)&timer_int)){
		res = "timer_int";
	}
	extern void set_pit_count();
	if(input>=((uint64_t)&set_pit_count)){
		res = "set_pit_count";
	}
	extern void get_pit_count();
	if(input>=((uint64_t)&get_pit_count)){
		res = "get_pit_count";
	}
	extern void resetTimer();
	if(input>=((uint64_t)&resetTimer)){
		res = "resetTimer";
	}
	extern void sleep();
	if(input>=((uint64_t)&sleep)){
		res = "sleep";
	}
	extern void initialise_timer();
	if(input>=((uint64_t)&initialise_timer)){
		res = "initialise_timer";
	}
	extern void usb_dump_descriptor();
	if(input>=((uint64_t)&usb_dump_descriptor)){
		res = "usb_dump_descriptor";
	}
	extern void usb_dump_device_descriptor();
	if(input>=((uint64_t)&usb_dump_device_descriptor)){
		res = "usb_dump_device_descriptor";
	}
	extern void usb_dump_device_type_from_interface();
	if(input>=((uint64_t)&usb_dump_device_type_from_interface)){
		res = "usb_dump_device_type_from_interface";
	}
	extern void usb_dump_device_endpoint();
	if(input>=((uint64_t)&usb_dump_device_endpoint)){
		res = "usb_dump_device_endpoint";
	}
	extern void getUSBEndpoint();
	if(input>=((uint64_t)&getUSBEndpoint)){
		res = "getUSBEndpoint";
	}
	extern void usb_send_bulk();
	if(input>=((uint64_t)&usb_send_bulk)){
		res = "usb_send_bulk";
	}
	extern void usb_recieve_bulk();
	if(input>=((uint64_t)&usb_recieve_bulk)){
		res = "usb_recieve_bulk";
	}
	extern void usb_test_bulk_endpoint();
	if(input>=((uint64_t)&usb_test_bulk_endpoint)){
		res = "usb_test_bulk_endpoint";
	}
	extern void usb_register_bulk_endpoints();
	if(input>=((uint64_t)&usb_register_bulk_endpoints)){
		res = "usb_register_bulk_endpoints";
	}
	extern void usb_request_set_config();
	if(input>=((uint64_t)&usb_request_set_config)){
		res = "usb_request_set_config";
	}
	extern void install_new_usb_device();
	if(input>=((uint64_t)&install_new_usb_device)){
		res = "install_new_usb_device";
	}
	extern void usb_generate_command_structure();
	if(input>=((uint64_t)&usb_generate_command_structure)){
		res = "usb_generate_command_structure";
	}
	extern void interrupt_ehci();
	if(input>=((uint64_t)&interrupt_ehci)){
		res = "interrupt_ehci";
	}
	extern void ehci_dump_hcsparams();
	if(input>=((uint64_t)&ehci_dump_hcsparams)){
		res = "ehci_dump_hcsparams";
	}
	extern void ehci_dump_hccparams();
	if(input>=((uint64_t)&ehci_dump_hccparams)){
		res = "ehci_dump_hccparams";
	}
	extern void ehci_dump_usblegsup();
	if(input>=((uint64_t)&ehci_dump_usblegsup)){
		res = "ehci_dump_usblegsup";
	}
	extern void ehci_dump_usbcmd();
	if(input>=((uint64_t)&ehci_dump_usbcmd)){
		res = "ehci_dump_usbcmd";
	}
	extern void ehci_dump_portsc();
	if(input>=((uint64_t)&ehci_dump_portsc)){
		res = "ehci_dump_portsc";
	}
	extern void ehci_reset_controller();
	if(input>=((uint64_t)&ehci_reset_controller)){
		res = "ehci_reset_controller";
	}
	extern void ehci_demand_ownership();
	if(input>=((uint64_t)&ehci_demand_ownership)){
		res = "ehci_demand_ownership";
	}
	extern void ehci_generate_transfer_descriptor();
	if(input>=((uint64_t)&ehci_generate_transfer_descriptor)){
		res = "ehci_generate_transfer_descriptor";
	}
	extern void ehci_generate_queue_head();
	if(input>=((uint64_t)&ehci_generate_queue_head)){
		res = "ehci_generate_queue_head";
	}
	extern void ehci_wait_for_completion();
	if(input>=((uint64_t)&ehci_wait_for_completion)){
		res = "ehci_wait_for_completion";
	}
	extern void ehci_offer_queuehead_to_ring();
	if(input>=((uint64_t)&ehci_offer_queuehead_to_ring)){
		res = "ehci_offer_queuehead_to_ring";
	}
	extern void ehci_request_device_addr();
	if(input>=((uint64_t)&ehci_request_device_addr)){
		res = "ehci_request_device_addr";
	}
	extern void ehci_request_device_descriptor();
	if(input>=((uint64_t)&ehci_request_device_descriptor)){
		res = "ehci_request_device_descriptor";
	}
	extern void ehci_get_endpoint();
	if(input>=((uint64_t)&ehci_get_endpoint)){
		res = "ehci_get_endpoint";
	}
	extern void ehci_register_bulk_endpoints();
	if(input>=((uint64_t)&ehci_register_bulk_endpoints)){
		res = "ehci_register_bulk_endpoints";
	}
	extern void ehci_request_set_config();
	if(input>=((uint64_t)&ehci_request_set_config)){
		res = "ehci_request_set_config";
	}
	extern void ehci_send_bulk();
	if(input>=((uint64_t)&ehci_send_bulk)){
		res = "ehci_send_bulk";
	}
	extern void ehci_recieve_bulk();
	if(input>=((uint64_t)&ehci_recieve_bulk)){
		res = "ehci_recieve_bulk";
	}
	extern void ehci_probe_port();
	if(input>=((uint64_t)&ehci_probe_port)){
		res = "ehci_probe_port";
	}
	extern void ehci_probe_ports();
	if(input>=((uint64_t)&ehci_probe_ports)){
		res = "ehci_probe_ports";
	}
	extern void initialise_ehci();
	if(input>=((uint64_t)&initialise_ehci)){
		res = "initialise_ehci";
	}
	extern void install_usb_hid();
	if(input>=((uint64_t)&install_usb_hid)){
		res = "install_usb_hid";
	}
	extern void usb_stick_generate_pointer();
	if(input>=((uint64_t)&usb_stick_generate_pointer)){
		res = "usb_stick_generate_pointer";
	}
	extern void usb_stick_one_read();
	if(input>=((uint64_t)&usb_stick_one_read)){
		res = "usb_stick_one_read";
	}
	extern void read_sectors();
	if(input>=((uint64_t)&read_sectors)){
		res = "read_sectors";
	}
	extern void usb_stick_inquiry();
	if(input>=((uint64_t)&usb_stick_inquiry)){
		res = "usb_stick_inquiry";
	}
	extern void usb_msd_test_unit_ready();
	if(input>=((uint64_t)&usb_msd_test_unit_ready)){
		res = "usb_msd_test_unit_ready";
	}
	extern void install_usb_msd();
	if(input>=((uint64_t)&install_usb_msd)){
		res = "install_usb_msd";
	}
	extern void ohci_reset();
	if(input>=((uint64_t)&ohci_reset)){
		res = "ohci_reset";
	}
	extern void ohci_init_hcca();
	if(input>=((uint64_t)&ohci_init_hcca)){
		res = "ohci_init_hcca";
	}
	extern void ohci_disable_interrupts();
	if(input>=((uint64_t)&ohci_disable_interrupts)){
		res = "ohci_disable_interrupts";
	}
	extern void ohci_set_operational();
	if(input>=((uint64_t)&ohci_set_operational)){
		res = "ohci_set_operational";
	}
	extern void ohci_create_endpoint_descriptor();
	if(input>=((uint64_t)&ohci_create_endpoint_descriptor)){
		res = "ohci_create_endpoint_descriptor";
	}
	extern void ohci_create_transfer_descriptor();
	if(input>=((uint64_t)&ohci_create_transfer_descriptor)){
		res = "ohci_create_transfer_descriptor";
	}
	extern void interrupt_ohci();
	if(input>=((uint64_t)&interrupt_ohci)){
		res = "interrupt_ohci";
	}
	extern void ohci_bus_reset();
	if(input>=((uint64_t)&ohci_bus_reset)){
		res = "ohci_bus_reset";
	}
	extern void ohci_read_port_status();
	if(input>=((uint64_t)&ohci_read_port_status)){
		res = "ohci_read_port_status";
	}
	extern void ohci_write_port_status();
	if(input>=((uint64_t)&ohci_write_port_status)){
		res = "ohci_write_port_status";
	}
	extern void ohci_is_operational();
	if(input>=((uint64_t)&ohci_is_operational)){
		res = "ohci_is_operational";
	}
	extern void wait_for_transfer_complete();
	if(input>=((uint64_t)&wait_for_transfer_complete)){
		res = "wait_for_transfer_complete";
	}
	extern void setup_control_transfer_for_get_descriptor();
	if(input>=((uint64_t)&setup_control_transfer_for_get_descriptor)){
		res = "setup_control_transfer_for_get_descriptor";
	}
	extern void initialise_ohci();
	if(input>=((uint64_t)&initialise_ohci)){
		res = "initialise_ohci";
	}
	extern void interrupt_xhci();
	if(input>=((uint64_t)&interrupt_xhci)){
		res = "interrupt_xhci";
	}
	extern void xhci_sleep();
	if(input>=((uint64_t)&xhci_sleep)){
		res = "xhci_sleep";
	}
	extern void xhci_dump_caplength();
	if(input>=((uint64_t)&xhci_dump_caplength)){
		res = "xhci_dump_caplength";
	}
	extern void xhci_dump_hciversion();
	if(input>=((uint64_t)&xhci_dump_hciversion)){
		res = "xhci_dump_hciversion";
	}
	extern void xhci_dump_hcsparams1();
	if(input>=((uint64_t)&xhci_dump_hcsparams1)){
		res = "xhci_dump_hcsparams1";
	}
	extern void xhci_dump_hcsparams2();
	if(input>=((uint64_t)&xhci_dump_hcsparams2)){
		res = "xhci_dump_hcsparams2";
	}
	extern void xhci_dump_hcsparams3();
	if(input>=((uint64_t)&xhci_dump_hcsparams3)){
		res = "xhci_dump_hcsparams3";
	}
	extern void xhci_dump_hccparams1();
	if(input>=((uint64_t)&xhci_dump_hccparams1)){
		res = "xhci_dump_hccparams1";
	}
	extern void xhci_dump_dboff();
	if(input>=((uint64_t)&xhci_dump_dboff)){
		res = "xhci_dump_dboff";
	}
	extern void xhci_dump_rtsoff();
	if(input>=((uint64_t)&xhci_dump_rtsoff)){
		res = "xhci_dump_rtsoff";
	}
	extern void xhci_dump_capability_registers();
	if(input>=((uint64_t)&xhci_dump_capability_registers)){
		res = "xhci_dump_capability_registers";
	}
	extern void xhci_dump_usbcmd();
	if(input>=((uint64_t)&xhci_dump_usbcmd)){
		res = "xhci_dump_usbcmd";
	}
	extern void xhci_dump_usbsts();
	if(input>=((uint64_t)&xhci_dump_usbsts)){
		res = "xhci_dump_usbsts";
	}
	extern void xhci_dump_page_size();
	if(input>=((uint64_t)&xhci_dump_page_size)){
		res = "xhci_dump_page_size";
	}
	extern void xhci_dump_device_notification_control_register();
	if(input>=((uint64_t)&xhci_dump_device_notification_control_register)){
		res = "xhci_dump_device_notification_control_register";
	}
	extern void xhci_dump_config();
	if(input>=((uint64_t)&xhci_dump_config)){
		res = "xhci_dump_config";
	}
	extern void xhci_dump_operational_registers();
	if(input>=((uint64_t)&xhci_dump_operational_registers)){
		res = "xhci_dump_operational_registers";
	}
	extern void xhci_dump_ports();
	if(input>=((uint64_t)&xhci_dump_ports)){
		res = "xhci_dump_ports";
	}
	extern void xhci_dump_slot_context();
	if(input>=((uint64_t)&xhci_dump_slot_context)){
		res = "xhci_dump_slot_context";
	}
	extern void xhci_get_port_link_state();
	if(input>=((uint64_t)&xhci_get_port_link_state)){
		res = "xhci_get_port_link_state";
	}
	extern void xhci_get_port_speed();
	if(input>=((uint64_t)&xhci_get_port_speed)){
		res = "xhci_get_port_speed";
	}
	extern void xhci_dump_usbport();
	if(input>=((uint64_t)&xhci_dump_usbport)){
		res = "xhci_dump_usbport";
	}
	extern void xhci_stop();
	if(input>=((uint64_t)&xhci_stop)){
		res = "xhci_stop";
	}
	extern void xhci_reset();
	if(input>=((uint64_t)&xhci_reset)){
		res = "xhci_reset";
	}
	extern void xhci_wait_for_controller_is_ready();
	if(input>=((uint64_t)&xhci_wait_for_controller_is_ready)){
		res = "xhci_wait_for_controller_is_ready";
	}
	extern void xhci_command_ring_get_switch();
	if(input>=((uint64_t)&xhci_command_ring_get_switch)){
		res = "xhci_command_ring_get_switch";
	}
	extern void xhci_request_free_command_trb();
	if(input>=((uint64_t)&xhci_request_free_command_trb)){
		res = "xhci_request_free_command_trb";
	}
	extern void xhci_ring_and_wait();
	if(input>=((uint64_t)&xhci_ring_and_wait)){
		res = "xhci_ring_and_wait";
	}
	extern void xhci_resultcode_explained();
	if(input>=((uint64_t)&xhci_resultcode_explained)){
		res = "xhci_resultcode_explained";
	}
	extern void xhci_request_device_address();
	if(input>=((uint64_t)&xhci_request_device_address)){
		res = "xhci_request_device_address";
	}
	extern void xhci_get_device_id();
	if(input>=((uint64_t)&xhci_get_device_id)){
		res = "xhci_get_device_id";
	}
	extern void xhci_request_ring_test();
	if(input>=((uint64_t)&xhci_request_ring_test)){
		res = "xhci_request_ring_test";
	}
	extern void xhci_request_device_update();
	if(input>=((uint64_t)&xhci_request_device_update)){
		res = "xhci_request_device_update";
	}
	extern void xhci_request_device_configuration();
	if(input>=((uint64_t)&xhci_request_device_configuration)){
		res = "xhci_request_device_configuration";
	}
	extern void xhci_request_device_descriptor();
	if(input>=((uint64_t)&xhci_request_device_descriptor)){
		res = "xhci_request_device_descriptor";
	}
	extern void xhci_request_device_name();
	if(input>=((uint64_t)&xhci_request_device_name)){
		res = "xhci_request_device_name";
	}
	extern void xhci_dump_device_name();
	if(input>=((uint64_t)&xhci_dump_device_name)){
		res = "xhci_dump_device_name";
	}
	extern void xhci_request_set_config();
	if(input>=((uint64_t)&xhci_request_set_config)){
		res = "xhci_request_set_config";
	}
	extern void xhci_recieve_bulk();
	if(input>=((uint64_t)&xhci_recieve_bulk)){
		res = "xhci_recieve_bulk";
	}
	extern void xhci_send_bulk();
	if(input>=((uint64_t)&xhci_send_bulk)){
		res = "xhci_send_bulk";
	}
	extern void xhci_fill_endpoint();
	if(input>=((uint64_t)&xhci_fill_endpoint)){
		res = "xhci_fill_endpoint";
	}
	extern void xhci_test_bulk();
	if(input>=((uint64_t)&xhci_test_bulk)){
		res = "xhci_test_bulk";
	}
	extern void xhci_register_bulk_endpoints();
	if(input>=((uint64_t)&xhci_register_bulk_endpoints)){
		res = "xhci_register_bulk_endpoints";
	}
	extern void xhci_get_endpoint();
	if(input>=((uint64_t)&xhci_get_endpoint)){
		res = "xhci_get_endpoint";
	}
	extern void xhci_initialise_port();
	if(input>=((uint64_t)&xhci_initialise_port)){
		res = "xhci_initialise_port";
	}
	extern void xhci_check_ports();
	if(input>=((uint64_t)&xhci_check_ports)){
		res = "xhci_check_ports";
	}
	extern void initialise_xhci();
	if(input>=((uint64_t)&initialise_xhci)){
		res = "initialise_xhci";
	}
	extern void load_elf_segment();
	if(input>=((uint64_t)&load_elf_segment)){
		res = "load_elf_segment";
	}
	extern void load_elf_executable();
	if(input>=((uint64_t)&load_elf_executable)){
		res = "load_elf_executable";
	}
	extern void load_test_executable();
	if(input>=((uint64_t)&load_test_executable)){
		res = "load_test_executable";
	}
	extern void fat_dump_mbr_entry();
	if(input>=((uint64_t)&fat_dump_mbr_entry)){
		res = "fat_dump_mbr_entry";
	}
	extern void fat_dump_mbr();
	if(input>=((uint64_t)&fat_dump_mbr)){
		res = "fat_dump_mbr";
	}
	extern void fat_dump_file();
	if(input>=((uint64_t)&fat_dump_file)){
		res = "fat_dump_file";
	}
	extern void fat_dump_filesystem();
	if(input>=((uint64_t)&fat_dump_filesystem)){
		res = "fat_dump_filesystem";
	}
	extern void fat_dump_boot_block();
	if(input>=((uint64_t)&fat_dump_boot_block)){
		res = "fat_dump_boot_block";
	}
	extern void fat_filesystem_is_enabled();
	if(input>=((uint64_t)&fat_filesystem_is_enabled)){
		res = "fat_filesystem_is_enabled";
	}
	extern void fat_read();
	if(input>=((uint64_t)&fat_read)){
		res = "fat_read";
	}
	extern void fat_compare_filenames();
	if(input>=((uint64_t)&fat_compare_filenames)){
		res = "fat_compare_filenames";
	}
	extern void fat_open();
	if(input>=((uint64_t)&fat_open)){
		res = "fat_open";
	}
	extern void fat_dir();
	if(input>=((uint64_t)&fat_dir)){
		res = "fat_dir";
	}
	extern void fat_initialise_fat();
	if(input>=((uint64_t)&fat_initialise_fat)){
		res = "fat_initialise_fat";
	}
	extern void fat_handle_partition();
	if(input>=((uint64_t)&fat_handle_partition)){
		res = "fat_handle_partition";
	}
	extern void clearFatDetection();
	if(input>=((uint64_t)&clearFatDetection)){
		res = "clearFatDetection";
	}
	extern void detect_fat();
	if(input>=((uint64_t)&detect_fat)){
		res = "detect_fat";
	}
	extern void convertRightBMPColor();
	if(input>=((uint64_t)&convertRightBMPColor)){
		res = "convertRightBMPColor";
	}
	extern void dumpBMP();
	if(input>=((uint64_t)&dumpBMP)){
		res = "dumpBMP";
	}
	extern void displayBMP();
	if(input>=((uint64_t)&displayBMP)){
		res = "displayBMP";
	}
	extern void getDefaultPSFFontBuffer();
	if(input>=((uint64_t)&getDefaultPSFFontBuffer)){
		res = "getDefaultPSFFontBuffer";
	}
	extern void getDefaultFont();
	if(input>=((uint64_t)&getDefaultFont)){
		res = "getDefaultFont";
	}
	extern void setActiveFont();
	if(input>=((uint64_t)&setActiveFont)){
		res = "setActiveFont";
	}
	extern void getActiveFont();
	if(input>=((uint64_t)&getActiveFont)){
		res = "getActiveFont";
	}
	extern void loadDefaultFont();
	if(input>=((uint64_t)&loadDefaultFont)){
		res = "loadDefaultFont";
	}
	extern void drawCharacterInDefaultFont();
	if(input>=((uint64_t)&drawCharacterInDefaultFont)){
		res = "drawCharacterInDefaultFont";
	}
	extern void getCharacterWidth();
	if(input>=((uint64_t)&getCharacterWidth)){
		res = "getCharacterWidth";
	}
	extern void getCharacterHeight();
	if(input>=((uint64_t)&getCharacterHeight)){
		res = "getCharacterHeight";
	}
	extern void drawCharacter();
	if(input>=((uint64_t)&drawCharacter)){
		res = "drawCharacter";
	}
	extern void draw_pixel_at();
	if(input>=((uint64_t)&draw_pixel_at)){
		res = "draw_pixel_at";
	}
	extern void getTextCursorBoundry();
	if(input>=((uint64_t)&getTextCursorBoundry)){
		res = "getTextCursorBoundry";
	}
	extern void clear_screen();
	if(input>=((uint64_t)&clear_screen)){
		res = "clear_screen";
	}
	extern void getScreenWidth();
	if(input>=((uint64_t)&getScreenWidth)){
		res = "getScreenWidth";
	}
	extern void getScreenHeight();
	if(input>=((uint64_t)&getScreenHeight)){
		res = "getScreenHeight";
	}
	extern void set_text_cursor_position();
	if(input>=((uint64_t)&set_text_cursor_position)){
		res = "set_text_cursor_position";
	}
	extern void do_teletype_character();
	if(input>=((uint64_t)&do_teletype_character)){
		res = "do_teletype_character";
	}
	extern void getTextCursorPositionX();
	if(input>=((uint64_t)&getTextCursorPositionX)){
		res = "getTextCursorPositionX";
	}
	extern void getTextCursorPositionY();
	if(input>=((uint64_t)&getTextCursorPositionY)){
		res = "getTextCursorPositionY";
	}
	extern void putc();
	if(input>=((uint64_t)&putc)){
		res = "putc";
	}
	extern void initialise_graphics_driver();
	if(input>=((uint64_t)&initialise_graphics_driver)){
		res = "initialise_graphics_driver";
	}
	extern void get_ioapic_base();
	if(input>=((uint64_t)&get_ioapic_base)){
		res = "get_ioapic_base";
	}
	extern void acpi_scan_for_rsdp();
	if(input>=((uint64_t)&acpi_scan_for_rsdp)){
		res = "acpi_scan_for_rsdp";
	}
	extern void acpi_dump_rsdp();
	if(input>=((uint64_t)&acpi_dump_rsdp)){
		res = "acpi_dump_rsdp";
	}
	extern void acpi_dump_xsdt();
	if(input>=((uint64_t)&acpi_dump_xsdt)){
		res = "acpi_dump_xsdt";
	}
	extern void parse_apic_table();
	if(input>=((uint64_t)&parse_apic_table)){
		res = "parse_apic_table";
	}
	extern void initialise_acpi();
	if(input>=((uint64_t)&initialise_acpi)){
		res = "initialise_acpi";
	}
	extern void get_apic_base();
	if(input>=((uint64_t)&get_apic_base)){
		res = "get_apic_base";
	}
	extern void apic_is_enabled();
	if(input>=((uint64_t)&apic_is_enabled)){
		res = "apic_is_enabled";
	}
	extern void set_apic_base();
	if(input>=((uint64_t)&set_apic_base)){
		res = "set_apic_base";
	}
	extern void read_apic_register();
	if(input>=((uint64_t)&read_apic_register)){
		res = "read_apic_register";
	}
	extern void write_apic_register();
	if(input>=((uint64_t)&write_apic_register)){
		res = "write_apic_register";
	}
	extern void get_local_apic_id();
	if(input>=((uint64_t)&get_local_apic_id)){
		res = "get_local_apic_id";
	}
	extern void get_local_apic_raw_version_register();
	if(input>=((uint64_t)&get_local_apic_raw_version_register)){
		res = "get_local_apic_raw_version_register";
	}
	extern void get_local_apic_version();
	if(input>=((uint64_t)&get_local_apic_version)){
		res = "get_local_apic_version";
	}
	extern void get_local_apic_max_lvt_entry();
	if(input>=((uint64_t)&get_local_apic_max_lvt_entry)){
		res = "get_local_apic_max_lvt_entry";
	}
	extern void get_local_apic_supports_eoi_suppresion();
	if(input>=((uint64_t)&get_local_apic_supports_eoi_suppresion)){
		res = "get_local_apic_supports_eoi_suppresion";
	}
	extern void set_lvt_cmci_register();
	if(input>=((uint64_t)&set_lvt_cmci_register)){
		res = "set_lvt_cmci_register";
	}
	extern void set_lvt_timer_register();
	if(input>=((uint64_t)&set_lvt_timer_register)){
		res = "set_lvt_timer_register";
	}
	extern void set_lvt_termal_monitor_register();
	if(input>=((uint64_t)&set_lvt_termal_monitor_register)){
		res = "set_lvt_termal_monitor_register";
	}
	extern void set_lvt_performance_counter_register();
	if(input>=((uint64_t)&set_lvt_performance_counter_register)){
		res = "set_lvt_performance_counter_register";
	}
	extern void set_lvt_lint0_register();
	if(input>=((uint64_t)&set_lvt_lint0_register)){
		res = "set_lvt_lint0_register";
	}
	extern void set_lvt_lint1_register();
	if(input>=((uint64_t)&set_lvt_lint1_register)){
		res = "set_lvt_lint1_register";
	}
	extern void set_lvt_error_register();
	if(input>=((uint64_t)&set_lvt_error_register)){
		res = "set_lvt_error_register";
	}
	extern void apic_eoi();
	if(input>=((uint64_t)&apic_eoi)){
		res = "apic_eoi";
	}
	extern void set_apic_timer_values();
	if(input>=((uint64_t)&set_apic_timer_values)){
		res = "set_apic_timer_values";
	}
	extern void debug_apic();
	if(input>=((uint64_t)&debug_apic)){
		res = "debug_apic";
	}
	extern void apic_get_interrupt_number();
	if(input>=((uint64_t)&apic_get_interrupt_number)){
		res = "apic_get_interrupt_number";
	}
	extern void initialise_apic();
	if(input>=((uint64_t)&initialise_apic)){
		res = "initialise_apic";
	}
	extern void outportb();
	if(input>=((uint64_t)&outportb)){
		res = "outportb";
	}
	extern void inportb();
	if(input>=((uint64_t)&inportb)){
		res = "inportb";
	}
	extern void outportw();
	if(input>=((uint64_t)&outportw)){
		res = "outportw";
	}
	extern void inportw();
	if(input>=((uint64_t)&inportw)){
		res = "inportw";
	}
	extern void outportl();
	if(input>=((uint64_t)&outportl)){
		res = "outportl";
	}
	extern void inportl();
	if(input>=((uint64_t)&inportl)){
		res = "inportl";
	}
	extern void getCR0();
	if(input>=((uint64_t)&getCR0)){
		res = "getCR0";
	}
	extern void getCR2();
	if(input>=((uint64_t)&getCR2)){
		res = "getCR2";
	}
	extern void getCR3();
	if(input>=((uint64_t)&getCR3)){
		res = "getCR3";
	}
	extern void getCR4();
	if(input>=((uint64_t)&getCR4)){
		res = "getCR4";
	}
	extern void setCR0();
	if(input>=((uint64_t)&setCR0)){
		res = "setCR0";
	}
	extern void setCR2();
	if(input>=((uint64_t)&setCR2)){
		res = "setCR2";
	}
	extern void setCR3();
	if(input>=((uint64_t)&setCR3)){
		res = "setCR3";
	}
	extern void setCR4();
	if(input>=((uint64_t)&setCR4)){
		res = "setCR4";
	}
	extern void hlt();
	if(input>=((uint64_t)&hlt)){
		res = "hlt";
	}
	extern void cli();
	if(input>=((uint64_t)&cli)){
		res = "cli";
	}
	extern void sti();
	if(input>=((uint64_t)&sti)){
		res = "sti";
	}
	extern void get_model();
	if(input>=((uint64_t)&get_model)){
		res = "get_model";
	}
	extern void check_apic();
	if(input>=((uint64_t)&check_apic)){
		res = "check_apic";
	}
	extern void cpuid();
	if(input>=((uint64_t)&cpuid)){
		res = "cpuid";
	}
	extern void cpuid_string();
	if(input>=((uint64_t)&cpuid_string)){
		res = "cpuid_string";
	}
	extern void get_cpu_info();
	if(input>=((uint64_t)&get_cpu_info)){
		res = "get_cpu_info";
	}
	extern void get_cpu_feature_information();
	if(input>=((uint64_t)&get_cpu_feature_information)){
		res = "get_cpu_feature_information";
	}
	extern void cpu_has_model_specific_registers();
	if(input>=((uint64_t)&cpu_has_model_specific_registers)){
		res = "cpu_has_model_specific_registers";
	}
	extern void cpu_get_specific_registers();
	if(input>=((uint64_t)&cpu_get_specific_registers)){
		res = "cpu_get_specific_registers";
	}
	extern void cpu_set_specific_registers();
	if(input>=((uint64_t)&cpu_set_specific_registers)){
		res = "cpu_set_specific_registers";
	}
	extern void __stack_chk_fail();
	if(input>=((uint64_t)&__stack_chk_fail)){
		res = "__stack_chk_fail";
	}
	extern void __stack_chk_fail_local();
	if(input>=((uint64_t)&__stack_chk_fail_local)){
		res = "__stack_chk_fail_local";
	}
	extern void cpu_get_current_ring();
	if(input>=((uint64_t)&cpu_get_current_ring)){
		res = "cpu_get_current_ring";
	}
	extern void cpu_get_ring_from_cs();
	if(input>=((uint64_t)&cpu_get_ring_from_cs)){
		res = "cpu_get_ring_from_cs";
	}
	extern void set_gdt_entry();
	if(input>=((uint64_t)&set_gdt_entry)){
		res = "set_gdt_entry";
	}
	extern void set_tss_descriptor();
	if(input>=((uint64_t)&set_tss_descriptor)){
		res = "set_tss_descriptor";
	}
	extern void x64_load_ltr();
	if(input>=((uint64_t)&x64_load_ltr)){
		res = "x64_load_ltr";
	}
	extern void initialize_gdt();
	if(input>=((uint64_t)&initialize_gdt)){
		res = "initialize_gdt";
	}
	extern void interrupt_eoi();
	if(input>=((uint64_t)&interrupt_eoi)){
		res = "interrupt_eoi";
	}
	extern void interrupt_get_int_number();
	if(input>=((uint64_t)&interrupt_get_int_number)){
		res = "interrupt_get_int_number";
	}
	extern void print_callstack();
	if(input>=((uint64_t)&print_callstack)){
		res = "print_callstack";
	}
	extern void MasterInteruptHandler00();
	if(input>=((uint64_t)&MasterInteruptHandler00)){
		res = "MasterInteruptHandler00";
	}
	extern void MasterInteruptHandler01();
	if(input>=((uint64_t)&MasterInteruptHandler01)){
		res = "MasterInteruptHandler01";
	}
	extern void MasterInteruptHandler02();
	if(input>=((uint64_t)&MasterInteruptHandler02)){
		res = "MasterInteruptHandler02";
	}
	extern void MasterInteruptHandler03();
	if(input>=((uint64_t)&MasterInteruptHandler03)){
		res = "MasterInteruptHandler03";
	}
	extern void MasterInteruptHandler04();
	if(input>=((uint64_t)&MasterInteruptHandler04)){
		res = "MasterInteruptHandler04";
	}
	extern void MasterInteruptHandler05();
	if(input>=((uint64_t)&MasterInteruptHandler05)){
		res = "MasterInteruptHandler05";
	}
	extern void MasterInteruptHandler06();
	if(input>=((uint64_t)&MasterInteruptHandler06)){
		res = "MasterInteruptHandler06";
	}
	extern void MasterInteruptHandler07();
	if(input>=((uint64_t)&MasterInteruptHandler07)){
		res = "MasterInteruptHandler07";
	}
	extern void MasterInteruptHandler08();
	if(input>=((uint64_t)&MasterInteruptHandler08)){
		res = "MasterInteruptHandler08";
	}
	extern void MasterInteruptHandler09();
	if(input>=((uint64_t)&MasterInteruptHandler09)){
		res = "MasterInteruptHandler09";
	}
	extern void MasterInteruptHandler0a();
	if(input>=((uint64_t)&MasterInteruptHandler0a)){
		res = "MasterInteruptHandler0a";
	}
	extern void MasterInteruptHandler0b();
	if(input>=((uint64_t)&MasterInteruptHandler0b)){
		res = "MasterInteruptHandler0b";
	}
	extern void MasterInteruptHandler0c();
	if(input>=((uint64_t)&MasterInteruptHandler0c)){
		res = "MasterInteruptHandler0c";
	}
	extern void MasterInteruptHandler0d();
	if(input>=((uint64_t)&MasterInteruptHandler0d)){
		res = "MasterInteruptHandler0d";
	}
	extern void MasterInteruptHandler0e();
	if(input>=((uint64_t)&MasterInteruptHandler0e)){
		res = "MasterInteruptHandler0e";
	}
	extern void MasterInteruptHandler0f();
	if(input>=((uint64_t)&MasterInteruptHandler0f)){
		res = "MasterInteruptHandler0f";
	}
	extern void MasterInteruptHandler10();
	if(input>=((uint64_t)&MasterInteruptHandler10)){
		res = "MasterInteruptHandler10";
	}
	extern void MasterInteruptHandler11();
	if(input>=((uint64_t)&MasterInteruptHandler11)){
		res = "MasterInteruptHandler11";
	}
	extern void MasterInteruptHandler12();
	if(input>=((uint64_t)&MasterInteruptHandler12)){
		res = "MasterInteruptHandler12";
	}
	extern void MasterInteruptHandler13();
	if(input>=((uint64_t)&MasterInteruptHandler13)){
		res = "MasterInteruptHandler13";
	}
	extern void MasterInteruptHandler14();
	if(input>=((uint64_t)&MasterInteruptHandler14)){
		res = "MasterInteruptHandler14";
	}
	extern void MasterInteruptHandler15();
	if(input>=((uint64_t)&MasterInteruptHandler15)){
		res = "MasterInteruptHandler15";
	}
	extern void MasterInteruptHandler16();
	if(input>=((uint64_t)&MasterInteruptHandler16)){
		res = "MasterInteruptHandler16";
	}
	extern void MasterInteruptHandler17();
	if(input>=((uint64_t)&MasterInteruptHandler17)){
		res = "MasterInteruptHandler17";
	}
	extern void MasterInteruptHandler18();
	if(input>=((uint64_t)&MasterInteruptHandler18)){
		res = "MasterInteruptHandler18";
	}
	extern void MasterInteruptHandler19();
	if(input>=((uint64_t)&MasterInteruptHandler19)){
		res = "MasterInteruptHandler19";
	}
	extern void MasterInteruptHandler1a();
	if(input>=((uint64_t)&MasterInteruptHandler1a)){
		res = "MasterInteruptHandler1a";
	}
	extern void MasterInteruptHandler1b();
	if(input>=((uint64_t)&MasterInteruptHandler1b)){
		res = "MasterInteruptHandler1b";
	}
	extern void MasterInteruptHandler1c();
	if(input>=((uint64_t)&MasterInteruptHandler1c)){
		res = "MasterInteruptHandler1c";
	}
	extern void MasterInteruptHandler1d();
	if(input>=((uint64_t)&MasterInteruptHandler1d)){
		res = "MasterInteruptHandler1d";
	}
	extern void MasterInteruptHandler1e();
	if(input>=((uint64_t)&MasterInteruptHandler1e)){
		res = "MasterInteruptHandler1e";
	}
	extern void MasterInteruptHandler1f();
	if(input>=((uint64_t)&MasterInteruptHandler1f)){
		res = "MasterInteruptHandler1f";
	}
	extern void GeneralFault_Handler();
	if(input>=((uint64_t)&GeneralFault_Handler)){
		res = "GeneralFault_Handler";
	}
	extern void NakedInterruptHandler();
	if(input>=((uint64_t)&NakedInterruptHandler)){
		res = "NakedInterruptHandler";
	}
	extern void interrupt_set_offset();
	if(input>=((uint64_t)&interrupt_set_offset)){
		res = "interrupt_set_offset";
	}
	extern void setRawInterrupt();
	if(input>=((uint64_t)&setRawInterrupt)){
		res = "setRawInterrupt";
	}
	extern void setInterrupt();
	if(input>=((uint64_t)&setInterrupt)){
		res = "setInterrupt";
	}
	extern void interrupts_disable();
	if(input>=((uint64_t)&interrupts_disable)){
		res = "interrupts_disable";
	}
	extern void interrupts_enable();
	if(input>=((uint64_t)&interrupts_enable)){
		res = "interrupts_enable";
	}
	extern void initialise_interrupts();
	if(input>=((uint64_t)&initialise_interrupts)){
		res = "initialise_interrupts";
	}
	extern void ioapic_is_enabled();
	if(input>=((uint64_t)&ioapic_is_enabled)){
		res = "ioapic_is_enabled";
	}
	extern void ioapic_write();
	if(input>=((uint64_t)&ioapic_write)){
		res = "ioapic_write";
	}
	extern void ioapic_read();
	if(input>=((uint64_t)&ioapic_read)){
		res = "ioapic_read";
	}
	extern void ioapic_set_redirection();
	if(input>=((uint64_t)&ioapic_set_redirection)){
		res = "ioapic_set_redirection";
	}
	extern void getMemoryInfoBlockCount();
	if(input>=((uint64_t)&getMemoryInfoBlockCount)){
		res = "getMemoryInfoBlockCount";
	}
	extern void memory_region_dump();
	if(input>=((uint64_t)&memory_region_dump)){
		res = "memory_region_dump";
	}
	extern void initialise_memory();
	if(input>=((uint64_t)&initialise_memory)){
		res = "initialise_memory";
	}
	extern void memset();
	if(input>=((uint64_t)&memset)){
		res = "memset";
	}
	extern void memcpy();
	if(input>=((uint64_t)&memcpy)){
		res = "memcpy";
	}
	extern void memclear();
	if(input>=((uint64_t)&memclear)){
		res = "memclear";
	}
	extern void malloc();
	if(input>=((uint64_t)&malloc)){
		res = "malloc";
	}
	extern void markMemoryRegionUsed();
	if(input>=((uint64_t)&markMemoryRegionUsed)){
		res = "markMemoryRegionUsed";
	}
	extern void calloc();
	if(input>=((uint64_t)&calloc)){
		res = "calloc";
	}
	extern void free();
	if(input>=((uint64_t)&free)){
		res = "free";
	}
	extern void is_whole_page_free();
	if(input>=((uint64_t)&is_whole_page_free)){
		res = "is_whole_page_free";
	}
	extern void alloc_whole_page_free();
	if(input>=((uint64_t)&alloc_whole_page_free)){
		res = "alloc_whole_page_free";
	}
	extern void malloc_whole_page();
	if(input>=((uint64_t)&malloc_whole_page)){
		res = "malloc_whole_page";
	}
	extern void page_map_indexer();
	if(input>=((uint64_t)&page_map_indexer)){
		res = "page_map_indexer";
	}
	extern void map_memory();
	if(input>=((uint64_t)&map_memory)){
		res = "map_memory";
	}
	extern void define_linear_memory_block();
	if(input>=((uint64_t)&define_linear_memory_block)){
		res = "define_linear_memory_block";
	}
	extern void define_seperate_memory_block();
	if(input>=((uint64_t)&define_seperate_memory_block)){
		res = "define_seperate_memory_block";
	}
	extern void initialise_paging();
	if(input>=((uint64_t)&initialise_paging)){
		res = "initialise_paging";
	}
	extern void reset_pic();
	if(input>=((uint64_t)&reset_pic)){
		res = "reset_pic";
	}
	extern void initialise_pic();
	if(input>=((uint64_t)&initialise_pic)){
		res = "initialise_pic";
	}
	extern void pic_eoi();
	if(input>=((uint64_t)&pic_eoi)){
		res = "pic_eoi";
	}
	extern void pic_get_interrupt_number();
	if(input>=((uint64_t)&pic_get_interrupt_number)){
		res = "pic_get_interrupt_number";
	}
	extern void disable_pic();
	if(input>=((uint64_t)&disable_pic)){
		res = "disable_pic";
	}
	extern void convertl();
	if(input>=((uint64_t)&convertl)){
		res = "convertl";
	}
	extern void convert();
	if(input>=((uint64_t)&convert)){
		res = "convert";
	}
	extern void character_is_control_character();
	if(input>=((uint64_t)&character_is_control_character)){
		res = "character_is_control_character";
	}
	extern void print_raw_string();
	if(input>=((uint64_t)&print_raw_string)){
		res = "print_raw_string";
	}
	extern void printk();
	if(input>=((uint64_t)&printk)){
		res = "printk";
	}
	extern void dump_syscall_regs();
	if(input>=((uint64_t)&dump_syscall_regs)){
		res = "dump_syscall_regs";
	}
	extern void syscallprobe();
	if(input>=((uint64_t)&syscallprobe)){
		res = "syscallprobe";
	}
	extern void syscall_enable();
	if(input>=((uint64_t)&syscall_enable)){
		res = "syscall_enable";
	}
	extern void syscall_set_segments();
	if(input>=((uint64_t)&syscall_set_segments)){
		res = "syscall_set_segments";
	}
	extern void syscall_set_entry_point();
	if(input>=((uint64_t)&syscall_set_entry_point)){
		res = "syscall_set_entry_point";
	}
	extern void syscall_set_mask();
	if(input>=((uint64_t)&syscall_set_mask)){
		res = "syscall_set_mask";
	}
	extern void initialise_syscall();
	if(input>=((uint64_t)&initialise_syscall)){
		res = "initialise_syscall";
	}
	extern void kernel_main();
	if(input>=((uint64_t)&kernel_main)){
		res = "kernel_main";
	}
	extern void gdt_flush();
	if(input>=((uint64_t)&gdt_flush)){
		res = "gdt_flush";
	}
	extern void call_stack_push();
	if(input>=((uint64_t)&call_stack_push)){
		res = "call_stack_push";
	}
	extern void call_stack_pop();
	if(input>=((uint64_t)&call_stack_pop)){
		res = "call_stack_pop";
	}
	extern void stack_push();
	if(input>=((uint64_t)&stack_push)){
		res = "stack_push";
	}
	extern void stack_pop();
	if(input>=((uint64_t)&stack_pop)){
		res = "stack_pop";
	}
	extern void grab_next_instruction();
	if(input>=((uint64_t)&grab_next_instruction)){
		res = "grab_next_instruction";
	}
	extern void grab_next_argument();
	if(input>=((uint64_t)&grab_next_argument)){
		res = "grab_next_argument";
	}
	extern void add_instruction_pointer_uint8();
	if(input>=((uint64_t)&add_instruction_pointer_uint8)){
		res = "add_instruction_pointer_uint8";
	}
	extern void add_instruction_pointer_uint64();
	if(input>=((uint64_t)&add_instruction_pointer_uint64)){
		res = "add_instruction_pointer_uint64";
	}
	extern void handle_next_instruction();
	if(input>=((uint64_t)&handle_next_instruction)){
		res = "handle_next_instruction";
	}
	extern void insert_stapel_cardridge();
	if(input>=((uint64_t)&insert_stapel_cardridge)){
		res = "insert_stapel_cardridge";
	}
	extern void syscallentrypoint();
	if(input>=((uint64_t)&syscallentrypoint)){
		res = "syscallentrypoint";
	}
	extern void jump_usermode();
	if(input>=((uint64_t)&jump_usermode)){
		res = "jump_usermode";
	}
	return res;
}
