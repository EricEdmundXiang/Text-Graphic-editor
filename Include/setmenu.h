#ifndef _SETMENU_H_
#define _SETMENU_H_
void SetMainMenu(struct type *MainMenu,char **MainMenuItem); //记录总菜单参数
void SetSubMenu(struct type *SubMenu,char **SubMenuItem,struct type *MainMenu); //记录下拉菜单参数 
#endif
