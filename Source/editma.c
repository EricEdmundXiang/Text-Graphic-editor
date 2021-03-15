#include"editma.h"
#include"shubiao.h"
#include"menu.h"
#include"svgasub.h"
#include"grank.h"
#include"draw.h"
#include"hanzi_.h"
#include"chinese.h"
#include"pic.h"
#include"work.h"
#include<graphics.h>
#include<bios.h>
#include<string.h>
#include<alloc.h>
#include<stdlib.h>
#include<dos.h>
#include<malloc.h>

void edit(struct edit *EditFace,struct type *MainMenu,int *mainactive,int *revise)
{
	int flag2 = 0,key,asc,rank,srank,textx,texty;
	int textw = textwidth("t");
	int texth = textheight("t");
	char temp[2];
	struct node *p;
	char code[3];
	
	code[0] = 0;
	GuangBiao(EditFace,MainMenu,EditFace->language,mainactive,&flag2);
	while(1)
	{
		if(flag2 == 1)
		{
			flag2 = 0;
			return;
		}
		key = bioskey(0);
		asc = 0xff & key;
		if(asc > 32&&asc < 127)
		{
			temp[0] = asc;
			temp[1] = 0;
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}
			if(EditFace->language == 1)
			{
				rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
				
				if(EditFace->column == 1 && EditFace->line > 1)
				{
					p = EditFace->start;
					while(p->rank != rank - 1)
					{
						p = p->next;
					}
					if(p->len == 1)
					{
						if(EditFace->line <= 11)
						{
							srank = GetRank(EditFace->start,EditFace->line-1,93);
							if(srank == 0)
							{
								EditFace->column = 93;
								EditFace->line --;
							}
						}
						else if(GetPic(EditFace->start,EditFace->line-11,92)) //插入图片位置限制在92之前 
						{
							srank = GetRank(EditFace->start,EditFace->line-11,93);
							if(srank == 0)
							{
								EditFace->column = 93;
								EditFace->line -= 11;
							}
						}
						else
						{
							srank = GetRank(EditFace->start,EditFace->line-1,93);
							if(srank == 0)
							{
								EditFace->column = 93;
								EditFace->line --;
							}
						}
					}
				}
				insert(rank,temp,EditFace);   
				redraw(rank,(EditFace->last)->rank,EditFace->line,EditFace->column,EditFace);
				
				EditFace->column ++;
				if(EditFace->column > 93&&GetPic(EditFace->start,EditFace->line,93)) 
				{
					EditFace->column = 1;
					EditFace->line += 11;
				}
				if(EditFace->column > 93&&!(GetPic(EditFace->start,EditFace->line,93))) 
				{
					EditFace->column = 1;
					EditFace->line ++;
				}
				*revise = 1;
				GuangBiao(EditFace,MainMenu,EditFace->language,mainactive,&flag2);
			}
			else if(EditFace->language == 0)
			{
				EditFace->count ++;
				if(EditFace->count <= 9)
				{
					strcat(EditFace->pin,temp);
					textx = (21 + EditFace->spellplace) * textw;
					texty = 600 - 2 * texth;
					setcolor(0x16);
					outtextxy(textx,texty,temp);
					EditFace->spellplace ++;
					GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
				}
				else
				{
					EditFace->count --;
					GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
				}
			}
		}
		else
		{
			switch(key)
			{
				case SPACE:
				{
					if(EditFace->clipbegin != 0)
					{
						bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
						redraw(1,EditFace->last->rank,1,1,EditFace);
						EditFace->clipbegin = 0;
						EditFace->clipend = 0;
					}
					if(EditFace->language == 1)
					{
						temp[0] = ' ';
						temp[1] = 0;
						rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
						if(EditFace->column == 1&&EditFace->line > 1)
						{
							p = EditFace->start;
							while(p->rank != rank - 1)
							{
								p = p->next;
							}
							if(p->len == 1)
							{
								if(EditFace->line < 11)
								{
									srank = GetRank(EditFace->start,EditFace->line-1,93);
									if(srank == 0)
									{
										EditFace->column = 93;
										EditFace->line --;
									}
								}
								else if(GetPic(EditFace->start,EditFace->line-11,92)) //插入图片位置限制在92之前 
								{
									srank = GetRank(EditFace->start,EditFace->line-11,93);
									if(srank == 0)
									{
										EditFace->column = 93;
										EditFace->line -= 11;
									}
								}
								else
								{
									srank = GetRank(EditFace->start,EditFace->line-1,93);
									if(srank == 0)
									{
									EditFace->column = 93;
									EditFace->line --;
									}
								}
							}
						}
						insert(rank,temp,EditFace);
						redraw(rank,(EditFace->last)->rank,EditFace->line,EditFace->column,EditFace);
				
						EditFace->column ++;
						if(EditFace->column > 93&&GetPic(EditFace->start,EditFace->line,93)) 
						{
							EditFace->column = 1;
							EditFace->line += 11;
						}
						if(EditFace->column > 93&&!(GetPic(EditFace->start,EditFace->line,93))) 
						{
							EditFace->column = 1;
							EditFace->line ++;
						}
						*revise = 1;
						GuangBiao(EditFace,MainMenu,EditFace->language,mainactive,&flag2);
					}
					else if(EditFace->language == 0)
					{
						PutCode(code,EditFace->pin);
						if(code[0] != 0)
						{
							EditFace->pin[0] = 0;
							EditFace->count = 0;
							EditFace->spellplace = 1;
							ChangeLanguage(0,1);
							rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
							insert(rank,code,EditFace);
							code[0] = 0;
							redraw(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);
							if(EditFace->column == 93&&!(GetPic(EditFace->start,EditFace->line,93))) 
							{
								EditFace->column = 1;
								EditFace->line ++;
							}
							else if(EditFace->column == 93&&GetPic(EditFace->start,EditFace->line,93))
							{
								EditFace->column = 1;
								EditFace->line += 11;
							}
							EditFace->column += 2;
							if(EditFace->column > 93&&!(GetPic(EditFace->start,EditFace->line,93)))
							{
								EditFace->column = 1;
								EditFace->line ++;
							}
							else if(EditFace->column > 93&&GetPic(EditFace->start,EditFace->line,93))
							{
								EditFace->column = 1;
								EditFace->line += 11;
							}
							*revise = 1;
							GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);
						}
						else
						GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
					}
					break;	
				}
				case LEFT:
				{
					if(EditFace->clipbegin != 0)
					{
						bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffff);
						redraw(1,EditFace->last->rank,1,1,EditFace);
						EditFace->clipbegin = 0;
						EditFace->clipend = 0;
					}
					if(EditFace->language == 1)
					{
						NextPlace(LEFT,EditFace);
						GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);
					} 
					else
					GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
					break;
				}
				case RIGHT:
				{
					if(EditFace->clipbegin != 0)
					{
						bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
						redraw(1,EditFace->last->rank,1,1,EditFace);
						EditFace->clipbegin = 0;
						EditFace->clipend = 0;
					}
					if(EditFace->language == 1)
					{
						NextPlace(RIGHT,EditFace);
						GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);
					} 
					else
					GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
					break; 
				}
				case UP:
				{
					if(EditFace->clipbegin != 0)
					{
						bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffff);
						redraw(1,EditFace->last->rank,1,1,EditFace);
						EditFace->clipbegin = 0;
						EditFace->clipend = 0;
					}
					if(EditFace->language == 1)
					{
						NextPlace(UP,EditFace);
						GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);	
					} 
					else
					GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
					break;
				}
				case DOWN:
				{
					if(EditFace->clipbegin != 0)
					{
						bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
						redraw(1,EditFace->last->rank,1,1,EditFace);
						EditFace->clipbegin = 0;
						EditFace->clipend = 0;
					}
					if(EditFace->language == 1)
					{
						NextPlace(DOWN,EditFace);
						GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);	
					} 
					else
					GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
					break;	
				}
				case BACKSPACE:
				{
					if(EditFace->clipbegin != 0)
					{
						bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
						redraw(1,EditFace->last->rank,1,1,EditFace);
						EditFace->clipbegin = 0;
						EditFace->clipend = 0;
					}
					if(EditFace->language == 1)
					{
						if(EditFace->column == 1&&EditFace->line == 1)
						{
							GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);
							break;
						}
						rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
						if(EditFace->column == 1&&EditFace->line > 1)
						{
							erase(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace,0xffff);
						}
						if(rank == 0)
						{
							EditFace->column = 92;
							srank = GetRank(EditFace->start,EditFace->line,EditFace->column);
							erase(srank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace,0xffff);
							DeleteNode(EditFace->line,EditFace->column,EditFace);
							redraw(srank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);
						}
						if(rank == EditFace->last->rank + 1)
						{
							NextPlace(LEFT,EditFace);
							erase(rank-1,EditFace->last->rank,EditFace->line,EditFace->column,EditFace,0xffff);
							DeleteNode(EditFace->line,EditFace->column,EditFace);
							redraw(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);  //只画图，不打字 
						}
						else
						{
							erase(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace,0xffff);
							NextPlace(LEFT,EditFace);
							DeleteNode(EditFace->line,EditFace->column,EditFace);
							redraw(rank-1,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);
					    }
					    if(EditFace->column == 1&&EditFace->line > 1)
					    {
					    	rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
					    	if(rank == 0)
					    	{
					    		EditFace->column = 93;
					    		EditFace->line --;
							}
						}
						/*rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
						if(rank == 0)
						{
							EditFace->column = 1;
							EditFace->line ++;
						}*/
						*revise = 1;
						GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);
					}
					else
					{
						EditFace->count --;
						if(EditFace->count >= 0)
						{
							EditFace->pin[EditFace->count] = 0;
							EditFace->spellplace --;
							bar_o((21 + EditFace->spellplace) * textw,600 - 3*texth,(22 + EditFace->spellplace)*textw,600 - texth,0xffff);
							GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
						}
						else
						{
							EditFace->count ++;
							GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
						}
					}
					break;	
				}
				case ENTER:
				{
					if(EditFace->clipbegin != 0)
					{
						bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
						redraw(1,EditFace->last->rank,1,1,EditFace);
						EditFace->clipbegin = 0;
						EditFace->clipend = 0;
					}
					if(EditFace->language == 1)
					{
						temp[0] = 13;
						temp[1] = 0;
						rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
						insert(rank,temp,EditFace);
						redraw(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);
						EditFace->column = 1;
						if(GetPic(EditFace->start,EditFace->line,93))
						{
							EditFace->line += 11;
						}	
						else
						{
							EditFace->line ++;
						}
						*revise = 1;
						GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);
						break;
					}
					else
					GuangBiao(EditFace,MainMenu,0,mainactive,&flag2);
					break;	
				}
				case F1:
				{
					EditFace->language = 1 - EditFace->language;
					if(EditFace->language == 1)
					{
						EditFace->spellplace = 1;
						EditFace->pin[0] = 0;
						EditFace->count = 0;
						ChangeLanguage(1,0);	
					}
					else
					ChangeLanguage(0,1);
					GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);
					break;	
				}
				case F2:    
				{
					int rank;
					rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
					if(EditFace->language == 0||rank > EditFace->last->rank||EditFace->start->data[0] == 0)
					{
						GuangBiao(EditFace,MainMenu,EditFace->language,mainactive,&flag2);
						break;
					}
					else
					{
						if(EditFace->clipbegin == 0)
						{
							EditFace->clipbegin = rank;
						}
						EditFace->clipend = rank;
						select(rank,rank,EditFace->line,EditFace->column,EditFace);
						NextPlace(RIGHT,EditFace);
						GuangBiao(EditFace,MainMenu,1,mainactive,&flag2);
						break;
					}
				}	
			}	
		} 
	}
}

