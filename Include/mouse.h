#ifndef _MOUSE_H_
#define _MOUSE_H_
int init(int xmi,int xma,int ymi,int yma); //��ʼ�����
void read(int *mx,int *my,int *mbutt); //��ȡ�������
void cursor(int x,int y); //�����
void newxy(int *mx,int *my,int *mbutt); //�ƶ������ 
#endif
