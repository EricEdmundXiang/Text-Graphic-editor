#ifndef _BOX_H_
#define _BOX_H_
int SaveWarn(struct buffer *imagebuffer); //储存未保存警告 
int dialog(struct buffer *imagebuffer,char *filename,char *type); //输入框 
void DialogArrow(int arrowx,int arrowy,int *flag2); //输入框显示时鼠标及光标的移动 
#endif
