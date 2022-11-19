#define _USE_LIN

#include <p18f25k22.h>

//#include "bitmaps.h"
#include "adc.h"
#include "paint.h"
#include "main.h"
#include "pcf8548.h"
#include "primitives.h"
#include "worm.h"
#include "graphics.h"
#include "E30Icons.h"
#include "speed.h"
#include "lin.h"
#include "ds1820.h"
#include "mcp7940.h"

#include "MenuControl_V2_0.h"
#define OSC_SPEED8




//*************************************************************
//Debug option
//*************************************************************
//#define _DEBUG
//************************************************************* 
//Compiler options
//*************************************************************


#define _USE_VARIABLE_TEXT_SIZE
//*************************************************************
// Variables
//*************************************************************

#define _DEV_ADDRESS 0x78
#define _FRAMESIZE_180 404
#define _FULL_FRAMESIZE 505

#define _SCREENSIZE_X	101
#define _SCREENSIZE_Y	32

//#pragma romdata configs=0x300000
//	unsigned char rom CONFIG1L=0x00;
//	unsigned char rom CONFIG1H=0xFF;

//	unsigned char rom CONFIG2L=0x00;
//	unsigned char rom CONFIG2H=0x0F;

//	unsigned char rom CONFIG3L=0x00;
//	unsigned char rom CONFIG3H=0x01;
typedef const rom char rconst;
extern rconst WelcomeImage[];
extern rconst DemoStyle2[];
extern rconst pressureSenseDemo[];
extern rconst SmallBall[];
extern unsigned char Brightness;
extern rom const char BMWCheck[];
extern rom const char Style1_Demo[];
extern const rom char dither_01[];
extern void (*ShowMenuSystem)(unsigned char);
extern unsigned char hours,minutes,Years,Months,Days;
#pragma udata


#pragma code
//****************************************************************
//Compiler control	
//****************************************************************
//

//****************************************************************
//Function prototypes	
//****************************************************************

void InitHW(void);
void interrupt_highprio(void);
void highPrioISR(void);
void lowPrioISR(void);
//
void ShowAlive(unsigned char);
void glcdPutImage2(unsigned rom char *,unsigned char, unsigned char);
void DelaySomeTime();
void DrawTestMenu();
unsigned char HandleKeys(void);
void DrawConsumption(unsigned char);
void DrawConsumptionCurrent(unsigned char);
void PutFixedPointValue(unsigned char);
unsigned char ReadADCValue(unsigned char);

unsigned char GetPressure(unsigned char);
void ShowDemo1();
void ShowDemo2();
void ShowDemo3();
void ShowDemo4();
void ShowTurbo();
void ShowSpeed();
void ShowTemp();
void HandleTimerOverflow();
unsigned char HandleDemoControl(unsigned char);
void SetJogMode(unsigned char);
unsigned char TestHWI2C(unsigned char);	
void SetDutyCycle(unsigned char);

#pragma code


//*************************************************************
//IT vectors
//*************************************************************
//High prio interrupt


#pragma code InterruptVectorHigh=0x008


void interrupt_highprio(void)
{
	_asm goto highPrioISR _endasm
}


#pragma code InterruptVectorLow=0x018
void interuupt_lowprio(void)
{
	_asm goto lowPrioISR _endasm
}

#pragma code
#pragma interrupt highPrioISR
void highPrioISR(void)
{
	INTCONbits.GIE=0;
	if((PIR2bits.TMR3IF)&(PIE2bits.TMR3IE)) HandleTimerOverflow();
	//if((PIR1bits.RCIF)&(PIE1bits.RCIE)) HandleUARTISR();
	//if((PIR1bits.TMR1IF)&(PIE1bits.TMR1IE)) HandleTMR1ISR();
	if((PIR2bits.CCP2IF)&(PIE2bits.CCP2IE)) CaptureInterrupt();
	if((PIR1bits.RC1IF)&(PIE1bits.RC1IE)) HandleIBUS_ISR();
	if((INTCONbits.INT0IF)&(INTCONbits.INT0IE)) HandleRTC_ISR();
	INTCONbits.INT0IF=0;
	INTCONbits.GIE=1;
}