void insert(int place,char *s,struct edit *EditFace)   //图像用@标志 
{
	struct node *p,*q;

	if(place == 1 && ((EditFace->start)->data[0]) == 0)
	{
		strcpy((EditFace->start)->data,s);
		if(*s == 13) (EditFace->start)->len = 0;
		else if(strcmp(s,"@") == 0) (EditFace->start)->len = 3;
		else
		{
			if(strlen(s) == 1)
			(EditFace->start)->len = 1;
			else if(strlen(s) == 2)
			(EditFace->start)->len = 2;
		}
	}
	else
	{
		q = (struct node*)malloc(sizeof(struct node));
		strcpy(q->data,s);
		if(*s == 13) q->len = 0;
		else if(strcmp(s,"@") == 0)
		{
			q->len = 3;
			strcpy(q->pic,EditFace->pn);
			EditFace->pn[0] ++;
		}
		else
		{
			if(strlen(s) == 1)
			q->len = 1;
			else if(strlen(s) == 2)
			q->len = 2;
		}
		q->rank = place;
		if(place == 1)
		{
			(EditFace->start)->prior = q;
			q->next = EditFace->start;
			q->prior = NULL;
			EditFace->start = q;
		}
		else if(place == (EditFace->last)->rank+1)
		{
			(EditFace->last)->next = q;
			q->prior = EditFace->last;
			q->next = NULL;
			EditFace->last = q;
		}
		else
		{
			p = EditFace->start;
			while(p->rank != place)
			{
				p = p->next;
			}
			q->prior = p->prior;
			(p->prior)->next = q;
			q->next = p;
			p->prior = q;
		}
	}
	p = q->next;
	while(p != NULL)
	{
		(p->rank) ++;
		p = p->next;
	}
}

