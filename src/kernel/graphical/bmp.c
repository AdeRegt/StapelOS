#include "../include/bmp.h"
#include "../include/string.h"
#include "../include/vga.h"

unsigned int convertRightBMPColor(BMP_HEADER* header,void* data,uint32_t x,uint32_t y){
    if(header->bits_per_pixel==32){
    void *pixel_buffer = (void*) (data + header->offset_to_pixelarray);
        uint32_t* xxx = (uint32_t*) pixel_buffer;
        return xxx[(y*header->width)+x];
    }else{
        printk("bmp: unknown conversion -> %d \n",header->bits_per_pixel);for(;;);
    }
    return 0;
}

void dumpBMP(BMP_HEADER* header){
    printk("bmp: sizeofbmp               : %d \n",header->sizeofbmp);
    printk("bmp: offset_to_pixelarray    : %d \n",header->offset_to_pixelarray);
	printk("bmp: bytes_in_DIB            : %d \n",header->bytes_in_DIB);
	printk("bmp: width                   : %d \n",header->width);
	printk("bmp: height                  : %d \n",header->height);
	printk("bmp: planes                  : %d \n",header->planes);
	printk("bmp: bits_per_pixel          : %d \n",header->bits_per_pixel);
	printk("bmp: compression             : %d \n",header->compression);
}

void displayBMP(void* data,int offsetX,int offsetY){
    BMP_HEADER* header = (BMP_HEADER*) data;
    if(!(header->signature[0]==BMP_SIGNATURE_0&&header->signature[1]==BMP_SIGNATURE_1)){
        printk("bmp: invalid signature\n");
        return;
    }

    for(uint32_t x = 0 ; x < header->width ; x++){
		for(uint32_t y = 0 ; y < header->height ; y++){
			draw_pixel_at(offsetX + x, offsetY + y, convertRightBMPColor(header,data,x,y));
		}
	}
}
