#ifndef _MOUSE_H_
#define _MOUSE_H_
int init(int xmi,int xma,int ymi,int yma); //初始化鼠标
void read(int *mx,int *my,int *mbutt); //读取鼠标坐标
void cursor(int x,int y); //画鼠标
void newxy(int *mx,int *my,int *mbutt); //移动画鼠标 
#endif
