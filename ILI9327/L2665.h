#ifndef L2665_H_INCLUDED
#define L2665_H_INCLUDED
                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


     
/*******************************************/
// LCD Libraries
/*******************************************/
#include "ILI9327.h" // 
#include "LCD_Draw.h"    // 
#include "LCD_Config.h" // VERY IMPORTANT CONTROLS ALL LCD RELATED LIBRARIES //
#include "Touch.h"
#include "Terminal.h" // printf 
#include "SD.h" 
#include "BMP.h" // functional but garbage 

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
#include "MAX5513.h"   // works fine  
#include "Accelerometer.h"  // works with menu
#include "RC_Servo.h" // timer n stuff
#include "L2665.h" // needs speed calc with the encoder 
#include "L293DD.h" // works fine // needs home calc  
#include "MCP23009.h" // Not complete //   -- doesnt work properly 
#include "Encoder.h"  // works 
/*******************************************/
// Macros N stuffs
/*******************************************/    
#include "macros.h"



/*******************************************/
// DC MOTOR DEFINES AND MACROS 
/*******************************************/    

// A = LEFT MOTOR   B = RIGHT MOTOR
#define     DCM_1A     PORTB_BIT2_MASK  // - motor1A 
#define     DCM_2A     PORTB_BIT0_MASK  // - motor2A
 
#define     DCM_1B     PORTB_BIT3_MASK  // - motor1B 
#define     DCM_2B     PORTB_BIT1_MASK  // - motor2B 

#define     DCM_STIN_ENABLE_A   PTP_PTP4_MASK  // motor Enable A
#define     DCM_STIN_ENABLE_B   PTP_PTP5_MASK  // motor Enable B

 

#define DCM_DDR                  DDRB
#define DCM_ENABLE_DDR           DDRP
#define DCM_ENABLE_PORT          PTP 
#define DCM_PORT                 PORTB 

#define DCM_LEFT_PWM             PWMDTY5
#define DCM_RIGHT_PWM            PWMDTY4



#define DCM_INIT_ENABLE_DDR()   {SETBIT(DCM_ENABLE_DDR,(DCM_STIN_ENABLE_B| DCM_STIN_ENABLE_A));   }
#define DCM_INIT_DDR()          {SETBIT(DCM_DDR,(DCM_1A |DCM_1B |DCM_2A |DCM_2B));   }

#define DCM_ENABLE_A              SETBIT(DCM_ENABLE_PORT,(DCM_STIN_ENABLE_A))
#define DCM_ENABLE_B              SETBIT(DCM_ENABLE_PORT,(DCM_STIN_ENABLE_B))
#define DCM_DISABLE_A             CLEARBIT(DCM_ENABLE_PORT,(DCM_STIN_ENABLE_A))
#define DCM_DISABLE_B             CLEARBIT(DCM_ENABLE_PORT,(DCM_STIN_ENABLE_B))


#define DC_L_SETSPEED_PERCENTAGE(percentage)    ( DCM_LEFT_PWM   = PWM_PERCENTAGE_CONVERSION((percentage%101)))
#define DC_R_SETSPEED_PERCENTAGE(percentage)    ( DCM_RIGHT_PWM  = PWM_PERCENTAGE_CONVERSION((percentage%101)))


#define DCM_1A_ENABLE               SETBIT(DCM_PORT, DCM_1A)
#define DCM_1B_ENABLE               SETBIT(DCM_PORT, DCM_1B)                             
#define DCM_1A_DISABLE              CLEARBIT(DCM_PORT, DCM_1A)                            
#define DCM_1B_DISABLE              CLEARBIT(DCM_PORT, DCM_1B)
                                                            
#define DCM_2A_ENABLE               SETBIT(DCM_PORT, DCM_2A)
#define DCM_2B_ENABLE               SETBIT(DCM_PORT, DCM_2B)                             
#define DCM_2A_DISABLE              CLEARBIT(DCM_PORT, DCM_2A)                            
#define DCM_2B_DISABLE              CLEARBIT(DCM_PORT, DCM_2B)
                                                            

#define DC_1_REVERSE_DIRECTION            {   DCM_1A_DISABLE;  DCM_2A_ENABLE;   }        // DCM_1B_ENABLE;eeds to do work on 1A and 2A
#define DC_1_FORWARD_DIRECTION            {   DCM_1A_ENABLE;   DCM_2A_DISABLE;  }   

#define DC_2_REVERSE_DIRECTION            {   DCM_1B_DISABLE;  DCM_2B_ENABLE;  }   
#define DC_2_FORWARD_DIRECTION            {   DCM_1B_ENABLE;   DCM_2B_DISABLE;  }  

#define DC_L_REVERSE_DIRECTION            {   DCM_1A_DISABLE;   DCM_2A_ENABLE;    }   
#define DC_L_FORWARD_DIRECTION            {   DCM_1A_ENABLE;    DCM_2A_DISABLE;   }   

#define DC_R_REVERSE_DIRECTION            {   DCM_1B_DISABLE;   DCM_2B_ENABLE;   }   
#define DC_R_FORWARD_DIRECTION            {   DCM_1B_ENABLE;    DCM_2B_DISABLE;  }   
/// MAKE A BREAK 
 
#define DC_L_BREAK            {   DCM_2A_DISABLE;  DCM_2B_DISABLE;  }   
#define DC_R_BREAK            {  DCM_1A_DISABLE;   DCM_1B_DISABLE;    }  


#define DC_ENABLE_A      0x10
#define DC_ENABLE_B      0x20

/*******************************************/
// PWM MACROS AND DEFINES 
/*******************************************/    

   
#define PWM_PORT               PTP
#define PWM_DDRP               DDRP

#define PWM_ENABLE             0b00110000// ; set all outputs high to enable pwm 
 

#define PWM_CLOCKPOL           0b00110000 
#define PWM_CLOCKSAB           0b00110000 // USE SA + SB CLOCKS FOR MOTOR
#define PWM_CLOCK              0b00000111 //  
#define PWM_CLOCKSA            16   // ; divide clock by  512*7       //period =   130ms

#define PWM_CENTER_EN          0b00000000

#define PWM_DUTY_45            182
#define PWM_DUTY_16            255      /// Each value = approx 0.509ms

#define PWM_DUTY_45_10         18
#define PWM_DUTY_45_60         108


void PWM_INIT(void);
void DCM_INIT(void);
unsigned char PWM_PERCENTAGE_CONVERSION(unsigned char percentage); 





   // DC motor Driver 


#endif /* L2665_H_ */