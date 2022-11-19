//header file for PCF8548.c

//extern static char FrameBuffer[];
#define _USE_VARIABLE_TEXT_SIZE
#define _TIMESNEWROMAN_SIZE10 0x01
#define _TIMESNEWROMAN_SIZE22 0x02
#define _TIMESNEWROMAN_SIZE8  0x00 //hence the smallest
#define _TIMESNEWROMAN_SIZE8_BOLD 0x03
#define _ARIAL_SIZE12_BOLD 0x04
#define _UNKNOWFONT 0xFF
#define _PCF8558_DEV_ADDR 0x78
//#define _FRAMESIZE 505 Won't fit properly!
#define _FULL_FRAMESIZE 505
#define _FRAMESIZE_180 404

signed char PCF8548_Init();
signed char i2cMasterSendMessage(unsigned char, unsigned char);
void glcdClearScreen(unsigned char);
signed char glcdRefreshDisplay180(unsigned char );
void glcdPutString(const rom unsigned char *);
signed char glcdPutLogo1();
void glcdSetFont(unsigned char);
signed char glcdPutCharFine(unsigned char, unsigned char,unsigned char );
void glcdPutStringDynamic(unsigned char *);
unsigned char InverseOrder(unsigned char );
void glcdPutImage(unsigned rom char *,unsigned char, unsigned char);
void glcdSetPixel(unsigned char,unsigned char);
void glcdInvertPixel(unsigned char,unsigned char);
void glcdClearPixel(unsigned char,unsigned char);
unsigned char glcdGetPixel(unsigned char,unsigned char);
signed char glcdClearInitial(void);
void glcdHighlightLine(unsigned char);
signed char glcdPutLogo(unsigned rom char *);




