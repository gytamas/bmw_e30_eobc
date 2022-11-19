//header dile for mcp7940.c


#define _MCP7940_I2C_ADDRESS 0xDE   //b'1101 1110

unsigned char TestMCP7940(unsigned char);
unsigned char ReadByteMCP7940(unsigned char);
void WriteByteMCP7940(unsigned char, unsigned char);
void HandleRTC_ISR();
void ReadTime();
void SetTime();
void ReadTimeToBuffer(unsigned char*);
void ReadDate();

