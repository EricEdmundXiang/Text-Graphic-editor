#include"manage.h"
#include"menu.h"
#include"svgasub.h"
#include"mouse.h"
#include"hanzi_.h"
#include"editma.h"
#include"draw.h"
#include"work.h"
#include<bios.h>
#include<stdio.h>
#include<alloc.h>
#include<stdlib.h>
#include<dos.h>
#include<string.h>
#include<conio.h>
#include<graphics.h>

extern int xmin,xmax,ymin,ymax;
extern int x,y,button;
extern int ch;
extern union REGS regs;

void ManageMenu(struct type *MainMenu,struct type *SubMenu)
{
	FILE *fp;
	char s[20],filename[20],temp[3],noname[15];
	struct edit EditFace;
	struct buffer imagebuffer;
	int MainActive = 0,SubActive[SUBNUM],i,j,revise = 0;
	int command; 
	int texth = textheight("t"),textw = textwidth("t");
	unsigned key;
	EditFace.start = (struct node*)malloc(sizeof(struct node));
	EditFace.clipstart = (struct node*)malloc(sizeof(struct node));
	EditFace.last = EditFace.start;
	(EditFace.start)->prior = NULL;
	(EditFace.start)->next = NULL;
	(EditFace.start)->data[0] = 0;
	EditFace.cliplast = EditFace.clipstart;
	EditFace.clipbegin = 0;
	EditFace.clipend = 0;
	(EditFace.clipstart)->prior = NULL;
	(EditFace.clipstart)->next = NULL;
	(EditFace.clipstart)->data[0] = 0;
	EditFace.line = 1;
	EditFace.column = 1;
	EditFace.pin[0] = 0;
	EditFace.count = 0;
	EditFace.language = 1;
	(EditFace.start)->rank = 1;
	EditFace.spellplace = 1;
	EditFace.pn[0] = '1';
	EditFace.pn[1] = 0;
	
	for(i = 0;i < SUBNUM;i ++)
	 SubActive[i] = 0;
	
	strcpy(noname,"noname");
	for(i = 1;;i ++)
	{
		if(i > 9)
		{
			temp[0] = i/10 + '0';
			temp[1] = i%10 + '0';
			temp[2] = 0;
		}
		else
		{
			temp[0] = i + '0';
			temp[1] = 0;
		}
		strcat(noname,temp);
		strcat(noname,".txt");        //这里要注意改格式！
		if((fp = fopen(noname,"rb")) == NULL) break;
		else
		{
			noname[6] = 0;
			fclose(fp);
		} 
    }
	strcpy(filename,noname);
	yingwen(filename,44*textw+4,4*texth+4,1,1,0);	

	edit(&EditFace,MainMenu,&MainActive,&revise);
	DrawSubMenu(&SubMenu[MainActive],&imagebuffer,MainActive);
	setwritemode(1);
	cursor(x,y);
	setwritemode(0);
	
	for(key = 0;;)
	{
		if(MainActive == 4||MainActive == 6)
		command = MainActive;
		else
		{
			for(i = 0;i < SUBNUM;i ++)
			{
				if(MainActive == SubMenu[i].parent)
				command = MainActive*100 + SubActive[i];
			}
		}
		for(;;)
		{
			if(MainActive == 4||MainActive == 6||MainActive == 0)
		    command = MainActive;
		    else
		    {
			    for(i = 0;i < SUBNUM;i ++)
			    {
				    if(MainActive == SubMenu[i].parent)
				    command = MainActive*100 + SubActive[i];
			    }
		    }
		    setwritemode(XOR_PUT);
		    newxy(&x,&y,&button);
		    if(!((x>0&&x<800&&y>0&&y<32)||(x>SubMenu[MainActive].coor[0]&&x<SubMenu[MainActive].coor[2]&&y>SubMenu[MainActive].coor[1]&&y<SubMenu[MainActive].coor[3]))&&ch==1)
		    {
		    	setwritemode(1);
				cursor(x,y);
				setwritemode(0);
		    	ActiveMainMenuItem(MainMenu,MainActive,0);
		    	ExitMenu(&imagebuffer);
		    	edit(&EditFace,MainMenu,&MainActive,&revise);
		    	ActiveMainMenuItem(MainMenu,MainActive,1);
		    	DrawSubMenu(&SubMenu[MainActive],&imagebuffer,MainActive);
		    	setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 0&&x < 112&&y > 0&&y < 32&&MainActive != 0)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ExitMenu(&imagebuffer);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				MainActive = 0;
				ActiveMainMenuItem(MainMenu,MainActive,1);
				DrawSubMenu(&SubMenu[0],&imagebuffer,MainActive);
				for(i = 0;i < SUBNUM;i ++)
				SubActive[i] = 0;
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 112&&x < 224&&y > 0&&y < 32&&MainActive != 1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ExitMenu(&imagebuffer);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				MainActive = 1;
				ActiveMainMenuItem(MainMenu,MainActive,1);
				DrawSubMenu(&SubMenu[1],&imagebuffer,MainActive);
				for(i = 0;i < SUBNUM;i ++)
				SubActive[i] = 0;
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 112&&x < 176&&y > 32&&y < 54&&MainActive == 1&&SubActive[1]!=0)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[1],SubActive[1],0);
				SubActive[1] = 0;
				ActiveSubMenuItem(&SubMenu[1],SubActive[1],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 112&&x < 176&&y > 54&&y < 76&&MainActive == 1&&SubActive[1]!=1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[1],SubActive[1],0);
				SubActive[1] = 1;
				ActiveSubMenuItem(&SubMenu[1],SubActive[1],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 112&&x < 176&&y > 76&&y < 98&&MainActive == 1&&SubActive[1]!=2)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[1],SubActive[1],0);
				SubActive[1] = 2;
				ActiveSubMenuItem(&SubMenu[1],SubActive[1],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 224&&x < 336&&y > 0&&y < 32&&MainActive != 2)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ExitMenu(&imagebuffer);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				MainActive = 2;
				ActiveMainMenuItem(MainMenu,MainActive,1);
				DrawSubMenu(&SubMenu[2],&imagebuffer,MainActive);
				for(i = 0;i < SUBNUM;i ++)
				SubActive[i] = 0;
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 224&&x < 288&&y > 32&&y < 54&&MainActive == 2&&SubActive[2]!=0)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],0);
				SubActive[2] = 0;
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 224&&x < 288&&y > 54&&y < 76&&MainActive == 2&&SubActive[2] != 1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],0);
				SubActive[2] = 1;
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 224&&x < 288&&y > 76&&y < 98&&MainActive == 2&&SubActive[2] != 2)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],0);
				SubActive[2] = 2;
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 224&&x < 288&&y > 98&&y < 120&&MainActive == 2&&SubActive[2] != 3)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],0);
				SubActive[2] = 3;
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			/*if(x > 224&&x < 288&&y > 120&&y < 142&&MainActive == 2&&SubActive[2] != 4)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],0);
				SubActive[2] = 4;
				ActiveSubMenuItem(&SubMenu[2],SubActive[2],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}*/
			if(x > 336&&x < 448&&y > 0&&y < 32&&MainActive!=3)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ExitMenu(&imagebuffer);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				MainActive = 3;
				ActiveMainMenuItem(MainMenu,MainActive,1);
				DrawSubMenu(&SubMenu[3],&imagebuffer,MainActive);
				for(i = 0;i < SUBNUM;i ++)
				SubActive[i] = 0;
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 336&&x < 400&&y > 32&&y < 54&&MainActive == 3&&SubActive[3]!=0)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[3],SubActive[3],0);
				SubActive[3] = 0;
				ActiveSubMenuItem(&SubMenu[3],SubActive[3],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 336&&x < 400&&y > 54&&y < 76&&MainActive == 3&&SubActive[3]!=1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[3],SubActive[3],0);
				SubActive[3] = 1;
				ActiveSubMenuItem(&SubMenu[3],SubActive[3],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 336&&x < 400&&y > 76&&y < 98&&MainActive == 3&&SubActive[3]!=2)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[3],SubActive[3],0);
				SubActive[3] = 2;
				ActiveSubMenuItem(&SubMenu[3],SubActive[3],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 336&&x < 400&&y > 98&&y < 120&&MainActive == 3&&SubActive[3]!=3)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[3],SubActive[3],0);
				SubActive[3] = 3;
				ActiveSubMenuItem(&SubMenu[3],SubActive[3],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 448&&x < 560&&y > 0&&y < 32&&MainActive != 4)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ExitMenu(&imagebuffer);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				MainActive = 4;
				ActiveMainMenuItem(MainMenu,MainActive,1);
				for(i = 0;i < SUBNUM;i ++)
				SubActive[i] = 0;
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 560&&x < 672&&y > 0&&y < 32&&MainActive != 5)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ExitMenu(&imagebuffer);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				MainActive = 5;
				ActiveMainMenuItem(MainMenu,MainActive,1);
				DrawSubMenu(&SubMenu[5],&imagebuffer,MainActive);
				for(i = 0;i < SUBNUM;i ++)
				SubActive[i] = 0;
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 560&&x < 624&&y > 32&&y < 54&&MainActive==5&&SubActive[5]!=0)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[5],SubActive[5],0);
				SubActive[5] = 0;
				ActiveSubMenuItem(&SubMenu[5],SubActive[5],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 560&&x < 624&&y > 54&&y <76&&MainActive==5&&SubActive[5]!=1)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveSubMenuItem(&SubMenu[5],SubActive[5],0);
				SubActive[5] = 1;
				ActiveSubMenuItem(&SubMenu[5],SubActive[5],1);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(x > 672&&x < 784&&y > 0&&y < 32&&MainActive != 6)
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ExitMenu(&imagebuffer);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				MainActive = 6;
				ActiveMainMenuItem(MainMenu,MainActive,1);
				for(i = 0;i < SUBNUM;i ++)
				SubActive[i] = 0;
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
			}
			if(kbhit())
			{
				break;
			}
			if(ch == 1)
			{
				if((x>448&&x<560&&y>0&&y<32)||(x>672&&x<784&&y>0&&y<32)||(x>0&&x<112&&y>0&&y<32)
				   ||(x>112&&x<176&&y>32&&y<98)||(x>224&&x<288&&y>32&&y<120)||(x>560&&x<624&&y>32&&y<76)||(x>336&&x<400&&y>32&&y<120))
				
				{
					setwritemode(1);
				    cursor(x,y);
				    setwritemode(0);
					ExitMenu(&imagebuffer);
					ActiveMainMenuItem(MainMenu,MainActive,0);
					MainActive = 0;
					for(i = 0;i < SUBNUM;i ++)
					SubActive[i] = 0;
					func(&EditFace,&imagebuffer,command,&MainActive,filename,&revise,MainMenu);
					ActiveMainMenuItem(MainMenu,MainActive,1);
					DrawSubMenu(&SubMenu[MainActive],&imagebuffer,MainActive);
					setwritemode(1);
				    cursor(x,y);
				    setwritemode(0);
				}
			}
			delay(25);
	    }
	    key = bioskey(0);
	    switch(key)
	    {
	    	case LEFT:
	    	{
	    		setwritemode(1);
				cursor(x,y);
				setwritemode(0);
	    		ExitMenu(&imagebuffer);
	    		ActiveMainMenuItem(MainMenu,MainActive,0);
	    		if(MainActive == 0) MainActive = MainMenu->itemnum-1;
	    		else MainActive --;
	    		ActiveMainMenuItem(MainMenu,MainActive,1);
	    		DrawSubMenu(&SubMenu[MainActive],&imagebuffer,MainActive);
	    		for(i = 0;i < SUBNUM;i ++)
	    		SubActive[i] = 0;
	    		setwritemode(1);
				cursor(x,y);
				setwritemode(0);
	    		break;
			}
			case RIGHT:
	    	{
	    		setwritemode(1);
				cursor(x,y);
				setwritemode(0);
	    		ExitMenu(&imagebuffer);
	    		ActiveMainMenuItem(MainMenu,MainActive,0);
	    		if(MainActive == MainMenu->itemnum-1) MainActive = 0;
	    		else MainActive ++;
	    		ActiveMainMenuItem(MainMenu,MainActive,1);
	    		DrawSubMenu(&SubMenu[MainActive],&imagebuffer,MainActive);
	    		for(i = 0;i < SUBNUM;i ++)
	    		SubActive[i] = 0;
	    		setwritemode(1);
				cursor(x,y);
				setwritemode(0);
	    		break;
			}
			case UP:
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				for(i = 0;i < SUBNUM;i ++)
				{
					if(SubMenu[i].parent == MainActive)
					{
						ActiveSubMenuItem(&SubMenu[i],SubActive[i],0);
						if(SubActive[i] == 0) SubActive[i] = SubMenu[i].itemnum-1;
						else SubActive[i] --;
						ActiveSubMenuItem(&SubMenu[i],SubActive[i],1);
					}
				}
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				break;
			}
			case DOWN:
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				for(i = 0;i < SUBNUM;i ++)
				{
					if(SubMenu[i].parent == MainActive)
					{
						ActiveSubMenuItem(&SubMenu[i],SubActive[i],0);
						if(SubActive[i] == SubMenu[i].itemnum-1) SubActive[i] = 0;
						else SubActive[i] ++;
						ActiveSubMenuItem(&SubMenu[i],SubActive[i],1);
					}
				}
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				break;
			}
			case ESC:
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				ExitMenu(&imagebuffer);
				edit(&EditFace,MainMenu,&MainActive,&revise);
				ActiveMainMenuItem(MainMenu,MainActive,1);
				DrawSubMenu(&SubMenu[MainActive],&imagebuffer,MainActive);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				break;
			}
			case ENTER:
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				ExitMenu(&imagebuffer);
				ActiveMainMenuItem(MainMenu,MainActive,0);
				MainActive = 0;
				for(i = 0;i < SUBNUM;i ++)
				SubActive[i] = 0;
				func(&EditFace,&imagebuffer,command,&MainActive,filename,&revise,MainMenu);
				ActiveMainMenuItem(MainMenu,MainActive,1);
				DrawSubMenu(&SubMenu[MainActive],&imagebuffer,MainActive);
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				break;
			}
		}
	}
}

