//用来记录各种变量与常量
#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4b00
#define RIGHT 0x4d00
#define ENTER 0x1c0d
#define SPACE 0x3920
#define ESC 0x011b
#define BACKSPACE 0x0e08
#define F1 0x3b00
#define F2 0x3c00
#define PAGEDOWN 0x342e
#define PAGEUP 0x332c

#define MAXNUM 7
#define SUBNUM 7

struct type
{
	int coor[4];
	int itemcoor[4*MAXNUM];
	int itemtextxy[2*MAXNUM];
	int itemnum;
	int parent;
	char **itemname;
};

struct buffer
{
	int coor[4];
	void *ibuffer;
};

struct edit 
{
	struct node *start;
	struct node *last;
	struct node *clipstart;
	struct node *cliplast;
	int line;
	int column;
	int language;
	int spellplace; 
	int clipbegin;
	int clipend;
	int count;
	char pin[10];
	char pn[2];
};

struct node
{
	char data[3];
	char pic[10];
	struct node *prior;
	struct node *next;
	int len;
	int rank;
};

