//worm.c
#include <p18f25k22.h>
#include "PCF8548.h"
#include "worm.h"
#include "graphics.h"
#include "randomizer.h"
#include "primitives.h"
#include "main.h"

extern unsigned char xRandom;

//Direction: YDir + XDir  -->  b  b
//  Y  X  Movement 	Key
//  0  0  			Up
// _______________________________
//| X  | Movement|| Y | Movement  |
//---------------||----|----------|
//| 0  |  X		 ||	 0 |   X	  |
//| 1  |  DOWN	 ||  1 |   RIGHT  |
//| F  |  UP	 ||  F |   LEFT   |
// -------------------------------
//
// Direction	Movement |Up pressed | Down pressed
//-----------|-----------|-----------|-------------
//		1    |	  ^		 |	  <(1-4) | >(1-3)
//		2	 |    ¡		 |	  <(2-4) | >(2-3)
//		3	 |    >		 |	  ^(3-1) | ¡(3-2)
//		4	 |    <		 |	  ^(4-1) | ¡(4-2)

unsigned char JointBufferX[_JOINTBUFFERSIZE],JointBufferY[_JOINTBUFFERSIZE];
unsigned char JointPointer;
unsigned char WormLength;
unsigned char DirectionChanged=0;
extern unsigned char gameState;
extern void (*ShowMenuSystem)(unsigned char);
extern void HandleMenu_V2(unsigned char);
extern void (*ShowMenuSystem)(unsigned char);	
unsigned char Direction,WormLength,addlength=0;
unsigned char HeadPosX,HeadPosY;
unsigned char FoodPosX,FoodPosY;

void StartGameWorm(unsigned char notUsed)
{
	ShowMenuSystem=PlayWorm;
	glcdClearScreen(0);
	InitGame_Worm();
	glcdRefreshDisplay180(0);
	gameState=1;	
	SetJogMode(_CONTINOUS_SEND);
	//DirectionChanged=1;	
}

//----------------------------------------------------------------------------------------------
//Function: PlayWorm
//Description: This is the main handle funciton to the Worm game. This should be called to handle
//		the game, and all necessary routines which are required for its operaiton should be called
//		from this function!
//Return value: 
//Input value: the keyinput.
//Effects: 
//----------------------------------------------------------------------------------------------
void PlayWorm(unsigned char keyinput)
{
		switch(HandleWormKeys(keyinput))
		{
			case 0:	ShowMenuSystem=HandleMenu_V2;
					SetJogMode(_MASTER_SLAVE_MODE);
				 	break;
			case 2:	glcdClearScreen(0);
					InitGame_Worm();
					glcdRefreshDisplay180(0);
					gameState=1;
					break;
			default:break;
		}
		HandleGame_Worm();
		Delay1KTCYx(50); //--> 50 should be defined as a constant!
}

void InitGame_Worm(void)
{
	Direction=3;
	HeadPosX=12;
	HeadPosY=9;
	glcdClearScreen(0);
	WormLength=_STARTINGLENGTH;
	JointPointer=0;
	JointBufferX[0]=10;
	JointBufferY[0]=7;
	FoodPosX=Randomize(xRandom);
		//do
		//{	
			WREG=xRandom;
			FoodPosX=Randomize(xRandom);
			while(FoodPosX>99) FoodPosX=divide(FoodPosX,3);
			if(FoodPosX<2) FoodPosX=2;
			WREG=FoodPosX^xRandom;
			FoodPosY=Randomize(FoodPosX^xRandom);
			if(FoodPosY<2) FoodPosY=2;
			while(FoodPosY>31) FoodPosY=divide(FoodPosY,5);
		//}
		//while(glcdGetPixel(FoodPosX,FoodPosY));
//	FoodPosX=Randomize(TMR0L);
//	while(FoodPosX>99) FoodPosX/=2;
//	FoodPosY=Randomize(FoodPosX);;
//	while(FoodPosY>30) FoodPosY/=2;
}

void HandleGame_Worm(void)
{
	unsigned char score[6];
	unsigned char temp;
	if(gameState)
	{
	switch(Direction)
	{
		case 1: HeadPosY++; break;
		case 2: HeadPosY--; break;
		case 3: HeadPosX++; break;
		case 4: HeadPosX--; break;
	}
	if((glcdGetPixel(HeadPosX,HeadPosY)&(!DirectionChanged))&&(!CheckFoodCollision()))
	{
		glcdClearScreen(0);
		gameState=0;
		DrawFrame();
	    //DrawSnake() ;
		glcdSetFont(_TIMESNEWROMAN_SIZE10);
		glcdPutStringFine(20,6,"GameOver");

		glcdSetFont(_TIMESNEWROMAN_SIZE8);
		glcdPutStringFine(19,19,"Score:");
		IntToString(WormLength-_STARTINGLENGTH,score);
		glcdPutStringFineDynamic(54,19,score);
		//glcdPutValueFine(WormLength-_STARTINGLENGTH,54,19);
		JointPointer=0;
	} 
	else
	{ 
		if(DirectionChanged)DirectionChanged--;
		glcdClearScreen(0);
		DrawFrame();
	    DrawSnake() ;
		DrawFood();
	//	glcdSetFont(_TIMESNEWROMAN_SIZE8);
	//	glcdPutValueFine(JointPointer,0,0);
	//	glcdPutValueFine(WormLength,8,0);
	//	glcdPutValueFine(xRandom,70,2);
//		glcdPutValueFine(TMR1L,70,15);
	}
	glcdRefreshDisplay180(0);
	}
}

