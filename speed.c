//speed.c
#include <p18f25k22.h>
#include "speed.h"

static unsigned int SpeedMeas[16];
unsigned char MeasPointer;
unsigned char CCPInterrupt;
unsigned char SpeedTest,test1=0;

extern unsigned char NumOfOverFlows;
#define _MIN_SPEED_OVERFLOW 4

void InitSpeedTimers()
{
	CCPInterrupt=0; 
	CCP2CON=0x04;  //b0000 0100 Capture mode, capture occures at every falling edge.
	CCPTMRS0=0x08; //0000 1000
	CCPTMRS0=0x0B; //b0000 1011. CCP2 uses Timer3
	PIE1=0x00;	 	
// asd
	PIE2bits.TMR3IE=1;
	IPR2bits.CCP2IP=1;
	IPR2bits.TMR3IP=1;	//high prio interrupt
	INTCON|=0xC0;
	T3CON=0x32;	   // 25k22--> 0011 0010  ---> 45k20: b'1011  1000 -> CCP2 uses T3, T3 is off, Fclk is Tosc/3 ---b'0011 0010. TMR3clk=fosc/4 Prescaler=1:8;  0x12--> TMR3clk=fosc
}
void StartSpeedMeasurement()
{
	NumOfOverFlows=0;
	CCPInterrupt=0;
	T3CONbits.TMR3ON=0;
	TMR3H=0;
	TMR3L=0;
	MeasPointer=0;
	PIE2bits.CCP2IE=1;
	Delay500ms();			//collect the data
//	while(MeasPointer==0)
//		if(NumOfOverFlows>_MIN_SPEED_OVERFLOW) break;
	PIE2bits.CCP2IE=0;	
	T3CONbits.TMR3ON=0;
}

void CaptureInterrupt()
{
//	PORTD^=0x02;
//	if(MeasPointer<16)
	{
		SpeedMeas[1]=CCPR2H;
		SpeedMeas[1]<<=8;
		SpeedMeas[1]+=CCPR2L;
		MeasPointer++;
	}
	PIR2bits.CCP2IF=0;
	CCPInterrupt++;
	TMR3L=0;
	TMR3H=0;
	if(!T3CONbits.TMR3ON)
	{
		T3CONbits.TMR3ON=1;		//Wait for the first falling edge
	}

}
unsigned char GetSpeed()
{
	unsigned char Value=0;
	unsigned char temp;
//	unsigned long Calib=518400;
	unsigned long Calib=416700;
	unsigned long SpeedValue;
	test1=CCPInterrupt;
//	unsigned int  Calib1=4050;
	if(MeasPointer<1) return 0;
	if(NumOfOverFlows>2) return 0;
	SpeedValue=65536;
	SpeedValue*=NumOfOverFlows;
	SpeedValue+=SpeedMeas[1];
//	temp=(((SpeedMeas[1]&0x3F00)>>6)+((SpeedMeas[1]&0x00C0)>>6)); //b 0011 1111 1100 0000
	if(SpeedValue==0) return 0;

	while(Calib>SpeedValue)
	{
		Calib-=SpeedValue;
		Value++;
	}
	if((SpeedValue>>1)>Calib) Value++;
	return 	(Value);
/*
	while(Calib1>temp)
	{
		Calib1-=temp;
		Value++;
	}
	if((temp>>1)>Calib1) Value++;
	return Value<<1;
*/
}

void Delay500ms()
{
	unsigned char cnt;
	for(cnt=0;cnt<4;cnt++)
		Delay1KTCYx(255);
}
