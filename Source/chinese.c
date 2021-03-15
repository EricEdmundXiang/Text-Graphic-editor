#include"hanzi_.h"
#include"draw.h"
#include"chinese.h"
#include"menu.h"
#include<graphics.h>
#include<bios.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void ChangeLanguage(int e,int c)
{
	int textw = textwidth("t"),texth = textheight("t");
	int ex = 5 * textw;
	int ey = 600 - 3*texth;
	int cx = 8 * textw;
	int cy = 600 - 3*texth;
	char *es = "Ó¢";
	char *cs = "ºº";
	
	if(e == 0)
	hanzi_s(ex,ey,es,0xffff);
	else
	hanzi_s(ex,ey,es,0x16);
	
	if(c == 0)
	{
		hanzi_s(cx,cy,cs,0xffff);
		bar_o(22*textw-5,600-3*texth-4,32*textw,600-1*texth,10);
		bar_o(36*textw-4,600-3*texth-4,61*textw,600-1*texth,10);
	}
	else
	{
		hanzi_s(cx,cy,cs,0x16);
		bar_o(22*textw-5,600-3*texth-4,32*textw,600-1*texth,0xffff);
		bar_o(36*textw-4,600-3*texth-4,61*textw,600-1*texth,0xffff);
	}
}

void PutCode(char *code,char *pin)
{
	int textw = textwidth("t"),texth = textheight("t");
	int spellx = 37 * textw,spelly = 600 - 3*texth;
	char total[221],*tcode = total;
	char c[2];
	int i,key,m = 0,j = 0,asc,k;
	
	GetCode(total,pin);
	if(*tcode != NULL)
	{
		j = 0;
		for(i = 0;i < 8;i ++)
		{
			if(spellx < 640&&*tcode != NULL)
			{
				hanzi(spellx,spelly,tcode,0x16);
				c[0] = 49 + i;
				c[1] = 0;
				setcolor(0);
				outtextxy(spellx-6,spelly+8,c);
				spellx += 25;
				tcode += 2;
				j ++;
			}
			else
			{
				spellx = 25 * i;
			}
		}
		spellx = 37 * textw;
	}
	else
	{
		code[0] = 0;
		return;
	}
	while(1)
	{
		key = bioskey(0);
		
		switch(key)
		{
			case PAGEDOWN:
			{
				if(*tcode != NULL)
				{
					m ++;
					j = 0;
					bar_o(36 * textw,600 - 3*texth,61*textw,600 - texth,0xffff);
					for(i = 0;i < 8;i ++)
					{
						if(spellx < 640&&*tcode != NULL)
						{
							hanzi(spellx,spelly,tcode,0x16);
							c[0] = 49 + i;
							c[1] = 0;
							outtextxy(spellx-6,spelly+8,c);
							spellx += 25;
							tcode += 2;
							j ++;
						}
						else
						{
							spellx = 25 * i;
						}
					}
					spellx = 37 * textw;
				}
				break;
			}
			case PAGEUP:
			{
				if(m > 0&&*(tcode-2*j) != NULL)
				{
					m --;
					bar_o(36*textw,600 - 3*texth,61*textw,600 - texth,0xffff);
					tcode -= 2*j + 16;
					j = 0;
					for(i = 0;i < 8;i ++)
					{
						if(spellx < 640&&*tcode != NULL)
						{
							hanzi(spellx,spelly,tcode,0x16);
							c[0] = 49 + i;
							c[1] = 0;
							outtextxy(spellx-6,spelly+8,c);
							spellx += 25;
							tcode += 2;
							j ++;
						}	
						else
						{
							spellx = 25*i;
						}
					}
					spellx = 37 * textw;	
				}
				break;	
			}		
		}
		asc = 0xff&key;
		if('0' < asc && asc < 49 + i)
		{
			if('0' < asc&&asc < '9')
			{
				k = asc-49;
				code[0] = *(tcode-(2*j-2*k));
				code[1] = *(tcode-(2*j-2*k)+1);
				code[2] = 0;
				bar_o(36*textw,600 - 3*texth,61*textw,600 - texth,0xffff);
			}
			else
			{
				code[0] = 0;
			}
			break;
		}
	}
	total[0] = 0;
}

void GetCode(char *tcode,char *pin)
{
	int i = 0;
	char wenjian[40] = "spell\\";
	char *pinyin = pin;
	char *suffix = ".txt";
	FILE *fp;
	strcat(wenjian,pinyin);
	strcat(wenjian,suffix);
	if((fp = fopen(wenjian,"rb")) == NULL)
	{
		tcode[0] = 0;
		return;	
	} 
	while((tcode[i] = fgetc(fp)) != EOF)
	{
		i ++;
	}
	tcode[i] = 0;
	fclose(fp);
}
