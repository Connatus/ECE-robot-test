#ifndef MCP23009_H_INCLUDED
#define MCP23009_H_INCLUDED
                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
   // 8Bit IO expander with open drain outputs  //
   //http://ww1.microchip.com/downloads/en/DeviceDoc/20002121C.pdf 
  
// MAX CLOCK IS 16MHz // 
// Clock from spi is 4MHz MAx
/* 
 NOTE THE GPIO DDR 1 = input 0 = output 

 CS     ---________________---
 MOSI   ---(OPCODE)(REG)___----

*/
/// Register Addresses


#define     MCP23009_OPCODE_WRITE     0x40   // needs RW
#define     MCP23009_OPCODE_READ      0x41   // needs RW 
/// 1 - read
 ///0 = write


 
#define     MCP23009_IODIR      0x00   // Controls the direction of the IO register // 0 output - 1 input // - opposite of HCS12
#define     MCP23009_IPOL       0x01   // Change polarity reg // 0 gpio has same logic  // 1 gpio has opposite logic 
#define     MCP23009_GPINTEN    0x02   // Interrupt on change // -- 0 gpio disabled interrupt // 1 enabled interrupt
#define     MCP23009_DEFVAL     0x03
#define     MCP23009_INTCON	   	0x04
#define     MCP23009_IOCON      0x05
#define     MCP23009_GPPU       0x06  // Pull up resistor configures puill up -- 0 pull up disabled 1-- pull up enabled. 
#define     MCP23009_INTF       0x07  // interrupt flag reg 
#define     MCP23009_INTCAP     0x08  // READ ONLY interrupt caputre register   /// flag set immediatly when interrupt is had
#define     MCP23009_GPIO       0x09  // GPIO register 0-  logic low   1 - Logic-high  // modifies the OLAT reg automaticlly 
#define     MCP23009_OLAT       0x0A  

#define     MCP23009_CS_               PTJ_PTJ6_MASK  
#define     MCP23009_INTERRUPT_        PTJ_PTJ7_MASK  

#define     MCP23009_PORT              PTJ
#define     MCP23009_DDR               DDRJ

/* For all registers it is 100% necessary for the previous state to be read and 
placed back inside/.. 
*/
  
  
  /// will need to read current IO register values //
#define   MCP23009_DDR_OUTPUT(pin) { MCP23009_WRITE(Register, Data); }  /// write spi function     
#define   MCP23009_DDR_INPUT(pin)  { MCP23009_WRITE(Register, Data); }  

#define   MCP23009_WRITE(Register, Data); {return; }// not sure about this one as the spi from this device might be 16 bits // //{ }

#define    MCP23009_INIT_DDR() { SETBIT(MCP23009_DDR, (MCP23009_INTERRUPT_ |MCP23009_CS_  )  );}
#define    MCP23009_CS_LOW()  {  CLEARBIT( MCP23009_PORT,MCP23009_CS_  );	} 
#define    MCP23009_CS_HIGH() {  SETBIT(MCP23009_PORT, MCP23009_CS_ );	}	


/// Interrupt is an input pin


unsigned char MCP23009_Register_Read(unsigned char Register);
unsigned char MCP23009_Register_Write(unsigned char Register, unsigned char Data);
unsigned char MCP23009_TEST(void);
  
  

#endif /* SWITCHES_ */