#include"menu.h"
#include"svgasub.h"
#include"hanzi_.h"
#include"draw.h"
#include"mouse.h"
#include"editma.h"
#include<stdio.h>
#include<malloc.h>
#include<bios.h>
#include<conio.h>
#include<graphics.h>

void DrawMainMenu(struct type *MainMenu)
{
	int i;
	
	bar_o(0,0,800,600,0xffffff);
	bar_o(MainMenu->coor[0],MainMenu->coor[1],MainMenu->coor[2],MainMenu->coor[3],10);
	for(i = 0;i < MainMenu->itemnum;i ++)
	{
		hanzi_s(MainMenu->itemtextxy[i*2],MainMenu->itemtextxy[i*2+1],MainMenu->itemname[i],0xffffff);
	}
}

void DrawSubMenu(struct type *SubMenu,struct buffer *imagebuffer,int active)
{
	int size,i;
	
	size = imagesize(SubMenu->coor[0],SubMenu->coor[1],SubMenu->coor[2],SubMenu->coor[3]);
	for(i = 0;i < 4;i ++)
	{
		imagebuffer->coor[i] = SubMenu->coor[i];
	}
	if((imagebuffer->ibuffer = (unsigned char*)malloc(size))==NULL)
	return;
	else
	{
		getimage(SubMenu->coor[0],SubMenu->coor[1],SubMenu->coor[2],SubMenu->coor[3],imagebuffer->ibuffer);
		bar_o(SubMenu->coor[0],SubMenu->coor[1],SubMenu->coor[2],SubMenu->coor[3],0x16);
		for(i = 0;i < SubMenu->itemnum;i ++)
		{
			hanzi_s(SubMenu->itemtextxy[i*2],SubMenu->itemtextxy[i*2+1],SubMenu->itemname[i],0xffffff);
		}
		ActiveSubMenuItem(SubMenu,0,1);
	}
}

void ActiveMainMenuItem(struct type *menu,int active,int status)
{
	int coor[4];
	
	coor[0] = menu->itemcoor[4*active]+8;
	coor[1] = menu->itemcoor[4*active+1]+2;
	coor[2] = menu->itemcoor[4*active+2]-8;
	coor[3] = menu->itemcoor[4*active+3]-2;
	
	if(status == 0)
	{
		rectangle_o(coor[0],coor[1],coor[2],coor[3],10);
	}
	else
	{
		rectangle_o(coor[0],coor[1],coor[2],coor[3],0xffffff);
	}
}

void ActiveSubMenuItem(struct type *SubMenu,int active,int status)
{
	int coor[4];
	
	coor[0] = SubMenu->itemcoor[4*active]+2;
	coor[1] = SubMenu->itemcoor[4*active+1]+1;
	coor[2] = SubMenu->itemcoor[4*active+2]-2;
	coor[3] = SubMenu->itemcoor[4*active+3]-1;
	
	if(status == 0)
	{
		//paint_gou(coor[0],coor[1],0x498);
		rectangle_o(coor[0],coor[1],coor[2],coor[3],0x16);
	}
	else
	{
		//paint_gou(coor[0],coor[1],0xffffff);
		rectangle_o(coor[0],coor[1],coor[2],coor[3],0xffffff);
	}	
} 

void DrawEditView(void)
{
	int textw = textwidth("t"),texth = textheight("t");
	
	bar_o(0,3*texth+8,799,599-3*texth,130);
	bar_o(3*textw-1,7*texth-1,801-3*textw,601-7*texth,0xffffff);
	bar_o(0,599-4*texth-4,799,599,10);
	setlinestyle(0,0,1);
	setcolor(0);
//	rectangle(801-3*textw,7*texth-1,799,601-7*texth);
//	line(801-3*textw,9*texth,799,9*texth);
//	line(801-3*textw,599-9*texth,799,599-9*texth);
//	bar_o(801-3*textw+1,7*texth,798,10*texth-1,0xffffff);
//	bar_o(801-3*textw+1,599-10*texth+1,798,599-7*texth+1,0xffffff);
} 

void ExitMenu(struct buffer *imagebuffer)
{
	if(imagebuffer->ibuffer != NULL)
	{
		putimage(imagebuffer->coor[0],imagebuffer->coor[1],imagebuffer->ibuffer,COPY_PUT);
		free(imagebuffer->ibuffer);
        imagebuffer->ibuffer=NULL;
	}
}

void welcome(void)
{
	int key = 0;
	
	bar_o(1,1,799,599,10);
	setlinestyle(0,0,3);
	setcolor(0xffffff);
	rectangle(15,15,785,585);
	rectangle(17,17,783,583);
	hz48(275,125,525,175,"图文编辑器",0xffffff);
	hz48(275,225,570,275,"按任意键进入",0xffffff);
	hz48(275,375,420,425,"付长平",0xffffff);
	hz48(275,445,420,495,"向璇渝",0xffffff);
	
	while(!kbhit())
	{
		;
	}
	key = bioskey(0);
}

void bar_o(int tx,int ty,int ta,int tb,unsigned int color)
{
	setfillstyle(SOLID_FILL, color);
	bar(tx, ty, ta, tb);
} 

void line_o(int tx,int ty,int ta,int tb,unsigned int color)
{
	setlinestyle(0,0,1);
	setcolor(color);
	line(tx,ty,ta,tb);
}

void rectangle_o(int tx,int ty,int ta,int tb,unsigned int color)
{
	setlinestyle(0,0,1);
	setcolor(color);
	rectangle(tx,ty,ta,tb);
}

