#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<bios.h>
#include"bmp.h"
#include"svgasub.h"


/********************************
检查BMP图像是否符合要求
********************************/
void BMP_check(bmp_picture image)
{
	if (image.file.bfType != 0X4D42)  //检查是否为bmp文件
	{
		printf("Not a BMP file!\n");
		printf("image.file.bfType=%u\n", image.file.bfType);
	}
	if (image.info.biCompression != 0) //检查是否为压缩文件
	{
		printf("Can Not Open a Compressed bmp file!\n");
		printf("image.info.biCompression=%u\n", image.info.biCompression);
	}
	if (image.info.biBitCount != 8)    //检查是否为256色文件
	{
		printf("Not a 256 color bmp file\n");
		printf("image.info.biBitCount=%u", image.info.biBitCount);
	}
	return;
}

/********************************
读取BMP图像
********************************/
int Read_BMP(char *filename, int x, int y)
{
	FILE *fp;
	long ptrwidth, ptrheight;
	bmp_picture bmp256;
	char * buffer;
	unsigned char np = 0, op = 0;
	unsigned long pos;
	unsigned int  linebyte;
	unsigned char red[256], green[256], blue[256];
	int i, j;
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		//printf("%s BMP File Open Fail!\n", filename);
		return 0;
	}
	fread((char *)&bmp256.file, sizeof(bitmapfile), 1, fp);
	fread((char *)&bmp256.info, sizeof(bitmapinfo), 1, fp);   //将bmp图像信息调至结构bmp256中
//	BMP_check(bmp256);  //检查bmp文件
	ptrwidth = bmp256.info.biWidth;
	ptrheight = bmp256.info.biHeight;
	linebyte = ((ptrwidth*(long)bmp256.info.biBitCount + 31) / 32) * 4;  //宽度修正	
	fseek(fp, (long)bmp256.file.bfOffset, SEEK_SET);
	if ((buffer = (char *)malloc(linebyte)) == NULL)  //分配动态内存
	{
		printf("Malloc Func Used Fail!");
	}
	for (i = ptrheight - 1; i >= 0; i--)
	{
		fread(buffer, linebyte, 1, fp);
		for (j = 0; j < ptrwidth; j++)
		{
			pos = (i + y)*(long)800 + (j + x);
			np = pos / 65536;
			if (np != op)  //SVGA显示换页
			{
				Select_Page(np);
				op = np;
			}
			pokeb(0xa000, pos % 65536, buffer[j]);
		}
	}
	free(buffer);
	fclose(fp);
	return 1;
}


/********************************
读取BMP图像 可以抠图
********************************/
void Read_BMP_K(char *filename, int x, int y, int color)
{
	FILE *fp;
	long ptrwidth, ptrheight;
	bmp_picture bmp256;
	char * buffer;
	unsigned char np = 0, op = 0;
	unsigned long pos;
	unsigned int  linebyte;
	unsigned char red[256], green[256], blue[256];
	int i, j;
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("%s BMP File Open Fail!\n", filename);
	}
	fread((char *)&bmp256.file, sizeof(bitmapfile), 1, fp);
	fread((char *)&bmp256.info, sizeof(bitmapinfo), 1, fp);   //将bmp图像信息调至结构bmp256中
	BMP_check(bmp256);  //检查bmp文件
	ptrwidth = bmp256.info.biWidth;
	ptrheight = bmp256.info.biHeight;
	linebyte = ((ptrwidth*(long)bmp256.info.biBitCount + 31) / 32) * 4;  //宽度修正	
	fseek(fp, (long)bmp256.file.bfOffset, SEEK_SET);
	if ((buffer = (char *)malloc(linebyte)) == NULL)  //分配动态内存
	{
		printf("Malloc Func Used Fail!");
	}
	for (i = ptrheight - 1; i >= 0; i--)
	{
		fread(buffer, linebyte, 1, fp);
		for (j = 0; j < ptrwidth; j++)
		{
			pos = (i + y)*(long)800 + (j + x);
			np = pos / 65536;
			if (np != op)  //SVGA显示换页
			{
				Select_Page(np);
				op = np;
			}
			if (buffer[j] != color)
			pokeb(0xa000, pos % 65536, buffer[j]);
		}
	}
	free(buffer);
	fclose(fp);
}
