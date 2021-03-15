#include"pic.h"
#include"draw.h"
#include"chinese.h"
#include"hanzi_.h"
#include"box.h"
#include"menu.h"
#include"mouse.h"
#include"bmp.h" 
#include"grank.h"
#include"editma.h"
#include<graphics.h>
#include<alloc.h>
#include<bios.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
extern int x,y,ch,button;

int OpenPic(struct buffer *imagebuffer,char *picfile)
{
	int coor[4],size,key,asc,count = 0,i,flag2 = 0;
	int textw = textwidth("t"),texth = textheight("t");
	char *s = "ͼƬ����·��";
	char *p = picfile;
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
	outtextxy(41*textw,23*texth,"Insert");
	outtextxy(41*textw,23*texth,"       picture");
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
					*picfile = 0;
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
					*picfile = 0;
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
							*picfile = 0;
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
							*picfile = 0;
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
						*picfile = 0;
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

int InsertPic(char *picfile,struct edit *EditFace)
{
	int sweepc,sweepl;
	int flag,rank;
	int textw = textwidth("t"),texth = textheight("t");
	char temp[20],temp2[2];
	struct node *p,*q;
//	char s[5];
	
	temp2[0] = '@';
	temp2[1] = 0;
	strcpy(temp,"pic\\");
	strcat(temp,picfile);
	strcat(temp,".bmp");
	if(EditFace->line > 20||EditFace->column >= 92) //92,93�в������ͼƬ 
	{
		PicError("�����༭��Χ");
		return 2;
	}
	if(EditFace->column > 74)
	{
		sweepc = 74;
	}
	else
	{
		sweepc = EditFace->column;
	}
	if(GetPic(EditFace->start,EditFace->line,92))
	{
		sweepl = EditFace->line + 11;
	}
	else
	{
		sweepl = EditFace->line + 1;
	}
	rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
	erase(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace,0xffff); 
	yingwen("@",(EditFace->column+1)*textw+8,(2*EditFace->line+5)*texth+4,1,1,0);
	EditFace->column ++;
	redraw(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);
	rank = GetRank(EditFace->start,sweepl,1);
	if(rank != 0)
	{
		erase(rank,EditFace->last->rank,sweepl,1,EditFace,0xffff);
		flag = Read_BMP(temp,(2+sweepc)*textw,(2*EditFace->line+5)*texth+17);        //(6+EditFace->line)*texth+18 
		if(flag == 0)
		{
			EditFace->column --;
			rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
			redraw(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);
			return 0;
		}
		redraw(rank,EditFace->last->rank,EditFace->line + 11,1,EditFace);
	} 
	else
	{
		flag = Read_BMP(temp,(2+sweepc)*textw,(2*EditFace->line+5)*texth+17);
		if(flag == 0)
		{
			EditFace->column --;
			rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
			redraw(rank,EditFace->last->rank,EditFace->line,EditFace->column,EditFace);
			return 0;
		}
	}
	
	//����ͼƬ 
	q = (struct node*)malloc(sizeof(struct node));
	q->len = 3;
	strcpy(q->data,temp2);
	strcpy(q->pic,EditFace->pn);  //�������ļ����� 
//	strcat(q->pic,".txt");
	EditFace->pn[0] ++;
	//����ͼƬ��� 
	rank = GetRank(EditFace->start,EditFace->line,EditFace->column - 1);
	q->rank = rank;
	
	if(rank == 1)
	{
		(EditFace->start)->prior = q;
		q->next = EditFace->start;
		q->prior = NULL;
		EditFace->start = q;
	}
	else if(rank == (EditFace->last)->rank+1)
	{
		(EditFace->last)->next = q;
		q->prior = EditFace->last;
		q->next = NULL;
		EditFace->last = q;
	}
	else
	{
		p = EditFace->start;
		while(p->rank != rank)
		{
			p = p->next;
		}
		q->prior = p->prior;
		(p->prior)->next = q;
		q->next = p;
		p->prior = q;
	}
	p = q->next;
	while(p != NULL)
	{
		(p->rank) ++;
		p = p->next;
	}
	SavePic(rank,EditFace->start);
	return 1;
}

void PicError(char *s2)
{
	int size;
	int textw = textwidth("t");
	int texth = textheight("t");
	int coor[4];
	char *s1 = "��ʾ";
	//char *s2 = "�����༭��Χ";
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
	hanzi_s(41*textw,27*texth+3,s2,0);
	hanzi_s(41*textw,29*texth+6,"���س����˳�",0);
	getchar();
	putimage(coor[0],coor[1],buffer,COPY_PUT);
	free(buffer);
}

void SavePic(int place,struct node *start)
{
	int i,j,rank,pflag = 0,c;
	int sweepc = 1,sweepl = 1;
	struct node *p;
	char s[10];
	FILE *fp;
	
	p = start;
	while(p->rank != place)    //��ȡ��place���ڵ�������� 
	{
		if(p->len == 0)
		{
			if(pflag == 1)
			{				
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
		    }
		    else if(pflag == 0)
		    {
		    	sweepc = 1;
				sweepl ++;
			}
			p = p->next;
		}
		else if(p->len == 1)
		{
			sweepc ++;
			if(sweepc > 93 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc > 93 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			else if(sweepc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			p = p->next;
		}
		else if(p->len == 2)
		{
			sweepc += 2;
			if(sweepc > 93 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc > 93 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			p = p->next;
		}
		else if(p->len == 3)
		{
			pflag = 1;
			sweepc ++;
			if(sweepc > 93 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc > 93 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			else if(sweepc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			p = p->next;
		}
	}
	
	if(sweepc > 74) sweepc = 74;
	fp = fopen(p->pic,"w+");
	for(i = 0;i < 159;i ++)
	{
		for(j = 0;j < 159;j ++)
		{
			c = getpixel((2+sweepc)*8+j,(2*sweepl+5)*8+17+i);
			sprintf(s,"%d ",c);
			fputs(s,fp);
		}
	}
	fclose(fp);
}

void PrintPic(int line,int column,struct node *start)
{
	int rank,i,j,k,shu;
	int sweepc;
	char s[5],temp;
	struct node *p;
	FILE *fp;
	
	p = start;
	rank = GetRank(start,line,column);
	while(p->rank != rank)
	{
		p = p->next;
	}
	if(column > 75) sweepc = 75;
	else sweepc = column;
	if((fp = fopen(p->pic,"rb")) == NULL)
	{
		printf("open error!");
	}
	else
	{
		for(i = 0;i < 159;i ++)
		{
			for(j = 0;j < 159;j ++)
			{
				k = 0;
				while(1)
				{
					temp = fgetc(fp);
					if(temp != ' ') s[k ++] = temp;
					else if(temp == ' ')
					{
						s[k] = '\0';
						shu = atoi(s);
						putpixel((sweepc+1)*8+8+j,(2*line+6)*8+10+i,shu);
						break;
					}
				}
			}
		}
		fclose(fp);
	}
} 

int Pselect(struct edit *EditFace,int *line,int *column)
{
	int rank,sweepl = 1,sweepc = 1,pflag = 0;
	struct node *p;
	
	p = EditFace->start;
	rank = GetRank(EditFace->start,EditFace->line,EditFace->column);
	if(rank == EditFace->last->rank + 1)
	{
		PicError("���ﲻ��ͼ��");
		return 0;
	}
	while(p->rank != rank)
	{
		if(p->len == 0)
		{
			if(pflag == 1)
			{				
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
		    }
		    else if(pflag == 0)
		    {
		    	sweepc = 1;
				sweepl ++;
			}
			p = p->next;
		}
		else if(p->len == 1)
		{
			sweepc ++;
			if(sweepc > 93 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc > 93 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			else if(sweepc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			p = p->next;
		}
		else if(p->len == 2)
		{
			sweepc += 2;
			if(sweepc > 93 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc > 93 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			p = p->next;
		}
		else if(p->len == 3)
		{
			pflag = 1;
			sweepc ++;
			if(sweepc > 93 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc > 93 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			else if(sweepc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 1)
			{
				sweepc = 1;
				sweepl += 11;
				pflag = 0;
			}
			else if(sweepc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 0)
			{
				sweepc = 1;
				sweepl ++;
			}
			p = p->next;
		}
	}
	if(sweepc > 74) sweepc = 74;
	*line = sweepl;
	*column = sweepc;
	if(p->len == 3)
	{
		return 1;
	}
	else if(p->len != 3)
	{
		PicError("���ﲻ��ͼ��");
		return 0;
	}
}

void Paint(int line,int column,struct node *start)
{
	int textw = textwidth("t"),texth = textheight("t");
	int color = 0;  //��ʼ��ɫ�Ǻ�ɫ 
	int i,n,m,sweepc,rank;
	
	bar_o(36*textw-4,600-3*texth-4,58*textw+7,600-1*texth,0xffff);
	bar_o(36*textw-3,600-3*texth-3,38*textw,600-1*texth-1,144);
	bar_o(38*textw+2,600-3*texth-3,40*textw+5,600-1*texth-1,156);
	bar_o(41*textw-1,600-3*texth-3,43*textw+1,600-1*texth-1,177);
	bar_o(43*textw+3,600-3*texth-3,46*textw-2,600-1*texth-1,70);
	bar_o(46*textw,600-3*texth-3,48*textw+2,600-1*texth-1,71);
	bar_o(48*textw+4,600-3*texth-3,50*textw+7,600-1*texth-1,79);
	bar_o(50*textw+9,600-3*texth-3,53*textw+4,600-1*texth-1,171);
	bar_o(53*textw+6,600-3*texth-3,56*textw+1,600-1*texth-1,130);
	bar_o(56*textw+3,600-3*texth-3,58*textw+6,600-1*texth-1,0);   //��ѡɫ��
	bar_o(62*textw,600-3*texth-3,68*textw,600-1*texth-1,130);
	bar_o(71*textw,600-3*texth-3,77*textw,600-1*texth-1,130);
	hanzi_s(63*textw+1,600-3*texth-1,"ȷ��",10);
	hanzi_s(72*textw+1,600-3*texth-1,"ȡ��",10);
	
	if(column > 74) sweepc = 74; //��ֹͼ���ұ߳����߽� 
	else sweepc = column;
	
	setwritemode(1);
	cursor(x,y);
	setwritemode(0);
	while(1)
	{
		for(i = 1;i <= 200;i ++)
		{
			if(i % 40 == 0)
			{
				setwritemode(XOR_PUT);
				newxy(&x,&y,&button);
				setwritemode(0);
			}
			if(x > 36*textw-3&&x < 38*textw&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 144;
			else if(x > 38*textw+2&&x < 40*textw+5&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 156;
			else if(x > 41*textw-1&&x < 43*textw+1&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 177;
			else if(x > 43*textw+3&&x < 46*textw-2&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 70;
			else if(x > 46*textw&&x < 48*textw+2&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 71;
			else if(x > 48*textw+4&&x < 50*textw+7&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 79;
			else if(x > 50*textw+9&&x < 53*textw+4&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 171;
			else if(x > 53*textw+6&&x < 56*textw+1&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 130;
			else if(x > 56*textw+3&&x < 58*textw+6&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) color = 0;  //���ɫ��ѡ����ɫ
			
			if(x >= (sweepc+1)*8+8&&x <= (sweepc+1)*8+8+158&&y >= (2*line+6)*8+10&&y <= (2*line+6)*8+10+158&&ch == 1) //������ڶ�Ӧͼ������ʱ(2+sweepc)*8+j,(2*sweepl+5)*8+17+i
			{
				bar_o(x,y-3,x+2,y-1,color);	
			}
			if(x > 62*textw&&x < 68*textw&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) //���ȷ�� 
			{
				//����ͼƬ
				rank = GetRank(start,line,column);
				SavePic(rank,start);
				bar_o(36*textw-4,600-3*texth-4,77*textw,600-1,10);	
				return;
			}
			else if(x > 71*textw&&x < 77*textw&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) //ȡ�� 
			{
				PrintPic(line,sweepc,start);  //��ӡ֮ǰ��ͼƬ
				bar_o(36*textw-4,600-3*texth-4,77*textw,600-1,10);
				return;	
			} 
		}
	}
}

void Crop(int line,int column,struct node *start)
{
	int textw = textwidth("t"),texth = textheight("t");
	int i,j = 0,sweepc;  //��j����0ʱ����Ӧ��һ���㣬j����1��Ӧ�ڶ����㣬j����2��Ӧ�ü����� 
	char s[10];
	int temp[4];
	int rank;
	
	hanzi_s(26*textw-4,600-3*texth-4,"��һ����",0xffff);
	hanzi_s(43*textw-4,600-3*texth-4,"�ڶ�����",0xffff);
	bar_o(62*textw,600-3*texth-3,68*textw,600-1*texth-1,130);
	bar_o(71*textw,600-3*texth-3,77*textw,600-1*texth-1,130);
	hanzi_s(63*textw+1,600-3*texth-1,"ȷ��",10);
	hanzi_s(72*textw+1,600-3*texth-1,"ȡ��",10);
	if(column > 74) sweepc = 74; //��ֹͼ���ұ߳����߽� 
	else sweepc = column;
	
	setwritemode(1);
	cursor(x,y);
	setwritemode(0);
	while(1)
	{
		for(i = 1;i <= 200;i ++)
		{
			if(i % 40 == 0)
			{
				setwritemode(XOR_PUT);
				newxy(&x,&y,&button);
				setwritemode(0);
			}
			else
			delay(1);
			if(x >= (sweepc+1)*8+8&&x <= (sweepc+1)*8+8+158&&y >= (2*line+6)*8+10&&y <= (2*line+6)*8+10+158&&ch == 1)  //��ӡ��һ�������� 
			{
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				if(j == 0)
				{
					itoa(x,s,10);
					temp[0] = x;
					yingwen(s,34*textw,600-3*texth-1,1,1,0xffff);
					yingwen(",",38*textw-4,600-3*texth-1,1,1,0xffff);
					itoa(y,s,10);
					temp[1] = y;	
					yingwen(s,38*textw+4,600-3*texth-1,1,1,0xffff);
					ch = 0;
					j = 1;
				}
				else if(j == 1)
				{
					itoa(x,s,10);
					temp[2] = x;
					yingwen(s,51*textw,600-3*texth-1,1,1,0xffff);
					yingwen(",",55*textw-4,600-3*texth-1,1,1,0xffff);
					itoa(y,s,10);
					temp[3] = y;	
					yingwen(s,55*textw+4,600-3*texth-1,1,1,0xffff);
					j = 2;
					ch = 0;
				}
				setwritemode(1);
				cursor(x,y);
				setwritemode(0);
				delay(100);
			}
			if(j == 2)
			{
				bar_o(temp[0],temp[1],temp[2],temp[3],0xffff);  //�ü�����ӡ����ɫ 
				j = 3;
			}
			if(x > 62*textw&&x < 68*textw&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) //���ȷ�� 
			{
				//����ͼƬ
				rank = GetRank(start,line,column);
				SavePic(rank,start);
				bar_o(26*textw-4,600-3*texth-4,77*textw,600-1,10);	
				return;
			}
			else if(x > 71*textw&&x < 77*textw&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) //ȡ�� 
			{
				PrintPic(line,sweepc,start);  //��ӡ֮ǰ��ͼƬ
				bar_o(26*textw-4,600-3*texth-4,77*textw,600-1,10);
				return;	
			} 
		}
	}
} 

void Rotate(int line,int column,struct node *start)
{
	int textw = textwidth("t"),texth = textheight("t");
	int i,n,m,sweepc,c,k,shu;
	int rank;
	char s[10];
	char temp;
	FILE *fp;
	
	bar_o(62*textw,600-3*texth-3,68*textw,600-1*texth-1,130);
	bar_o(71*textw,600-3*texth-3,77*textw,600-1*texth-1,130);
	hanzi_s(63*textw+1,600-3*texth-1,"ȷ��",10);
	hanzi_s(72*textw+1,600-3*texth-1,"ȡ��",10);
	if(column > 74) sweepc = 74; //��ֹͼ���ұ߳����߽� 
	else sweepc = column;
	
	if((fp = fopen("pic.txt","w+")) == NULL)  //��ͼƬ��ʱ���ȡ 
	{
		printf("open error!");
	}
	else
	{
		for(n = 0;n < 159;n ++)
		{
			for(m = 0;m < 159;m ++)
			{
				c = getpixel((2+sweepc)*8+158-n,(2*line+5)*8+17+m);
				sprintf(s,"%d ",c);
				fputs(s,fp);
			}
		}
		fclose(fp);
	}
	if((fp = fopen("pic.txt","rb")) == NULL)  //��ͼƬ�����ӡ���� 
	{
		printf("open error!");
	}
	else
	{
		for(n = 0;n < 159;n ++)
		{
			for(m = 0;m < 159;m ++)
			{
				k = 0;
				while(1)
				{
					temp = fgetc(fp);
					if(temp != ' ') s[k ++] = temp;
					else if(temp == ' ')
					{
						s[k] = '\0';
						shu = atoi(s);
						putpixel((sweepc+1)*8+8+m,(2*line+6)*8+10+n,shu);
						break;
					}
				}
			}
		}
		fclose(fp);
	}
	setwritemode(1);
	cursor(x,y);
	setwritemode(0);
	while(1)
	{
		for(i = 1;i <= 200;i ++)
		{
			if(i % 40 == 0)
			{
				setwritemode(XOR_PUT);
				newxy(&x,&y,&button);
				setwritemode(0);
			}
			else
			delay(1);
			if(x > 62*textw&&x < 68*textw&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) //���ȷ�� 
			{
				//����ͼƬ
				rank = GetRank(start,line,column);
				SavePic(rank,start);
				bar_o(26*textw-4,600-3*texth-4,77*textw,600-1,10);	
				return;
			}
			else if(x > 71*textw&&x < 77*textw&&y > 600-3*texth-3&&y < 600-1*texth-1&&ch == 1) //ȡ�� 
			{
				PrintPic(line,sweepc,start);  //��ӡ֮ǰ��ͼƬ
				bar_o(26*textw-4,600-3*texth-4,77*textw,600-1,10);
				return;	
			} 
		}
	}
}

void Preview(struct edit *EditFace)
{
	int textw = textwidth("t"),texth = textheight("t");
	int sweepl = 1,sweepc = 1;
	int textx,texty;
	struct node *p;
	p = EditFace->start;
	
	bar_o(1,1,800,600,0xffff);
	rectangle_o(20*textw,2*texth,80*textw,73*texth,0);
	while(p != NULL)    //ԭ��ͬredraw�Ĵ�ӡԤ�� 
	{
		if(p->len == 1)  //Ӣ�Ĵ�ӡһ��С���� 
		{
			textx = (sweepc+1)*5+8+19*textw;
			texty = (2*sweepl+5)*5+2*texth;
			bar_o(textx,texty,textx+2,texty+3,7);
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
		else if(p->len == 2)  //���ִ�ӡ��һ��ķ��� 
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
			textx = (sweepc+1)*5+8+19*textw;
			texty = (2*sweepl+5)*5+2*texth;
			bar_o(textx,texty-2,textx+5,texty+3,7);
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
		else if(p->len == 3)
		{
			textx = (sweepc+1)*5+8+19*textw;
			texty = (2*sweepl+5)*5+2*texth;
			bar_o(textx,texty,textx+2,texty+3,7);
			bar_o(textx,texty+8,textx+100,texty+103,7);
			sweepc ++;
			if(sweepc > 93&&GetPic(EditFace->start,sweepl,93))
			{
				sweepc = 1;
				sweepl += 11;
			}
			else if(sweepc > 93&&!(GetPic(EditFace->start,sweepc,93)))
			{
				sweepc = 1;
				sweepl ++;
			}
		}
		else if(p->len == 0)
		{
			if(GetPic(EditFace->start,sweepl,93))
			{
				sweepc = 1;
				sweepl += 11;
			}
			else if(!(GetPic(EditFace->start,sweepl,93)))
			{
				sweepc = 1;
				sweepl ++;
			}
		}
		p = p->next;
	}
	getchar();
	//��������
	bar_o(0,0,800,600,0xffff);
	bar_o(0,0,799,32,10);
	hanzi_s(40,8,"�½�",0xffff);
	hanzi_s(152,8,"�ĵ�",0xffff);
	hanzi_s(264,8,"�༭",0xffff);
	hanzi_s(376,8,"ͼƬ",0xffff);
	hanzi_s(488,8,"��ӡ",0xffff); 
	hanzi_s(600,8,"����",0xffff);
	hanzi_s(712,8,"�˳�",0xffff);      
	DrawEditView();  //�ػ��༭ҳ�� 
	ChangeLanguage(1,0);  //�ػ�����״̬��
	redraw(1,EditFace->last->rank,1,1,EditFace); 
}
 
