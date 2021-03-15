#ifndef	PIC_H
#define	PIC_H
int OpenPic(struct buffer *imagebuffer,char *picfile); //输入要插入的图像的名称 
int InsertPic(char *picfile,struct edit *EditFace); //在光标下一行插入图片 
void PicError(char *s2); //防止图像超出编辑范围 
void SavePic(int place,struct node *start); //储存图像 
void PrintPic(int line,int column,struct node *start); //光标对应的len如果为3，那么在其下面打印其对应的图像
int Pselect(struct edit *EditFace,int *line,int *column);  //判断光标当前位置是否对应图片，是返回1，否返回0 
void Paint(int line,int column,struct node *start);  //对对应行列的图片进行涂写操作 
void Crop(int line,int column,struct node *start);  //对对应的图片进行裁剪操作 
void Rotate(int line,int column,struct node *start);  //对对应的图片进行旋转操作 
void Preview(struct edit *EditFace);  //打印预览 
#endif
