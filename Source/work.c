#include"svgasub.h"
#include"work.h"
#include"hanzi_.h"
#include"menu.h" 
#include"draw.h"
#include"box.h"
#include"editma.h"
#include"grank.h"
#include"pic.h"
#include<stdlib.h>
#include<bios.h>
#include<graphics.h>
#include<alloc.h>
#include<stdio.h>
#include<string.h>
#include<process.h>

void func(struct edit *EditFace,struct buffer *imagebuffer,int command,int *MainActive,char *filename,int *revise,struct type *MainMenu)
{
	FILE *fp;
	char noname[15],temp[3];
	int i,flag;
	int textw = textwidth("t");
	int texth = textheight("t");
	
	strcpy(noname,"noname");
	for(i = 1;;i ++)
	{
		if(i > 9)
		{
			temp[0] = i / 10 + '0';
			temp[1] = i % 10 + '0';
			temp[2] = 0;
		}
		else
		{
			temp[0] = i + '0';
			temp[1] = 0;
		}
		strcat(noname,temp);
		strcat(noname,".txt");
		if((fp = fopen(noname,"rb")) == NULL)
		break;
		else
		{
			noname[6] = 0;
			fclose(fp);
		}
	}
	switch(command)
	{
		case 0:   //新建 
		{
			int op1,op2,flag;
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}
			if(*revise == 1)
			{
				op1 = SaveWarn(imagebuffer);
				if(op1 == 1)
				{
					op2 = dialog(imagebuffer,filename,"Save");
					if(op2 == 1)
					{
						flag = save(filename,EditFace->start);
						if(flag == 0)
						{
							edit(EditFace,MainMenu,MainActive,revise);
							break;	
						}	
						else if(flag == 1)
						{
							freeall(EditFace);
							*revise = 0;
							bar_o(44*textw+4,4*texth+4,60*textw+4,5*texth+4,130);
							setcolor(0);
							strcpy(filename,noname);
							yingwen(filename,44*textw+4,4*texth+4,1,1,0);
							edit(EditFace,MainMenu,MainActive,revise);
							break;
						}
					}
					else if(op2 == 2)
					{
						edit(EditFace,MainMenu,MainActive,revise);
						break;	
					}	
				}
				else if(op1 == 2)
				{
					edit(EditFace,MainMenu,MainActive,revise);
					break;	
				}
				else if(op1 == 0)
				{
					freeall(EditFace);
					*revise = 0;
					bar_o(44*textw+4,4*texth+4,60*textw+4,5*texth+4,130);
					setcolor(0);
					strcpy(filename,noname);
					yingwen(filename,44*textw+4,4*texth+4,1,1,0);
					edit(EditFace,MainMenu,MainActive,revise);
					break;	
				}	
			} 
			else
			{
				freeall(EditFace);
				bar_o(44*textw+4,4*texth+4,60*textw+4,5*texth+8,130);
				setcolor(0);
				strcpy(filename,noname);
				yingwen(filename,44*textw+4,4*texth+4,1,1,0);
				edit(EditFace,MainMenu,MainActive,revise);
				break;	
			}
			break;
		}
		case 100:    //打开文档函数 
		{
			int op1,op2,op3,flag;
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}
			if(*revise == 1)
			{
				op1 = SaveWarn(imagebuffer);
				if(op1 == 1)
				{
					op2 = dialog(imagebuffer,filename,"Save");
					if(op2 == 1)
					{
						flag = save (filename,EditFace->start);
						if(flag == 0)
						{
							edit(EditFace,MainMenu,MainActive,revise);
							break;
						}
						else
						{
							freeall(EditFace);
							*revise = 0;
							op3  = dialog(imagebuffer,filename,"Open");
							if(op3 == 1)
							{
								flag = OpenFile(filename,EditFace);
								if(flag == 0)
								{
									edit(EditFace,MainMenu,MainActive,revise);
									break;
								}
								else if(flag == 1)
								{
									bar_o(44*textw+4,4*texth+4,60*textw+4,5*texth+8,130);
									yingwen(filename,44*textw+4,4*texth+4,1,1,0);
									redraw(1,EditFace->last->rank,1,1,EditFace);
									edit(EditFace,MainMenu,MainActive,revise);
									break;
								}
							}
							else if(op3 == 2)
							{
								edit(EditFace,MainMenu,MainActive,revise);
								break;
							}
						}
					}
					else if(op2 == 2)
					{
						edit(EditFace,MainMenu,MainActive,revise);
						break;
					}
				}
				else if(op1 == 0)
				{
					freeall(EditFace);
					bar_o(44*textw+4,4*texth+4,60*textw+4,5*texth+8,130);
					*revise=0;
					op2 = dialog(imagebuffer,filename,"Open");
					if(op2 == 1)
					{
						flag = OpenFile(filename,EditFace);
						if(flag == 0)
						{
							edit(EditFace,MainMenu,MainActive,revise);
							break;
						}
						else if(flag == 1)
						{
							yingwen(filename,44*textw+4,4*texth+4,1,1,0);
							redraw(1,EditFace->last->rank,1,1,EditFace);
							edit(EditFace,MainMenu,MainActive,revise);
							break;
						}
					}
					else if(op2 == 2)
					{
						edit(EditFace,MainMenu,MainActive,revise);
						break;
					}
				}
				else if(op1 == 2)
				{
					edit(EditFace,MainMenu,MainActive,revise);
					break;
				}
			}
			else
			{
				freeall(EditFace);
				bar_o(44*textw+4,4*texth+4,60*textw+4,5*texth+8,130);
				op1 = dialog(imagebuffer,filename,"Open");
				if(op1 == 1)
				{
					flag = OpenFile(filename,EditFace);
					if(flag == 0)
					{
						edit(EditFace,MainMenu,MainActive,revise);
						break;
					}
					else if(flag == 1)
					{
						yingwen(filename,44*textw+4,4*texth+4,1,1,0);
						redraw(1,EditFace->last->rank,1,1,EditFace);
						edit(EditFace,MainMenu,MainActive,revise);
						break;
					}
				}
				else if(op1==2)
				{
					edit(EditFace,MainMenu,MainActive,revise);
					break;
				}
			}
			break;
		}
		case 101:  //保存 
		{
			int op,flag;
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}
			op = dialog(imagebuffer,filename,"Save");
			if(op == 1)
			{
				flag = save(filename,EditFace->start);
				if(flag == 0)
				{
					edit(EditFace,MainMenu,MainActive,revise);
					break;	
				}	
				else if(flag == 1)
				{
					*revise = 0;
					edit(EditFace,MainMenu,MainActive,revise);
					break;
				}
			} 
			else if(op == 2)
			{
				edit(EditFace,MainMenu,MainActive,revise);
				break;
			}
		}
		case 102:  //删除文档
		{
			int op,flag;
			char filename[20];
			
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}
			op = dialog(imagebuffer,filename,"Delete");
			if(op == 1)
			{
				flag = 	unlink(filename);
				if(flag == -1)
				error("路径不存在");
				edit(EditFace,MainMenu,MainActive,revise);
				break;
			}
			else if(op == 2)
			{
				edit(EditFace,MainMenu,MainActive,revise);
				break;	
			}	
		} 
		case 200:
		{
			cut(EditFace);
			edit(EditFace,MainMenu,MainActive,revise);
			break;
		}
		case 202:
		{
			paste(EditFace);
			*revise = 1;
			edit(EditFace,MainMenu,MainActive,revise);
			break;
		}
		case 201:
		{
			copy(EditFace);
			edit(EditFace,MainMenu,MainActive,revise);
			break;
		}
		case 300:   //插入图片 
		{
			char picfile[15];
			int op,flag;
			
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}
			op = OpenPic(imagebuffer,picfile);
			if(op == 1)
			{
				flag = InsertPic(picfile,EditFace);
				if(flag == 0)
				{
					error("路径不存在");
					edit(EditFace,MainMenu,MainActive,revise);
					break;	
				}	
				else if(flag == 1)
				{
					*revise = 1;
					edit(EditFace,MainMenu,MainActive,revise);
					break;
				}
				else if(flag == 2)
				{
					edit(EditFace,MainMenu,MainActive,revise);
					break;
				}
			} 
			else if(op == 2)
			{
				edit(EditFace,MainMenu,MainActive,revise);
				break;
			}
		}
		case 301:  //图片涂写 
		{
			int op;
			int l,c;
			
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}  //清除反白
			op = Pselect(EditFace,&l,&c);  //判断光标这里是不是对应图片 ,并且l,c表示图片的行列数 
			if(op == 1)
			{
				Paint(l,c,EditFace->start);
				edit(EditFace,MainMenu,MainActive,revise);
				break;
			}
			else
			{
				edit(EditFace,MainMenu,MainActive,revise);
				break;
			}
		}
		case 303:  //图片裁剪
		{
			int op;
			int l,c;
			
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}  //清除反白
			op = Pselect(EditFace,&l,&c);
			if(op == 1)
			{
				Crop(l,c,EditFace->start);
				edit(EditFace,MainMenu,MainActive,revise);
				break;	
			}	
			else
			{
				edit(EditFace,MainMenu,MainActive,revise);
				break;
			}
		} 
		case 302:  //图片旋转
		{
			int op;
			int l,c;
			
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}  //清除反白
			op = Pselect(EditFace,&l,&c);
			if(op == 1)
			{
				Rotate(l,c,EditFace->start);
				edit(EditFace,MainMenu,MainActive,revise);
				break;		
			}
			else
			{
				edit(EditFace,MainMenu,MainActive,revise);
				break;
			}	
		} 
		case 4:
		{
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			}  //清除反白
			Preview(EditFace);
			edit(EditFace,MainMenu,MainActive,revise);
			break;
		}
		case 6:
		{
			int open1,open2,flag;
			if(EditFace->clipbegin != 0)
			{
				bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
				redraw(1,EditFace->last->rank,1,1,EditFace);
				EditFace->clipbegin = 0;
				EditFace->clipend = 0;
			} 
			if(*revise == 1)
			{
				open1 = SaveWarn(imagebuffer);
				if(open1 == 1)
				{
					open2 = dialog(imagebuffer,filename,"Save");
					if(open2 == 1)
					{
						flag = save(filename,EditFace->start);
						if(flag == 0)
						{
							edit(EditFace,MainMenu,MainActive,revise);
							break;
						}
						else
						{
							freeall(EditFace);
							freeclip(EditFace);
							exit(0);
						}
					}
					else if(open2 == 2)
					{
						edit(EditFace,MainMenu,MainActive,revise);
						break;
					}
				} 
				else if(open1 == 0)
				{
					freeall(EditFace);
					freeclip(EditFace);
					exit(0);	
				} 
				else if(open1 == 2)
				{
					edit(EditFace,MainMenu,MainActive,revise);
					break;
				}
			}
			else
			{
				freeall(EditFace);
				freeclip(EditFace);
				exit(0);
			}
			break;
		}
	}
}

