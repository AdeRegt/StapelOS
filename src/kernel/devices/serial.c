#include "../include/string.h"
#include "../include/cpu.h"
#include "../include/timer.h"
#include "../include/serial.h"
#include "../include/interrupts.h"

uint16_t serialportnumber_to_address(uint16_t portnumber){
    if(portnumber==1){
        return COM1;
    }
    if(portnumber==2){
        return COM2;
    }
    if(portnumber==3){
        return COM3;
    }
    if(portnumber==4){
        return COM4;
    }
    if(portnumber==5){
        return COM5;
    }
    if(portnumber==6){
        return COM6;
    }
    if(portnumber==7){
        return COM7;
    }
    if(portnumber==8){
        return COM8;
    }
    return 0;
}

int enable_serial_port(uint16_t portnumber){
    uint16_t port = serialportnumber_to_address(portnumber);
    outportb(port + 1, 0x00);    // Disable all interrupts
    outportb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outportb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outportb(port + 1, 0x00);    //                  (hi byte)
    outportb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outportb(port + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outportb(port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(inportb(port + 0) != 0xAE) {
        return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outportb(port + 4, 0x0F);
    return 0;
}

void initialise_serial(){
    for(int i = 1 ; i <= 8 ; i++){
        int r = enable_serial_port(i);
        if(r==0){
            printk("COM port %d is enabled with the return type of %d \n", i, r);
        }
    }
}