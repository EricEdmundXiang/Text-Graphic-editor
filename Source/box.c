#include"menu.h"
#include"draw.h" 
#include"hanzi_.h" 
#include"mouse.h"
#include"box.h"
#include<graphics.h>
#include<alloc.h>
#include<conio.h>
#include<bios.h>
#include<process.h>
#include<dos.h>
extern x,y,button,ch;

int SaveWarn(struct buffer *imagebuffer)
{
	int coor[4],i,size;
	int textw = textwidth("t"),texth = textheight("t");
	char c[] = "文件未保存，是否保存？";
	char c1[] = "Yes     No     Cancel";
	
	coor[0] = 34 * textw;
	coor[1] = 24 * texth;
	coor[2] = 59 * textw;
	coor[3] = 34 * texth;
	for(i = 0;i < 4;i ++)
	{
		imagebuffer->coor[i] = coor[i];
	}
	size = imagesize(coor[0],coor[1],coor[2],coor[3]);
	imagebuffer->ibuffer = (unsigned char*)malloc(size);
	getimage(coor[0],coor[1],coor[2],coor[3],imagebuffer->ibuffer);
	bar_o(coor[0],coor[1],coor[2]-2,coor[3]-2,130);
	rectangle_o(coor[0],coor[1],coor[2]-2,coor[3]-2,7);
	setcolor(1);
	outtextxy(coor[0]+9*textw-4,coor[1]+texth+6,"Warning");
	hanzi_s(35*textw,28*texth,c,0);
	setwritemode(1);
	cursor(x,y);
	setwritemode(0);
	bar_o(36*textw-3,32*texth-5,39*textw+3,33*texth+1,7);
	bar_o(44*textw-3,32*texth-5,46*textw+3,33*texth+1,7);
	bar_o(51*textw-3,32*texth-5,57*textw+3,33*texth+1,7); 
	setcolor(10);
	outtextxy(36*textw,32*texth,c1);
	
	while(1)
	{
		setwritemode(XOR_PUT);
		newxy(&x,&y,&button);
		if(x > 36*textw-3&&x < 39*textw+3&&y > 32*texth-5&&y < 33*texth+1&&ch == 1)
		{
			setwritemode(1);
			cursor(x,y);
			setwritemode(0);
			ExitMenu(imagebuffer);
			return 1;
		}
		else if(x > 44*textw-3&&y > 32*texth-5&&x < 46*textw+3&&y < 33*texth+1&&ch == 1)
		{
			setwritemode(1);
			cursor(x,y);
			setwritemode(0);
			ExitMenu(imagebuffer);
			return 0;
		}
		else if(x > 51*textw-3&&y > 32*texth-5&&x < 57*textw+3&&y < 33*texth+1&&ch == 1)
		{
			setwritemode(1);
			cursor(x,y);
			setwritemode(0);
			ExitMenu(imagebuffer);
			return 2;
		}
		delay(40);
	}
}