void freeall(struct edit *EditFace)
{
	struct node *p,*q;
	int textw = textwidth("t"),texth = textheight("t");
	
	p = EditFace->start;
	p->data[0] = 0;
	q = p->next;
	while(q != NULL)
	{
		p = q->next;
		free(q);
		q = p;
	}
	EditFace->last = EditFace->start;
	(EditFace->start)->prior = NULL;
	(EditFace->start)->next = NULL;
	EditFace->line = 1;
	EditFace->column = 1;
	EditFace->spellplace = 1;
	EditFace->pin[0] = 0;
	EditFace->count = 0;
	EditFace->language = 1;
	EditFace->start->rank = 1;
	EditFace->pn[0] = '1';
	bar_o(3*textw-1,7*texth-1,801-3*textw-2,601-7*texth,0xffffff);
}

void freeclip(struct edit *EditFace)
{
	
	struct node *p,*q;
	p = EditFace->clipstart;
	p->data[0] = 0;
	q = p->next;
	while(q != NULL)
	{
		p = q->next;
		free(q);
		q = p;
	}
	EditFace->cliplast = EditFace->clipstart;
	EditFace->clipstart->next = NULL;
}

int save(char *filename,struct node *start)
{
	FILE *fp;
	char s[10];
	struct node *p;
	
	p = start;
	if((fp = fopen(filename,"wb")) == NULL)
	{
		error("路径不存在");
		return 0;	
	}
	else
	{
		while(p != NULL)
		{
			if(p->data[0] == 0)
			{
				fprintf(fp,"%c",p->data[0]);
				fclose(fp);
				return 1;
			}
			else
			{
				if(p->len == 0)
				{
					fprintf(fp,"%c",p->data[0]);
				}
				else if(p->len == 1)
				{
					fprintf(fp,"%c",p->data[0]);
				}
				else if(p->len == 2)
				{
					fprintf(fp,"%c",p->data[0]);
					fprintf(fp,"%c",p->data[1]);
				}
				else if(p->len == 3)
				{
					SavePic(p->rank,start);
					fprintf(fp,"%c",p->data[0]);
				}
				p = p->next;
			}
		}
		fprintf(fp,"%c",0);
		fclose(fp);   //文本和图像标志的储存 
	}
	
	return 1;		
} 

