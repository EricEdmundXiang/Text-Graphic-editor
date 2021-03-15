#include"svgasub.h"
#include<graphics.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include"mouse.h"

int xmin = 1,xmax = 799,ymin = 1,ymax = 599,kaiqi = 1,flagg;
int x = 300,y = 400,button;
union REGS regs;
int ch = 0;

int init(int xmi,int xma,int ymi,int yma) //初始化鼠标
{
	int retcode;
	regs.x.ax = 0;
	int86(51,&regs,&regs);
	retcode = regs.x.ax;
	if(retcode == 0) return 0;
	regs.x.ax = 7;
	regs.x.cx = xmi;
	regs.x.dx = xma;
	int86(51,&regs,&regs);
	regs.x.ax = 8;
	regs.x.cx = ymi;
	regs.x.dx = yma;
	int86(51,&regs,&regs);
	return retcode;
 } 
 
void read(int *mx,int *my,int *mbutt) //读取鼠标坐标
{
	int xx0 = *mx,yy0 = *my,buto = 0;
	int xnew,ynew;
	do{
		regs.x.ax = 3;
		int86(51,&regs,&regs);
		xnew = regs.x.cx;
		ynew = regs.x.dx;
		*mbutt = regs.x.bx;
	}while(xnew == xx0&&ynew == yy0&&*mbutt == buto);
	*mx = xnew;
	*my = ynew;
	if(*mbutt == 1)
	{
		*mx = xnew;
		*my = ynew;
		ch = 1;
	}
	else if(*mbutt == 2)
	{
		*mx = xnew;
		*my = ynew;
		ch = 2;
	}
	else if(*mbutt == 0)
	{
		*mx = xnew;
		*my = ynew;
		ch = 0;
	}
 } 
 
void cursor(int x,int y) //画鼠标
{
	setlinestyle(0,0,2);
 	setcolor(0xffffff);
    line(x,y,x+8,y+8);
    line(x+8,y+8,x+5,y+8);
    line(x+5,y+8,x+8,y+16);
    line(x+8,y+16,x+6,y+16);
    line(x+6,y+16,x+3,y+9);
    line(x+3,y+9,x,y+12);
    line(x,y+12,x,y);
}

 
 void newxy(int *mx,int *my,int *mbutt) //移动画鼠标
 {
 	int xx0 = *mx,yy0 = *my,x,y;
 	int xm,ym;
 	read(&xm,&ym,mbutt);
 	if(ch == 1)
 	{
 		cursor(xx0,yy0);
 		cursor(xm,ym);
	 }
	else if(ch == 2)
	{
		cursor(xx0,yy0);
		cursor(xm,ym);
	}
	else
	{
		cursor(xx0,yy0);
		cursor(xm,ym);
	}
	*mx = xm;
	*my = ym;
  } 
  
