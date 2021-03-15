#ifndef _GRANK_H_
#define _GRANK_H_
int GetRank(struct node *start,int line,int column); //核心算法，获取节点的序列数 
int GetPic(struct node *start,int line,int column); //判断光标所在行是否插入了图像 
#endif
