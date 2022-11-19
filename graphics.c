//Graphics.c

#include "primitives.h"
#include "PCF8548.h"
#include "graphics.h"

//#define _USE_COMPLEX_LINE
//#ifdef _USE_COMPLEX_LINE
#define _USE_GLCD_LINE
#ifdef _USE_GLCD_LINE
void glcdLine(unsigned char XStart,unsigned char YStart,unsigned char XEnd,unsigned char YEnd)
{
	signed char deltaX,deltaY,error;
	unsigned char ystep,steep,Y,X;
	steep=(abs(YEnd-YStart)>abs(XEnd-XStart));
	if(steep)
	{
		swap(&XStart,&YStart);
		swap(&XEnd,&YEnd);
	}
	if(XStart>XEnd)
	{
		swap(&XStart,&XEnd);
		swap(&YStart,&YEnd);
	}
	deltaX=XEnd-XStart;
	deltaY=abs(YEnd-YStart);
	error=deltaX/2;
	Y=YStart;
	if(YStart<YEnd) ystep=1;
	else ystep=-1;
	for(X=XStart;X<=XEnd;X++)
	{
		if(steep) glcdSetPixel(Y,X);
		else glcdSetPixel(X,Y);
		error-=deltaY;
		if(error<0)
		{
			Y+=ystep;
			error+=deltaX;
		}
	}
}
#endif
#ifdef _USE_FULL_LINE
unsigned char glcdFixedLine(unsigned char XStart,unsigned char YStart,unsigned char XEnd,unsigned char YEnd,unsigned char len)
{
	signed char deltaX,deltaY,error;
	unsigned char ystep,steep,Y,X;
	steep=(abs(YEnd-YStart)>abs(XEnd-XStart));
	if(steep)
	{
		swap(&XStart,&YStart);
		swap(&XEnd,&YEnd);
	}
	if(XStart>XEnd)
	{
		swap(&XStart,&XEnd);
		swap(&YStart,&YEnd);
	}
	deltaX=XEnd-XStart;
	deltaY=abs(YEnd-YStart);
	error=deltaX/2;
	Y=YStart;
	if(YStart<YEnd) ystep=1;
	else ystep=-1;
	for(X=XStart;X<=XEnd;X++)
	{
		if(!len) return 0;
		if(steep){ glcdSetPixel(Y,X);}
		else {glcdSetPixel(X,Y);}
		len--;
		error-=deltaY;
		if(error<0)
		{
			Y+=ystep;
			error+=deltaX;
		}
	}
	return len;
}
#else
unsigned char glcdFixedLine(unsigned char XStart,unsigned char YStart,unsigned char XEnd,unsigned char YEnd,unsigned char len)
{
	unsigned char cnt;
	if(XStart==XEnd)
	{
		if(YStart<YEnd)
		{
			for(cnt=YStart;cnt<=YEnd;cnt++)
			{
				if(!len) return 0;
				glcdSetPixel(XStart,cnt);
				glcdSetPixel(XStart+1,cnt);
				glcdSetPixel(XStart-1,cnt);
				len--;
			}
		}
		else
		{
			for(cnt=YStart;cnt>=YEnd;cnt--)
			{
				if(!len) return 0;
				glcdSetPixel(XStart,cnt);
				glcdSetPixel(XStart+1,cnt);
				glcdSetPixel(XStart-1,cnt);
				len--;
			}
		}
	}
	else
	{
		if(XStart<XEnd)
		{
			for(cnt=XStart;cnt<=XEnd;cnt++)
			{
				if(!len) return 0;
				glcdSetPixel(cnt,YStart);
				glcdSetPixel(cnt,YStart+1);
				glcdSetPixel(cnt,YStart-1);
				len--;
			}
		}
		else
		{
			for(cnt=XStart;cnt>=XEnd;cnt--)
			{
				if(!len) return 0;
				glcdSetPixel(cnt,YStart);
				glcdSetPixel(cnt,YStart+1);
				glcdSetPixel(cnt,YStart-1);
				len--;
			}
		}
	}
	return len;
}
#endif

