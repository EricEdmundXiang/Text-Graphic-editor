#ifndef _DRAW_H_
#define _DRAW_H_
void DrawMainMenu(struct type *MainMenu); //画主菜单
void DrawSubMenu(struct type *SubMenu,struct buffer *imagebuffer,int active); //画下拉菜单
void ActiveMainMenuItem(struct type *menu,int active,int status); //激活主菜单选项 
void DrawEditView(void); //画编辑界面 
void ActiveSubMenuItem(struct type *SubMenu,int active,int status); //激活下拉菜单函数
void ExitMenu(struct buffer *imagebuffer); //返回主菜单 
void welcome(void); //画出欢迎界面 
void bar_o(int tx,int ty,int ta,int tb,unsigned int color); //画色块函数 
void line_o(int tx,int ty,int ta,int tb,unsigned int color); //画直线函数 
void rectangle_o(int tx,int ty,int ta,int tb,unsigned int color); //画矩阵函数 
#endif
