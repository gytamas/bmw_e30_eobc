//header file for grapghics.c


void glcdLine(unsigned char,unsigned char,unsigned char,unsigned char);
unsigned char glcdFixedLine(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char);
void glcdDrawBarFixedWidth(unsigned char, unsigned char, unsigned char );
void glcdPutValueFine(unsigned char,unsigned char, unsigned char,unsigned char); 
void ConvertValue(unsigned char,unsigned char *);
void glcdDrawHorizontalBar_StyleA(unsigned char,unsigned char,unsigned char,unsigned char);
void glcdPutFloatFine(unsigned int,unsigned char,unsigned char,unsigned char);
//void ConvertValue2(unsigned char,unsigned char *,unsigned char);
void ConvertValue2(unsigned int,unsigned char *,unsigned char);

//extern  char FrameBuffer[_FRAMESIZE_180];

