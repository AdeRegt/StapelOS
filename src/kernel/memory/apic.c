#include "../include/apic.h"
#include "../include/cpu.h"
#include "../include/string.h"
#include "../include/paging.h"

void* apicbase;

void *get_apic_base(){
    uint32_t eax, edx;
    cpu_get_specific_registers(IA32_APIC_BASE_MSR, &eax, &edx);
    return (void*) ((uint64_t)((eax & 0xfffff000)));
}

uint8_t apic_is_enabled(){
    uint32_t eax, edx;
    cpu_get_specific_registers(IA32_APIC_BASE_MSR, &eax, &edx);
    return (eax & 0x800)>0;
}

void set_apic_base(void* addr){
    uint32_t edx = 0;
	uint32_t eax = ((uint64_t)addr & 0xfffff100) | IA32_APIC_BASE_MSR_ENABLE;

	cpu_set_specific_registers(IA32_APIC_BASE_MSR, eax, edx);
}

uint32_t read_apic_register(uint64_t offset){
    uint64_t addr = ((uint64_t)apicbase)+offset;
    return ((volatile uint32_t*)(addr))[0];
}

void write_apic_register(uint64_t offset,uint32_t message){
    uint64_t addr = ((uint64_t)apicbase)+offset;
    ((volatile uint32_t*)(addr))[0] = message;
}

uint8_t get_local_apic_id(){
    return ((read_apic_register(0x20))>>24)&0xFF;
}

uint32_t get_local_apic_raw_version_register(){
    return read_apic_register(0x30);
}

uint8_t get_local_apic_version(){
    return get_local_apic_raw_version_register() && 0xFF;
}

uint8_t get_local_apic_max_lvt_entry(){
    return (get_local_apic_raw_version_register() >> 16) && 0xFF;
}

uint8_t get_local_apic_supports_eoi_suppresion(){
    return (get_local_apic_raw_version_register() >> 24) & 1;
}

void set_lvt_cmci_register(uint8_t vector,uint8_t delivery_mode,uint8_t delivery_status,uint8_t mask){
    uint32_t val = 0;
    val |= vector;
    val |= delivery_mode<<8;
    val |= delivery_status<<12;
    val |= mask<<16;
    write_apic_register(0x2F0,val);
}

void set_lvt_timer_register(uint8_t vector,uint8_t delivery_status,uint8_t mask,uint8_t timer_mode){
    uint32_t val = 0;
    val |= vector;
    val |= delivery_status<<12;
    val |= mask<<16;
    val |= timer_mode<<17;
    write_apic_register(0x320,val);
}

void set_lvt_termal_monitor_register(uint8_t vector,uint8_t delivery_mode,uint8_t delivery_status,uint8_t mask){
    uint32_t val = 0;
    val |= vector;
    val |= delivery_mode<<8;
    val |= delivery_status<<12;
    val |= mask<<16;
    write_apic_register(0x330,val);
}

void set_lvt_performance_counter_register(uint8_t vector,uint8_t delivery_mode,uint8_t delivery_status,uint8_t mask){
    uint32_t val = 0;
    val |= vector;
    val |= delivery_mode<<8;
    val |= delivery_status<<12;
    val |= mask<<16;
    write_apic_register(0x340,val);
}

void set_lvt_lint0_register(uint8_t vector,uint8_t delivery_mode,uint8_t delivery_status,uint8_t interrupt_input_pin_polarity,uint8_t remote_irr,uint8_t trigger_mode,uint8_t mask){
    uint32_t val = 0;
    val |= vector;
    val |= delivery_mode<<8;
    val |= delivery_status<<12;
    val |= interrupt_input_pin_polarity<<13;
    val |= remote_irr<<14;
    val |= trigger_mode<<15;
    val |= mask<<16;
    write_apic_register(0x350,val);
}

void set_lvt_lint1_register(uint8_t vector,uint8_t delivery_mode,uint8_t delivery_status,uint8_t interrupt_input_pin_polarity,uint8_t remote_irr,uint8_t trigger_mode,uint8_t mask){
    uint32_t val = 0;
    val |= vector;
    val |= delivery_mode<<8;
    val |= delivery_status<<12;
    val |= interrupt_input_pin_polarity<<13;
    val |= remote_irr<<14;
    val |= trigger_mode<<15;
    val |= mask<<16;
    write_apic_register(0x360,val);
}

void set_lvt_error_register(uint8_t vector,uint8_t delivery_status,uint8_t mask){
    uint32_t val = 0;
    val |= vector;
    val |= delivery_status<<12;
    val |= mask<<16;
    write_apic_register(0x370,val);
}

void apic_eoi(){
    write_apic_register(0xB0,0);
}

void set_apic_timer_values(uint32_t vals){
    if(vals){
        write_apic_register(0x380,vals);
    }
}

void debug_apic(){
    printk("cmci: %x , timer: %x , termal: %x , performance: %x , lint0: %x , lint1: %x , error: %x , 0x280: %x \n",read_apic_register(0x2F0),read_apic_register(0x320),read_apic_register(0x330),read_apic_register(0x340),read_apic_register(0x350),read_apic_register(0x360),read_apic_register(0x370),read_apic_register(0x280));
}

uint8_t apic_get_interrupt_number(){
    for(int u = 0 ; u < 8 ; u++){
        for(int i = 0 ; i < 32 ; i++){
            if(read_apic_register(0x100 + (u*0x10)) & (1<<i)){
                return (u*32)+i;
            }
        }
    }
    return 0;
}

void initialise_apic(){
    //
    // According to osdev.org, the local APIC is enabled at boot time, we just need to find it...
    // use: https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf
    apicbase = get_apic_base();
    define_linear_memory_block(apicbase);
    // debug_apic();
    if(((uint64_t)apicbase)!=EXPECTED_APIC_BASE){
        printk("Unexpected APIC base! Expected %x found %x \n",EXPECTED_APIC_BASE,apicbase);
        return ;
    }
    apic_get_interrupt_number();
    set_lvt_cmci_register(0x10,0b101,0,0);
    set_lvt_timer_register(0x21,0,0,1);//1
    set_lvt_termal_monitor_register(0x12,0b101,0,0);
    set_lvt_performance_counter_register(0x13,0b101,0,0);
    set_lvt_lint0_register(0x14,0b101,0,0,0,0,0);
    set_lvt_lint1_register(0x15,0b101,0,0,0,0,0);
    set_lvt_error_register(0x16,0,0);
    if(apic_is_enabled()==0){
        printk("apic is not enabled yet?!\n");
        set_apic_base(get_apic_base());
    }
    write_apic_register(0x280,0xFF);
    set_apic_timer_values(0x200000);
    // debug_apic();
}