void redraw(int begin,int end,int line,int column,struct edit *EditFace)
{
	int texth = textheight("t");
	int textw = textwidth("t");
	int textx,texty;
	int i;
	int pflag = 0;
	struct node *p;
	p = EditFace->start;
	erase(begin,end,line,column,EditFace,0xffff);
	
	if(begin > (EditFace->last)->rank) delay(1);
	else
	{
		while(p->rank != begin)
		{
			p = p->next;
		}
		for(i = begin;i <= end;i ++)    //len = 3时只写@，画图在下面 
		{
			if(p->len == 3)
			{
				textx = (column+1)*textw+8;
				texty = (2*line+5)*texth+4;
				if(texty >= 601-10*texth)
				{
					error("超出编辑范围"); 
				}
				yingwen(p->data,textx,texty,1,1,0);
				column ++;//这里要写画图的函数，并且pflag要联合在edit，redraw和erase中 (已写) 
				//pflag = 1;
				if(column > 93&&GetPic(EditFace->start,line,93))
				{
					column = 1;
					line += 11;
					//pflag = 0;
				}
				else if(column > 93&&!(GetPic(EditFace->start,line,93)))
				{
					column = 1;
					line ++;
				} 
			}
			else if(p->len == 0&&GetPic(EditFace->start,line,93))
			{
				column = 1;
				line += 11;
				texty = (2*line+5)*texth+4;
				if(texty >= 601-10*texth)
				{
					error("超出编辑范围"); 
				}
			}
			else if(p->len == 0&&!(GetPic(EditFace->start,line,93)))
			{
				column = 1;
				line ++;
				texty = (2*line+5)*texth+4;
				if(texty >= 601-10*texth)
				{
					error("超出编辑范围"); 
				}
			}
			else if(p->len == 1)
			{
				textx = (column+1)*textw+8;
				texty = (2*line+5)*texth+3;
				if(texty >= 601-10*texth)
				{
					error("超出编辑范围"); 
				}
				yingwen(p->data,textx,texty-1,1,1,0);
				column ++;
				if(column > 93&&GetPic(EditFace->start,line,93))
				{
					column = 1;
					line += 11;
				}
				else if(column > 93&&!(GetPic(EditFace->start,line,93)))
				{
					column = 1;
					line ++;
				}
			}
			else if(p->len == 2)
			{
				if(column == 93&&GetPic(EditFace->start,line,93))
				{
					column = 1;
					line += 11;
				}
				else if(column == 93&&!(GetPic(EditFace->start,line,93)))
				{
					column = 1;
					line ++;
				}
				textx = (column+1)*textw+8;
				texty = (2*line+4)*texth+8;
				if(texty >= 601-10*texth)
				{
					error("超出编辑范围");  
				}
				hanzi(textx,texty,p->data,0);
				column += 2;
				if(column > 93&&GetPic(EditFace->start,line,93))
				{
					column = 1;
					line += 11;
					//pflag = 0;
				}
				else if(column > 93&&!(GetPic(EditFace->start,line,93)))
				{
					column = 1;
					line ++;
				}
			}
			p =p->next;
		}
	}
	p = EditFace->start;      //重新画图 
	pflag = 0,line = 1,column = 1;  //初始化 
	while(p != NULL)
	{
		if(p->len == 3)
		{
			PrintPic(line,column,EditFace->start);
			column ++; 
			pflag = 1;
			if(column > 93&&pflag == 1)
			{
				column = 1;
				line += 11;
				pflag = 0;
			}
			else if(column > 93&&pflag == 0)
			{
				column = 1;
				line ++;
			}  
		}
		else if(p->len == 0&&pflag == 1)
		{
			column = 1;
			line += 11;
			pflag = 0;
		}
		else if(p->len == 0&&pflag == 0)
		{
			column = 1;
			line ++;
		}
		else if(p->len == 1)
		{
			column ++;
			if(column > 93&&pflag == 1)
			{
				column = 1;
				line += 11;
				pflag = 0;
			}
			else if(column > 93&&pflag == 0)
			{
				column = 1;
				line ++;
			}
		}
		else if(p->len == 2)
		{
			if(column == 93&&pflag == 1)
			{
				column = 1;
				line += 11;
			}
			else if(column == 93&&pflag == 0)
			{
				column = 1;
				line ++;
			}
			column += 2;
			if(column > 93&&pflag == 1)
			{
				column = 1;
				line += 11;
				pflag = 0;
			}
			else if(column > 93&&pflag == 0)
			{
				column = 1;
				line ++;
			}
		}
		p =p->next;	
	} 
}