int dialog(struct buffer *imagebuffer,char *filename,char *type)
{
	int coor[4],size,key,asc,count = 0,i,flag2 = 0;
	int textw = textwidth("t"),texth = textheight("t");
	char *s = "文件名及路径";
	char *p = filename;
	char temp[2];
	int arrowx = 35 * textw,arrowy = 31 * texth;
	
	coor[0] = 34 * textw;
	coor[1] = 22 * texth;
	coor[2] = 59 * textw;
	coor[3] = 36 * texth;
	
	for(i = 0;i < 4;i ++)
	{
		imagebuffer->coor[i] = coor[i];
	}
	size = imagesize(coor[0],coor[1],coor[2],coor[3]);
	imagebuffer->ibuffer = (unsigned char*)malloc(size);
	getimage(coor[0],coor[1],coor[2],coor[3],imagebuffer->ibuffer);
	bar_o(coor[0],coor[1],coor[2],coor[3],130);
	bar_o(coor[0],coor[1],coor[2],coor[1]+3*texth,10);
	rectangle_o(coor[0],coor[1],coor[2],coor[3],7);
	line_o(coor[0],coor[1]+3*texth,coor[2],coor[1]+3*texth,7);
	setcolor(0);
	outtextxy(41*textw,23*texth,type);
	outtextxy(41*textw,23*texth,"       File");
	bar_o(35*textw-3,29*texth-2,50*textw+2,31*texth+2,0xffff);
	bar_o(51*textw,29*texth,54*textw,31*texth,7);
	bar_o(51*textw,32*texth,58*textw,34*texth,7);
	hanzi_s(35*textw,26*texth,s,0);
	outtextxy(35*textw+108,26*texth+8,":");
	setcolor(10);
	outtextxy(51*textw+4,29*texth+4,"OK");
	outtextxy(51*textw+4,32*texth+4,"Cancel");
	
	DialogArrow(arrowx,arrowy,&flag2);
	while(1)
	{
		if(flag2 == 1)
		{
			setwritemode(1);
			cursor(x,y);
			setwritemode(0);
			*p = 0;
			ExitMenu(imagebuffer);
			flag2 = 0;
			return 1;
		}
		else if(flag2 == 2)
		{
			setwritemode(1);
			cursor(x,y);
			setwritemode(0);
			*p = 0;
			ExitMenu(imagebuffer);
			flag2 = 0;
			return 2;
		}
		key = bioskey(0);
		asc = 0xff&key;
		if(33 <= asc&&asc <= 126)
		{
			count ++;
			if(count <= 14)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				*(p ++) = asc;
				temp[0] = asc;
				temp[1] = 0;
				setcolor(0);
				outtextxy(arrowx,arrowy-8,temp);
				arrowx += textw;
				DialogArrow(arrowx,arrowy,&flag2);
				if(flag2 == 1)
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					*p = 0;
					ExitMenu(imagebuffer);
					flag2 = 0;
					return 1;
				}
				else if(flag2==2)
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					*filename = 0;
					ExitMenu(imagebuffer);
					flag2 = 0;
					return 2;
				}
			}
			else
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				count --;
				DialogArrow(arrowx,arrowy,&flag2);
				if(flag2 == 1)
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					*p = 0;
					ExitMenu(imagebuffer);
					flag2 = 0;
					return 1;
				}
				else if(flag2==2)
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					*filename = 0;
					ExitMenu(imagebuffer);
					flag2 = 0;
					return 2;
				}
			}
		}
		else
		{
			switch(key)
			{
				case BACKSPACE:
				{
					setwritemode(1);
					cursor(x,y);
					setwritemode(0);
					count --;
					if(count >= 0)
					{
						p --;
						bar_o(arrowx-8,arrowy-8,arrowx,arrowy,0xffff);
						arrowx -= textw;
						DialogArrow(arrowx,arrowy,&flag2);
						if(flag2==1)
						{
							setwritemode(1);
							cursor(x,y);
							setwritemode(0);
							*p=0;
							ExitMenu(imagebuffer);
							flag2=0;
							return 1;
						}
						else if(flag2==2)
						{
							setwritemode(1);
							cursor(x,y);
							setwritemode(0);
							*filename=0;
							ExitMenu(imagebuffer);
							flag2=0;
							return 2;
						}
					}
					else
					{
						count ++;
						DialogArrow(arrowx,arrowy,&flag2);
						if(flag2==1)
						{
							setwritemode(1);
							cursor(x,y);
							setwritemode(0);
							*p=0;
							ExitMenu(imagebuffer);
							flag2=0;
							return 1;
						}
						else if(flag2==2)
						{
							setwritemode(1);
							cursor(x,y);
							setwritemode(0);
							*filename=0;
							ExitMenu(imagebuffer);
							flag2=0;
							return 2;
						}
					}
					break;
				}
				default:
				{
					if(flag2==1)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*p=0;
						ExitMenu(imagebuffer);
						flag2=0;
						return 1;
					}
					else if(flag2==2)
					{
						setwritemode(1);
						cursor(x,y);
						setwritemode(0);
						*filename=0;
						ExitMenu(imagebuffer);
						flag2=0;
						return 2;
					}
					DialogArrow(arrowx,arrowy,&flag2);
					break;
				}
			}
		}
	}
} 

void DialogArrow(int arrowx,int arrowy,int *flag2)
{
	int i,flag = 0;
	int textw = textwidth("t"),texth = textheight("t");
	
	setwritemode(1);
	cursor(x,y);
	setwritemode(0);
	while(1)
	{
		line_o(arrowx,arrowy-16,arrowx,arrowy,0);
		for(i = 1;i <= 200;i ++)
		{
			if(kbhit())
			{
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
			if(x > 51*textw&&y > 29*texth+1&&x < 54*textw+1&&y < 31*texth+1&&ch == 1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				*flag2=1;
				return ;
			}
			if(x > 51*textw&&y > 32*texth&&x < 58*textw&&y < 34*texth&&ch == 1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				*flag2=2;
				return ;
			}
		}
		if(flag)
		{
			line_o(arrowx,arrowy-16,arrowx,arrowy,0xffff);
			break;
		}
		line_o(arrowx,arrowy-16,arrowx,arrowy,0xffff);
		for(i = 1;i <= 200;i ++)
		{
			if(kbhit())
			{
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
			if(x > 51*textw&&y > 29*texth+1&&x < 54*textw+1&&y < 31*texth+1&&ch == 1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				*flag2=1;
				return ;
			}
			if(x > 51*textw&&y > 32*texth&&x < 58*textw&&y < 34*texth&&ch == 1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				*flag2=2;
				return ;
			}
		}
		if(flag)
		break;
	}
}
