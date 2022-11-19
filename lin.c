//LIN Comstack
#include "usart.h"
#include "main.h"
#include "lin.h"
#include <p18f25k22.h>

unsigned static char RCBuffer[_RCBUFFER_SIZE];
unsigned static char IBUSDataBuffer[_IBUS_MAX_LENGTH];
unsigned static char *RCBufferPointer;
unsigned static char *IBUSDataBufferPointer;
unsigned static char *StackPointer;
unsigned static char MessageLength,ChkSum,StackState,IBUSSrcID,IBUSDestID;
void blink(unsigned char);
extern unsigned char JogValue;
extern unsigned char JoystickValue;
extern void SaveString(unsigned char*);
extern void SaveListParams(unsigned char*);
extern void SaveItemToEEPROM(unsigned char*);

unsigned char CommState=_RESPONSE_ARRIVED;
void InitIBUS()
{
	LIN_CS=0;
	Delay1KTCYx(10);
	LIN_CS=1;
}

void InitIBUSStack()
{
	unsigned char cnt;
	RCBufferPointer=&RCBuffer[0];
	StackPointer=&RCBuffer[0];
	StackState=_GET_SOURCE_ID;
//	for(cnt=0;cnt<_IBUS_MAX_LENGTH;cnt++) IBUSDataBuffer[cnt]=0x00;
//	for(cnt=0;cnt<_RCBUFFER_SIZE;cnt++) RCBuffer[cnt]=0x00;
}

void HandleIBUS_ISR(void)
{
	//PORTD|=0x01;
	while(DataRdy1USART())
	{
		*RCBufferPointer=getc1USART();
		*RCBufferPointer++;
		if(RCBufferPointer>&RCBuffer[_RCBUFFER_SIZE-1])
			RCBufferPointer=&RCBuffer[0];
	}

	PIR1bits.RCIF=0;
}

unsigned char counter;
void HandleIBUSStack()
{
	//if(!LIN_ERROR)
	//	InitIBUS();
	while(RCBufferPointer!=StackPointer)
	{
		switch(StackState)
		{
			case _GET_SOURCE_ID:

				IBUSSrcID=*StackPointer;
				StackState=_GET_LENGTH;
				ChkSum=0x00;
				ChkSum^=IBUSSrcID;
				break;
			case _GET_LENGTH:

				MessageLength=*StackPointer;
				counter=MessageLength-1;
				//blink(counter);
				ChkSum^=*StackPointer;
				if(MessageLength>_IBUS_MAX_LENGTH)
				{
					ResetIBUSStack();
				}
				StackState=_GET_DEST_ID;
				break;
			case _GET_DEST_ID:

				IBUSDestID=*StackPointer;
				ChkSum^=*StackPointer;
				StackState=_GET_DATA;
				IBUSDataBufferPointer=&IBUSDataBuffer[0];
				break;
			case _GET_DATA:

					*IBUSDataBufferPointer++=*StackPointer;
					ChkSum^=*StackPointer;
					counter--;
					if(counter==1)
						StackState=_GET_CHKSUM;
				break;
			case _GET_CHKSUM:
				if(ChkSum!=*StackPointer)
					{
						CommState=_RESPONSE_ARRIVED;
				//		PORTD|=0x02;	
						ResetIBUSStack();
						return;
					}
				else
				{	
				 //	PORTD&=0xFD;
					HandleIBUSMessage();
					StackState=_GET_SOURCE_ID;
					CommState=_RESPONSE_ARRIVED;
				}
				break;
		}
		StackPointer++;
		if(StackPointer>&RCBuffer[_RCBUFFER_SIZE-1])
			StackPointer=&RCBuffer[0];
	}
}

void ResetIBUSStack()
{
	//blink(3);
	Delay1KTCYx(255);
	InitIBUSStack();
}



void Debug_FillRCBuffer(unsigned char *input)
{
	while(*input)
	{
		*RCBufferPointer++=*input++;
	}
}