void error(char *s2)
{
	int size;
	int textw = textwidth("t");
	int texth = textheight("t");
	int coor[4];
	char *s1 = "错误";
	//char *s2 = "路径不存在";
	void *buffer;
	
	coor[0] = 36 * textw;
	coor[1] = 24 * texth;
	coor[2] = 58 * textw;
	coor[3] = 33 * texth-3;
	
	size = imagesize(coor[0],coor[1],coor[2],coor[3]);
	buffer = (unsigned char*)malloc(size);
	getimage(coor[0],coor[1],coor[2],coor[3],buffer);
	bar_o(coor[0],coor[1],coor[2],coor[3],130);
	rectangle_o(coor[0],coor[1],coor[2],coor[3],7);
	hanzi_s(44*textw+8,24*texth+6,s1,1);
	hanzi_s(41*textw+8,27*texth+3,s2,0);
	hanzi_s(41*textw,29*texth+6,"按回车键退出",0);
	getchar();
	putimage(coor[0],coor[1],buffer,COPY_PUT);
	free(buffer);
}

int OpenFile(char *filename,struct edit *EditFace) 
{
	
	FILE *fp;
	int rank = 1;
	char temp[3];
	//char temp1[2] = "1";
	char s;
	
	if((fp = fopen(filename,"rb")) == NULL)     //打印汉字和英文 ,图像用@标志 
	{
		error("路径不存在");
		return 0;
	}
	else
	{
		while(!feof(fp))
		{
			temp[0] = getc(fp);
			if(temp[0] == 0)
			break;
			else if(32 <= temp[0]&&temp[0] < 127||temp[0] == 13)
			{
				temp[1] = 0;
			}
			else
			{
				temp[1] = getc(fp);
				temp[2] = 0;
			}
			insert(rank,temp,EditFace);
			rank ++;
		}
		fclose(fp);
	}
//	strcpy(EditFace->pn,temp1);
	return 1;
}

