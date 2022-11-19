//menucontrol.c
#include "menuitems.h"
#include "graphics.h"
#include "pcf8548.h"
#include "menucontrol.h"
#include "main.h"
#include "lin.h"
#include "buttons.h"
#include <p18f25k22.h>
//---------------------------------------------------------------------------------------
//Basic menucontrol data structure
//---------------------------------------------------------------------------------------




#define _MAXCONTRAST		135
#define _MINCONTRAST		105
#define _MAXBRIGHTNESS		15

unsigned rom const char * getMenuItem(unsigned char);
unsigned char ShowContrastMenu(unsigned char);
unsigned char ShowBrightnessMenu(unsigned char);
//---------------------------------------------------------------------------------------
//Function:InitMenu
//Description: Initializes the menu's system variables
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
void InitMenu(void)
{
	MenuControl.DisplayState=_NORMALSTATE;
	MenuControl.CurrentLevel=_MAINMENU;
	MenuControl.HighlightedItem=_CONTRASTMENU;
	MenuControl.Line=1;
	Contrast=120;

	
}

void HandleMenu(unsigned char Keyboard)
{
	switch(Keyboard)
	{
		case _BTN_MENU_UP:
		case _KEY_INC:
			if(*(getMenuItem((MenuControl.HighlightedItem+1)))==MenuControl.CurrentLevel)
			MenuControl.HighlightedItem++;
			if(MenuControl.HighlightedItem>(MenuControl.Line+2)) MenuControl.Line++; 
			Keyboard=0;
			break;
		case _BTN_MENU_DOWN:
		case _KEY_DEC:
			if(MenuControl.HighlightedItem>1) 
			MenuControl.HighlightedItem--;
			if(MenuControl.HighlightedItem<(MenuControl.Line)) MenuControl.Line--; 
			Keyboard=0;
			break;
	//	case _BTN_ENTER:
		case _KEY_ENTER:
			if(MenuControl.HighlightedItem==_GAME1) //Pong(&SmallBall[0]);
 			{
			//	InitGame_Pong(&SmallBall[0]);
				InitGame_Worm();
				MenuControl.DisplayState=_GAME_WORM;
				break;
			}
			if(MenuControl.HighlightedItem==_RESET) _asm reset _endasm;
			MenuControl.CurrentLevel=*(getMenuItem(MenuControl.HighlightedItem)+1);
			MenuControl.Line=*(getMenuItem(MenuControl.HighlightedItem)+2);
			MenuControl.HighlightedItem=MenuControl.Line;
			if(MenuControl.Line==255) MenuControl.DisplayState=_NORMALSTATE;
			Keyboard=0;
			break;
		case _BTN_ESC:
			if(MenuControl.CurrentLevel!=_MAINMENU)
			{
				MenuControl.CurrentLevel=*(getMenuItem(MenuControl.CurrentLevel));
				MenuControl.HighlightedItem=*(getMenuItem(MenuControl.CurrentLevel)+1);
				MenuControl.Line=MenuControl.HighlightedItem;
			}			
			else ExitMenu();
			Keyboard=0;
			break;
		default:
			break;
	}
}
void DrawMenu(void)
{
	unsigned char cnt,line=1;
	unsigned char *pointertemp;
	for(cnt=MenuControl.Line;cnt<(MenuControl.Line+3);cnt++)
	{
		if(!((*getMenuItem(cnt))==MenuControl.CurrentLevel)) break;
		glcdPutStringFine(1,(line-1)*10+1,(getMenuItem(cnt)+4));
	//	if((*(getMenuItem(cnt)+3))==_SHOWVALUE) glcdPutValueFine(ShowValue(),70,((line-1)*10+1)); 
		if(cnt==MenuControl.HighlightedItem) glcdHighlightLine(((line-1)*10));
		line++;
	}
	
}
unsigned rom const char * getMenuItem(unsigned char MenuItemNumber)
{
	switch(MenuItemNumber)
	{
	case _CONTRASTMENU:
		return &Menuitem_Contrast[0];
	case _BRIGHTNESSMENU:
		return &Menuitem_Brightness[0];
	case _DISPLAYDASHTEMP:
		return &Menuitem_DashTemp[0];
	case _CONFIGMENU:
		return &Menuitem_Config[0];
	case _GAMESMENU:
		return &Menuitem_Games[0];
	case _GAME1:
		return &Games_Game1[0];
	case _EDITCONSTANT:
		return &Menuitem_EditConstant[0];
	case _RESET:
		return &Menuitem_Reset[0];
	}
}


