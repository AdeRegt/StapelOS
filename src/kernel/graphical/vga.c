#include "../include/vga.h"
#include "../include/string.h"

GraphicsInfo *graphics_info;

void draw_pixel_at(unsigned int x,unsigned int y,unsigned int colour){
    unsigned int BBP = 4;
    *(unsigned int*)((x*BBP) +(y*graphics_info->PixelsPerScanLine*BBP) + graphics_info->BaseAddress) = colour;
}

unsigned int getTextCursorBoundry(){
  return 10;
}

void clear_screen(){
  for(int y = 0 ; y < graphics_info->Height ; y++){
    for(int x = 0 ; x < graphics_info->Width ; x++){
      draw_pixel_at (x, y, 0);
    }
  }
  set_text_cursor_position(getTextCursorBoundry(),getTextCursorBoundry());
}

unsigned int getScreenWidth(){
  return graphics_info->Width;
}

unsigned int getScreenHeight(){
  return graphics_info->Height;
}

unsigned int text_cursor_x = 0;
unsigned int text_cursor_y = 0;

void set_text_cursor_position(unsigned int x,unsigned int y){
  text_cursor_x = x;
  text_cursor_y = y;
}

void do_teletype_character(char t){
  if(t=='\n'){
    goto handlenewline;
  }else{
    text_cursor_x += getCharacterWidth () + 1;
    if(text_cursor_x>=(getScreenWidth () - getTextCursorBoundry ())){
      goto handlenewline;
    }
  }
  return;
  handlenewline:
  text_cursor_x = getTextCursorBoundry ();
  text_cursor_y += getCharacterHeight () + 1;
  if(text_cursor_y>=(getScreenHeight () - getTextCursorBoundry () ))
  {
    clear_screen ();
  }
}

unsigned int getTextCursorPositionX(){
  return text_cursor_x;
}

unsigned int getTextCursorPositionY(){
  return text_cursor_y;
}

void putc(char t){
  if(character_is_control_character(t)==0){
    drawCharacterInDefaultFont(t,0xFFFFFFFF,getTextCursorPositionX(),getTextCursorPositionY());
  }
  do_teletype_character(t);
}

void initialise_graphics_driver(GraphicsInfo* hi){
  graphics_info = hi;
  loadDefaultFont();
  clear_screen();
}
