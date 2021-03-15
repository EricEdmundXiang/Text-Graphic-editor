#ifndef _SVGA_SUBSYSTEM_H_
#define _SVGA_SUBSYSTEM_H_


typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} SVGA_COLOR;

////////////////////////////////////////////////////////
int SVGA_Init(void);
int SVGAInit(void);
void SVGA_Deinit(void);
static void Set_Pal(const SVGA_COLOR * col);
void Set_Pal_File(const char * path);
unsigned int Select_Page(unsigned char index);
//////////////////////////////////////////////////////

#endif