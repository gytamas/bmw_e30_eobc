//screensaver.c

#include "screensaver.h"
#include "PCF8558.h"
//#include "bitmaps.h"

#define _SCREENSIZE_X 101
#define _SCREENSIZE_Y 31

//Global variables
unsigned rom char *object;
unsigned char x,y;
signed char xspeed,yspeed;

unsigned char getbitmapSizeX(unsigned const rom char *);
unsigned char getbitmapSizeY(unsigned const rom char *);
void Wait(void);

void InitGame_Pong(unsigned rom char *image)
{
	object=image;
	xspeed=1;
	yspeed=1;
	x=10;
	y=6;
}
void HandleGame_Pong(void) //(unsigned rom char *image)
{
//	unsigned char x=10,y=6;
//	signed char xspeed=1,yspeed=1;
	
//	while(1)
//	{

		x+=xspeed;
		if(x==0) xspeed=1;
		if((x+getbitmapSizeX(object)+1)==_SCREENSIZE_X) xspeed=-1;
		y+=yspeed;
		if(y==0) yspeed=1;
		if((y+getbitmapSizeY(object))==_SCREENSIZE_Y) yspeed=-1;
		glcdClearScreen(0);
		glcdPutImage(object,x,y);
		glcdRefreshDisplay180(0);
//		Wait();
//	}
}
unsigned char HandlePongKeys(unsigned char key)
{
	//if(key==_BTN_ESC) return 0; //exit game
	switch(key)
	{
		case _BTN_ESC: return 0; 
		case _BTN_MENU_UP:
			xspeed=1;
			return 1;
		case _BTN_MENU_DOWN:
			xspeed=-1;
			return 1;
	}
}
unsigned char getbitmapSizeX(unsigned const rom char *bitmap)
{
	return *bitmap;
}

unsigned char getbitmapSizeY(unsigned const rom char *bitmap)
{
	return *(bitmap+1);
}

void Wait(void)
{
	Delay1KTCYx(255);
	//Delay1KTCYx(255);
}