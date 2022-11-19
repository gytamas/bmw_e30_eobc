#include "i2c_data.h"
#include "p18f25k22.h"
#include <delays.h>
/**********************************************************************
*     Function Name:    signed char SWWriteI2C(unsigned char data_out)*
*     Return Value:     error condition if bus error occurred         *
*     Parameters:       Single data byte for I2C bus.                 *
*     Description:      This routine writes a single byte to the      *
*                       I2C bus.                                      *
**********************************************************************/
signed char SWPutcI2C( unsigned char data_out )
{
  BIT_COUNTER = 8;                // initialize bit counter
  I2C_BUFFER = data_out;          // data to send out
  SCLK_LAT = 0;                   // set latch to 0
                                 
  do
  {
    if ( !SCLK_PIN )              // test if clock is low
    {                             // if it is then ..
      if ( Clock_test( ) )        // wait on clock for a short time
      {
        return ( -1 );            // return with error condition      
      }
    }

    else 
    {
     I2C_BUFFER &= 0xFF;          // generate movlb instruction
      _asm
      rlcf I2C_BUFFER,1,1         // rotate into carry and test  
      _endasm

      if ( STATUS & 0x01 )        // if carry set, transmit out logic 1
      {
       CLOCK_LOW;                 // set clock pin output to drive low
       DATA_HI;                   // release data line to float high 
       Delay1TCY();
            // user may need to modify based on Fosc
       CLOCK_HI;                  // release clock line to float high 
       Delay1TCY();  
            // user may need to modify based on Fosc
      }
      else                        // transmit out logic 0
      {
        CLOCK_LOW;                // set clock pin output to drive low
        DATA_LAT = 0;             // set data pin latch to 0
        DATA_LOW;                 // set data pin output to drive low 
        Delay1TCY();  			  // user may need to modify based on Fosc
        CLOCK_HI;                 // release clock line to float high 
        Delay1TCY();			  // user may need to modify based on Fosc
      }

     BIT_COUNTER --;              // reduce bit counter by 1
    }
  } while ( BIT_COUNTER );        // stay in transmit loop until byte sent 

  return ( 0 );                   // return with no error
}

signed char SWPutcI2C180( unsigned char data_out )
{
  BIT_COUNTER = 8;                // initialize bit counter
  I2C_BUFFER = data_out;          // data to send out
  SCLK_LAT = 0;                   // set latch to 0
                                 
  do
  {
    if ( !SCLK_PIN )              // test if clock is low
    {                             // if it is then ..
      if ( Clock_test( ) )        // wait on clock for a short time
      {
        return ( -1 );            // return with error condition      
      }
    }

    else 
    {
     I2C_BUFFER &= 0xFF;          // generate movlb instruction
      _asm
      rrcf I2C_BUFFER,1,1         // rotate into carry and test  
      _endasm

      if ( STATUS & 0x01 )        // if carry set, transmit out logic 1
      {
       CLOCK_LOW;                 // set clock pin output to drive low
       DATA_HI;                   // release data line to float high 
       Delay1TCY();              // user may need to modify based on Fosc
       CLOCK_HI;                  // release clock line to float high 
       Delay1TCY();              // user may need to modify based on Fosc
      }
      else                        // transmit out logic 0
      {
        CLOCK_LOW;                // set clock pin output to drive low
        DATA_LAT = 0;             // set data pin latch to 0
        DATA_LOW;                 // set data pin output to drive low 
        Delay1TCY();             // user may need to modify based on Fosc
        CLOCK_HI;                 // release clock line to float high 
        Delay1TCY();             // user may need to modify based on Fosc
      }

     BIT_COUNTER --;              // reduce bit counter by 1
    }
  } while ( BIT_COUNTER );        // stay in transmit loop until byte sent 

  return ( 0 );                   // return with no error
}

/********************************************************************
*     Function Name:    signed char SWAckI2C(void)                  *
*     Return Value:     error condition status                      *
*     Parameters:       void                                        *
*     Description:      This function generates a bus acknowledge   *
*                       sequence.                                   *
********************************************************************/
signed char SWAckI2C( void )
{
  SCLK_LAT = 0;                   // set clock pin latch to 0  
  CLOCK_LOW;                      // set clock pin to output to drive low
  DATA_HI;                        // release data line to float high 
  Delay1TCY();                   // user may need to modify based on Fosc
  CLOCK_HI;                       // release clock line to float high
//  Delay1TCY();                    // 1 cycle delay
//  Delay1TCY();                    // 1 cycle delay

  if ( DATA_PIN )                 // error if ack = 1, slave did not ack
  {
    return ( -1 );                // return with acknowledge error
  }
  else
  {
    return ( 0 );                 // return with no error
  }
}


/********************************************************************
*     Function Name:    void SWStopI2C(void)                        *
*     Return Value:     void                                        *
*     Parameters:       void                                        *
*     Description:      Send I2C bus stop condition.                *
********************************************************************/
void SWStopI2C( void )
{
  SCLK_LAT = 0;                   // set clock pin latch to 0
  CLOCK_LOW;                      // set clock pin to output to drive low
  DATA_LAT = 0;                   // set data pin latch to 0
  DATA_LOW;                       // set data pin output to drive low
  Delay1TCY();                   // user may need to modify based on Fosc
  CLOCK_HI;                       // release clock pin to float high
  Delay1TCY();                   // user may need to modify based on Fosc
  DATA_HI;                        // release data pin to float high
//  Delay1TCY();                    // user may need to modify based on Fosc
//  Delay1TCY();
}


/********************************************************************
*     Function Name:    void SWStartI2C(void)                       *
*     Return Value:     void                                        *
*     Parameters:       void                                        *
*     Description:      Send I2C bus start condition.               *
********************************************************************/
void SWStartI2C( void )
{
  DATA_LAT = 0;                   // set data pin latch to 0
  DATA_LOW;                       // set pin to output to drive low
  Delay1TCY();                   // user may need to modify based on Fosc
}


