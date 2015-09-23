/*
 * Test Library 
 *
 * Created: 5/30/2013 4:22:36 PM
 *  Author: mfolz
 */ 


#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
                                            
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

// geting close 
#include "Assw9.h"



/*  Board_Function
0: RS232                     - RS232 INPUT TERMINAL (Disable Interrupts)
1: Stepper Motor             - USE ISR //  PT4- PT7
2: RC Servo                  - // basically the assignment //
3: DC Motor                  -  Open-loop Motor() // isr driven  DCM_STIN_ENABLE_A   PP4 - PP5
4: DC Motor Encoder          -  // Measure speeds accuratly 
5: RS-232                    - // 
6: Serial Communications     - // Just a simple terminal program 
7: ADC & Accelerometer       -  //Function to read all 3 axes of the accelerometer and return in an array (passed in as a parameter) as engineering units with fixed point representation.   
8: DAC (via SPI)             -  //   use dac tste
9: LCD                       -  // already done // 
*/ 

/*
  unsigned char RS232_ECD(void);
  unsigned char Stepper_Motor_ECD(void);
  unsigned char RC_Servo_ECD(void);
  unsigned char DC_Motor_ECD(void);
  unsigned char DC_Motor_Encoder_ECD(void);
  unsigned char RS232_ECD(void);
  unsigned char SerialTerminal_ECD(void);
  unsigned char Accelerometer_ECD(void);
  unsigned char DAC_ECD(void);
*/ 

/*
  return vars must be sent!
*/

       
/// NEEDS TO BE OUTSIDE OF ROUTINE // STACK BLOWN OTHERWISE 
extern unsigned char Local_Message_Storage_Array_RS232[RS232_MESSAGE_STORAGE_LENGTH]; 


unsigned char Ping_ECD( unsigned int Data_length);
unsigned char Stepper_Motor_ECD( unsigned int Data_length);
unsigned char RC_Servo_ECD( unsigned int Data_length); 
unsigned char DC_Motor_ECD( unsigned int Data_length); 
unsigned char DC_Motor_Encoder_ECD( unsigned int Data_length);
unsigned char RS232_ECD(unsigned char COM_PORT);
unsigned char SerialTerminal_ECD(void);
unsigned char Accelerometer_ECD(unsigned char *Data_Array);
unsigned char Camera_ECD( unsigned int Data_length);

void Test_RS232(void);
void testanal(void);                    
void testLibrary(void);
  

void ILI9327_INIT(void);
void Touch_Test(void);

void MAX5513_Test(void);
void Accelerometer_Test(void);

#endif /* TEST_H_ */


