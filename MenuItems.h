//MenuItems.h
//MenuItem={Level,connect,firstelement,extraparameter,text}

//MainMenu
//--------------------------------
#define _MAINMENU 				0
#define _GAMESMENU 				5
#define _CONTRASTMENU 			1
#define _BRIGHTNESSMENU 		2
#define _DISPLAYDASHTEMP 		3
#define _CONFIGMENU				4
#define _RESET					6
//GamesMenu
//--------------------------------
#define _GAME1					7
//ConfigMenu
//--------------------------------
#define _EDITCONSTANT				10
#define _MENUTHEME				11

//Extraparameter options
//--------------------------------
#define _NONE		0
#define _SHOWVALUE	1
#define _EXIT	255

//--------------------------------

//#define _BTN_ENTER		0x0A
//#define _BTN_ESC		0x05
//#define _BTN_LEFT		0x0D
//#define _BTN_RIGHT		0x07

unsigned rom const char Menuitem_Contrast[]={_MAINMENU,_CONTRASTMENU,_NONE,_NONE,'C','o','n','t','r','a','s','t',0,};
unsigned rom const char Menuitem_Brightness[]={_MAINMENU,_BRIGHTNESSMENU,_NONE,_NONE,'B','r','i','g','h','t','n','e','s','s',0};
unsigned rom const char Menuitem_DashTemp[]={_MAINMENU,_DISPLAYDASHTEMP,_NONE,_NONE,'D','a','s','h','T','e','m','p',0};
unsigned rom const char Menuitem_Config[]={_MAINMENU,_CONFIGMENU,_EDITCONSTANT,_NONE,'C','o','n','f','i','g',0};
unsigned rom const char Menuitem_Games[]={_MAINMENU,_GAMESMENU,_GAME1,_NONE,'G','a','m','e','s',0};

unsigned rom const char Games_Game1[]={_GAMESMENU,_GAME1,_NONE,_NONE,'S','n','a','k','e',0};

//unsigned rom const char	Meniutem_EditConstant[]={_CONFIGMENU,_EDITCONSTANT,_EXIT,_SHOWVALUE,'C','o','n','s','t','a','n','t','=','3','3','2','9','2',0,};
unsigned rom const char	Menuitem_EditConstant[]={_CONFIGMENU,_EDITCONSTANT,_EXIT,_NONE,'C','o','n','s','t','a','n','t','=','3','3','2','9','2',0,};
unsigned rom const char Menuitem_Reset[]={_MAINMENU,_NONE,_NONE,_NONE,'R','e','s','e','t',0};