#pragma interrupt lowPrioISR
void lowPrioISR(void)
{
	INTCONbits.GIE=0;
	if((INTCONbits.INT0IF)&(INTCONbits.INT0IE)) HandleRTC_ISR();
	INTCONbits.INT0IF=0;
	INTCONbits.GIE=1;
}
//Main routine
//****************************************************************
unsigned const rom char CalibRationValues[16][2]={{0,0},{6,1},{12,2},{23,3},{33,4},{47,5},{60,6},{71,7},{80,8},{87,9},{100,10},{116,11},{130,12},{146,13},{161,14}};

unsigned char xRandom,gameState,Key;
unsigned char previousKeyInput=0;
unsigned char NumOfOverFlows;
unsigned char DemoID=2;
unsigned char loop=1;
unsigned char JogValue=0x7F,JoystickValue=0;
unsigned char JogReadMode=_MASTER_SLAVE_MODE;


void main(void)
{

	unsigned char speedX=1,speedY=1,posX=0,posY=0;
	unsigned char brghTemp,temp=0;

	unsigned char cnt,i;
//	unsigned char charray[7];

unsigned int test1=0;
//TEST-----------------------------------

//---------------------------------------
//

	InitHW();
	ShowAlive(5);
	for(cnt=0;cnt<36;cnt++)
	{
		SetDutyCycle(cnt);
		Delay1KTCYx(100);
	}
//SetDutyCycle(50);
	StatusLED=0;
	if(TestHWI2C(_DEFAULT_CONTRAST_DAC)==0) StatusLED=1;
	Delay1KTCYx(255);	
	if(TestHWI2C(_DEFAULT_CONTRAST_DAC)==0) StatusLED=1;
  	configuureMP7940(0);
	ReadTime();
	if((minutes==0)&&(hours==0))
	{
		WriteByteMCP7940(1,0x40);
		WriteByteMCP7940(2,0x11);
		WriteByteMCP7940(5,0x01);
		WriteByteMCP7940(6,0x14);
		WriteByteMCP7940(4,0x12);
	}
/*while(1)
{
	TestMCP7940(0);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);

}
*/
// LIN DEBUG:
//---------------
	InitIBUS();
	InitIBUSStack();

//-----------LIN enable
//	RCSTAbits.CREN=1;
//---------------------


//end of LIN DEBUG
//----------------
//glcdPutLogo1();
	StatusLED=0;
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	if(PCF8548_Init()) StatusLED=1;//PORTD|=0x80;
//	if(PCF8548_SendTestImage()) PORTD|=0x80;
//	glcdPutTestData();
	glcdClearInitial();
	glcdClearScreen(0);

//Online TEST:
//-------------
//	InitMainMenu();
//	HandleMenu_V2(HandleKeys());
//	while(1);
//	EnterGamesMenu_V2();

//_-----------------
//	glcdPutLogo(pressureSenseDemo);
	for(cnt=0;cnt<=14;cnt++)
	{
		glcdPutLogo(WelcomeImage);
		glcdDitherArea(0,0,101,24,cnt,dither_01); //this need to be fixed!!!!!!!!!!!! 24-->32
		glcdRefreshDisplay180(0);
		Delay1KTCYx(120);
	}
	DelaySomeTime();
	DelaySomeTime();
	DelaySomeTime();
	glcdClearScreen(0);
//	ShowDemo1();
//	while(1);

	
/*	for(temp=0;temp<5;temp++)
	{
		glcdPutLogo(BMWCheck);
		DelaySomeTime();
		glcdRefreshDisplay180(0);
		glcdClearScreen(0x00);
		DelaySomeTime();
		glcdRefreshDisplay180(0);
		
	}
*/
//	glcdPutLogo(Style1_Demo);
//	glcdRefreshDisplay180(0);
//	DelaySomeTime();
//	DelaySomeTime();
//	DelaySomeTime();
//	DelaySomeTime();
//	DelaySomeTime();
//	while(HandleKeys()!=_KEY_UP);
//	glcdClearScreen(0x00);	
	loop=1;
	while(loop)
	{
		switch(DemoID)
		{
		case 4:
			ShowTurbo();
			break;
		case 3:
			ShowSpeed();
			break;
		case 2:
			 ShowTemp();//ShowDemo5();
			//ShowTurbo();
			break;
		case 1:
			ShowDemo1();
			break;
		}
	//Delay1KTCYx(255);
	//Delay1KTCYx(255);
	//Delay1KTCYx(255);
	}
#ifdef _SHOW_DEMOS
	while(loop)
	{
	do
	{
		temp=HandleKeys();
	}
	while((temp==0)||(temp==0x0F));
	HandleDemoControl(temp);
	if(loop==0) break;
	switch(DemoID)
	{
		case 1:
			ShowDemo1();
			break;
		case 2:
			ShowSpeed();
			break;
		case 3:
			ShowDemo3();
			break;
		case 4:
			ShowDemo4();
			break;
		case 5:
			ShowDemo5();
			break;
	}
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	}

#endif
	InitMainMenu();
	while(1)
	{
		while(1)//MenuControl.DisplayState)
		{
			ShowMenuSystem(HandleKeys());
		}
	}	
	//DeadEnd
	while(1);

}

