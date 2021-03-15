#include"menu.h"
#include"setmenu.h"
#include"hanzi_.h"
#include<string.h>
#include<graphics.h>

void SetMainMenu(struct type *MainMenu,char **MainMenuItem) //记录总菜单参数
{
	int i,totallength = 0,interval,j = 0;
	int textw = textwidth("t");
	int texth = textheight("t");
	
	for(i = 0;MainMenuItem[i] != NULL;i ++)
	{
		totallength += ChineseStrlen(MainMenuItem[i]);
	}
	MainMenu->itemnum = i;
	MainMenu->itemname = MainMenuItem;
	MainMenu->coor[0] = 0;
	MainMenu->coor[1] = 0;
	MainMenu->coor[2] = 799;
	MainMenu->coor[3] = 3 * texth+8;
	interval = (799/textw - totallength) / i;
	for(i = 0;i < MainMenu->itemnum;i ++)
	{
		MainMenu->itemcoor[4*i] = j * textw;
		MainMenu->itemcoor[4*i+1] = 0;
		MainMenu->itemcoor[4*i+2] = (j + ChineseStrlen(MainMenuItem[i])+interval)*textw;
		MainMenu->itemcoor[4*i+3] = 3*texth+8;
		MainMenu->itemtextxy[2*i] = (j + 0.5*interval)*textw - 8;
		MainMenu->itemtextxy[2*i+1] = texth;
		j += ChineseStrlen(MainMenuItem[i]) + interval;
	}
} 

void SetSubMenu(struct type *SubMenu,char **SubMenuItem,struct type *MainMenu) //记录下拉菜单参数
{
	int i,menuw,parent,maxlen = 0;
	int textw = 16;
	int texth = 16;
	parent = SubMenu->parent;
	
	for(i = 0;SubMenuItem[i] != NULL;i ++)
	{
		if(ChineseStrlen(SubMenuItem[i]) > maxlen)
		maxlen = ChineseStrlen(SubMenuItem[i]);
	}
	SubMenu->itemnum = i;
	SubMenu->itemname = SubMenuItem;
	menuw = (maxlen+2) * textw;
	if((MainMenu->itemcoor[4*parent]+menuw) < 799)
	{
		SubMenu->coor[0] = MainMenu->itemcoor[4*parent];
		SubMenu->coor[2] = SubMenu->coor[0] + menuw;
	}
	else
	{
		SubMenu->coor[2] = MainMenu->itemcoor[4*parent+2];
		SubMenu->coor[0] = SubMenu->coor[2] - menuw;
	}
	SubMenu->coor[1] = MainMenu->coor[3];
	SubMenu->coor[3] = SubMenu->coor[1] + (SubMenu->itemnum)*(texth+6);
	for(i = 0;i < SubMenu->itemnum;i ++)
	{
		SubMenu->itemcoor[4*i] = SubMenu->coor[0];
		SubMenu->itemcoor[4*i+1] = SubMenu->coor[1] + i*(texth+6);
		SubMenu->itemcoor[4*i+2] = SubMenu->coor[2];
		SubMenu->itemcoor[4*i+3] = SubMenu->itemcoor[4*i+1]+texth+6;
		SubMenu->itemtextxy[2*i] = SubMenu->itemcoor[4*i] + textw;
		SubMenu->itemtextxy[2*i+1] = SubMenu->itemcoor[4*i+1] + 3;
	}
} 
