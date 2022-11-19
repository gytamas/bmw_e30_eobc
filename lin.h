//lin.h

void HandleIBUS_ISR(void);
void InitIBUSStack(void);
void InitIBUS();
void HandleIBUSMessage();
void ResetIBUSStack();
void HandleIBUSStack();
void Debug_FillRCBuffer(unsigned char *);
void blink(unsigned char);
void sendByte(unsigned char );
void SendIBUS(unsigned rom char *);
void SendIBUSData(unsigned char);
void SendIBUSDataGeneric(unsigned char,unsigned char,unsigned char);
unsigned char GetParam(unsigned char );

void SendIBUSFunction(unsigned char,unsigned char);
unsigned char IsCommReadyToSend();
void SaveListParams(unsigned char *);

unsigned char IBUSWaitForResponse(unsigned char);
extern unsigned char JOGValue;

//IBUS states:
#define _GET_SOURCE_ID	0x00
#define _GET_LENGTH		0x01
#define _GET_DEST_ID	0x02
#define _GET_DATA		0x03
#define _GET_CHKSUM		0x04


#define _RCBUFFER_SIZE 30
#define _IBUS_MAX_LENGTH 20


//IBUS ID's
#define _IJOG_ID 0x54
#define _COMP_ID  0x54
#define _SELF_ID  0x10
#define _HORNCTRL_ID 0x44

//IBUS Messages:
#define _SET_BRIGHTNESS 0x01
#define _SET_BRGHT_FADE 0x02
#define _READ_JOGVALUE  0x03
#define _SET_JOGMODE	0x04

#define _JOG_ANSWER     0x03
#define _JOGVALUE_RESET 0x7F

#define _GET_ID 0x0A
#define _HORN_GET_LIST 0x01
#define _HORN_GET_ITEMSTRING 0x03
#define _HORN_SET_ACTIVE_ITEM 0x04
#define _HORN_PLAYTUNE 0x15

#define _MESSAGE_SENT 0x00
#define _RESPONSE_ARRIVED 0x01

