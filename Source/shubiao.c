#include"shubiao.h"
#include"svgasub.h"
#include"mouse.h"
#include"menu.h"
#include"draw.h"
#include"grank.h"
#include<bios.h>
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<conio.h>
#include<graphics.h>

extern int xmin,xmax,ymin,ymax,kaiqi,flagg;
extern int x,y,button;
extern int ch;
extern union REGS regs;

void GuangBiao(struct edit *EditFace,struct type *MainMenu,int op,int *mainactive,int *flag2)
{
	int textw = textwidth("t"),texth = textheight("t"),flag = 0;
	int i,j;
	int textx,texty;
	int spellx,spelly;
	int bar[7] = {0};
	
	textx = (EditFace->column+1)*textw+8;
	texty = (6+2*EditFace->line)*texth+8;
	spellx = (21 + EditFace->spellplace) * textw;
	spelly = 600 - texth;
	
	//RollBar(EditFace);
	
	if(kaiqi == 1)
	{
		kaiqi = 0;
		if(init(xmin,xmax,ymin,ymax) == 0)
		{
			printf("The mouse's part is error!");
			exit(1);
		}
	}
	setwritemode(1);
	cursor(x,y);
	setwritemode(0);
	if(op)
	{
		while(1)
		{
			line_o(textx,texty-16,textx,texty,0);
			for(i = 1;i <= 200;i ++)
			{
				if(kbhit())
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					flag = 1;
					flagg = 2;
					break;
				}
				else
				delay(1);
				if(i % 40 == 0)
				{
					setwritemode(XOR_PUT);
					newxy(&x,&y,&button);
					setwritemode(0);
					if(x > 0&&x < 112&&y > 0&&y < 32&&ch==0&&bar[0]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,0,1);
						bar[0] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 0&&x < 112&&y > 0&&y < 32)&&ch==0&&bar[0]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,0,0);
						bar[0] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 0&&x < 112&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 0;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 112&&x < 224&&y > 0&&y < 32&&ch==0&&bar[1]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,1,1);
						bar[1] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 112&&x < 224&&y > 0&&y < 32)&&ch==0&&bar[1]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,1,0);
						bar[1] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 112&&x < 224&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 1;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 224&&x < 336&&y > 0&&y < 32&&ch==0&&bar[2]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,2,1);
						bar[2] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 224&&x < 336&&y > 0&&y < 32)&&ch==0&&bar[2]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,2,0);
						bar[2] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 224&&x < 336&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 2;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 336&&x < 448&&y > 0&&y < 32&&ch==0&&bar[3]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,3,1);
						bar[3] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 336&&x < 448&&y > 0&&y < 32)&&ch==0&&bar[3]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,3,0);
						bar[3] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 336&&x < 448&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 3;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 448&&x < 560&&y > 0&&y < 32&&ch==0&&bar[4]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,4,1);
						bar[4] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 448&&x < 560&&y > 0&&y < 32)&&ch==0&&bar[4]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,4,0);
						bar[4] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 448&&x < 560&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 4;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 560&&x < 672&&y > 0&&y < 32&&ch==0&&bar[5]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,5,1);
						bar[5] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 560&&x < 672&&y > 0&&y < 32)&&ch==0&&bar[5]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,5,0);
						bar[5] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 560&&x < 672&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 5;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 672&&x < 784&&y > 0&&y < 32&&ch==0&&bar[6]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,6,1);
						bar[6] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 672&&x < 784&&y > 0&&y < 32)&&ch==0&&bar[6]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,6,0);
						bar[6] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 672&&x < 784&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 6;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
			    }
			}
			if(flag)
			{
				line_o(textx,texty-16,textx,texty,0xffffff);
				break;
			}
			line_o(textx,texty-16,textx,texty,0xffffff);
			for(i = 1;i <= 200;i ++)
			{
				if(kbhit())
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					flag = 1;
					flagg = 2;
					break;
				}
				else
				delay(1);
				if(i%40 == 0)
				{
					setwritemode(XOR_PUT);
					newxy(&x,&y,&button);
					setwritemode(0);
					if(x > 0&&x < 112&&y > 0&&y < 32&&ch==0&&bar[0]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,0,1);
						bar[0] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 0&&x < 112&&y > 0&&y < 32)&&ch==0&&bar[0]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,0,0);
						bar[0] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 0&&x < 112&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 0;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 112&&x < 224&&y > 0&&y < 32&&ch==0&&bar[1]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,1,1);
						bar[1] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 112&&x < 224&&y > 0&&y < 32)&&ch==0&&bar[1]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,1,0);
						bar[1] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 112&&x < 224&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 1;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 224&&x < 336&&y > 0&&y < 32&&ch==0&&bar[2]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,2,1);
						bar[2] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 224&&x < 336&&y > 0&&y < 32)&&ch==0&&bar[2]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,2,0);
						bar[2] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 224&&x < 336&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 2;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 336&&x < 448&&y > 0&&y < 32&&ch==0&&bar[3]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,3,1);
						bar[3] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 336&&x < 448&&y > 0&&y < 32)&&ch==0&&bar[3]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,3,0);
						bar[3] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 336&&x < 448&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 3;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 448&&x < 560&&y > 0&&y < 32&&ch==0&&bar[4]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,4,1);
						bar[4] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 448&&x < 560&&y > 0&&y < 32)&&ch==0&&bar[4]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,4,0);
						bar[4] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 448&&x < 560&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 4;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 560&&x < 672&&y > 0&&y < 32&&ch==0&&bar[5]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,5,1);
						bar[5] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 560&&x < 672&&y > 0&&y < 32)&&ch==0&&bar[5]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,5,0);
						bar[5] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 560&&x < 672&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 5;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
					if(x > 672&&x < 784&&y > 0&&y < 32&&ch==0&&bar[6]==0)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,6,1);
						bar[6] = 1;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(!(x > 672&&x < 784&&y > 0&&y < 32)&&ch==0&&bar[6]==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						ActiveMainMenuItem(MainMenu,6,0);
						bar[6] = 0;
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
					}
					if(x > 672&&x < 784&&y > 0&&y < 32&&ch==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*mainactive = 6;
						*flag2 = 1;
						line_o(textx,texty-16,textx,texty,0xffffff);
						return;
					}
			    }
			}
			if(flag) 
			break;
		}
	}
	else if(op == 0)
	{
		while(1)
		{
			line_o(spellx,spelly-16,spellx,spelly,0);
			for(i = 1;i <= 200;i ++)
			{
				if(kbhit())
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					flag = 1;
					break;
				}
				else
				delay(1);
				if(i % 40 == 0)
				{
					setwritemode(XOR_PUT);
					newxy(&x,&y,&button);
					setwritemode(0);
				}
			}
			if(flag)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				line_o(spellx,spelly-16,spellx,spelly,0xffff);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				break;
			}
			line_o(spellx,spelly-16,spellx,spelly,0xffff);
			for(i = 1;i <= 200;i ++)
			{
				if(kbhit())
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					flag = 1;
					break;
				}
				else
				delay(1);
				if(i % 40 == 0)
				{
					setwritemode(XOR_PUT);
					newxy(&x,&y,&button);
					setwritemode(0);
				}
			}
			if(flag)
			break;
		}
	}
} 

/*void RollBar(struct edit *EditFace)
{
	int i,j,rank,nextpage,editpage,flag = 0,coor[4];
	int textw = textwidth("t"),texth = textheight("t");
	float k;
	
	if(EditFace->start->data[0] == 0) i = 1;
	else
	for(i = 1;;i ++)
	{
		for(j = 1;j <= 94;j ++)
		{
			rank = GetRank(EditFace->start,i,j);
			if(rank == (EditFace->last)->rank+1)
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1) break;
	}
	
	nextpage = i - 30;
	if(nextpage <= 0) k = 0;
	else 
	k = (float)((595 - 20*texth)) / (float)(nextpage);

	coor[0] = 802-3*textw+2;
	coor[1] = 10*texth + 3 + (int)(editpage*k);
	coor[2] = 796;
	coor[3] = 14*texth + 1 + (int)(editpage*k);
	bar_o(coor[0],coor[1],coor[2],coor[3],0xffffff);
}*/

