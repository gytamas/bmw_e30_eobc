//PCF8558 driver
#include <p18f25k22.h>
#include "PCF8548.h"
#include "bmwlogo.h"
//#include "font1.h"
#include "font2.h"
#include "font3.h" //font6 can be used insted of font3. Same size, but bold letters.
//#include "font6.h"
#include "font4.h"
#include "font5.h"
#include "main.h"
#include "primitives.h"
#include "bitmaps.h"
#include "swi2c_simple.h"
#include "dither.h"
//Variable: fontdatapointer;
//Description: points to the selected fonts parameters. The parameters are:
//             0-SizeX, 1-SizeY, 2-fontoffset. "fontoffset" contains a correction value for incomplete fonts, so that they
//			   can be used with ASCII coding
//
//Device sepcific data:
//=====================
//I2CAddress:
//----------
#define _DEV_ADDRESS 0x78
//
rconst *fontdatapointer;
unsigned char cursorX,cursorY;
#pragma udata large_buffer
static char FrameBuffer[_FRAMESIZE_180];
#pragma code

//---------------------------------------------------------------------------------------
//Function: PCF8548 initialization with default values.
//Description: 
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value: 
//---------------------------------------------------------------------------------------
signed char PCF8548_Init()
{
	//
	if(i2cMasterSendMessage(0x80,0x20))return -1;
	if(i2cMasterSendMessage(0x80,0x0C))return -1;	//
	if(i2cMasterSendMessage(0x80,0x06))return -1;	//?
	if(i2cMasterSendMessage(0x80,0x21))return -1;	//Set extended mode
	if(i2cMasterSendMessage(0x80,0x14))return -1;	//Set bias
	if(i2cMasterSendMessage(0x80,0x20))return -1;	//back to normal mode
	if(i2cMasterSendMessage(0x80,0x40))return -1;	
	if(i2cMasterSendMessage(0x80,0x80))return -1;
	
}
//---------------------------------------------------------------------------------------
//Function: i2cMasterSendMessage
//Description: Sends 3bytes to the i2c slave: slave address, control byte, databye. 
//						 Specifically designed for PCF8548!
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value: 
//---------------------------------------------------------------------------------------
signed char i2cMasterSendMessage(unsigned char control, unsigned char data)
{
		SWStartI2C();
		SWPutcI2C(_DEV_ADDRESS); 
		if(SWAckI2C()!=0)  return -1;
		SWPutcI2C(control); 
		if(SWAckI2C()!=0) return -1;
		SWPutcI2C(data); //Xaddress
		if(SWAckI2C()!=0) return -1;
		SWStopI2C();
		return 0;
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
void glcdSetFont(unsigned char fontID)
{

	switch(fontID)
	{
	/*	case _TIMESNEWROMAN_SIZE10:
			fontdatapointer=&fontheader_TimesSize10[0];
			break;
*/
		case _TIMESNEWROMAN_SIZE22:  //Currently not used!
			fontdatapointer=&fontheader_TimesSize22[0];
			break;
		case _TIMESNEWROMAN_SIZE8:
			fontdatapointer=&fontheader_TimesSize8[0];
			//fontdatapointer=&fontheader_ArialSize8Bold[0];
			break;
		case _TIMESNEWROMAN_SIZE8_BOLD:
			fontdatapointer=&fontheader_ArialSize8_Bold[0];
			break;
		case _ARIAL_SIZE12_BOLD:
			fontdatapointer=&fontheader_ArialSize12_Bold[0];
			break;
	}
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
signed char glcdRefreshDisplay180(unsigned char mask)
{
		unsigned int cnt;
		unsigned char temp;
		SWStartI2C();
		SWPutcI2C(_DEV_ADDRESS); 
		if(SWAckI2C()!=0)  return -1;
		SWPutcI2C(0x40); 
		if(SWAckI2C()!=0)  return -1;
		for(cnt=0;cnt<_FULL_FRAMESIZE;cnt++)
		{
			if(cnt>=_FRAMESIZE_180) temp=0x00; else
			temp=FrameBuffer[_FRAMESIZE_180-cnt-1];
			SWPutcI2C180(temp^mask);
			SWAckI2C();
		}
		SWStopI2C();
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
void glcdClearScreen(unsigned char pattern)
{
	unsigned int i;
	for(i=0;i<_FRAMESIZE_180;i++) FrameBuffer[i]=pattern;
	
}

//---------------------------------------------------------------------------------------
//Function: 
//Description: this is needed because the last line is not used, and in order to save memory
// in the PIC the last line is not mapped into the PIC's memory (2nd buffer), but due to this
// when the screen is refreshed this line is omitted, and trash could be displayed. 
//Usage:
//Author: GyT
//Revivison: 0.1
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
signed char glcdClearInitial()
{
		unsigned int cnt;
		SWStartI2C();
		SWPutcI2C(_DEV_ADDRESS); 
		if(SWAckI2C()!=0)  return -1;
		SWPutcI2C(0x40); 
		if(SWAckI2C()!=0)  return -1;
		for(cnt=0;cnt<_FULL_FRAMESIZE;cnt++)
		{
			SWPutcI2C180(0x00);
			SWAckI2C();
		}
		SWStopI2C();
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
/*
signed char glcdPutLogo1()
{
	unsigned int x,i=0;
	unsigned char y;	
	for(y=0;y<=4;y++)
	{
		for(x=y;x<505;x+=5)
		{
				FrameBuffer[i]=bmwlogo[x]; 
				i++;
		}
	}
}
*/
signed char glcdPutLogo(unsigned rom char *image)
{
	unsigned int x,i=0;
	unsigned char y;	
	for(y=0;y<=4;y++)
	{
		for(x=y;x<505;x+=5)
		{
				if(i<_FRAMESIZE_180)
					FrameBuffer[i]=image[x]; 
				i++;
		}
	}
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
void glcdPutImage(unsigned rom char * image,unsigned char posX, unsigned char posY)
{
	unsigned char x,y,ytemp,temp=0;
	unsigned int j,cnt;
	unsigned char sizeX=*image++;
	unsigned char sizeY=((*image++)>>3)+1;
	cnt=0;
	ytemp=(posY&0x18)>>3;
	for(x=posX;x<=posX+sizeX;x++)
	{
		for(y=ytemp;y<sizeY+ytemp;y++)
		{
			j=101;
			j*=y;
			j+=x+1;
			FrameBuffer[j]|=temp|(*(image+cnt)<<(posY&0x07));
			temp=*(image+cnt)>>(8-(posY&0x07));
			if((y==(ytemp+sizeY)-1)&(!(temp==0)))
			{
				 FrameBuffer[j+101]|=temp; //do another round!
				 temp=0;
			}
			cnt++;
		}
	}
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
signed char glcdPutChar(unsigned char character)
{
	unsigned char x,y,cnt,newsizeX;
	unsigned int i,j;
	rconst *fontdatapointertemp=fontdatapointer;
	unsigned char sizeX=*fontdatapointertemp++;
	unsigned char sizeY=((*fontdatapointertemp++)>>3)+1;
	i=character-*fontdatapointertemp++;
	i*=((sizeX+1)*sizeY);
#ifdef _USE_VARIABLE_TEXT_SIZE
	newsizeX=sizeX;
	for(x=0;x<(sizeX*sizeY-sizeY);x++)
	{
		cnt=0;
		for(j=x;j<=x+sizeY;j++) cnt|=*(fontdatapointertemp+i+j);
		if(!cnt) 
		{
			newsizeX=divide(x+1,sizeY)+1;
		//	newsizeX=((x+1)>>(sizeY-1))+1;
			x=100;
		}
	}
	sizeX=newsizeX; 
 
#endif
	fontdatapointertemp+=i;
//	fontdatapointer++;
	for(y=cursorY;y<sizeY+cursorY;y++)
	{
		cnt=0;
		for(x=cursorX;x<=cursorX+sizeX;x++)
		{
			j=101;
			j*=y;
			j+=x;
			FrameBuffer[j]=*(fontdatapointertemp+sizeY*cnt+y-cursorY);
			cnt++;
		}
	}
	cursorX+=sizeX; //+1 is optional
}
//---------------------------------------------------------------------------------------
//Function: 
//Description: 
//Usage:
//Author: GyT
//Revivison: 0.2
//Inputs: 
//Return value:
//---------------------------------------------------------------------------------------
//unsigned char InverseGraphic;
signed char glcdPutCharFine(unsigned char xpos, unsigned char ypos,unsigned char character)
{
	unsigned char x,y,cnt,newsizeX,temp=0;
	unsigned int i,j;
	unsigned char dontshow=0;
	rconst *fontdatapointertemp=fontdatapointer;
	unsigned char sizeX=*fontdatapointertemp++;
	unsigned char sizeY=((*fontdatapointertemp++)>>3)+1;
	if(character==0x20)
	{
		character='1';
		dontshow=1;
	}
	cursorY=(ypos&0x18)>>3;
	cursorX=xpos;
	i=character-*fontdatapointertemp++;
	i*=((sizeX+1)*sizeY);
	newsizeX=sizeX;
#ifdef _USE_VARIABLE_TEXT_SIZE	
	for(x=0;x<(sizeX*sizeY-sizeY);x++)
	{
		cnt=0;
		for(j=x;j<=x+sizeY;j++) cnt|=*(fontdatapointertemp+i+j);
		if(!cnt) 
		{
			newsizeX=divide(x+sizeY,sizeY);
		//	newsizeX=((x+1)>>(sizeY-1))+1;
			x=100; //use break insted....
		}
	}
//	sizeX=newsizeX;
	if(newsizeX<3) newsizeX=3;
#endif
	fontdatapointertemp+=i;
//	fontdatapointer++;
	cnt=0;
	for(x=cursorX;x<=cursorX+newsizeX;x++)
	{
		for(y=cursorY;y<sizeY+cursorY;y++)
		{
			j=101;
			j*=y;
			j+=x;
			if(!dontshow)FrameBuffer[j]|=temp|(*(fontdatapointertemp+cnt)<<(ypos&0x07));
			temp=*(fontdatapointertemp+cnt)>>(8-(ypos&0x07));
			if((y==(cursorY+sizeY)-1)&(!(temp==0)))
			{
				 if(!dontshow)FrameBuffer[j+101]|=temp; //do another round!
				 temp=0;
			}
			cnt++;
			//if(InverseGraphic) FrameBuffer[j]=~FrameBuffer[j];
		}
	}
	if(newsizeX==sizeX) cursorX++;
	cursorX+=newsizeX;
	sizeX=newsizeX;
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
void glcdSetCursor(unsigned char x,unsigned char y)
{
	cursorX=x;
	cursorY=y;
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
void glcdPutString(const rom unsigned char *input)
{
	while(*input)
	{
		glcdPutChar(*input++);		
	}
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
//#ifdef _USE_SIMPLEPUTSTRING
void glcdPutStringFine(unsigned char x, unsigned char y,const rom unsigned char *input)
{
	unsigned char temp;
	cursorX=x;
	while(*input)
	{
		temp=*input;
		glcdPutCharFine(cursorX,y,*input++);		
	}
}
//#endif
void glcdPutStringFineDynamic(unsigned char x, unsigned char y, unsigned char *input)
{
	cursorX=x;
	while(*input)
	{
		glcdPutCharFine(cursorX,y,*input++);		
	}
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
void glcdPutStringDynamic(unsigned char *input)
{
	while(*input)
	{
		glcdPutChar(*input++);		
	}
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

unsigned char InverseOrder(unsigned char input)
{
 unsigned char i,h;
 for(h = i = 0; i < 8; i++) 
 {
 	 h = (h << 1) + (input & 1); 
  	input >>= 1; 
 }	
 return h;
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
void glcdSetPixel(unsigned char posX,unsigned char posY)
{
	int j=(posY&0x18)>>3;
	j*=101;
	j+=posX;
	FrameBuffer[j]|=(1<<(posY&0x07));
}

void glcdInvertPixel(unsigned char posX,unsigned char posY)
{
	int j=(posY&0x18)>>3;
	j*=101;
	j+=posX;
	FrameBuffer[j]^=(1<<(posY&0x07));
}
void glcdClearPixel(unsigned char posX,unsigned char posY)
{
	int j=(posY&0x18)>>3;
	j*=101;
	j+=posX;
	FrameBuffer[j]&=!(1<<(posY&0x07));
}
unsigned char glcdGetPixel(unsigned char posX,unsigned char posY)
{
	int j=(posY&0x18)>>3;
	j*=101;
	j+=posX;
	if((FrameBuffer[j]>>(posY&0x07))&0x01) return 1;
	else return 0;
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
void glcdHighlightLine0(unsigned char line)
{
	unsigned char cnt;
	unsigned int j=line-1;
	j*=101;
	for(cnt=0;cnt<101;cnt++)//101;cnt++)
		FrameBuffer[(j+cnt)]^=0xFF;
}

//void glcdDrawBar(unsigned char posXStart,unsigned char posYStart,unsigned char height, unsigned char lenght)
void glcdHighlightLine(unsigned char posYStart)
{
	unsigned int j;
	unsigned char temp,cnt;
	j=(posYStart&0x18)>>3;
	j*=101;
	//j+=posXStart;
	for(cnt=0;cnt<88;cnt++)//101;cnt++)
	{
		FrameBuffer[j+cnt]^=(0xFF<<(posYStart&0x07));
		temp=0xFF>>(6-(posYStart&0x07)); // a little trick
		FrameBuffer[j+cnt+101]^=temp;
	}	
}


//there is an error, width had to be 8 less!!! this should be fixed!!! For.e.g for full display 24 had to be used instead of 32!!
void glcdDitherArea(unsigned char XStart, unsigned char YStart,unsigned char Width, unsigned char Height, unsigned char state,unsigned rom char *image)
{
	unsigned char x,y,backupbyte,mask,deb,ytemp;
	unsigned int j,DitherPos;
	unsigned rom char *dither;

	unsigned char sizeY=((YStart+Height)>>3)+1;
	ytemp=(YStart&0x18)>>3;

	for(y=ytemp;y<sizeY+ytemp;y++)
	{
		j=y;
		j*=101;
		for(x=XStart;x<(XStart+Width);x++)
		{
			dither=image;
			//j+=x;
			backupbyte=FrameBuffer[j+x];
			dither+=state*8;
			dither+=(x%8);
			deb=*dither;
			FrameBuffer[j+x]&=*dither;
			if(((YStart%8)!=0)&&(ytemp==y))
			{
				mask=(1<<(YStart%8))-1;
				FrameBuffer[j+x]&=(0xFF-mask);
				FrameBuffer[j+x]|=(backupbyte&mask);
			}		
			if((y==(sizeY+ytemp-1))&&((YStart+Height)%8!=0))
			{
				mask=(1<<((YStart+Height)%8))-1;
				FrameBuffer[j+x]&=mask;
				FrameBuffer[j+x]|=(backupbyte&(0xFF-mask));
			}
		}
	}
}

