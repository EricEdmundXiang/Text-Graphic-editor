#ifndef _DRAW_H_
#define _DRAW_H_
void DrawMainMenu(struct type *MainMenu); //�����˵�
void DrawSubMenu(struct type *SubMenu,struct buffer *imagebuffer,int active); //�������˵�
void ActiveMainMenuItem(struct type *menu,int active,int status); //�������˵�ѡ�� 
void DrawEditView(void); //���༭���� 
void ActiveSubMenuItem(struct type *SubMenu,int active,int status); //���������˵�����
void ExitMenu(struct buffer *imagebuffer); //�������˵� 
void welcome(void); //������ӭ���� 
void bar_o(int tx,int ty,int ta,int tb,unsigned int color); //��ɫ�麯�� 
void line_o(int tx,int ty,int ta,int tb,unsigned int color); //��ֱ�ߺ��� 
void rectangle_o(int tx,int ty,int ta,int tb,unsigned int color); //�������� 
#endif