//=======================================================================================
//=============================== Function implementations===============================
//=======================================================================================


//---------------------------------------------------------------------------------------
//Function:
//Description:
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
void InitHW(void)
{
	PORTA=0x00;
	TRISA=0xCB;	//b'1101 1011
	PORTB=0x00;
	TRISB=0xFF;	//b'xxxx x11x
	PORTC=0x00;
	TRISC=0x8A;	//b'1000 1010

	ANSELA=0x03;
	ANSELC=0x00;
	ANSELB=0x00;
	SLRCON=0xFF;
	OSCCON=0x70;	//b'0011 

	ANSELB=0x00;
	ANSELC=0x00;

	OSCCON=0x70;	//b'0011 
	
	CCP1CON=0x0C;	//b'0000 1100
	T2CON=0x07;		//b'0000 0111
	PR2=50;			//--> Fpwm~=4khz
	CCPR1L=0;
//ADC
	OpenADC(ADC_FOSC_64 & ADC_LEFT_JUST & ADC_12_TAD,ADC_CH0 & ADC_INT_OFF, 13);
	ADCON1=0x00;	//Somethings wrong with OpenADC(), so ADCON1 need to be written //b'00

//UART
	//OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_SINGLE_RX & USART_BRGH_HIGH,51);
	TXSTA1=0x24;		//b'0010
	RCSTA1=0x80;
	SPBRG1=51;
	BAUDCON1=0x00;

	//IT
	INTCONbits.GIE=1;
    INTCONbits.PEIE=0; //no interrupts for now
	INTCONbits.INT0IE=1;
	INTCON2bits.INTEDG0=1;

	PIE1bits.RC1IE=1;
	IPR1bits.RC1IP=1; //High priority
	RCONbits.IPEN=1; //Enable interrupt priorites

	//I2C
	SSP2ADD=0x4F;	//Internal I2c clock frequency should be set to ~100kHz
	SSP2STAT=0x80;	//b'10000000		' slew rate control disabled (low speed)
	SSP2CON1=0x28;	//b'0010 1000 	sync. serial port enabled, MSSP configured as I2C Master 
	SSP2CON2=0x00;
}


void ShowAlive(unsigned char period)
{
	period*=2;
	while(period--)
	{
		Delay1KTCYx(255);		
		StatusLED=!StatusLED;
	}
}

