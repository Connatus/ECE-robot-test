#ifndef RCSERVO_H_INCLUDED 
#define RCSERVO_H_INCLUDED

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
 #include "Timer.h"

/*******************************************/
// Macros N stuffs
/*******************************************/    
#include "macros.h"      


#define RCSERVO_PULSE_LENGTH   20 // 20 ms total pulse length 

/// Defines for PULSE in us 
#define RCSERVO_OUTPUT_PIN  PTIT_PTIT2_MASK     //mask 
#define RCSERVO_OUTPUT_PORT PTIT
#define RCSERVO_OUTPUT_DDR  DDRT    //


 /// PT0 // - 

#define RCSERVO_ENABLE_DDR   SETBIT(RCSERVO_OUTPUT_DDR, RCSERVO_OUTPUT_PIN); 
// must be a free running counter /// 0x0000 - 0xFFFF wraps back to 0x0000 - 



#define     PULSE_MAX         300 //2400us
#define     PULSE_MIN         75  //600us 
#define     RC_DEGREE_RANGE   135 // 

extern volatile unsigned char   OC2_Output_Flag; 
//volatile unsigned int    Pulse_High =75;
extern volatile unsigned int    Pulse_High;
extern volatile unsigned int    Pulse_Low;   
  

unsigned char RCServo_Set_Degrees(unsigned char degrees); 
unsigned int RCServo_Degrees_Calulate(unsigned char degrees);
unsigned int RCServo_Set_Degrees_Sweep(unsigned char degrees); 

   /*

#define TCTL_1_2 ((*(volatile word * const) & TCTL1))
#define SET_OC_ACTION(chnl,action)  \
  FORCE_WORD(TCTL_1_2, 0x03 << (chnl*2), ( (action) << ((chnl)*2)))
  
  
                                          
//  600us , 1500us, 2400us 
#define STEPPER_MIN_VALUE	75
#define STEPPER_MIN_PERCENTAGE 25
#define STEPPER_MAX_PERCENTAGE 75

#define STEPPER_OUTPUT_TIMER  	TC2
#define SIGNAL_INPUT_TIMER			TC0
#define WATCHDOG_TIMER				TC7 /// doesn't use pin

  


// TCO FLAGS
volatile int TC0_Input_Flag; 
volatile int Percentage_Out;
volatile long Percentage;

unsigned char TC0_Capture_Flag;  
unsigned char TCO_Input_Count; 
unsigned int Time_Low[2];
unsigned int Pulse_Length;
unsigned int Pulse_Width;
unsigned int Pulse_Flag;  
unsigned int Timer_Difference;  
unsigned int Start_Timer_Val;
unsigned int End_Timer_Val;
unsigned int  Timer_Val; 
     
unsigned long Pulse_Calculate;            

/// OC2 Flags 
unsigned char OC2_Output_Flag;
volatile int Kill_OC2; 
volatile int Pulse_Low;
volatile int Pulse_High;


/// Watch Dog Flags 
volatile int Watch_Dog_TimeOut_Flag; 
volatile int Watch_Dog_Invalid_Flag; 
 
 
 
 // Local Flags  and Vars 
int Valid_Data_Flag; 
int Input_Timeout; 
int Local_Kill_OC2; 

unsigned int Percentage_Main;  
unsigned long Pulse_High_Main; 


                   */


//void capture_input_timer(void);
//void RC_Servo_Assignment(void);





#endif    
