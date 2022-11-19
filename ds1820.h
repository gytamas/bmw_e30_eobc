//header file for ds1820.c

#define DQ TRISAbits.TRISA5;

unsigned char ds1820_Reset();
void ds1820_SendByte(unsigned char);
unsigned char ds1820_ReadByte();
void ds1820_writeOne();
void ds1820_writeNull();
unsigned int ds1820_ReadTempSimple();
unsigned int ds1820_GetTemp(unsigned int );

