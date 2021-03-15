/******建立文件信息区结构******/
typedef struct BMP_file{
	unsigned int bfType;    //文件类型，“BM”，bmp文件的标识
	unsigned long bfSize;    //bmp文件长度
	unsigned int Reserved1;    //系统保留
	unsigned int reserved2;    //系统保留
	unsigned long bfOffset;    //文件描述区长度
} bitmapfile;

/******建立图像信息区结构******/
typedef struct BMP_info{
	unsigned long biSize;  //图形尺寸（以像素为单位）
	unsigned long biWidth;  //图形宽度（以像素为单位）
	unsigned long biHeight;  //图形高度（以像素为单位）
	unsigned int  biPlane;    //此项数据必须为1
	unsigned int  biBitCount;  //每一个像素占二进制位数(1表示黑白色、4表示16色、8表示256色、8以上表示真彩图)
	unsigned long biCompression;  //是否是压缩格式
	unsigned long biSizeImage;    //位图占用字节数(计算公式=(大于等于biWidth的最小的4的整倍数)*biHeight)
	unsigned long biXpolsPerMeter;    //指定目标设备的水平分辨率(单位为每米的像素个数)
	unsigned long biYpelsPerMeter;    //指定目标设备的垂直分辨率(单位为每米的像素个数)
	unsigned long biClrUsed;    //此图实际用到的颜色数，若为0，则用到的颜色数为2的biBitCount次方
	unsigned long biClrImportant;    //制定本图像中重要的颜色数，若为0，则所有颜色一样重要
} bitmapinfo;


/***建立BMP文件完整结构定义***/
typedef struct bmp_picture_typ
{
	bitmapfile file;
	bitmapinfo info;
	char far *buffer;
}bmp_picture, *bmp_picture_ptr;


/****************导入BMP*******************/
void BMP_check(bmp_picture image);
void Read_BMP_K(char *filename, int x, int y, int color);
int Read_BMP(char *filename, int x, int y);