void DrawMainMenu(unsigned char Keyboard)
{
		 glcdClearScreen(0);
		 glcdSetFont(_TIMESNEWROMAN_SIZE8);
		 switch(MenuControl.CurrentLevel)
		{
			case _MAINMENU:
			case _CONFIGMENU:
			case _GAMESMENU:
		 		DrawMenu();
				HandleMenu(Keyboard);
				break;
			case _DISPLAYDASHTEMP:
				//DrawDashTemp();
				break;
			case _BRIGHTNESSMENU:
				if(!ShowBrightnessMenu(Keyboard))
				{
					MenuControl.CurrentLevel=_MAINMENU;
					MenuControl.HighlightedItem=_BRIGHTNESSMENU;
					MenuControl.Line=_BRIGHTNESSMENU;
				}
				break;
			case _CONTRASTMENU:
				if(!ShowContrastMenu(Keyboard))
				{
					MenuControl.CurrentLevel=_MAINMENU;
					MenuControl.HighlightedItem=_CONTRASTMENU;
					MenuControl.Line=_CONTRASTMENU;
				}
				break;
			default: break;
		} 
		 
		 glcdRefreshDisplay180(0);
	}

void ExitMenu(void)
{
	MenuControl.DisplayState=_NORMALSTATE;
}



unsigned char ShowContrastMenu(unsigned char Keyboard)
{
	glcdClearScreen(0);
	switch(Keyboard)
	{
		case _BTN_ESC:
			Keyboard=0;
			return 0;
		case _BTN_ENTER:
			Keyboard=0;
			//Save setting to eeprom, then exit to main menu
			glcdPutStringFine(61,2,"Saved");
			//return 1;
			break;
		//case _BTN_MENU_DOWN:
		case _KEY_INC:
			if(Contrast<_MAXCONTRAST) Contrast++;
			break;
		//case _BTN_MENU_UP:
		case _KEY_DEC:
			if(Contrast>_MINCONTRAST) Contrast--;
			break;
		default: break;
	}
//	if(!Keyboard) 	PutDAC(Contrast,DAC_DOUBLE_GAIN | DAC_ADDR_CONTR | DAC_ON);	
	glcdPutStringFine(3,2,"Contrast:");
	glcdPutValueFine(Contrast,80,2);
	glcdDrawBarFixedWidth(4,19,(Contrast-100)*3);
	glcdRefreshDisplay180(0);

	Keyboard=0;
	return 1;
}


unsigned char ShowBrightnessMenu(unsigned char Keyboard)
{
	glcdClearScreen(0);
	switch(Keyboard)
	{
		case _BTN_ESC:
			Keyboard=0;
			return 0;
		case _BTN_ENTER:
			Keyboard=0;
			//Save setting to eeprom, then exit to main menu
			glcdPutStringFine(61,2,"Saved");
			SendIBUSFunction(0x02,Brightness*3);
			break;
		//case _BTN_MENU_DOWN:
		case _KEY_DEC:
			if(Brightness<_MAXBRIGHTNESS) Brightness+=1;
			break;
		//case _BTN_MENU_UP:
		case _KEY_INC:
			if(Brightness>0) Brightness-=1;
			break;
		default: break;
	}
	CCPR1L=Brightness*6;
//	if(!Keyboard) 	PutDAC(Brightness*10,DAC_DOUBLE_GAIN | DAC_ADDR_BACKL | DAC_ON);	
	glcdPutStringFine(3,2,"Brightness:");
	glcdDrawBarFixedWidth(4,19,Brightness*6);
	glcdRefreshDisplay180(0);
	Keyboard=0;
	return 1;
}

unsigned char GetMenuState(void)
{
	if(MenuControl.DisplayState)
	return 1;
	else return 0;
}