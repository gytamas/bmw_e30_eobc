//main.h

//=============================================================
//================Basic device info:===========================
//=============================================================
#define __NAME "BMW E34 Automatic Transmission Display Unit"
#define __HW_REV "1.00"
#define __SW_REV "0.2"
#define __REVDATE "11/03/06"
//=============================================================
#define _DEFAULT_CONTRAST_DAC 225
#define StatusLED PORTAbits.RA2

//Compiler options:
#define	_CYCLIC_DISPLAY_REFRESH

// Addresses and byte configs:
#define _DEFAULT_SLAVE_ADDR 0xA0
#define _R5A_DEV_ADDRES 0x70

#define _ADC_CHANNEL_TEMP   0x04 //B'0000 0100
#define _ADC_CHANNEL_SUPPLY 0x00


#define _FREQ_CALIB	33292 //36621 //78125

unsigned char getTemp(void);

extern struct
{
	unsigned DisplayState 		:8;
	unsigned CurrentLevel		:8;
	unsigned HighlightedItem	:8;
	unsigned Line				:8;
} MenuControl;

//LIN pinout:

#define LIN_CS PORTCbits.RC0
#define LIN_ERROR PORTCbits.RC1
#define KEYBOARD_IT PORTBbits.RB5

//General IOs
#define AIRHORNBUTTON PORTAbits.RA3

//IBUS ID's
#define _IJOG_ID 0x54
#define _COMP_ID  0x54
#define _OBC_ID	0x10

//KEY IDS
#define _KEY_LEFT 	0x0D
#define _KEY_RIGHT	0x07
#define _KEY_UP		0x0E
#define _KEY_DOWN	0x0B
#define _KEY_INC	0x10
#define _KEY_DEC	0x80
#define _KEY_ENTER	0x55


#define _MASTER_SLAVE_MODE 0x00
#define _CONTINOUS_SEND	   0x01