void erase(int begin,int end,int line,int column,struct edit *EditFace,int color) 
{
	int sweepl,sweepc,x,y,textx,texty,i;
	int textw = textwidth("t");
	int texth = textheight("t");
	struct node *p,*q;
	sweepl = line;
	sweepc = column;
	p = EditFace->start;
	if(begin > (EditFace->last)->rank)
	{
	//	bar_o((column+2)*textw,((line-1)*2+7)*texth,(column+3)*textw,(line*2+7)*texth,color);
		return;
	}

	while(p->rank != begin)
	{
		p = p->next;
	}
	q = p;
	for(i = begin;i <= end;i ++)
	{
		if(q->len == 0&&GetPic(EditFace->start,sweepl,93))
		{
			sweepc = 1;
			sweepl += 11;
		}
		else if(q->len == 0&&!(GetPic(EditFace->start,sweepl,93)))
		{
			sweepc = 1;
			sweepl ++;
		}
		else if(q->len == 1)
		{
			sweepc ++;
			if(sweepc > 93&&GetPic(EditFace->start,sweepl,93))
			{
				sweepc = 1;
				sweepl += 11;
			}
			else if(sweepc > 93&&!(GetPic(EditFace->start,sweepl,93)))
			{
				sweepc = 1;
				sweepl ++;
			}
		}
		else if(q->len == 2)
		{
			if(sweepc == 93&&GetPic(EditFace->start,sweepl,93))
			{
				sweepc = 1;
				sweepl += 11;
			}
			else if(sweepc == 93&&!(GetPic(EditFace->start,sweepl,93)))
			{
				sweepc = 1;
				sweepl ++;
			}
			sweepc += 2;
			if(sweepc > 93&&GetPic(EditFace->start,sweepl,93))
			{
				sweepc = 1;
				sweepl += 11;
			}
			else if(sweepc > 93&&!(GetPic(EditFace->start,sweepl,93)))
			{
				sweepc = 1;
				sweepl ++;
			}
		}
		else if(q->len == 3)
		{
			sweepc ++; 
			if(sweepc > 93&&GetPic(EditFace->start,sweepl,93))
			{
				sweepc = 1;
				sweepl += 11;
			}
			else if(sweepc > 93&&!(GetPic(EditFace->start,sweepl,93)))
			{
				sweepc = 1;
				sweepl ++;
			}  
		}
		q = q->next;
	}
		x = sweepc-1;
		if(x < 1)
		{
			x = 93;
			y = sweepl-1;
		}
		else
		y = sweepl;

	if(line == y&&!(GetPic(EditFace->start,y,93)))  //最后一行没有图片 
	{
		bar_o((column+2)*textw,((line-1)*2+7)*texth,(x+4)*textw,((line-1)*2+9)*texth,color);
	}
	else if(line == y&&GetPic(EditFace->start,y,93)) //最后一行有图片
	{
		bar_o((column+2)*textw,((line-1)*2+7)*texth,97*textw,((line-1)*2+9)*texth,color);
		bar_o(3*textw,(line*2+7)*texth,97*textw,601-7*texth,color);
	} 
	else if(line != y&&!(GetPic(EditFace->start,y,93)))  //最后一行没有图片 
	{
		bar_o((column+2)*textw,((line-1)*2+7)*texth,97*textw,((line-1)*2+9)*texth,color);
		bar_o(3*textw,((y-1)*2+7)*texth,(x+4)*textw,((y-1)*2+9)*texth,color);
		if(y-line > 1)
		bar_o(3*textw,(line*2+7)*texth,97*textw,((y-1)*2+7)*texth,color);
	}
	else if(line != y&&GetPic(EditFace->start,y,93))  //最后一行有图片 
	{
		bar_o((column+2)*textw,((line-1)*2+7)*texth,97*textw,((line-1)*2+9)*texth,color);
		bar_o(3*textw,((y-1)*2+7)*texth,97*textw,((y-1)*2+9)*texth,color);
		if(y-line > 1)
		bar_o(3*textw,(line*2+7)*texth,97*textw,((y-1)*2+7)*texth,color);
		bar_o(3*textw,(y*2+7)*texth,97*textw,601-7*texth,color);
	}
} 

