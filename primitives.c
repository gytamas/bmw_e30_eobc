//additional functions
#include "primitives.h"

//---------------------------------------------------------------------------------------
//Function:
//Description:
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
unsigned char abs(signed char input)
{
	if(input<0) return (~input+1);
	else return input;
}

//---------------------------------------------------------------------------------------
//Function:
//Description:
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
void swap(unsigned char *val1,unsigned char *val2)
{
	unsigned char temp;
	temp=*val1;
	*val1=*val2;
	*val2=temp;
}

//---------------------------------------------------------------------------------------
//Function:
//Description:
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
unsigned char divide(unsigned char a, unsigned char b)
{
	unsigned char result=0;
	while(a>b) 
	{
		a-=b;
		result++;
	}
	a*=2;
	if(!(b>a)) result++;
	return result;
}

unsigned char divideInt(int a, unsigned b)
{
	unsigned char result=0;
	while(a>b) 
	{
		a-=b;
		result++;
	}
	a*=2;
	if(!(b>a)) result++;
	return result;
}
	
//---------------------------------------------------------------------------------------
//Function:
//Description:
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
unsigned char charToHex(unsigned rom char *input)
{
	unsigned char temp1;
	temp1=*input;
	if(*input<0x41) temp1=(*input++)-0x30;
	else temp1=(*input++)-0x37;
	temp1*=16;
	if(*input<0x41) temp1+=(*input++)-0x30;
	else temp1+=(*input++)-0x37;
	return temp1;
}
//---------------------------------------------------------------------------------------
//Function:
//Description:
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
void strcpylen(auto char *from,auto char *to, unsigned char len)
{
	unsigned char i;
	i=0;
	do
	{
		*to++=*from++;
		i++;
	}
	while(i<len);
	*to=0x00;
}
//---------------------------------------------------------------------------------------
//Function:
//Description:
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
signed char strcomp(auto char *input1,const rom char *input2)
{
	while(*input1)
	{
		if(*input1++!=*input2++) return 0;
	}
	return 1;
}

//---------------------------------------------------------------------------------------
//Function:
//Description:
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
unsigned char Length(unsigned char *str)
{
	 unsigned char cnt=0;
		while(*str++) if(cnt++==255) break;
		return cnt;
}
//---------------------------------------------------------------------------------------
//Function: IntToString
//Description: Simple integer to string conversion
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
void IntToString(int input, char *output)
{
	unsigned char temp=0;
	while(input>=10000)
	{
		input-=10000;
		temp++;
	}
	if(temp>0) *output++=temp+0x30;
	temp=0;
	while(input>=1000)
	{
		input-=1000;
		temp++;
	}
	if(temp>0) *output++=temp+0x30;
	temp=0;
	while(input>=100)
	{
		input-=100;
		temp++;
	}
	if(temp>0) *output++=temp+0x30;
	temp=0;
	while(input>=10)
	{
		input-=10;
		temp++;
	}
	if(temp>0) *output++=temp+0x30;
	*output++=input+0x30;
	*output++=0x00;
}