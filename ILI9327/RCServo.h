#ifndef RCSERVO_H_INCLUDED 
#define RCSERVO_H_INCLUDED

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



///

#define RCSERVO_PULSE_LENGTH   20 // 20 ms total pulse length 

/// Defines for PULSE in us 
#define RCSERVO_ANGLE_90    2400 
#define RCSERVO_ANGLE_0     1500  
#define RCSERVO_ANGLE_N90    600  

#define RCSERVO_OUTPUT_PIN  PTIT_PTIT2     //mask 
#define RCSERVO_OUTPUT_PORT PTIT
#define RCSERVO_OUTPUT_DDR  DDRT    //


#define RCSERVO_ENABLE_DDR   SETBIT(RCSERVO_OUTPUT_DDR, RCSERVO_OUTPUT_PIN); 


#endif    
