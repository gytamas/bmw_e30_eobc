#include "MenuControl_v2_0.h"
#include "graphics.h"
#include "pcf8548.h"
#include "main.h"
#include "lin.h"
#include "buttons.h"
#include "internalE2P.h"
//#include "worm.h"d

#include <p18f25k22.h>
//TEST

#define _MAX_ITEMS_TO_DISPLAY 3
#define _END_OF_MENU 0x0000
#define _MAX_MENU_DEPTH 5


//Should be defined elswhere!!!!!!!
//------------------------------------
#define _MAXCONTRAST		135
#define _MINCONTRAST		105
#define _MAXBRIGHTNESS		15
//---------------[Definition of menu system]-----------------
// Menuitems:
// unsigned const rom int <name of menuitem>[(array)]={<a pointer to a function which should be called in case 
// 		menuitem is called>,<pointer to an array which contains the list of the menus>,<string of the menu>
// 
//
//
//
//------------------------------------------------------------

//Extern variables and functions:

unsigned char Contrast,Brightness;

extern const rom char Symbol_MenuArrowDown[];
extern const rom char Symbol_MenuArrowUp[];
extern const rom char Symbol_CheckBoxUnChecked[];
extern const rom char Symbol_CheckBoxChecked[];
extern void StartGameWorm();
extern void PlayWorm(unsigned char);
extern void StartGameWorm(unsigned char);
extern void ReadTime();
extern unsigned char hours,minutes;
extern unsigned const rom char dither_01;
//extern unsigned char InverseGraphic;

unsigned const int rom ConfigMenu_Items[];
unsigned const int rom GamesMenu_Items[];
unsigned const int rom AirHornMenu_Items[];
unsigned const int rom DateTimeMenu_Items[];

typedef unsigned const rom int menuitem;
menuitem BrightnessMenu[]={&ShowBrightnessMenu_V2,0,"Backlight"};
menuitem ContrastMenu[]={&ShowContrastMenu_V2,0,"Contrast"};
menuitem ConfigMenu[]={&EnterMenu,&ConfigMenu_Items[0],"Config"};
menuitem GamesMenu[]={&EnterMenu,&GamesMenu_Items,"Games"};
menuitem Reset[]={&ResetMCU_V2,0,"Reset"};
menuitem ExitFromMenu[]={0,0,"Exit"};
menuitem Back[]={&MenuItems_Back,0,"Back"};
menuitem GameItem_Snake[]={&PlayPizzaWorm,0,"Snake"};
menuitem AirHornMenu[]={&EnterAirHornMenu,&AirHornMenu_Items,"MelodyHorn"};//{&EnterAirHornMenu,&AirHornMenu_Items,"MelodyHorn"};
menuitem Melody[]={&SelectMelodies,0,"SelectMelody"};
menuitem MelodySpeed[]={&ShowMelodySpeedMenu,0,"TimeBase"};
menuitem RefreshMelodies[]={&RefreshList,0,"Refresh"};
menuitem DateTimeMenu[]={&EnterMenu,&DateTimeMenu_Items,"Set Time"};
menuitem TimeMenu[]={&ShowTimeMenu,0,"Set Time"};
menuitem DateMenu[]={&ShowDateMenu,0,"Set Date"};
menuitem Play[]={&PlayTune,0,"Play"};

unsigned char MenuGlobalTemp;
unsigned char Shift=3;
unsigned char TestMenuBuffer[40];
unsigned char TestBufferMenuLine=0;
unsigned int MenuHistory[_MAX_MENU_DEPTH];
unsigned char Depth=0;
void (*ShowMenuSystem)(unsigned char);

unsigned const int rom MainMenu_Items[]=
{
	&DateTimeMenu,
	&BrightnessMenu,
	&ContrastMenu,
	&ConfigMenu,
	&AirHornMenu,
	&GamesMenu,
	&Reset,
	&ExitFromMenu,
	_END_OF_MENU
};

