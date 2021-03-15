#include<stdio.h>
#include"menu.h"
#include"grank.h"

int GetRank(struct node *start,int line,int column)
{
	int templ = 1,tempc = 1,rank = 1;
	int pflag = 0;
	struct node *p;
	
	p = start;
	if((p->next) == NULL)
	{
		if(p->data[0] == 0) return 1;
		else
		{
			if(line == 1&&column == 1) return 1;
			else if(column == 2&&line == 1&&p->len == 2) return 0;
			else if(column == 2&&line == 1&&p->len == 1) return 2;
			else if(column == 3&&line == 1&&p->len == 2) return 2;
			else return 0;
		}
	}
	else
	{
		if(line == 1&&column == 1) return 1;
		while(p != NULL)
		{
			if(p->len == 0)
			{
				if(pflag == 1)
				{				
					tempc = 1;
					templ += 11;
					pflag = 0;
			    }
			    else if(pflag == 0)
			    {
			    	tempc = 1;
					templ ++;
				}
				rank ++;
			}
			else if(p->len == 1)
			{
				tempc ++;
				if(tempc > 93 && pflag == 1)
				{
					tempc = 1;
					templ += 11;
					pflag = 0;
				}
				else if(tempc > 93 && pflag == 0)
				{
					tempc = 1;
					templ ++;
				}
				else if(tempc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 1)
				{
					tempc = 1;
					templ += 11;
					pflag = 0;
				}
				else if(tempc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 0)
				{
					tempc = 1;
					templ ++;
				}
				rank ++;
			}
			else if(p->len == 2)
			{
				tempc += 2;
				if(tempc > 93 && pflag == 1)
				{
					tempc = 1;
					templ += 11;
					pflag = 0;
				}
				else if(tempc > 93 && pflag == 0)
				{
					tempc = 1;
					templ ++;
				}
				rank ++;
			}
			else if(p->len == 3)
			{
				pflag = 1;
				tempc ++;
				if(tempc > 93 && pflag == 1)
				{
					tempc = 1;
					templ += 11;
					pflag = 0;
				}
				else if(tempc > 93 && pflag == 0)
				{
					tempc = 1;
					templ ++;
				}
				else if(tempc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 1)
				{
					tempc = 1;
					templ += 11;
					pflag = 0;
				}
				else if(tempc == 93 && p->next != NULL && (p->next)->len == 2 && pflag == 0)
				{
					tempc = 1;
					templ ++;
				}
				rank ++;
			}
			if(templ == line&&tempc == column) return rank;
			else p = p->next;
		} 
		return 0;
	}
}

int GetPic(struct node *start,int line,int column)
{
	int rank,tempc = 1;
	struct node *p;
	
	p = start;
	rank = GetRank(start,line,1);
	if(rank == 0) return 0;
	while(p->rank != rank)
	{
		p = p->next;
	}
	while(tempc <= column)
	{
		if(p->len == 3)
		{
			return 1;
		}
		else if(p->len == 1)
		{
			tempc ++;
		}
		else if(p->len == 2)
		{
			tempc += 2;
		}
		else if(p->len == 0)
		{
			return 0;
		}
		p = p->next;
	}
	return 0;
} 
