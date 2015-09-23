#ifndef MAX5513_H_INCLUDED
#define MAX5513_H_INCLUDED
                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Macros.h"

#include "Timer.h"  


#include "Analog.h" 
// http://www.digikey.ca/product-detail/en/MAX5513EUA%2B/MAX5513EUA%2B-ND

/// 16 bit communication 
/// 4 -        8 -         4
/// ctrlbits   data bits   subbits

// all four modes allow for VREF modification 
#define    MAX5513_CTL_LOAD           0x0F    // Loads values from internal shift reg to output
#define    MAX5513_CTL_ENTER_SHUTDOWN 0x0E    // output set to high impedence
#define    MAX5513_CTL_NRML_MODE      0x0D    // DACS output REFLECT contents in dac reg
#define    MAX5513_CTL_ENTER_STANDBY  0x0C


#define    MAX5513_CTL_LOAD_A         0x09   // immed
#define    MAX5513_CTL_LOAD_B         0x0B   // immed


#define    MAX5513_VREF_1_2V          0x00
#define    MAX5513_VREF_1_9V          0x40
#define    MAX5513_VREF_2_4V          0x80
#define    MAX5513_VREF_3_8V          0xC0


#define    MAX5513_DDR    DDRP
#define    MAX5513_PORT   PTP
#define    MAX5513_CS     PTP_PTP3_MASK


#define MAX5513_INIT_DDR() { SETBIT(MAX5513_DDR,MAX5513_CS );}
#define MAX5513_CS_LOW()  {  CLEARBIT( MAX5513_PORT,MAX5513_CS );	} 
#define MAX5513_CS_HIGH() {  SETBIT( MAX5513_PORT, MAX5513_CS );	}	


#define MAX5513_ON_3_4V() { MAX5513_Send_CMD(MAX5513_CTL_NRML_MODE,MAX5513_VREF_3_8V); } 
#define MAX5513_ON_1_2V() { MAX5513_Send_CMD(MAX5513_CTL_NRML_MODE,MAX5513_VREF_1_2V); } 

 // device will wake 
#define MAX5513_OFF() { MAX5513_Send_CMD(MAX5513_CTL_ENTER_SHUTDOWN, 0x00); } 


unsigned char MAX5513_Set_Chan(unsigned char vout, unsigned char channel);
unsigned char MAX5513_Send_CMD(unsigned char command, unsigned char data);

unsigned char MAX5513_Set_Read(unsigned char vout, unsigned char channel, unsigned char analog_in_pin);

#endif 