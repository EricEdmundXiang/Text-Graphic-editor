#include"svgasub.h"
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int SVGA_Init(void)
{
	int ret = 0;
	ret = SVGAInit();
	Set_Pal_File("win.act");
	return ret;
}

int SVGAInit(void)
{
	extern void _Cdecl SVGA_driver(void);
	int  GraphDriver, GraphMode = 4;
	GraphDriver = installuserdriver("SVGA", 0);
	if (GraphDriver < 0)
	{
		printf("InstallUserDriver Fail\n");
		return -1;
	}
	if (registerbgidriver(SVGA_driver) < 0) {
		printf("RegisterBGIDriver Fail\n");
		return -1;
	}
	initgraph(&GraphDriver, &GraphMode, "");
	//setviewport(0, 0, 1024, 768, 1);

	return 0;
}

void SVGA_Deinit(void)
{
	closegraph();
}


//pattle

static void Set_Pal(const SVGA_COLOR * col)
{
	int i = 0;

	for (; i < 256; i++) {
		outportb(0x3C8, i);
		outportb(0x3C9, (col[i].R) >> 2);
		outportb(0x3C9, (col[i].G) >> 2);
		outportb(0x3C9, (col[i].B) >> 2);
	}
}

void Set_Pal_File(const char * path)
{
	SVGA_COLOR     col[256];
	FILE           *fpcol = NULL;

	if ((fpcol = fopen(path, "rb")) == NULL)	{
		printf("Can't open file: %s\n", path);
		return;
	}

	if (fread((char*)&col, sizeof(col), 1, fpcol) != 1)	{
		fprintf(stderr, "Invalid file type\n");
		return;
	}

	Set_Pal(col);
}

/************************************************
功能说明：SVGA显存换页面
参数说明：index，页面号
返回值  ：0
*******************************************************/
unsigned int Select_Page(unsigned char index)
{
	union REGS in, out;
	in.x.ax = 0x4f05;			//换页
	in.x.bx = 0;				//表示当前窗口
	in.x.dx = index;			//在显存中的位面号
	int86(0x10, &in, &out);
	return 0;
}