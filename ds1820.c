//ds1820 thermometer
#include <p18f25k22.h>
#include "ds1820.h"
unsigned char ds1820_Reset()
{
	unsigned char timer=20;
	PORTAbits.RA4=0;
	TRISAbits.RA4=0;
	Delay1KTCYx(2);	//~500us
	TRISAbits.RA4=1;
	while(timer--)
	{
		if(!PORTAbits.RA4)
		{
			 while(!PORTAbits.RA4);
			 Delay10TCYx(60);
			 return 1;
		}
		Delay100TCYx(2); //~50us
	}
			return 0;
}


void ds1820_SendByte(unsigned char data)
{
	unsigned char bits;
	for(bits=0;bits<8;bits++)
	{
		if(data&0x01) ds1820_writeOne();
		else ds1820_writeNull();
		data>>=1;
	}
	Delay10TCYx(40);
}



unsigned char ds1820_ReadByte()
{
	static unsigned char bits,data=0;
	for(bits=0;bits<8;bits++)
	{
		data>>=1;
		TRISAbits.RA4=0;
		Delay10TCYx(2); //~5us
		TRISAbits.RA4=1;
		Delay10TCYx(2); //~5us
		if(PORTAbits.RA4==1) data+=0x80;
		Delay10TCYx(24);
	}
	Delay10TCYx(40);
	return data;
}

void ds1820_writeOne()
{
	TRISAbits.RA4=0;
	Delay10TCYx(2); //~5us
	TRISAbits.RA4=1;
	Delay10TCYx(24); //~100us
}

void ds1820_writeNull()
{
	TRISAbits.RA4=0;
	Delay10TCYx(2); //~5us
	Delay10TCYx(24); //~100us
	TRISAbits.RA4=1;
}

unsigned int ds1820_ReadTempSimple()
{
	
	unsigned int temp;
	unsigned char ctemp;
	ds1820_SendByte(0x44);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);
	Delay1KTCYx(255);

	ds1820_Reset();
	ds1820_SendByte(0xCC);
	ds1820_SendByte(0xBE);
	ctemp=ds1820_ReadByte();
	temp=ds1820_ReadByte();
	temp<<=8;
	temp+=ctemp;
	ds1820_Reset();
	return temp;
}

unsigned int ds1820_GetTemp(unsigned int digivalue)
{
	unsigned char temp=0;
	if((digivalue&0x000F)>=8) temp=5;
	digivalue>>=4;
	digivalue*=10;
	digivalue+=temp;
	return digivalue;
}