void DelaySomeTime()
{
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);	
	Delay1KTCYx(255);
	Delay1KTCYx(255);
}



unsigned char HandleKeys(void)
{
//#define _USE_SIMPLE_KEYS
	unsigned char retvalue=0;
	#ifdef _USE_SIMPLE_KEYS
	char keyInput=PORTB&0x0F;
	//if(keyInput&0x10) keyInput|=0x01;
	keyInput&=0x0F;
	if(previousKeyInput==keyInput) return 0;
	else
	{
	previousKeyInput=keyInput;
	 return keyInput;
	}
	#else
/* TEST VERSION WITH PC RS232 CONNETION!
	HandleIBUSStack();
	if (JogValue!=0)
	{	
		retvalue=JogValue;	
		JogValue=0;
	}
	return retvalue;
*/
	if(!AIRHORNBUTTON)
	{
		Delay1KTCYx(100);
		if(!AIRHORNBUTTON)
		ShowAirHornStarter();
	}
		//#ifdef _CONTINOUS_SEND
		if(JogReadMode==_CONTINOUS_SEND)
		{
			HandleIBUSStack();
			if(JoystickValue!=0) //Joystick has higher priority than the Jog
			{
				retvalue=JoystickValue;
				JoystickValue=0;
				JogValue=0x7F;
			}
			else if(JogValue!=0x7F)
			{
				if(JogValue<0x7F)
				{
					 retvalue=_KEY_INC;
					 JogValue++;
				}
				else
				{	
					retvalue=_KEY_DEC;
					JogValue--;
				}
				
			}
			return retvalue;
		}
		//#else
		else
		{
			if(KEYBOARD_IT)
			{
				//PORTD^=0x01;
				ResetIBUSStack();
				SendIBUSData(_READ_JOGVALUE);
				IBUSWaitForResponse(_READ_JOGVALUE);
			}
		//		HandleIBUSStack();
				if(JoystickValue!=0) //Joystick has higher priority than the Jog
				{
					retvalue=JoystickValue;
					JoystickValue=0;
					JogValue=0x7F;
				}
				else if(JogValue!=0x7F)
				{
					if(JogValue<0x7F) 
					{
						retvalue=_KEY_INC;
						JogValue++;
					}
					else 
					{
						retvalue=_KEY_DEC;
						JogValue--;
					}
					//JogValue=0;
				}
				return retvalue;
		}
		//#endif
	#endif
}


//Theme tests

void DrawConsumption(unsigned char value)
{
	glcdPutImage(Symbol_FuelStation,0,1);
	glcdPutImage(Symbol_Average,20,0);
	glcdPutImage(Symbol_L_100km,77,1);
	glcdLine(0,22,100,22);
}

void DrawConsumptionCurrent(unsigned char value)
{
	glcdPutImage(Symbol_FuelStation,0,1);
	glcdPutImage(Symbol_Current,20,0);
	glcdPutImage(Symbol_L_100km,77,1);
	glcdLine(0,22,100,22);
}

void PutFixedPointValue(unsigned char value)
{
	char stringtemp[3]={'0','0','0'};
	unsigned char temp=0;
	while(value>=100)
	{
		value-=100;
		stringtemp[0]++;
	}
	while(value>=10)
	{
		value-=10;
		stringtemp[1]++;
	}
	stringtemp[2]+=value;
	glcdSetFont(_TIMESNEWROMAN_SIZE22);
	if(stringtemp[0]>'0') glcdPutCharFine(36,4,stringtemp[0]);
	glcdPutCharFine(47,4,stringtemp[1]);
	glcdPutCharFine(65,4,stringtemp[2]);
	glcdPutCharFine(59,4,':');
}

