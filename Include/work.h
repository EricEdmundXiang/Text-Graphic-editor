#ifndef _WORK_H_
#define _WORK_H_
void func(struct edit *EditFace,struct buffer *imagebuffer,int command,int *MainActive,char *filename,int *revise,struct type *MainMenu);
void freeall(struct edit *EditFace); //ɾ���༭���� 
void freeclip(struct edit *EditFace); //ɾ�����а����� 
int save(char *filename,struct node *start); //���溯�� 
void error(char *s2); //������ 
int OpenFile(char *filename,struct edit *EditFace); //�򿪺��� 
void cut(struct edit *EditFace); //���к���
void paste(struct edit *EditFace); //ճ������
void copy(struct edit *EditFace); //���ƺ��� 
#endif
