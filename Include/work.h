#ifndef _WORK_H_
#define _WORK_H_
void func(struct edit *EditFace,struct buffer *imagebuffer,int command,int *MainActive,char *filename,int *revise,struct type *MainMenu);
void freeall(struct edit *EditFace); //É¾³ý±à¼­Á´±í 
void freeclip(struct edit *EditFace); //É¾³ý¼ôÇÐ°åÁ´±í 
int save(char *filename,struct node *start); //´¢´æº¯Êý 
void error(char *s2); //±¨´íº¯Êý 
int OpenFile(char *filename,struct edit *EditFace); //´ò¿ªº¯Êý 
void cut(struct edit *EditFace); //¼ôÇÐº¯Êý
void paste(struct edit *EditFace); //Õ³Ìùº¯Êý
void copy(struct edit *EditFace); //¸´ÖÆº¯Êý 
#endif
