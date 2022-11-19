//header file for menucontrol.h

#define _NORMALSTATE	1
#define _GAME_WORM		0


void DrawMenu(void);
void HandleMenu(unsigned char);
void InitMenu(void);
void DrawMainMenu(unsigned char);
void ExitMenu(void);
unsigned char GetMenuState(void);

struct
{
	unsigned DisplayState 		:8;
	unsigned CurrentLevel		:8;
	unsigned HighlightedItem	:8;
	unsigned Line				:8;
	
} MenuControl;

unsigned char Contrast,Brightness;
