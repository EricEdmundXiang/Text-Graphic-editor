#ifndef	EDITMA_H
#define	EDITMA_H
void edit(struct edit *EditFace,struct type *MainMenu,int *mainactive,int *revise); //�༭ģʽ����
void insert(int place,char *s,struct edit *EditFace); //����ڵ� 
void redraw(int begin,int end,int line,int column,struct edit *EditFace); //ˢ�½��� 
void erase(int begin,int end,int line,int column,struct edit *EditFace,int color); //������begin��end֮�������
void NextPlace(int op,struct edit *EditFace); //�����ƶ� 
void DeleteNode(int line,int column,struct edit *EditFace); //ɾ���ַ� 
void select(int begin,int end,int line,int column,struct edit *EditFace);  //ѡ���ı� 
#endif
