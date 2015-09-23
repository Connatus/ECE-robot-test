

#ifndef L293DD_H_INCLUDED
#define L293DD_H_INCLUDED
                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


/*******************************************/
// Macros N stuffs
/*******************************************/    
#include "macros.h"

// STEPPER MOTOR DEFINES //
#define     STM_1A     PTT_PTT4_MASK  // - motor1A 
#define     STM_1B     PTT_PTT5_MASK  // - motor1B 

#define     STM_2A     PTT_PTT6_MASK  // - motor2A 
#define     STM_2B     PTT_PTT7_MASK  // - motor2B 

#define     STM_DDR           DDRT
#define     STM_PORT          PTT

#define     STMOTOR_INIT_DDR()          {SETBIT(STM_DDR,(STM_1A |STM_1B |STM_2A |STM_2B));   }


// STEPPER ENABLE DEFINES // 
#define     STM_ENABLE   PTP_PTP7_MASK  // motor Enable 
#define STM_ENABLE_DDR    DDRP 
#define STM_PORT_ENABLE   PTP 


#define STMOTOR_INIT_ENABLE_DDR()   {SETBIT(STM_ENABLE_DDR,(STM_ENABLE));   }
#define STMOTOR_ENABLE()             {SETBIT(STM_PORT_ENABLE,(STM_ENABLE));}


// STEPPER SWITCH DEFINES // 
#define     SWITCH_RIGHT_     PTS_PTS3_MASK  
#define     SWITCH_LEFT_      PTS_PTS2_MASK
#define     SWITCH_DDR        DDRS
#define     SWITCH_PORT       PTS 

#define     SWITCH_INIT_DDR()  {CLEARBIT(SWITCH_DDR ,(SWITCH_LEFT_ | SWITCH_RIGHT_));   }
#define     SWITCH_CHECK_L()    CHECKBIT(SWITCH_PORT,SWITCH_LEFT_ )      // used for checking right press 
#define     SWITCH_CHECK_R()    CHECKBIT(SWITCH_PORT,SWITCH_RIGHT_)      // checks left press // when button is pressed gnd is sent to pin
/// END OF STEPPER SWITCH DEFINES //  


// STEPPER VARIABLE AND DEFINES 
#define STEPPER_SET_SPEED(SPEED)         ((Stepper_Speed) = (SPEED)) 

#define B_FSF                  2   //bipolar full step forward
#define B_FSB                  -2  //bipolar full step backward 
#define B_HSF                  1   //bipolar half step forward
#define B_HSB                  -1  //bipolar half step backward

/* 
   0x80,  0xA0,  0x20,  0x60,  0x40,  0x50,  0x10,  0x90

*/             

#define STEPPER_SPEED_FAST        300
#define STEPPER_SPEED_MEDIUM      500
#define STEPPER_SPEED_SLOW        1000 

#define STEPPER_FULL_SWEEP_DEGREES 180 // 180 deg is full range of motion before switches are hit //
#define STEPPER_FULL_SWEEP_STEPS   197 // ish 

#define STEPPER_WATCHDOG_TIMER				TC7 /// doesn't use pin



extern volatile unsigned char Stepper_Direction_Flag; 
extern volatile unsigned char Stepper_WholeStep_Flag;
extern volatile unsigned int  Stepper_Count_Steps; 
extern volatile unsigned int  Stepper_Steps;
extern volatile unsigned int  Stepper_Speed; // delay by 4us idealy set inbetween 300-1000
extern volatile char STEPPER_MOTOR_STEP; 

                       

unsigned char STMOTOR_TEST(void);
unsigned char STMOTOR_FIND_HOME(void);
unsigned char STMOTOR_INIT(void);

unsigned char STMOTOR_MOVE_DEGREES(unsigned char degrees,  unsigned char Direction); 
unsigned char STMOTOR_MOVE_DEGREES_FROM_FAR_RIGHT(unsigned char degrees);       
unsigned char STMOTOR_COMPLETE_MOTION(unsigned char Steps, unsigned char Direction);





// stepper motor driver 
#endif /* L293DD_H_ */