unsigned const int rom ConfigMenu_Items[]=
{
	&Back,
	_END_OF_MENU
};
unsigned const int rom GamesMenu_Items[]=
{
	&GameItem_Snake,
	&Back,
	_END_OF_MENU
};
unsigned const int rom AirHornMenu_Items[]=
{
	&Play,
	&Melody,
	//&MelodySpeed, --> not yet supported
	&RefreshMelodies,
	&Back,
	_END_OF_MENU
};
unsigned const int rom DateTimeMenu_Items[]=
{
	&TimeMenu,
	&DateMenu,	
	&Back,
	_END_OF_MENU
};

unsigned const rom int *Menu=&MainMenu_Items[0];
unsigned const rom int  *SelectedMenuItem=MainMenu_Items;
//EndOfTest

//----------------------------------------------------------------------------------------------
//Function: GetMenustring
//Description: Returns a pointer to the string (or name) of the menuitem indicated by the menuitem 
// 		input parameter
//Return value: A pointer to the string (or name) of the menuitem
//Input value: The currently selected menuitem.
//Effects: No effects.
//----------------------------------------------------------------------------------------------
unsigned const rom char *GetMenuString(unsigned const rom int *menuitem)
{
	return *(menuitem+2);
}

//----------------------------------------------------------------------------------------------
//Function: GetFunction
//Description: Returns the function allocated to the the menuitem indicated by the menuitem input parameter
//Return value: A pointer to the funciton which should be called when the currently selected menuitem
// 		is triggered.
//Input value: The currently selected menuitem.
//Effects: No effects.
//----------------------------------------------------------------------------------------------
unsigned const rom int *GetFunction(unsigned const rom int *menuitem)
{
	return (*(unsigned const rom int*) menuitem);
}

//----------------------------------------------------------------------------------------------
//Function: GetMenu
//Description: Returns a pointer to the array of the submenu indicated by the menuitem input parameter
//Return value: A pointer to the currently selected submenu folder
//Input value: A pointer of the currently selected menuitem
//Effects: No effects.
//----------------------------------------------------------------------------------------------
unsigned const rom int *GetMenu(unsigned const rom int *menuitem)
{
		return *(menuitem+1);
}

/*
void TestGetFunction()
{
//	unsigned char (*functionPointer)();
//	functionPointer=(unsigned char (*)())GetFunction();


	unsigned const rom int *MenuItemToDraw;
	unsigned const rom int (*functionPtr)();
	MenuItemToDraw=Menu+Shift;
	functionPtr=(unsigned const rom int(*)())GetFunction(*SelectedMenuItem);
	functionPtr();
}
*/
//----------------------------------------------------------------------------------------------
//Function: EnterMenu
//Description: If menuitem is linked to a nother menu, then this function is used to enter.
//Return value: not used!
//Input value: None.
//Effect: Menu pointer is changed according to the selected menuitem.
//----------------------------------------------------------------------------------------------
unsigned char EnterMenu()
{
	unsigned const rom int *MenuToEnter=GetMenu(*SelectedMenuItem);
	Shift=0;
	MenuItems_Enter(MenuToEnter);
	SelectedMenuItem=MenuToEnter;
}	
/* Not needed any more, EnterMenu() function is used insted (same applies for all submenus)
unsigned char EnterGamesMenu_V2()
{
	Shift=0;
	TestBufferMenuLine=0;
	MenuItems_Enter(GamesMenu_Items);
	SelectedMenuItem=GamesMenu_Items;
	//Menu=&GamesMenu_Items[0];
}
*/

//----------------------------------------------------------------------------------------------
//Function: 
//Description: 
//Return value: 
//Input value: 
//Effects: 
//----------------------------------------------------------------------------------------------
unsigned char ShowContrastMenu_V2(unsigned char Keyboard)
{
	ShowMenuSystem=HandleContrastMenu;
}
//----------------------------------------------------------------------------------------------
//Function: 
//Description: 
//Return value: 
//Input value: 
//Effects: 
//----------------------------------------------------------------------------------------------
unsigned char EnterConfigMenu_V2(unsigned char Keyboard)
{
}
//----------------------------------------------------------------------------------------------
//Function: 
//Description: 
//Return value: 
//Input value: 
//Effects: 
//----------------------------------------------------------------------------------------------
unsigned char ShowBrightnessMenu_V2()
{
	ShowMenuSystem=HandleBrightnessMenu;
}