void ShowDemo1()
{
	unsigned char temp;
	ReadTime();
	ReadDate();
	WriteByteMCP7940(0x07,0x40);	//b'0100 0000'
	while(1)
	{
	glcdClearScreen(0);
	DrawConsumption(0);
	glcdSetFont(_TIMESNEWROMAN_SIZE8_BOLD);
	//glcdPutStringFine(1,24,"2012;03;11");
	glcdPutStringFine(1,24,"20");
	glcdPutValueFine((Years&0xF0)>>4,13,24,0);
	glcdPutValueFine((Years&0x0F),19,24,0);
	glcdPutCharFine(25,24,':');
	glcdPutValueFine((Months&0xF0)>>4,28,24,0);
	glcdPutValueFine((Months&0x0F),34,24,0);
	glcdPutCharFine(40,24,':');
	glcdPutValueFine((Days&0xF0)>>4,43,24,0);
	glcdPutValueFine((Days&0x0F),49,24,0);

	glcdPutValueFine((hours&0xF0)>>4,72,24,0);
	glcdPutValueFine((hours&0x0F),78,24,0);
	glcdPutCharFine(84,24,';');
	glcdPutValueFine((minutes&0xF0)>>4,87,24,0);
	glcdPutValueFine((minutes&0x0F),93,24,0);
//	glcdPutValueFine(hours,71,24,0);
//	glcdPutCharFine(83,24,';');
//	glcdPutValueFine(minutes,87,24,1);

	//glcdPutValueFine(((ReadByteMCP7940(1)&0x70)>>4),87,24);
	//glcdPutValueFine((ReadByteMCP7940(1)&0x0F),93,24);
	PutFixedPointValue(63);
	glcdRefreshDisplay180(0);
	temp=HandleKeys();
	if((temp==_KEY_INC)|(temp==_KEY_DEC)|(temp==_KEY_ENTER)) 
	{
		HandleDemoControl(temp);
		WriteByteMCP7940(0x07,0x00);	//b'0100 0000'
		break;
	}
	}
/*
	while(1)
	{
		temp=HandleKeys();
		if(!(temp==0)||(temp==0x0F))
		{
			if((temp==_KEY_INC)|(temp==_KEY_DEC)|(temp==_KEY_ENTER)) 
			{
				HandleDemoControl(temp);
				break;
			}
		}
	}
*/
}


void ShowDemo4()
{
	glcdClearScreen(0);
//	glcdPutLogo(DemoStyle2);
	glcdRefreshDisplay180(0);
}

void ShowTurbo()
{
	unsigned char cnt,ADCValue;
	unsigned char temp;
	//for(cnt=0;cnt<=30;cnt+=1)
	while(1)
	{
		//HandleIBUSStack();
	ADCValue=ReadADCValue(1);
	if(ADCValue>=90)ADCValue-=90;
	else ADCValue=0;
	if(ADCValue>161) ADCValue=161;
	//if(ADCValue>=90)ADCValue-=90;
	//else ADCValue=0;
	//temp=cnt*8;
	//temp/=3;
	glcdClearScreen(0);
	glcdPutImage(Symbol_ProgressBarStyle_A,0,14);
	glcdPutImage(Symbol_TurboIcon,2,0);
	glcdPutImage(Symbol_UnitBar,80,2);
	glcdDrawHorizontalBar_StyleA(5,23,(ADCValue/2),6);
	glcdSetFont(_ARIAL_SIZE12_BOLD);
	//glcdPutStringFine(56,1,"1:2");
	//glcdPutValueFine(cnt/2,56,1);
	glcdPutFloatFine(GetPressure(ADCValue),56,1,2);


	glcdRefreshDisplay180(0);
	//Delay1KTCYx(255);

		temp=HandleKeys();
		if((temp==_KEY_INC)|(temp==_KEY_DEC)|(temp==_KEY_ENTER)) 
		{
			HandleDemoControl(temp);
			break;
		}
	}
}

