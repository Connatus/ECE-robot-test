

#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED
                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


/*******************************************/
// Processor Modules 
/*******************************************/
#include "SPI.h"     // works great
#include "RS232.h"  // null modem works // needs impr
#include "Analog.h" // 10 - 8 bit  0 = 10  8
#include "Timer.h"  // timer and delay

/*******************************************/
// Board Modules 
/*******************************************/
#include "MAX5513.h"   // DAC 
#include "Accelerometer.h"
#include "RC_Servo.h" // timer n stuff 
#include "MCP23009.h" // Not complete //   -- doesnt work properly 

#define     ENC_A    PTT_PTT0_MASK  // - Enable Encoder A // pull high
#define     ENC_B    PTT_PTT1_MASK  // - Enable Encoder B // pull high 

#define     ENCODER_PORT    PTT
#define     ENCODER_DDR     DDRT



#define     ENC_A_CHECK         CHECKBIT(PTT,ENC_A)
#define     ENC_B_CHECK         CHECKBIT(PTT,ENC_B)

#define     ENC_DDR_ENABLE      CLEARBIT(DDRT,(ENC_A || ENC_B));


#define TCTL_1_2 ((*(volatile word * const) & TCTL1))
#define SET_OC_ACTION(chnl,action)  \
  FORCE_WORD(TCTL_1_2, 0x03 << (chnl*2), ( (action) << ((chnl)*2)))
  
  
#define FORCE_WERD(reg,value)   (reg) = ((value) & 0xFFFF)
                                          



#define ENCODER_LEFT_TIMER			TC0
#define ENCODER_RIGHT_TIMER			TC1
#define WATCHDOG_TIMER			  	TC4 /// doesn't use pin

  


// TCO FLAGS


extern unsigned int EN_L_Pulse_Flag;  
extern unsigned int EN_R_Pulse_Flag;  
extern volatile int L_TIMER;
extern volatile int R_TIMER; 
extern unsigned volatile int L_Counter;
extern unsigned volatile int R_Counter; 
     
     
     
     
extern volatile int WATCH_L_COUNTER;
extern volatile int WATCH_R_COUNTER;
extern volatile int WATCH_DOG_FLAG; 




void ENCODER(void); 
void Encoder_Init(void); 

// stepper motor driver 
#endif /* ENCODER_H_INCLUDED */