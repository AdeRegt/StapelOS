#include "../include/string.h"
#include "../include/cpu.h"
#include "../include/timer.h"
#include "../include/ps2_keyboard.h"
#include "../include/interrupts.h"

unsigned char kbdus[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 9 */
    '9', '0', '-', '=', '\b',                         /* Backspace */
    '\t',                                             /* Tab */
    'q', 'w', 'e', 'r',                               /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     /* Enter key */
    0,                                                /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`', 0,                              /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',               /* 49 */
    'm', ',', '.', '/', 0,                     /* Right shift */
    '*',
    0,   /* Alt */
    ' ', /* Space bar */
    0,   /* Caps lock */
    0,   /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0,     /* < ... F10 */
    0,     /* 69 - Num lock*/
    0,     /* Scroll Lock */
    0,     /* Home key */
    0, /* Up Arrow */
    0,     /* Page Up */
    '-',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
    '+',
    1,       /* 79 - End key*/
    0, /* Down Arrow */
    0,       /* Page Down */
    0,       /* Insert Key */
    0,       /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

unsigned char KBDUS[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*',    /* 9 */
    '(', ')', '_', '+', '\b',                         /* Backspace */
    '\t',                                             /* Tab */
    'Q', 'W', 'E', 'R',                               /* 19 */
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',     /* Enter key */
    0,                                                /* 29   - Control */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
    '\"', '~', 0,                              /* Left shift */
    '|', 'Z', 'X', 'C', 'V', 'B', 'N',                /* 49 */
    'M', '<', '>', '?', 0,                     /* Right shift */
    '*',
    0,   /* Alt */
    ' ', /* Space bar */
    0,   /* Caps lock */
    0,   /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0,     /* < ... F10 */
    0,     /* 69 - Num lock*/
    0,     /* Scroll Lock */
    0,     /* Home key */
    0, /* Up Arrow */
    0,     /* Page Up */
    '-',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
    '+',
    1,       /* 79 - End key*/
    0, /* Down Arrow */
    0,       /* Page Down */
    0,       /* Insert Key */
    0,       /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

uint8_t ps2_read_status_register(){
    return inportb(PS2_STATUS_REGISTER);
}

uint8_t ps2_read_data_port(){
    while((ps2_read_status_register()&PS2_STATUS_FLAG_OUTPUT_BUFFER_STATUS)==0);
    return inportb(PS2_DATA_REGISTER);
}

void ps2_write_data_port(uint8_t data){
    while((ps2_read_status_register()&PS2_STATUS_FLAG_INPUT_BUFFER_STATUS)==1);
    outportb(PS2_DATA_REGISTER,data);
}

void ps2_write_command_register(uint8_t data){
    while((ps2_read_status_register()&PS2_STATUS_FLAG_INPUT_BUFFER_STATUS)==1);
    outportb(PS2_COMMAND_REGISTER,data);
}

uint8_t ps2_chip_echo(){
    ps2_write_data_port(PS2_DATA_COMMAND_ECHO);
    uint8_t res = ps2_read_data_port();
    if(res!=PS2_DATA_COMMAND_ECHO){
        printk("unexpected responsein %s !=%x \n",__func__,res);
        return 0;
    }
    return 1;
}

uint8_t ps2_chip_reset(){
    ps2_write_data_port(PS2_DATA_COMMAND_RESET);
    uint8_t res = ps2_read_data_port();
    if(res!=PS2_DATA_RESPONSE_ACK){
        printk("unexpected responsein %s !=%x \n",__func__,res);
        return 0;
    }
    res = ps2_read_data_port();
    if(res!=PS2_DATA_RESPONSE_SELF_TEST_PASSED){
        printk("unexpected responsein %s !=%x \n",__func__,res);
        return 0;
    }
    return 1;
}

uint8_t ps2_chip_set_default_parameters(){
    ps2_write_data_port(PS2_DATA_COMMAND_DEFAULTS);
    uint8_t res = ps2_read_data_port();
    if(res!=PS2_DATA_RESPONSE_ACK){
        printk("unexpected responsein %s !=%x \n",__func__,res);
        return 0;
    }
    return 1;
}

uint8_t ps2_chip_get_current_scancode_set(){
    ps2_write_data_port(PS2_DATA_COMMAND_SCANCODESET);
    sleep(2);
    ps2_write_data_port(0);
    sleep(2);
    uint8_t res = ps2_read_data_port();
    sleep(2);
    if(res!=PS2_DATA_RESPONSE_ACK){
        printk("unexpected responsein %s !=%x \n",__func__,res);
        return 0;
    }
    sleep(2);
    return ps2_read_data_port();
}

uint8_t ps2_chip_enablescanning(){
    ps2_write_data_port(PS2_DATA_COMMAND_ENABLESCANNING);
    uint8_t res = ps2_read_data_port();
    if(res!=PS2_DATA_RESPONSE_ACK){
        printk("unexpected responsein %s !=%x \n",__func__,res);
        return 0;
    }
    return 1;
}

uint8_t* getKeymapFor(uint8_t flags){
    if(flags&0x01){ // capitalise
        return KBDUS;
    }
    return kbdus;
}

uint8_t scancode_to_char(uint8_t code,uint8_t shift){
    return getKeymapFor(shift)[code];
}

static uint8_t shift_is_pressed = 0;
static uint8_t ctrl_is_pressed = 0;
static uint8_t alt_is_pressed = 0;
static uint8_t getcbuffer = 0;
__attribute__((interrupt)) void irq_keyboard(interrupt_frame *frame){
    uint8_t scancode = ps2_read_data_port();
    if(scancode==0x2A||scancode==0x36){
        shift_is_pressed = 1;
    }else if(scancode==0xAA||scancode==0xB6){
        shift_is_pressed = 0;
    }else if(scancode==0x1D||scancode==0xE0){
        ctrl_is_pressed = 1;
    }else if(scancode==0x9D){
        ctrl_is_pressed = 0;
    }else if(scancode==0x38){
        alt_is_pressed = 1;
    }else if(scancode==0xB8){
        alt_is_pressed = 0;
    }else{ 
        if((scancode&0x80)==0){
            getcbuffer = scancode_to_char(scancode,shift_is_pressed);
            // printk("Key is pressed with code %x generating %c [ shift:%x | ctrl:%x | alt:%x ] \n",scancode,getcbuffer,shift_is_pressed,ctrl_is_pressed,alt_is_pressed);
        }
    }
    outportb(0x20,0x20);
}

uint8_t getch(){
    uint8_t t = getcbuffer;
    getcbuffer = 0;
    return t;
}

void initialise_ps2_keyboard(){
    if(ps2_chip_echo()==0){
        return;
    }
    if(ps2_chip_reset()==0){
        return;
    }
    if(ps2_chip_set_default_parameters()==0){
        return;
    }
    if(ps2_chip_get_current_scancode_set()!=0x41){
        printk("%s: unexpected scancode set , it returns: %x \n",__func__,ps2_chip_get_current_scancode_set());
        return;
    }
    setInterrupt(1, irq_keyboard);
    if(ps2_chip_enablescanning()==0){
        return;
    }
}