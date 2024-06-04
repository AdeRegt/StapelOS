#include <stdint.h>

typedef struct {
	uint8_t magic[2];
	uint8_t mode;
	uint8_t charsize;
} PSF1_Header;

typedef struct {
	PSF1_Header* psf1_Header;
	void* glyphBuffer;
} PSF1_Font;

PSF1_Font* getDefaultFont();
void setActiveFont(PSF1_Font *av);
PSF1_Font *getActiveFont();
void drawCharacter(PSF1_Font *font,char character,unsigned int colour,unsigned long xOff,unsigned long yOff);
void drawCharacterInDefaultFont(char character,unsigned int colour,unsigned long x , unsigned long y);
void loadDefaultFont();
uint8_t getCharacterWidth();
uint8_t getCharacterHeight();