void ResetMCU_V2()
{
	_asm reset _endasm;
}
/*
unsigned char EnterAirHornMenu()
{
	Shift=0;
	MenuItems_Enter(AirHornMenu_Items);
	SelectedMenuItem=AirHornMenu_Items;
}
*/
unsigned char ShowTimeMenu()
{
	ShowMenuSystem=HandleTimeMenu;
	ReadTime();
	MenuGlobalTemp=0;
}
unsigned char ShowDateMenu()
{
	ShowMenuSystem=HandleTimeMenu;
	ReadTime();
	MenuGlobalTemp=0;
}

//-----------------------------------------
//Global variables for list control object:
//-----------------------------------------
unsigned char listItemAddress;
unsigned char listSelectedItem;
unsigned char listActiveItem;
unsigned char listMaxItems;
//-----------------------------------------
#define _MELODYHORN_ACTIVE_ITEM 9
#define _MELODYHORN_EEPROMSTART 8
unsigned char SelectMelodies()
{
	listMaxItems=int_EEPROM_getc(_MELODYHORN_EEPROMSTART);
	listItemAddress=_MELODYHORN_EEPROMSTART;
	//listActiveItem=int_EEPROM_getc(_MELODYHORN_ACTIVE_ITEM);
	listSelectedItem=0;
	Shift=0;	
	ShowMenuSystem=HandleMelodyMenu;
//now change the xxx function pointer to yyy

//------[test]
/*
	char i;
	PutListFromEEPROM(8);
	for(i=0; i<30;i++) Delay1KTCYx(255);
*/
}
unsigned char ShowMelodySpeedMenu()
{
}

void InitMainMenu()
{
	//Load System variables:
	Contrast=120;	//Should be loaded from the internal eeprom!
	Brightness=0;	//Should be loaded from the internal eeprom!

	ShowMenuSystem=HandleMenu_V2;
	glcdSetFont(_TIMESNEWROMAN_SIZE8);
	Menu=&MainMenu_Items[0];
	Shift=0;					//Shift indicates the shift of the first menuitem from the top
}
void DrawMenu_V2()
{		 
	unsigned const rom int *MenuItemToDraw;
	unsigned char DrawnLines=1;
	MenuItemToDraw=Menu+Shift;
//	ClearTestBuffer();
	glcdClearScreen(0);
	glcdSetFont(_TIMESNEWROMAN_SIZE8);
	while(*MenuItemToDraw!=_END_OF_MENU)
	{
		glcdPutStringFine(1,(DrawnLines-1)*10+1,GetMenuString(*MenuItemToDraw));
		//DrawMenuItem(GetMenuString(*MenuItemToDraw));
		if(*MenuItemToDraw==*SelectedMenuItem)
			glcdHighlightLine(((DrawnLines-1)*10));//HighlightCurrentLine();
		if(DrawnLines==_MAX_ITEMS_TO_DISPLAY) break;
		DrawnLines++;
		MenuItemToDraw++;
	}
	if(SelectedMenuItem!=Menu) glcdPutImage(Symbol_MenuArrowUp,92,1);
	if(*(SelectedMenuItem+1)!=_END_OF_MENU)  glcdPutImage(Symbol_MenuArrowDown,92,23);
	glcdLine(88,0,88,32);
	glcdLine(89,0,89,32);
	glcdRefreshDisplay180(0);
}

void HighlightCurrentLine()
{
}


void DrawMenuItemDebug(unsigned const rom char *menustring)
{
	unsigned char cnt=TestBufferMenuLine;
	while(*menustring)TestMenuBuffer[cnt++]=*menustring++;
	TestBufferMenuLine+=12;
}

void DrawMenuItem(unsigned const rom char *menustring)
{
	//unsigned char cnt=TestBufferMenuLine;
	//while(*menustring)TestMenuBuffer[cnt++]=*menustring++;
	//TestBufferMenuLine+=12;

}

void ClearTestBuffer()
{
	unsigned char cnt;
	for(cnt=0;cnt<40;cnt++) TestMenuBuffer[cnt]=0x00;
}

