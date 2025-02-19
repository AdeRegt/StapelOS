#pragma once 
#include <stdint.h>

#define BMP_SIGNATURE_0 'B'
#define BMP_SIGNATURE_1 'M'

typedef struct {
	uint8_t signature[2];
	uint32_t sizeofbmp;
	uint32_t unused1;
	uint32_t offset_to_pixelarray;
	uint32_t bytes_in_DIB;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bits_per_pixel;
	uint32_t compression;
}  __attribute__((packed)) BMP_HEADER;

void displayBMP(void* data,int x,int y);