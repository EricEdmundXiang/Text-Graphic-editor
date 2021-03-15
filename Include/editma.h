#ifndef	EDITMA_H
#define	EDITMA_H
void edit(struct edit *EditFace,struct type *MainMenu,int *mainactive,int *revise); //编辑模式管理
void insert(int place,char *s,struct edit *EditFace); //插入节点 
void redraw(int begin,int end,int line,int column,struct edit *EditFace); //刷新界面 
void erase(int begin,int end,int line,int column,struct edit *EditFace,int color); //擦除从begin到end之间的内容
void NextPlace(int op,struct edit *EditFace); //光标的移动 
void DeleteNode(int line,int column,struct edit *EditFace); //删除字符 
void select(int begin,int end,int line,int column,struct edit *EditFace);  //选择文本 
#endif
