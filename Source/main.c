#include"setmenu.h"
#include"menu.h"
#include"svgasub.h"
#include"draw.h"
#include"manage.h"
#include"chinese.h"

void main()
{
	struct type MainMenu,SubMenu[SUBNUM];
	
	char *MainMenuItem[] = {"�½�","�ĵ�","�༭","ͼƬ","��ӡ","����","�˳�",0};
	char *SubMenuItem1[] = {"��","����","ɾ��",0};
	char *SubMenuItem2[] = {"����","����","ճ��","����",0};
	char *SubMenuItem3[] = {"����","Ϳд","��ת","�ü�",0};
	char *SubMenuItem5[] = {"����","����",0};

	SVGA_Init();
	SubMenu[1].parent = 1;
	SubMenu[2].parent = 2;
	SubMenu[3].parent = 3;
	SubMenu[5].parent = 5;
	
	SetMainMenu(&MainMenu,MainMenuItem);
	SetSubMenu(&SubMenu[1],SubMenuItem1,&MainMenu);
	SetSubMenu(&SubMenu[2],SubMenuItem2,&MainMenu);
	SetSubMenu(&SubMenu[3],SubMenuItem3,&MainMenu);
	SetSubMenu(&SubMenu[5],SubMenuItem5,&MainMenu);
	welcome();
	DrawMainMenu(&MainMenu);
	DrawEditView();
	ChangeLanguage(1,0);
	ManageMenu(&MainMenu,SubMenu);
}