void cut(struct edit *EditFace)  //图像处理看select，这个没关系 
{
	int i,rank,srank;
	char *s;
	struct node *p,*q,*r;
	
	p = EditFace->start;
	if(EditFace->clipbegin != 0&&EditFace->language == 1)
	{
		freeclip(EditFace);
		while(p->rank != EditFace->clipbegin)
		{
			p = p->next;	
		}	
		strcpy(EditFace->clipstart->data,p->data);
		EditFace->clipstart->len = p->len;
		p = p->next;
		r = EditFace->clipstart;
		for(i = EditFace->clipbegin + 1;i <= EditFace->clipend;i ++)
		{
			q = (struct node *)malloc(sizeof(struct node));
			strcpy(q->data,p->data);
			q->len = p->len;
			r->next = q;
			q->prior = r;
			q->next = NULL;
			r = q;
			p = p->next;
		}
		EditFace->cliplast = r;
		for(i = EditFace->clipend;i >= EditFace->clipbegin;i --)
		{
			rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
			if(rank == 0)
			{
				EditFace->column = 92;
				DeleteNode(EditFace->line,EditFace->column,EditFace);
			}
			else
			{
				NextPlace(LEFT,EditFace);
				DeleteNode(EditFace->line,EditFace->column,EditFace);
			}
			//如果怕DeleteNode后排版有问题可以全部清楚了再重新redraw
		/*	if(editstage->row==1&&editstage->line>1)
			{
				rank=getrank(editstage->start,editstage->line,editstage->row);
				if(rank==0)
				{
					editstage->row=76;
					editstage->line--;
					editstage->scrline--;
				}
			}*/    //这个要判断图片！！！！ 
		}
		bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
		redraw(1,EditFace->last->rank,1,1,EditFace);
		EditFace->clipbegin = 0;
		EditFace->clipend = 0;
		return; 
	} 
	else
	return;
}

void paste(struct edit *EditFace)   //图像关键看redraw函数！！
{
	int i,rank;
	char temp[3];
	struct node *p;
	
	p = EditFace->clipstart;
	if(EditFace->clipstart->data[0] != 0&&EditFace->language == 1)
	{
		while(p != NULL)
		{
			strcpy(temp,p->data);
			rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
			insert(rank,temp,EditFace);
			redraw(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);
			NextPlace(RIGHT,EditFace);
			p = p->next;
		}
		return;
	}
	else
	return;
}

void copy(struct edit *EditFace)  //判断不能copy图像！！
{
	int i,rank;
	struct node *p,*q,*r;
	
	p = EditFace->start;
	if(EditFace->clipbegin != 0&&EditFace->language == 1)
	{
		freeclip(EditFace);
		while(p->rank != EditFace->clipbegin)
		{
			p = p->next;	
		}	
		strcpy(EditFace->clipstart->data,p->data);
		EditFace->clipstart->len = p->len;
		p = p->next;
		r = EditFace->clipstart;
		for(i = EditFace->clipbegin + 1;i <= EditFace->clipend;i ++)
		{
			q = (struct node *)malloc(sizeof(struct node));
			strcpy(q->data,p->data);
			q->len = p->len;
			r->next = q;
			q->prior = r;
			q->next = NULL;
			r = q;
			p = p->next;
		}
		EditFace->cliplast = r;
		bar_o(3*8-1,7*8-1,801-3*8,601-7*8,0xffffff);
		redraw(1,EditFace->last->rank,1,1,EditFace);
		EditFace->clipbegin = 0;
		EditFace->clipend = 0;
		return; 
	}
	else
	return;	
} 
