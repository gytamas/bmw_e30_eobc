//MCP7940 RTC
//#include "i2c.h"
#include "mcp7940.h"
#include <p18f25k22.h>
unsigned char hours,minutes,Years,Months,Days;
void HandleRTC_ISR()
{	
	PORTAbits.RA2^=1;
	ReadTime();
}	


void ReadTime()
{
	hours=ReadByteMCP7940(2)&0x3F;
	minutes=ReadByteMCP7940(1)&0x7F;
}

void ReadDate()
{
	Years=ReadByteMCP7940(6);
	Months=ReadByteMCP7940(5)&0x1F;
	Days=ReadByteMCP7940(4)&0x3F;
}
void SetTime()
{	
	WriteByteMCP7940(2,hours);
	WriteByteMCP7940(1,minutes);
}

void configuureMP7940(unsigned char address)
{
	INTCONbits.INT0IE=0;
	SSP2CON2bits.SEN=1;
	while(SSP2CON2bits.SEN);	//wait till the start condition is stransfered
	PIR3bits.SSP2IF=0;
	SSP2BUF=_MCP7940_I2C_ADDRESS;
	while(!PIR3bits.SSP2IF);
//	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;
	SSP2BUF=0x00;
	while(!PIR3bits.SSP2IF);
//	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;

	SSP2BUF=0x80;	//b'0000 0000'
	while(!PIR3bits.SSP2IF);
//	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;


	SSP2CON2bits.PEN=1;
	while(SSP2CON2bits.PEN);
	PIR3bits.SSP2IF=0;

	INTCONbits.INT0IE=1;
}
/*
unsigned char ReadByteMCP7940(unsigned char regAddress)
{
	unsigned char retval=0;
	StartI2C2();
	IdleI2C2();
	WriteI2C2(_MCP7940_I2C_ADDRESS);
	IdleI2C2();
	WriteI2C2(regAddress);
	IdleI2C2();
	RestartI2C2();
	IdleI2C2();
	WriteI2C2(_MCP7940_I2C_ADDRESS+1);
	IdleI2C2();
	retval=ReadI2C2();
	IdleI2C2();
	NotAckI2C2();
	IdleI2C2();
	StopI2C2();
	return retval;
}

*/
unsigned char TestMCP7940(unsigned char address)
{
}
//unsigned char TestMCP7940(unsigned char address)
unsigned char ReadByteMCP7940(unsigned char regAddress)
{

//	signed char retval=0;
	unsigned char retval=0;
	INTCONbits.INT0IE=0;


	//PORTAbits.RA2=1;
	SSP2CON2bits.SEN=1;
	while(SSP2CON2bits.SEN);	//wait till the start condition is stransfered
	PIR3bits.SSP2IF=0;
	SSP2BUF=_MCP7940_I2C_ADDRESS;
	while(!PIR3bits.SSP2IF);
//	if(!SSP2CON2bits.ACKSTAT) PORTAbits.RA2=0;
//	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;

	SSP2BUF=regAddress;

	while(!PIR3bits.SSP2IF);
	PIR3bits.SSP2IF=0;
//read byte

	SSP2CON2bits.RSEN=1;
	while(SSP2CON2bits.RSEN);	//wait till the start condition is stransfered
	PIR3bits.SSP2IF=0;
	SSP2BUF=_MCP7940_I2C_ADDRESS+1;
	while(!PIR3bits.SSP2IF);
//	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;

//	PORTAbits.RA2=0;

	SSP2CON2bits.RCEN=1;
	while(!SSP2STATbits.BF);
	retval=SSP2BUF;
	PIR3bits.SSP2IF=0;
	SSP2STATbits.BF=0;

//	PORTAbits.RA2=1;
	
//Acknowledge received data.
	SSP2CON2bits.ACKDT=1;
	SSP2CON2bits.ACKEN=1;
	while(!PIR3bits.SSP2IF);
	PIR3bits.SSP2IF=0;

//Send stop at the en
	SSP2CON2bits.PEN=1;
	while(SSP2CON2bits.PEN);
	PIR3bits.SSP2IF=0;
	INTCONbits.INT0IE=1;
	return retval;

}

void WriteByteMCP7940(unsigned char regAddress,unsigned char value)
{

	INTCONbits.INT0IE=0;
	SSP2CON2bits.SEN=1;
	while(SSP2CON2bits.SEN);	//wait till the start condition is stransfered
	PIR3bits.SSP2IF=0;
	SSP2BUF=_MCP7940_I2C_ADDRESS;
	while(!PIR3bits.SSP2IF);
//	if(SSP2CON2bits.ACKDT) retval=1;
	PIR3bits.SSP2IF=0;

	SSP2BUF=regAddress;
	while(!PIR3bits.SSP2IF);
	PIR3bits.SSP2IF=0;

	SSP2BUF=value;
	while(!PIR3bits.SSP2IF);
	PIR3bits.SSP2IF=0;

	SSP2CON2bits.PEN=1;
	while(SSP2CON2bits.PEN);
	PIR3bits.SSP2IF=0;

	INTCONbits.INT0IE=1;
}