void NextPlace(int op,struct edit *EditFace)
{
	int rank,sweepl,sweepc,srank,sweepc1,sweepl1;
	int flag = 0;
	struct node *p;
	int i;
	
	switch(op)
	{
		case LEFT:
		{
			p = EditFace->start;
			rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
			if(rank > 1)
			{
				if(EditFace->column == 1&&EditFace->line > 1)
				{
					if(EditFace->line <= 11)
					{
						sweepl1 = EditFace->line - 1;
					}
					else if(GetPic(EditFace->start,EditFace->line-11,92)) //这里的图片判断有问题?
					{
						sweepl1 = EditFace->line - 11;
					}
					else
					{
						sweepl1 = EditFace->line - 1;
					}
					for(sweepc1 = 1;sweepc1 <= 93;sweepc1 ++)
					{
						srank = GetRank(EditFace->start,sweepl1,sweepc1);
						if(srank == rank - 1)
						{
							EditFace->column = sweepc1;
							EditFace->line = sweepl1;
							break;	
						}
					}
				}
				while(p->rank != rank - 1)
				{
					p = p->next;
				}
				if(p->len == 1||p->len == 3)
				{
					EditFace->column --;
				}
				else if(p->len == 2)
				{
					EditFace->column -= 2;
				}
			}
			break;
		}
		case RIGHT:
		{
			p = EditFace->start;
			rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
			if(rank == 1&&EditFace->start->data[0] == 0) 
			break;
			if(rank < EditFace->last->rank+1)
			{
				if(GetPic(EditFace->start,EditFace->line,93))
				{
					sweepl = EditFace->line + 11;
				}
				else
				{
					sweepl = EditFace->line + 1;
				}
				while(p->rank != rank)
				{
					p = p->next;
				}
				if(p->len == 1||p->len == 3)
				{
					EditFace->column ++;
				}
				else if(p->len == 2)
				{
					EditFace->column += 2;
				}
				for(sweepc = 1;sweepc <= 93;sweepc ++)
				{
					srank = GetRank(EditFace->start,sweepl,sweepc);
					if(srank == rank + 1)
					{
						EditFace->column = 1;
						EditFace->line = sweepl;
						break;
					}
				}
			}
			break;	
		}
		case UP:
		{
			if(EditFace->line > 1)
			{
				if(EditFace->line <= 11)
				{
					sweepl = EditFace->line - 1;
				}
				else if(GetPic(EditFace->start,EditFace->line-11,92))
				{
					sweepl = EditFace->line - 11;
				}
				else
				{
					sweepl = EditFace->line - 1;
				}
				sweepc = 1;
				rank = GetRank(EditFace->start,sweepl,sweepc);
				p = EditFace->start;
				while(p->rank != rank)
				{
					p = p->next;	
				}	
				srank = GetRank(EditFace->start,EditFace->line,sweepc);
				for(i = rank;i < srank;i ++)
				{
					if(p->len == 0)
					{
						flag = 1;
						break;
					}
					else p = p->next;
				}
				if(flag == 1)
				{
					rank = p->rank;
					for(sweepc = 1;sweepc <= 93;sweepc ++)
					{
						srank = GetRank(EditFace->start,sweepl,sweepc);
						if(srank == rank)
						break;	
					}
					if(EditFace->column >= sweepc)
					{
						EditFace->column = sweepc;
						EditFace->line = sweepl;
					}
					else
					{
						sweepc = 1;
						rank = GetRank(EditFace->start,sweepl,EditFace->column);
						for(;sweepc <= 93;sweepc ++)
						{
							srank = GetRank(EditFace->start,sweepl,sweepc);
							if(srank == rank)
							break;	
						}	
						EditFace->column = sweepc;
						EditFace->line = sweepl;
					}	
				}
				if(flag == 0)
				{
					if(EditFace->column == 93)
					{
						rank = GetRank(EditFace->start,EditFace->line,1);
						sweepc = 1;	
						for(;sweepc <= 93;sweepc ++)
						{
							srank = GetRank(EditFace->start,sweepl,sweepc);
							if(srank == rank - 1)
							break;
						}
						EditFace->column = sweepc;
						EditFace->line = sweepl;
					}
					else
					{
						rank = GetRank(EditFace->start,sweepl,EditFace->column);
						sweepc = 1;
						for(;sweepc <= 93;sweepc ++)
						{
							srank = GetRank(EditFace->start,sweepl,sweepc);
							if(srank == rank)
							break;	
						}
						EditFace->column = sweepc;
						EditFace->line = sweepl;
					}	
				}		
			}
			break;	
		}
		case DOWN:
		{
			rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
			if(rank == EditFace->last->rank + 1) break;
			if(EditFace->last->rank == 1) break;
			if(GetPic(EditFace->start,EditFace->line,92))
			{ 
				sweepl = EditFace->line + 11;
			}
			else if(!(GetPic(EditFace->start,EditFace->line,92)))
			{
				sweepl = EditFace->line + 1;
			}
			rank = GetRank(EditFace->start,sweepl,1);
			if(rank == 0) flag = 1;
			if(flag == 0)
			{
				rank = GetRank(EditFace->start,sweepl+1,1);
				if(rank == 0) flag = 1;
				if(flag == 1)
				{
					for(sweepc = 1;sweepc <= 93;sweepc ++)
					{
						srank = GetRank(EditFace->start,sweepl,sweepc);
						if(srank == EditFace->last->rank + 1)
						break;	
					}
					if(EditFace->column >= sweepc)
					{
						EditFace->column = sweepc;
						EditFace->line = sweepl;	
					}
					else
					{
						rank = GetRank(EditFace->start,sweepl,EditFace->column);
						for(sweepc = 1;sweepc <= 93;sweepc ++)
						{
							srank = GetRank(EditFace->start,sweepl,sweepc);
							if(srank == rank)
							break;	
						}
						EditFace->column = sweepc;
						EditFace->line = sweepl;	
					}	
				}
				else if(flag == 0)
				{
					sweepc = 1;
					rank = GetRank(EditFace->start,sweepl,sweepc);
					p = EditFace->start;
					while(p->rank != rank)
					{
						p = p->next;	
					}	
					srank = GetRank(EditFace->start,sweepl+1,sweepc);
					for(i = rank;i < srank;i ++)
					{
						if(p->len == 0)
						{
							flag = 1;
							break;
						}
						else
						p = p->next;
					}
					if(flag == 1)
					{
						rank = p->rank;
						for(;sweepc <= 93;sweepc ++)
						{
							srank = GetRank(EditFace->start,sweepl,sweepc);
							if(srank == rank)
							break;
						}
						if(EditFace->column >= sweepc)
						{
							EditFace->column = sweepc;
							EditFace->line = sweepl;
						}
						else
						{
							rank = GetRank(EditFace->start,sweepl,EditFace->column);
							for(sweepc = 1;sweepc <= 93;sweepc ++)
							{
								srank = GetRank(EditFace->start,sweepl,sweepc);
								if(srank == rank)
								break;
							}
							EditFace->column = sweepc;
							EditFace->line = sweepl;
						}
					}
					else
					{
						if(EditFace->column == 93)
						{
							rank = GetRank(EditFace->start,sweepl+1,1);
							for(sweepc = 1;sweepc <= 93;sweepc ++)
							{
								srank = GetRank(EditFace->start,sweepl,sweepc);
								if(srank == rank - 1)
								break;
							}
							EditFace->column = sweepc;
							EditFace->line = sweepl;
						}
						else
						{
							rank = GetRank(EditFace->start,sweepl,EditFace->column);
							for(sweepc = 1;sweepc <= 93;sweepc ++)
							{
								srank = GetRank(EditFace->start,sweepl,sweepc);
								if(srank == rank)
								break;
							}
							EditFace->column = sweepc;
							EditFace->line = sweepl;
						}
					}
				}	
			}
			break;	
		}	
	}
}

