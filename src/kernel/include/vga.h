#pragma once
#include "font.h"

typedef struct {
	void* BaseAddress;
	uint64_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
  unsigned char strategy;
} GraphicsInfo;

void initialise_graphics_driver(GraphicsInfo *hi);
void draw_pixel_at(unsigned int x,unsigned int y,unsigned int colour);
void clear_screen();
unsigned int getScreenWidth();
unsigned int getScreenHeight();
void set_text_cursor_position(unsigned int x,unsigned int y);
void do_teletype_character(char t);
unsigned int getTextCursorPositionX();
unsigned int getTextCursorPositionY();
unsigned int getTextCursorBoundry();
void putc(char t);
