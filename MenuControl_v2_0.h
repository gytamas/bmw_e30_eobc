//Header file for MenuControl_V2_0.c




unsigned char ShowContrastMenu_V2(unsigned char);
unsigned const rom char *GetMenuString();
unsigned const rom int *GetFunction(unsigned const rom int *);
//unsigned char EnterGamesMenu_V2();
unsigned char ShowContrastMenu_V2(unsigned char);
unsigned char ShowBrightnessMenu_V2();
unsigned char ShowDateTimeMenu();
unsigned char ShowTimeMenu();
unsigned char ShowDateMenu();
void ResetMCU_V2();
//unsigned char EnterConfigMenu_V2(unsigned char);
void HighlightCurrentLine();
void DrawMenu_V2();
void HandleMenu_V2(unsigned char);
void DrawMenuItem(unsigned const rom char *);
void ClearTestBuffer();
void PlayPizzaWorm();
void SelectNext();
void SelectPrevious();
unsigned const rom char *GetMenuString(unsigned const rom int *);
void MenuItems_Back();
void MenuItems_Enter(unsigned const int rom *);
void TestIt();
void HandleContrastMenu(unsigned char);
void HandleBrightnessMenu(unsigned char);
void HandleTimeMenu(unsigned char);
void HandleDateMenu(unsigned char);
//unsigned char EnterAirHornMenu();
unsigned char SelectMelodies();
unsigned char ShowMelodySpeedMenu();
unsigned const rom int *FindMenuItemOfContainer(unsigned const rom int *,unsigned const rom int*);
unsigned const rom int *GetMenu(unsigned const rom int *);
unsigned char EnterMenu();
unsigned char RefreshList();
void ProgressBar(unsigned char, unsigned const rom char *);
//void GetTuneNamesFromEEPROM();
//void ReadTestDataFromEEPROM(unsigned char, unsigned char *);

void PutListFromEEPROM(unsigned char);

//MenuParameters:
extern unsigned char Contrast,Brightness; //shouldn't be extern in the future. original menu system should be removed!
void SaveString(unsigned char *);
void SaveListParams(unsigned char*);
void SaveItemToEEPROM(unsigned char*);
void TestItMelody();

void ShowRadioButtonList(unsigned char,unsigned char,unsigned char, unsigned char (*)(unsigned char*,unsigned char*));
unsigned char GetItemFromEEPROM(unsigned char*,unsigned char *);
void listFindItemAddress(unsigned char, unsigned char *);
void HandleMelodyMenu(unsigned char);
unsigned char EnterAirHornMenu();
void ShowCommError();
unsigned char PlayTune();
void ShowAirHornStarter();