void HandleIBUSMessage()
{
	//PORTD&=0xFC;
	if((IBUSSrcID==_IJOG_ID) && (IBUSDestID==_SELF_ID))
	{
		switch(IBUSDataBuffer[0])
		{
			case _JOG_ANSWER:
				JogValue=IBUSDataBuffer[1];
				JoystickValue=IBUSDataBuffer[2];
				break;
		}
	}
	if((IBUSSrcID==0x44) && (IBUSDestID==_SELF_ID))
	{		
		switch(IBUSDataBuffer[0])
		{	
			case _GET_ID:
				SaveString(&IBUSDataBuffer[1]);
				break;
			case _HORN_GET_LIST:
				SaveListParams(&IBUSDataBuffer[1]);
				break;
			case _HORN_GET_ITEMSTRING:
				SaveItemToEEPROM(&IBUSDataBuffer[1]);
				break;
		}
	}	
}

unsigned char GetParam(unsigned char paramNum)
{
	return IBUSDataBuffer[paramNum];
}
/*
void HandleIBUSMessage()
{
	if((IBUSSrcID==_MFL_ID) & (IBUSDestID==_RADIO_ID))
	{
		switch(IBUSDataBuffer[0])
		{
			case _VOLUME_BTN:
				if(IBUSDataBuffer[1]==_VOLUME_INCREASE)
					IncreaseVolume(1);
				if(IBUSDataBuffer[1]==_VOLUME_DECREASE)
					DecreaseVolume(1);
				break;
			case _ARROW_BTN:
				if(IBUSDataBuffer[1]==_CHANNEL_INCREASE)
					IncreaseChannel();
				if(IBUSDataBuffer[1]==_CHANNEL_DECREASE)
					DecreaseChannel();
				break;
		}
	}
	else if(IBUSDestID==_AC_CONTROL_ID)
	{
		if((IBUSDataBuffer[0]==0x3A)&(IBUSDataBuffer[1]==0x01))
		{
			ChangeMode();
		}
	}
	else return;
}

*/
void SendIBUS(unsigned rom char *message)
{
	while(*message)
	{
		sendByte(*message++);
	}
}

void sendByte(unsigned char data)
{
	putc1USART(data);
	while(Busy1USART());
}

void SendIBUSData(unsigned char data)
{
	CommState=_MESSAGE_SENT;
	Delay1KTCYx(255);
	RCSTAbits.CREN=0;
	sendByte(_SELF_ID);
	sendByte(0x04);
	sendByte(_IJOG_ID);
	sendByte(_READ_JOGVALUE);
	sendByte(data);
	sendByte((_SELF_ID^4^_IJOG_ID^_READ_JOGVALUE^data));
	RCSTAbits.CREN=1;
}

void SendIBUSDataGeneric(unsigned char address,unsigned char function, unsigned char param)
{
	CommState=_MESSAGE_SENT;
	Delay1KTCYx(255);
	RCSTAbits.CREN=0;
	sendByte(_SELF_ID);
	sendByte(0x04);
	sendByte(address);
	sendByte(function);
	sendByte(param);
	sendByte((_SELF_ID^4^address^function^param));
	RCSTAbits.CREN=1;
}

void SendIBUSFunction(unsigned char function,unsigned char data)
{
	CommState=_MESSAGE_SENT;
	Delay1KTCYx(255);
	RCSTAbits.CREN=0;
	sendByte(_SELF_ID);
	sendByte(0x04);
	sendByte(_IJOG_ID);
	sendByte(function);
	sendByte(data);
	sendByte((_SELF_ID^4^_IJOG_ID^function^data));
	RCSTAbits.CREN=1;
}
void blink(unsigned char blinks)
{
	while(blinks--)
	{
		PORTA|=0x10;
		Delay1KTCYx(255);
		Delay1KTCYx(255);
		PORTA&=0xEF;
		Delay1KTCYx(255);		
		Delay1KTCYx(255);

	}
}

#define _TIMEOUTRELOAD 65000
unsigned char IBUSWaitForResponse(unsigned char MsgID)
{
	unsigned int timeOut=_TIMEOUTRELOAD;
	//unsigned int timOutHigh=10;
	while(CommState!=_RESPONSE_ARRIVED) 
	{
		if(!timeOut--) return 2;
		HandleIBUSStack(); // There should be a timout implemented!
	}
	//PORTD&=0xFE;
	if(IBUSDataBuffer[0]!=MsgID) return 0;
	else return 1;
}

/*
unsigned char IBUSWaitForResponse(unsigned char MsgID)
{
	HandleIBUSStack(); // There should be a timout implemented!
	if(CommState==_RESPONSE_ARRIVED)
	{
		PORTD&=0xFE;
		if(IBUSDataBuffer[0]!=MsgID) return 0;
		else return 1;
	}
	else return 0;

}
*/