/*
Modified for RTC test:

void ShowSpeed()
{
	unsigned char style=0,temp=0,sloop=0,speedAct=0,ADCValue;
	unsigned int speed=0,asd;

	unsigned char tens,ones;

	//InitSpeedTimers();
	while(1)
	{
		//HandleIBUSStack();
	ADCValue=ReadADCValue(1);
	if(ADCValue>=90)ADCValue-=90;
	else ADCValue=0;
	if(ADCValue>161) ADCValue=161;
		if(sloop>1)
		{
			speed>>=1;
			speedAct=speed;
			speed=0;
			sloop=0;
		}
		asd=0;//GetSpeed();
		speed+=asd;
		sloop++;
		//StartSpeedMeasurement();
		glcdClearScreen(0);
		glcdSetFont(_TIMESNEWROMAN_SIZE8);
		glcdPutStringFine(1,24,"Turbo=");
		glcdPutStringFine(55,24,"bar");
		glcdSetFont(_TIMESNEWROMAN_SIZE8_BOLD);
		glcdPutFloatFine(GetPressure(ADCValue),36,24,2);
		glcdPutImage(Symbol_SpeedIndicator,0,0);
		glcdPutImage(Symbol_km_h,78,0);
		glcdLine(0,22,99,22);
		glcdSetFont(_TIMESNEWROMAN_SIZE22);
		ones=(ReadByteMCP7940(0)&0x7f);
		tens=ones>>4;
		tens*=10;
		ones&=0x0F;
		tens=ones+tens;
		glcdPutValueFine(tens,37,4,0);//speedAct,37,4);
		glcdRefreshDisplay180(0);
		temp=HandleKeys();
		if((temp==_KEY_INC)|(temp==_KEY_DEC)|(temp==_KEY_ENTER)) 
		{
			HandleDemoControl(temp);
			break;
		}
	}
}
*/
void ShowSpeed()
{
	unsigned char style=0,temp=0,sloop=0,speedAct=0,ADCValue;
	unsigned int speed=0,asd;

	InitSpeedTimers();
	while(1)
	{
		//HandleIBUSStack();
	ADCValue=ReadADCValue(1);
	if(ADCValue>=90)ADCValue-=90;
	else ADCValue=0;
	if(ADCValue>161) ADCValue=161;
		if(sloop>1)
		{
			speed>>=1;
			speedAct=speed;
			speed=0;
			sloop=0;
		}
		asd=GetSpeed();
		speed+=asd;
		sloop++;
		StartSpeedMeasurement();
		glcdClearScreen(0);
		glcdSetFont(_TIMESNEWROMAN_SIZE8);
		glcdPutStringFine(1,24,"Turbo=");
		glcdPutStringFine(55,24,"bar");
		glcdSetFont(_TIMESNEWROMAN_SIZE8_BOLD);
		glcdPutFloatFine(GetPressure(ADCValue),36,24,2);
		glcdPutImage(Symbol_SpeedIndicator,0,0);
		glcdPutImage(Symbol_km_h,78,0);
		glcdLine(0,22,99,22);
		glcdSetFont(_TIMESNEWROMAN_SIZE22);
		glcdPutValueFine(speedAct,37,4,0);
//DEBUG:
//	if(LIN_ERROR)
//	glcdPutValueFine(1,37,4,0);
//	else
//	glcdPutValueFine(0,37,4,0);
//END OF DEBUG
		glcdRefreshDisplay180(0);
		temp=HandleKeys();
		if((temp==_KEY_INC)|(temp==_KEY_DEC)|(temp==_KEY_ENTER)) 
		{
			HandleDemoControl(temp);
			break;
		}
	}
}


