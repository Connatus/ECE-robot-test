#ifndef ACCELEROMETER_H_INCLUDED
#define ACCELEROMETER_H_INCLUDED
                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

   // http://www.digikey.ca/product-detail/en/LIS352ARTR/497-11075-1-ND // 
#include "Macros.h"
#include "Analog.h"
 
 
 
/*******************************************/
// SD and FAT Libraries 
/*******************************************/
#include "ff.h" // use FatFs from Elm-Chan.org
#include "ffconf.h"
#include "integer.h"
#include "diskio.h" // use FatFs from Elm-Chan.org (diskio used for disk initialization)
#include "file.h"

/*******************************************/
// Processor Modules 
/*******************************************/
#include "SPI.h"     // garbage 
#include "RS232.h"  // null modem works // needs impr
#include "Analog.h" // 10 - 8 bit 
#include "Timer.h"  // timer and delay


// CONTROLS TEH ENABLING OF INTERRUPTS // 
/// INTERUPTS DONT WORK WELL!!!!!!! /// ITS SHIT COMPLETE SHIT
#define ACCELEROMETER_INTERRUPT 0

#define Accel_Max   850 

#define Accel_G      98               // 2 g = 196 approx         2 g = approx 90degrees
#define Accel_Degree_Val      46    // Accel value is worth .456 degrees 


#define Accelerometer_Tollerance 5 // not in percent but in analog value // approx 1% 
extern unsigned int Accel_X_Zero;//   810 // needs to be in ram 
extern unsigned int Accel_Y_Zero;//   610
extern unsigned int Accel_Z_Zero;//   870
extern unsigned char Accel_Negative_Flags;  // 0000 0111 //  zyx 
 
extern volatile unsigned int anal_x, anal_y, anal_z;
extern  signed int deg_x, deg_y, deg_z; 

void Accelerometer_Read(void); 
void Accelerometer_INIT(void);
void Accelerometer_Test_2(void);
void Accelerometer_Val2Degree(void);
signed int Accelerometer_Calc_Val(unsigned int anal_in, char acc_axis, unsigned int refrence);

signed int * Accelerometer_Read_Values(void);

                  
#define     ACCELEROMETER_CS_NOT    PTP_PTP0   
#define     ACCELEROMETER_S0_IN     PTP_PTP1  
#define     ACCELEROMETER_S1_IN     PTP_PTP2 

 
#define     ACCELEROMETER_PORT      PTP 
#define     ACCELEROMETER_DDR       DDRP


 // 0 for normal mode 1 for power-down 
#define     ACCELEROMETER_ENABLE()         CLEARBIT(ACCELEROMETER_CS_NOT,1); 
#define     ACCELEROMETER_DISABLE()        SETBIT(ACCELEROMETER_CS_NOT,1); 
    
    
#define ACCELEROMETER_X()                \
  CLEARBIT(ACCELEROMETER_S1_IN,1);          \
   CLEARBIT(ACCELEROMETER_S0_IN,1);                  \

#define ACCELEROMETER_Y()                \
  CLEARBIT(ACCELEROMETER_S1_IN,1);          \
   SETBIT(ACCELEROMETER_S0_IN,1);   
   
#define ACCELEROMETER_Z()                \
  SETBIT(ACCELEROMETER_S1_IN,1);          \
   CLEARBIT(ACCELEROMETER_S0_IN,1);   

#define ACCELEROMETER_AUX_IN()                \
  SETBIT(ACCELEROMETER_S1_IN,1);          \
   SETBIT(ACCELEROMETER_S0_IN,1);         


#define ACCELEROMETER_INIT_DDR()	{ SETBIT(ACCELEROMETER_DDR,(PTP_PTP0_MASK | PTP_PTP1_MASK | PTP_PTP2_MASK )); }  


#endif /* SWITCHES_ */