void PlayPizzaWorm()	//should be an external fucntion, from worm.c! - or maybe this solution should do it:
{
	ShowMenuSystem=StartGameWorm;
}

void MenuItems_Enter(unsigned const rom int *menucontainer)
{
	MenuHistory[Depth++]=(unsigned int)Menu;
	Menu=menucontainer;
}


void MenuItems_Back()
{
	TestBufferMenuLine=0;
	//first, we have to find the menuitem which lead to the selected menu.
	SelectedMenuItem=FindMenuItemOfContainer(Menu,(unsigned const rom int*)MenuHistory[Depth-1]);
	Menu=(unsigned const rom int*)MenuHistory[--Depth];	
	if((SelectedMenuItem-Menu)>2)
		Shift=SelectedMenuItem-Menu-2;
	else Shift=0;
}
void SelectNext()
{
	if(*(SelectedMenuItem+1)!=_END_OF_MENU) *SelectedMenuItem++;
	if(((SelectedMenuItem-Menu)-Shift)>=_MAX_ITEMS_TO_DISPLAY) Shift++;
}

void SelectPrevious()
{
	if(*SelectedMenuItem!=*Menu) *SelectedMenuItem--; 
	//if the selected MenuItem equals to the first item in the current menu system, we shouldn't decrement the selectedMenuItems
	if((SelectedMenuItem-Menu)<Shift) Shift--;
}
unsigned const rom int *FindMenuItemOfContainer(unsigned const rom int *ContainerToFind,unsigned const rom int *ContainerToSearchIn)
{
	while(*((unsigned const rom int*)(*ContainerToSearchIn+2))!=(unsigned int)ContainerToFind) //+2 because of the int type.. The index of the pointer is +1
	{
		if(*ContainerToSearchIn==_END_OF_MENU) return 0;
		ContainerToSearchIn++;
	}
	return ContainerToSearchIn;
}

void TestIt()
{
	SelectedMenuItem=FindMenuItemOfContainer(Menu,(unsigned const rom int*)MenuHistory[Depth-1]);
}
void HandleMenu_V2(unsigned char Keyboard)
{
	unsigned char Refresh=1;
	unsigned const rom int (*KeyFunction)();
	switch(Keyboard)
	{
		case _BTN_MENU_UP:
		case _KEY_INC:
			SelectNext();
			Refresh=1;
			break;
		case _BTN_MENU_DOWN:
		case _KEY_DEC:
			SelectPrevious();
			Refresh=1;
			break;
		case _KEY_ENTER:
			KeyFunction=(unsigned const rom int(*)())GetFunction(*SelectedMenuItem);
			KeyFunction();
			Refresh=1;
			break;
		case _BTN_ESC:
			break;
		default:
			break;
	}
	if(Refresh)
		DrawMenu_V2();
}