void DeleteNode(int line,int column,struct edit *EditFace)
{
	
	int rank;
	struct node *p;
	
	p = EditFace->start;
	rank = GetRank(EditFace->start,line,column);
	if(rank == 1)
	{
		if(p->next == NULL)
		p->data[0] = 0;
		else
		{
			EditFace->start = p->next;
			EditFace->start->prior = NULL;
			free(p);
			p = EditFace->start;
			do
			{
				p->rank --;
				p = p->next;
			}while(p != NULL);
		}
	}
	else if(rank == EditFace->last->rank)
	{
		p = EditFace->last;
		EditFace->last = p->prior;
		EditFace->last->next = NULL;
		free(p);
	}
	else
	{
		while(p->rank != rank)
		{
			p = p->next;
		}
		p->prior->next = p->next;
		p->next->prior = p->prior;
		free(p);
		p = EditFace->start;
		while(p->rank != rank+1)
		{
			p = p->next;
		}
		do
		{
			p->rank --;
			p = p->next;
		}while(p != NULL);
	}
}

void select(int begin,int end,int line,int column,struct edit *EditFace)
{
	int textx,texty,i;
	int textw = textwidth("t"),texth = textheight("t");
	struct node *p;
	
	p = EditFace->start;
//	erase(begin,end,line,column,EditFace,130);
	if(begin > EditFace->last->rank)
	return;
	while(p->rank != begin)
	{
		p = p->next;	
	} 
	
	for(i = begin;i <= end;i ++)
	{
		if(p->len == 0&&GetPic(EditFace->start,line,93))
		{
			column = 1;
			line += 11;
		}
		else if(p->len == 0&&!(GetPic(EditFace->start,line,93)))
		{
			column = 1;
			line ++;
		}
		else if(p->len == 1)
		{
			bar_o((2+column)*textw,(2*line+5)*texth,(3+column)*textw,(2*line+7)*texth,130);
			textx = (column + 2)*textw;
			texty = (2*line+5)*texth+4;
			yingwen(p->data,textx,texty-2,1,1,0);
			column ++;
			if(column > 93&&GetPic(EditFace->start,line,93))
			{
				column = 1;
				line += 11;
			}
			else if(column > 93&&!(GetPic(EditFace->start,line,93)))
			{
				column = 1;
				line ++;
			}
		}
		else if(p->len == 2)
		{
			if(column == 93&&GetPic(EditFace->start,line,93))
			{
				column = 1;
				line += 11;
			}
			else if(column == 93&&!(GetPic(EditFace->start,line,93)))
			{
				column = 1;
				line ++;
			}
			bar_o((2+column)*textw,(2*line+5)*texth,(4+column)*textw,(2*line+7)*texth,130);
			textx = (column+1)*textw+8;
			texty = (2*line+4)*texth+8;
			hanzi(textx,texty,p->data,0);
			column += 2;
			if(column > 93&&GetPic(EditFace->start,line,93))
			{
				column = 1;
				line += 11;
			}
			else if(column > 93&&!(GetPic(EditFace->start,line,93)))
			{
				column = 1;
				line ++;
			}
		}
		else if(p->len == 3)     //图像判断 
		{
			error("只能反白文本"); 
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			} 
		}
		p = p->next;
	}
} 
