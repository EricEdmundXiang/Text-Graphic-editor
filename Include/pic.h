#ifndef	PIC_H
#define	PIC_H
int OpenPic(struct buffer *imagebuffer,char *picfile); //����Ҫ�����ͼ������� 
int InsertPic(char *picfile,struct edit *EditFace); //�ڹ����һ�в���ͼƬ 
void PicError(char *s2); //��ֹͼ�񳬳��༭��Χ 
void SavePic(int place,struct node *start); //����ͼ�� 
void PrintPic(int line,int column,struct node *start); //����Ӧ��len���Ϊ3����ô���������ӡ���Ӧ��ͼ��
int Pselect(struct edit *EditFace,int *line,int *column);  //�жϹ�굱ǰλ���Ƿ��ӦͼƬ���Ƿ���1���񷵻�0 
void Paint(int line,int column,struct node *start);  //�Զ�Ӧ���е�ͼƬ����Ϳд���� 
void Crop(int line,int column,struct node *start);  //�Զ�Ӧ��ͼƬ���вü����� 
void Rotate(int line,int column,struct node *start);  //�Զ�Ӧ��ͼƬ������ת���� 
void Preview(struct edit *EditFace);  //��ӡԤ�� 
#endif
