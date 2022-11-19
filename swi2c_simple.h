signed char SWPutcI2C( unsigned char);
signed char SWPutcI2C180( unsigned char);
signed char SWAckI2C( void );
void SWStopI2C( void );
void SWStartI2C( void );
	  
#define  DATA_LOW   TRISCbits.TRISC4 = 0; // define macro for data pin output
#define  DATA_HI    TRISCbits.TRISC4 = 1; // define macro for data pin input
#define  DATA_LAT   LATCbits.LATC4        // define macro for data pin latch GREEN RED
#define  DATA_PIN   PORTCbits.RC4        // define macro for data pin


#define  CLOCK_LOW  TRISCbits.TRISC3 = 0; // define macro for clock pin output
#define  CLOCK_HI   TRISCbits.TRISC3 = 1; // define macro for clock pin input
#define  SCLK_LAT   LATCbits.LATC3        // define macro for clock pin latch
#define  SCLK_PIN   PORTCbits.RC3         // define macro for clock pin



//REMARKS:
// SW_I2C CLOCK line is located at RB1
// SW_I2C DATA line is located at RB0
