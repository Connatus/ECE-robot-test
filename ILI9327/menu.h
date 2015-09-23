#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
// INCLUDE ALL LIBS CAUSE REASONS //

/*******************************************/
// SD and FAT Libraries   (CURRENTLY DEAD)
// ALL LIBRARIES ARE DISABLED IN FAT.H // SET _FATFSENABLE  =1 
// 
/*******************************************/     
#include "ff.h" // use FatFs from Elm-Chan.org
#include "ffconf.h"
#include "integer.h"
#include "diskio.h" // use FatFs from Elm-Chan.org (diskio used for disk initialization)
#include "file.h"
               
/******************************************/ 
#include "Test.h" // UNSORTED PLEASE SORT ME !!!!!
/******************************************/ 


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

/// no need to return values // error process inside menu
void  Accelerometer_Menu(void); 
void Encoder_menu(void);

#endif 