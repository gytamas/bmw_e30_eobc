#include <p18f25k22.h>

unsigned char int_EEPROM_getc(unsigned char address)
{
    EEADR=address;
    EECON1bits.EEPGD= 0; // 0 = Access data EEPROM memory
    EECON1bits.CFGS = 0; // 0 = Access Flash program or DATA EEPROM memory
    EECON1bits.RD   = 1; // EEPROM Read
    return EEDATA;       // return data
}

void Write_EEPROM(unsigned char address, unsigned char data) 
{
	 EEADR = address; // Data Memory Address to read
	 EEDATA = data; // Data Memory Value to write
	 EECON1bits.EEPGD = 0; // Point to DATA memory
	 EECON1bits.CFGS = 0; // Access program FLASH or Data EEPROM memory
	 EECON1bits.WREN = 1; // Enable writes
	 // required sequence
	 INTCONbits.GIE = 0; // Disable interrupts
	 EECON2 = 0x55; // Write 55h
	 EECON2 = 0xaa; // Write AAh
	 EECON1bits.WR = 1; // Set WR bit to begin write
	 INTCONbits.GIE = 1; // Enable interrupts
	 while (!PIR2bits.EEIF);
	 PIR2bits.EEIF = 0; // clear EEPROM write operation interrupt flag bit
	 EECON1bits.WREN = 0; // disable writes on write complete (EEIF set)
}
 