void HandleBrightnessMenu(unsigned char Keyboard)
{
	glcdClearScreen(0);
	switch(Keyboard)
	{
		case _BTN_ESC:
			Keyboard=0;
			ShowMenuSystem=HandleMenu_V2;
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
}

void ProgressBar(unsigned char percentage, unsigned const rom char *label)
{
	glcdClearScreen(0);
	glcdPutStringFine(3,2,label);
	glcdDrawBarFixedWidth(4,19,percentage);
	glcdRefreshDisplay180(0);
}

void HandleContrastMenu(unsigned char Keyboard)
{
	glcdClearScreen(0);
	switch(Keyboard)
	{
		case _BTN_ESC:
			Keyboard=0;
			ShowMenuSystem=HandleMenu_V2;
			return;
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
	glcdPutValueFine(Contrast,80,2,0);
	glcdDrawBarFixedWidth(4,19,(Contrast-100)*3);
	glcdRefreshDisplay180(0);

	Keyboard=0;
}


//----------------------------
//----------------------------

void ShowRadioButtonList(unsigned char dataStartAddress,unsigned char activeItemID,unsigned char highLightedItemInList,unsigned char (*GetItem)(unsigned char*,unsigned char*))
{
	unsigned char address=dataStartAddress;
	unsigned char menuString[12];
	unsigned char drawnLines=0;
	glcdClearScreen(0);
	glcdSetFont(_TIMESNEWROMAN_SIZE8);
	do
	{
		if(!GetItem(&address,menuString)) break;
		glcdPutStringFineDynamic(1,(drawnLines)*10+1,menuString);
		if((drawnLines+Shift)==highLightedItemInList)
			glcdHighlightLine(((drawnLines)*10));//HighlightCurrentLine();
		if((drawnLines+Shift)==activeItemID) glcdPutImage(Symbol_CheckBoxChecked,90,(drawnLines)*10+1);
		else glcdPutImage(Symbol_CheckBoxUnChecked,90,(drawnLines)*10+1);
		drawnLines++;
	}while(drawnLines<3);
	glcdRefreshDisplay180(0);
}
unsigned char GetItemFromEEPROM(unsigned char *address,unsigned char *buffer)
{
	do
	{
		*buffer=int_EEPROM_getc((*address)++);
		if(*buffer==0xFF) return 0;
	}while(*buffer++);
	return 1;
}

void listFindItemAddress(unsigned char itemNum, unsigned char *addresToSearchFrom)
{
	unsigned char eepromItemNum=0;
	while(eepromItemNum++<itemNum)
		while(int_EEPROM_getc((*addresToSearchFrom)++));
}
//----------------------------
//----------------------------
unsigned char EnterAirHornMenu()
{

	unsigned const rom int *MenuToEnter=GetMenu(*SelectedMenuItem);
	unsigned int percentage;
	SendIBUSDataGeneric(_HORNCTRL_ID,_HORN_GET_LIST,0x00);
	if(IBUSWaitForResponse(_HORN_GET_LIST)==2) 
	{
		ShowCommError();
	//	return;
	}
	listActiveItem=GetParam(0);
	Shift=0;
	MenuItems_Enter(MenuToEnter);
	SelectedMenuItem=MenuToEnter;
}

void HandleMelodyMenu(unsigned char Keyboard)
{
	unsigned char Refresh=1;
	switch(Keyboard)
	{
		case _BTN_MENU_UP:
		case _KEY_INC:
			if(listSelectedItem<(listMaxItems-1)) listSelectedItem++;
			if((listSelectedItem-Shift)>=_MAX_ITEMS_TO_DISPLAY) Shift++;
			Refresh=1;
			break;
		case _BTN_MENU_DOWN:
		case _KEY_DEC:
			if(listSelectedItem>0) listSelectedItem--;
			if(listSelectedItem<Shift) Shift--;
			Refresh=1;
			break;
		case _KEY_ENTER:
			listActiveItem=listSelectedItem;
			Refresh=1;
			break;
		case _BTN_ESC:
			//if(int_EEPROM_getc(_MELODYHORN_ACTIVE_ITEM)!=listActiveItem)
			{
				//Write_EEPROM(_MELODYHORN_ACTIVE_ITEM,listActiveItem);
				SendIBUSDataGeneric(_HORNCTRL_ID,_HORN_SET_ACTIVE_ITEM,listActiveItem);
				if(IBUSWaitForResponse(_HORN_SET_ACTIVE_ITEM)==2) 
				{
					ShowCommError();
					return;
				}
			}
			Shift=0;
			ShowMenuSystem=HandleMenu_V2;
			break;
		default:
			break;
	}
	if(Refresh)
	{
		listItemAddress=8+2;
		listFindItemAddress(Shift,&listItemAddress);
		ShowRadioButtonList(listItemAddress,listActiveItem,listSelectedItem,GetItemFromEEPROM);
	}

}

void PutListFromEEPROM(unsigned char E2PAddress)
{
	unsigned char text[12];
	unsigned char *textpointer;
	unsigned char DrawnLines=1;
	unsigned char NumberOfItems=int_EEPROM_getc(E2PAddress++);
	unsigned char SelectedItem=int_EEPROM_getc(E2PAddress++);
	unsigned char HighLightedItemInList=1;
	ClearTestBuffer();
	glcdClearScreen(0);
	do
	{
		textpointer=&text[0];
		do
		{
			*textpointer=int_EEPROM_getc(E2PAddress++);
			if(*textpointer==0xFF)	break;
		}while(*textpointer++);
		if(*textpointer==0xFF)	break;
		glcdPutStringFineDynamic(1,(DrawnLines-1)*10+1,text);
		if(DrawnLines==HighLightedItemInList)
			glcdHighlightLine(((DrawnLines-1)*10));//HighlightCurrentLine();
		if(DrawnLines==SelectedItem) glcdPutImage(Symbol_CheckBoxChecked,90,(DrawnLines-1)*10+1);
		else glcdPutImage(Symbol_CheckBoxUnChecked,90,(DrawnLines-1)*10+1);
		if(DrawnLines>2) break;
		DrawnLines++;
	}while(NumberOfItems--);
	glcdRefreshDisplay180(0);
}
/*
void GetTuneNamesFromEEPROM()
{
	unsigned char text[20];
	unsigned char E2PAddress=10;
	unsigned char *textpointer=&text[0];
	do
	{
		do
		{
			*textpointer=int_EEPROM_getc(E2PAddress++);
			if(*textpointer==0xFF)	break;
		}while(*textpointer++);
	}while((*textpointer++)!=0xFF);
}
void ReadTestDataFromEEPROM(unsigned char startAddress, unsigned char *text)
{
	do
	{
		*text=int_EEPROM_getc(startAddress++);
		if(*text==0xFF) break;
	}while(*text++);
}
*/

void ShowCommError()
{
	unsigned char i;
	glcdClearScreen(0);
	glcdLine(5,3,95,3);
	glcdLine(96,4,96,26);
	glcdLine(95,27,5,27);
	glcdLine(4,26,4,4);
	glcdPutStringFine(15,6,"Communication");
	glcdPutStringFine(40,17,"Error");
	glcdRefreshDisplay180(0);
	for(i=0;i<30;i++) Delay1KTCYx(255);
}

void ShowAirHornStarter()
{
	unsigned char pressAndHold=0;
	glcdClearScreen(0);
	//glcdPutStringFine(3,2,"Contrast:");
	while(1)
	{
		if(PORTAbits.RA3)
		{
			Delay1KTCYx(255);
			Delay1KTCYx(255);
			Delay1KTCYx(255);
			Delay1KTCYx(255);
			if(PORTAbits.RA3) break;
		}
		glcdSetFont(_TIMESNEWROMAN_SIZE8);
		glcdPutStringFine(3,2,"Hold button");
		glcdDrawBarFixedWidth(4,19,pressAndHold);
		glcdRefreshDisplay180(0);
		Delay1KTCYx(45);
		pressAndHold+=5;
		if(pressAndHold>90)
		{
			PlayTune();
			while(!PORTAbits.RA3);
			break;
		}
	}
}

unsigned char PlayTune()
{
	SendIBUSDataGeneric(_HORNCTRL_ID,_HORN_PLAYTUNE,0x00);
	if(IBUSWaitForResponse(_HORN_GET_LIST)==2) 
	{
		ShowCommError();
		return;
	}
}

unsigned char EEPROMAddress;
unsigned char RefreshList()
{
	unsigned char cnt,numOfMelodies;
	unsigned int percentage;
	SendIBUSDataGeneric(_HORNCTRL_ID,_HORN_GET_LIST,0x00);
	if(IBUSWaitForResponse(_HORN_GET_LIST)==2) 
	{
		ShowCommError();
		return;
	}
	listActiveItem=GetParam(0);
	if(int_EEPROM_getc(_MELODYHORN_ACTIVE_ITEM)!=listActiveItem)
		Write_EEPROM(_MELODYHORN_ACTIVE_ITEM,listActiveItem);
	numOfMelodies=GetParam(1);//3;
	Write_EEPROM(_MELODYHORN_EEPROMSTART,numOfMelodies);
	EEPROMAddress=10;	
	for(cnt=0;cnt<numOfMelodies;cnt++)
	{
		percentage=cnt;
		percentage*=100;
		percentage/=numOfMelodies;
		ProgressBar(percentage,"Downloading;;");
		SendIBUSDataGeneric(_HORNCTRL_ID,_HORN_GET_ITEMSTRING,cnt);
		if(IBUSWaitForResponse(_HORN_GET_ITEMSTRING)==2)
		{
			ShowCommError();
			return;
		}
	}	
	Write_EEPROM(EEPROMAddress++,0xFF);
}

void SaveItemToEEPROM(unsigned char *data)
{
	while(*data++) Write_EEPROM(EEPROMAddress++,*data);
//	Write_EEPROM(EEPROMAddress++,0x00);
}

void SaveString(unsigned char *data)
{
	unsigned char cnt=0;
	unsigned char stringData[15];
	unsigned char stringID=*data++;
	
	while(*data) 
	{
		stringData[cnt++]=*data++;
	}
	stringData[cnt]=0x00;

	glcdClearScreen(0);
	glcdPutStringFineDynamic(1,24,stringData);
	glcdRefreshDisplay180(0);
}

void SaveListParams(unsigned char *data)
{
//	if(int_EEPROM_getc(_MELODYHORN_ACTIVE_ITEM)!=*data)
//		Write_EEPROM(_MELODYHORN_ACTIVE_ITEM,*data);
}

void TestItMelody()
{
	SelectMelodies();
	HandleMelodyMenu(0);
	listFindItemAddress(2,&listItemAddress);
}

unsigned char BlinkCounter;
#define _BLINKPERIOD_OFF 10
#define _BLINKPERIOD  20
void HandleTimeMenu(unsigned char Keyboard)
{
	unsigned char temp;
	glcdClearScreen(0);
	switch(Keyboard)
	{
	//	case _BTN_ESC:
	//		Keyboard=0;
	//		ShowMenuSystem=HandleMenu_V2;
		case _KEY_LEFT:		
			if(MenuGlobalTemp>0) MenuGlobalTemp--;
			else MenuGlobalTemp=3;
			break;
		case _KEY_RIGHT:
			if(MenuGlobalTemp<3) MenuGlobalTemp++;
			else MenuGlobalTemp=0;
			break;
		//case _BTN_MENU_DOWN:
		case _KEY_INC:
			switch(MenuGlobalTemp)
			{
				case 0:
					if((hours&0xF0)>=0x10) hours-=0x10;
					break;
				case 1:
					if((hours&0x0F)>0) hours--;
					break;
				case 2:
					if((minutes&0xF0)>=0x10) minutes-=0x10;
					break;
				case 3:
					if((minutes&0x0F)>0) minutes--;
					break;
			}
			break;
		//case _BTN_MENU_UP:
		case _KEY_DEC:
			switch(MenuGlobalTemp)
			{
				case 0:
					if((hours)<0x14) hours+=0x10;
					break;
				case 1:
					if(hours<0x23) hours++;
					break;
				case 2:
					if(minutes<0x50) minutes+=0x10;
					break;
				case 3:
					if(minutes<0x59) minutes++;
					break;
			}

			break;
		case _KEY_ENTER:
			SetTime();
			ShowMenuSystem=HandleMenu_V2;
			break;
		default: break;
	}
	glcdSetFont(_TIMESNEWROMAN_SIZE8);
	glcdPutStringFine(1,1,"Set Time");
	glcdLine(0,11,49,11);
	glcdLine(0,12,49,12);
	glcdSetFont(_ARIAL_SIZE12_BOLD);
	if((MenuGlobalTemp!=0) || BlinkCounter<_BLINKPERIOD_OFF)
		glcdPutValueFine((hours&0xF0)>>4,34,16,0);
	if((MenuGlobalTemp!=1) || BlinkCounter<_BLINKPERIOD_OFF)
		glcdPutValueFine((hours&0x0F),43,16,0);
	glcdPutCharFine(54,16,';');
	if((MenuGlobalTemp!=2) || BlinkCounter<_BLINKPERIOD_OFF)
		glcdPutValueFine((minutes&0xF0)>>4,59,16,0);
	if((MenuGlobalTemp!=3) || BlinkCounter<_BLINKPERIOD_OFF)
		glcdPutValueFine((minutes&0x0F),68,16,0);
	BlinkCounter++;
	if(BlinkCounter>_BLINKPERIOD) BlinkCounter=0;
	glcdRefreshDisplay180(0);
	Keyboard=0;
}