#ifdef _SIMPLE
unsigned char HandleWormKeys(unsigned char key)
{
	switch(key)
	{
		case _BTN_ESC: 
		case _KEY_ENTER:return 0;
		case _BTN_UP:
			switch(Direction)
			{
			case 1:	
			case 2: Direction=4; break;
			case 3:	
			case 4: Direction=1; break;
			}

			return 1;
		case _BTN_DOWN:
			switch(Direction)
			{
			case 1:
			case 2: Direction=3; break;
			case 3:
			case 4: Direction=2; break;
			}

		default:	return 1;
	}
}
#else
unsigned char HandleWormKeys(unsigned char key)
{
	if(JointPointer<(_JOINTBUFFERSIZE-1))
	{
	switch(key)
	{
		case _BTN_ESC:
		case _KEY_ENTER: return 0;
		case _BTN_UP:
		//	if((HeadPosX%3)||(HeadPosY%3)) return 2;
			switch(Direction)
			{
			//case 1: 
			//case 2: Direction=4; break;
			case 3:
			case 4: Direction=1; break;
			}
			DirectionChanged=1;
			break;
		case _BTN_DOWN:
		//	if((HeadPosX%3)||(HeadPosY%3)) return 2;
			switch(Direction)
			{
			//case 1: 
			//case 2: Direction=3; break;
			case 3:
			case 4: Direction=2; break;
			}
			DirectionChanged=1;
			break;
//
#define _USE_LEFTRIGHT
#ifdef _USE_LEFTRIGHT
		case _BTN_LEFT:
			switch(Direction)
			{
			case 1:
			case 2: Direction=4; break;
			//case 3:
			//case 4: Direction=2; break;
			}
			DirectionChanged=1;
			break;
		case _BTN_RIGHT:
			switch(Direction)
			{
			case 1:
			case 2: Direction=3; break;
			//case 3:
			//case 4: Direction=2; break;
			}
			DirectionChanged=1;
			break;
#endif
//
		case _BTN_ENTER: if(!gameState) return 2; else addlength+=10; return 1;
		default:	return 1;
	}
	AddJoint(HeadPosX,HeadPosY);
	}
	return 1;
}
#endif
void AddJoint(unsigned char x, unsigned char y)
{
	
		JointPointer++;
		JointBufferX[JointPointer]=x;
		JointBufferY[JointPointer]=y;

}
//maybe this is unnecessary..
void RemoveJoint()
{
	unsigned char i;
	if(!JointPointer) return;
	for(i=0;i<JointPointer;i++)
	{
		JointBufferX[i]=JointBufferX[i+1];
		JointBufferY[i]=JointBufferY[i+1];
	}
	JointPointer--;
}

void DrawSnake(void)
{
	unsigned char temp=JointPointer,length;
	//Draw head
	if(addlength)
	{
		if(WormLength<255) WormLength++;
		addlength--;
	}
	length=glcdFixedLine(HeadPosX,HeadPosY,JointBufferX[temp],JointBufferY[temp],WormLength);
	while(1)
	{	
		if(!temp) break;
		if(!(length=glcdFixedLine(JointBufferX[temp],JointBufferY[temp],JointBufferX[temp-1],JointBufferY[temp-1],length)))
		{
			 if(temp>1) RemoveJoint();
			 break;
		}	
		temp--;
	}
}

void DrawFrame(void)
{
		unsigned char temp;
		for(temp=0;temp<101;temp++) 
		{
			 glcdSetPixel(temp,0);
			 glcdSetPixel(temp,31);
		}
		for(temp=0;temp<32;temp++)
		{
			glcdSetPixel(0,temp);
			glcdSetPixel(100,temp);
		}
}

void DrawFood(void)
{
	glcdSetPixel(FoodPosX+1,FoodPosY);
	glcdSetPixel(FoodPosX-1,FoodPosY);
	glcdSetPixel(FoodPosX,FoodPosY+1);
	glcdSetPixel(FoodPosX,FoodPosY-1);
}
unsigned char CheckFoodCollision(void)
{
	unsigned char temp=0;
	if((HeadPosX==FoodPosX+1)&&(HeadPosY==FoodPosY)) temp=1;
	if((HeadPosX==FoodPosX-1)&&(HeadPosY==FoodPosY)) temp=1;
	if((HeadPosX==FoodPosX)&&(HeadPosY==FoodPosY+1)) temp=1;
	if((HeadPosX==FoodPosX)&&(HeadPosY==FoodPosY-1)) temp=1;
	if(temp)
	{
		addlength+=_INCREMENT;
		do
		{	
			WREG=FoodPosX;
			FoodPosX=Randomize(FoodPosY);
			while(FoodPosX>99) FoodPosX=divide(FoodPosX,3);
			if(FoodPosX<2) FoodPosX=2;
			WREG=FoodPosY;
			FoodPosY=Randomize(FoodPosX);
			if(FoodPosY<2) FoodPosY=2;
			while(FoodPosY>31) FoodPosY=divide(FoodPosY,5);
		}
		while(glcdGetPixel(FoodPosX,FoodPosY));
		return 1;
	}
	return 0;
}