void glcdDrawBarFixedWidth(unsigned char PosX, unsigned char PosY, unsigned char Length)
{
	//Draw barframes	
	glcdLine(4,17,94,17);
	glcdLine(94,17,94,23);
	glcdLine(94,23,4,23);
	//glcdLine(4,23,4,17);
	glcdLine(2,15,96,15);
	glcdLine(96,15,96,25);
	glcdLine(96,25,2,25);
	glcdLine(2,25,2,15);
	//Then draw the bar itself
	Length++;
	glcdFixedLine(PosX,PosY,PosX+90,PosY,Length);
	glcdFixedLine(PosX,PosY+3,PosX+90,PosY+3,Length); //not a nice solution...

}
void glcdDrawHorizontalBar_StyleA(unsigned char XStart,unsigned char YStart,unsigned char Length,unsigned char BarWidth)
{
	unsigned char x,y;
	for(x=XStart;x<(XStart+Length);x++)	
		for(y=YStart;y<(YStart+BarWidth);y++) 
			glcdInvertPixel(x,y);
}

void glcdPutValueFine(unsigned char value,unsigned char posX, unsigned char posY,unsigned char zeros) 
{
	unsigned char valueString[5];
	unsigned char *valuePointer;
	valuePointer=&valueString[0];

	ConvertValue(value,&valueString[0]);
	if(value<10) 
	{
		if(zeros==0)
			valueString[1]=' ';
		valuePointer=&valueString[2];
	}
	else if(value<100)
	{
		if(zeros<2)
		 valuePointer=&valueString[1];

	}

	glcdPutStringFineDynamic(posX,posY,valuePointer);
}
void glcdPutFloatFine(unsigned int value,unsigned char posX,unsigned char posY,unsigned char Decimal)
{
	unsigned char valueString[6]={0,0,0,0,0,0};	// e.g.: 12.5= 0x31 0x32 '.' 0x35 0x00
	if((value>1000)&&(Decimal<3)) Decimal++; 
	ConvertValue2(value,&valueString[0],Decimal);
	glcdPutStringFineDynamic(posX,posY,valueString);
}

void ConvertValue(unsigned char value,unsigned char *result)
{
	unsigned char cnt;
	*result='0';
	*(result+1)='0';
	*(result+2)='0';

	while(value>=100)
	{
		(*result)++;
		value-=100;
	};

	while(value>=10)
	{
		(*(result+1))++;
		value-=10;
	}
	(*(result+2))+=value;
	*(result+3)=0x00;
}

/*
void ConvertValue2(unsigned char value, unsigned char *result, unsigned char decimal)
{
//---------------
// value Decimal
// 0000  	0
// 000.0  	1
// 00.00  	2
// 0.000  	3
//---------------
	unsigned char cnt;
	if(decimal)decimal--;
	while(value>=1000)
	{
		(*result)++;
		value-=1000;
	}
	if(*result>0)
	{
		*result+=0x30;
		*result++;
	}
	while(value>=100)
	{
		(*result)++;
		value-=100;
	}
	if(*result>0)
	{
		*result+=0x30;
		*result++;
	}
	if(decimal--==0)*result++=':';
	while(value>=10)
	{
		(*result)++;
		value-=10;
	}
	*result+=0x30;
	*result++;
	if(decimal--==0)*result++=':';
	*result+=value;
	*result+=0x30;
	*++result=0x00;
}
*/
void ConvertValue2(unsigned int value, unsigned char *result, unsigned char decimal)
{
//---------------
// value Decimal
// 0000  	0
// 000.0  	1
// 00.00  	2
// 0.000  	3
//---------------
	unsigned char cnt;
	if(decimal)decimal--;

	while(value>=1000)
	{
		(*result)++;
		value-=1000;
	}
	if(*result>0)
	{
		*result+=0x30;
		*result++;
	}
	while(value>=100)
	{
		(*result)++;
		value-=100;
	}
	if(*result>0)
	{
		*result+=0x30;
		*result++;
	}
	if(decimal--==0)*result++=':';
	while(value>=10)
	{
		(*result)++;
		value-=10;
	}
	*result+=0x30;
	*result++;
	if(decimal--==0)*result++=':';
	*result+=value;
	*result+=0x30;
	*++result=0x00;
}