void ShowTemp()
{

	unsigned char temp=0;
	unsigned int Temperature=0;
	
	ds1820_Reset(); 

	while(1)
	{
		ds1820_SendByte(0xCC);
		glcdClearScreen(0);
		glcdPutImage(Symbol_EngineTemp,0,0);
		glcdPutImage(Symbol_UnitCelsius,79,5);
		glcdLine(0,22,99,22);
		glcdSetFont(_TIMESNEWROMAN_SIZE8);
		glcdPutStringFine(21,24,"EngineTemp");

		Temperature=ds1820_ReadTempSimple();
		Temperature=ds1820_GetTemp(Temperature);
		glcdSetFont(_ARIAL_SIZE12_BOLD);
		if(Temperature<2000)
			glcdPutFloatFine(Temperature,46,6,2);
		else 
		{
			glcdSetFont(_TIMESNEWROMAN_SIZE8);
			glcdPutStringFine(53,5,"Error");
			glcdSetFont(_ARIAL_SIZE12_BOLD);
		}

		//glcdPutStringFineDynamic(58,8,&TempValue[0]);
		glcdRefreshDisplay180(0);

		temp=HandleKeys();
		if((temp==_KEY_INC)|(temp==_KEY_DEC)|(temp==_KEY_ENTER)) 
		{
			HandleDemoControl(temp);
			break;
		}
	}
}

unsigned char ReadADCValue(unsigned char channel)
{
	char SampleCount;
	unsigned int Sample;
	ADCON0=(channel<<2);
	for(SampleCount=0;SampleCount<4;SampleCount++)
	{
		ADCON0bits.ADON=1;
		ADCON0bits.GO_DONE=1;
		while(ADCON0bits.GO_DONE);
		Sample+=ADRESH;
		Delay1KTCYx(5);
	}
	return Sample>>2;// ADRESH;
}


unsigned char GetPressure(unsigned char rawinput)
{
	unsigned char i=0,x;
	//find the value from the calibration values array
	while(CalibRationValues[i][0]<rawinput) 
	{	
		i++;
		if(i==16)break;
	}
	if(rawinput!=CalibRationValues[i][0]) 
	{
		//Coarse interpolation:
		if((CalibRationValues[i][0]-rawinput)>(rawinput-CalibRationValues[i-1][0]))
			return CalibRationValues[i-1][1];
		else
			return CalibRationValues[i][1];
	}
	else
	{
		return CalibRationValues[i][1];
	}
	
}

void HandleTimerOverflow()
{
	NumOfOverFlows++;
	PIR2bits.TMR3IF=0;
}

unsigned char HandleDemoControl(unsigned char key)
{
	switch(key)
	{
		case _KEY_INC:
			DemoID++;
			if(DemoID>4) DemoID=1;
			return 0;
		break;
		case _KEY_DEC:
			DemoID--;
			if(DemoID<1) DemoID=4;
			return 0;
		break;
		case _KEY_ENTER:
			loop=0;
			return 0;
		break;
	}
	return 1;
}


void SetJogMode(unsigned char Mode)
{
	unsigned char RetryCount=10;
	do
	{
		if(RetryCount==0) break;
		SendIBUSFunction(_SET_JOGMODE,Mode);	
		RetryCount--;
	}
	while(!IBUSWaitForResponse(_SET_JOGMODE));
	if(!RetryCount) return;  //It is important that when there is no response from the Jog to this command, then the read mode should be left in the last mode!
	JogReadMode=Mode;
}

#define _DAC_I2C_ADDRESS 0xC0

unsigned char TestHWI2C(unsigned char data)
{
	signed char retval=0;
	SSP2CON2bits.SEN=1;
	while(SSP2CON2bits.SEN);	//wait till the start condition is stransfered
	PIR3bits.SSP2IF=0;
	SSP2BUF=_DAC_I2C_ADDRESS;
	while(!PIR3bits.SSP2IF);
	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;
	SSP2BUF=0x00;
	while(!PIR3bits.SSP2IF);
	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;
	SSP2BUF=data;
	while(!PIR3bits.SSP2IF);
	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;
	SSP2CON2bits.PEN=1;
	while(SSP2CON2bits.PEN);
	return retval;
}

void SetDutyCycle(unsigned char dutyCycle)
{
	dutyCycle>>=1;
	CCPR1L=dutyCycle;
}
//


