#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
/*

FONT IS BROKEN PLEASE NOTE FONT ISNT THE FULL ARRAY ?/

Files can not be created using fat fs// they must be pre-existing and in all caps

*/ 

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

/*******************************************/
// INTERRUPTS    USED !!! 
/*******************************************/    
     
     //TC0      //interrupt 0 void TC0handler(void) // INPUT R    STM
     //TC1      //interrupt 9 void TC1handler(void) // INPUT L      STM   
     //TC3      //void interrupt 10 OC2_isr -- NEEDED FOR RC SERVO //     
     //TC4      //interrupt 12 void TC4handler(void) // WATCHDOG      STM
     //TC5      // Timer_Delay_10us(int k) - USES TC5 
     //TC6      //interrupt 14 void TC6handler -- ACCEL    // WATCHDOG      // ACCELEROMETER REMOVED // USED FOR DC MOTOR SPEED AVERAGE
     //// 
     //TC7      //interrupt 15 void TC7handler(void) = stepper motor interrupt // 

          
         

#include "error.h" /// ERRORNO

#include "menu.h" 


///END 

void ASMSTUFF(void);
void RS232_INIT(void);
void RS232_TEST(void); // used to test the interrupt rs232 

/////// SD And FAT
void SD_INIT_FAT(void);

void DC_MOTOR_SHOW_BILL(void); 
void ENCODER_SHOW_BILL(void);




//qwer12340500F00400Babcd // MOTOR TEST
//qwer2234100050L0100110Labcd // ENCODER TEST


void main(void) {
   unsigned int i =0;
   unsigned char Error =0;
   struct LCD_Geometry *pointCurrent= &Current;
   unsigned int Local_Process =0; 
   unsigned int Local_counter =0;
   unsigned char Local_Error_Flag_Number =0;  
   Error_Flag_Number =0;  
 
   Timer_INIT(); /// ENABLE TIMERS  FIRST  ALL THINGS DEPEND ON THIS THAT USE DELAYS !!! FUCK
   ILI9327_INIT();// init lcd
   
    //ENCODER(); 
    DCM_INIT(); 
    RC_SERVO_INIT(); 
    STMOTOR_INIT(); 
    STMOTOR_FIND_HOME();  
    Accelerometer_INIT(); // init accel // read from input  
    Encoder_Init(); 
    /// FOREVER LOOP    
   
    
    RS232_TEST();
   
  
   
     //WORKS GREAT 
  // RC_SERVO_INIT(); 
  

    
   // DO ENCODER SHIT HERE
  
  //   Encoder_menu(); 
  
// STMOTOR_TEST(); 
 // ENCODER(); 
  
  
  // init sd // write hello world // 
 // SD_INIT_FAT();
  
  
  
  // DCMOTOR WORKS// SET SPEED USING SET SPEED PERCENTAGE //
   /// WORKS GREAT 
/*  DCM_INIT(); 
   DC_1_REVERSE_DIRECTION;
   DC_2_FORWARD_DIRECTION ;  
   DC_R_SETSPEED_PERCENTAGE(40); 
   DC_L_SETSPEED_PERCENTAGE(100);       */
 
  
// ENCODER WORKS 
/*
interrupt 10 void TC1handler(void) // INPUT R 
interrupt 9 void TC2handler(void) // INPUT L 
interrupt 12 void TC4handler(void) // WATCHDOG 
*/
  // Encoder_menu();
  //  ENCODER(); 
  // STEPPER MOTOR WORKS    //
   //STMOTOR_TEST();

// GETS ACCEL VALUES // WORKS GREAT
/*
interrupt 14 void TC6handler  // TIMER WATCHDOG
*/
//  Accelerometer_Menu();  //
 //Accelerometer_Test_2(); 

// NEEDS MORE WORK // WORKS FINE BUT NEEDS To BE RUN IN THE BACKGROUND 
// USING TIMERS
 //Touch_Test();   
    
   // RS232_INIT();
 // printf("waitforever");
  
  
    while(1){
     asm("NOP");
     continue; 
  
  }
    
  
   
   // WORKS GREAT WITH INPUT FROM SERIAL // 
   // SHOULD CHANGE 
  // RS232_INIT();
         /*extern unsigned char RS232_Termination_String[4] = {
       //  0xDE, 0xAD, 0xBE, 0xEF
         'a','b', 'c','d'
      };                                                                                             

      extern unsigned char RS232_Transmission_String[4] = {
        //  0xFE, 0xED, 0xDE, 0xAD 
         'q','w','e','r'
      };
        */

  


  
// Analog_Init(ANALOG_10BIT);
 //Touch_Test();

//MAX5513_Test();
 //Accelerometer_Test(); 


}

/// PWM is consistant yet motor seems to slow perhaps the enable pins are fucked 

void ENCODER_SHOW_BILL(void){
    //// WORKS GREAT // 
       DCM_INIT();
     DC_2_REVERSE_DIRECTION ;
     DC_L_SETSPEED_PERCENTAGE(20);
     DC_1_FORWARD_DIRECTION ;
     DC_R_SETSPEED_PERCENTAGE(20); 
   Encoder_menu();
}

void DC_MOTOR_SHOW_BILL(void){
  DCM_INIT(); 
  DC_L_SETSPEED_PERCENTAGE(100); 
  DC_R_SETSPEED_PERCENTAGE(50); 
  DC_1_REVERSE_DIRECTION;
  DC_2_FORWARD_DIRECTION ;
 
  while(1){
   continue; 
    
  }
}


#if _FATFSENABLE != 0

void SD_INIT_FAT(void){
   unsigned int fuck =0;
   unsigned char fontshit[5];  
   unsigned char fucker =0; 
   SD_INIT();      
   errCode = f_mount(0, &filesystem);
   Fat_FS_Error(errCode,"f_mount");
   printf("\n Mounted File System: Type SD");
   Write_Hello_World(); 
}

#endif /* !_FS_READONLY */

void RS232_INIT(void){

// Init Vars for RS232
   RS232_Processed_Data_Flag= 0;
   RS232_Recieve_Flag = 0; 
   RS232_Counter = 0; // set counter to 0;   
   ERROR_PRINT_SCREEN( RS232_Init(9600)); 	

}


void RS232_TEST(void){
  struct LCD_Geometry *pointCurrent= &Current;
	struct LCD_Properties *pointProperties= &Properties;
   struct Terminal_Program_Values	*pointTerminal = &TerminalProperties;
 
  unsigned int i =0; 
  unsigned int RS232_LENGTH =0;
  unsigned char Error =0;
  unsigned int Local_Process =0; 
  unsigned int Local_counter =0;
  unsigned int Local_Message_Storage_Counter =0; 
  unsigned char Local_Error_Flag_Number =0;  

   int Encoder_L_Counter =0;
   int Encoder_R_Counter =0; 
   unsigned char Encoder_Watchdog_Flag =0; 


  Error_Flag_Number =0; 
 
 
  RS232_INIT();
//  RS232_ECD(1); 
  
 /* / Accelerometer_INIT(); 
   // fill outline 
   LCD_Fill_Rectangle(0,0,pointTerminal->xResolution,pointProperties->yResolution ,  0x00FFFF); //
     /// Disable any currently running interrupts /// 
   LCD_Fill_Rectangle(20,20,pointTerminal->xResolution-40,pointTerminal->yResolution-40, 0x000000);
  
  pointCurrent->size = 2;
  pointTerminal->previousx = 24; 
  pointTerminal->currentline = 2;
	printf("PROJECT IV - ROBIT V0.%d", 3); 
	
	
  pointTerminal->previousx = 25; 
  pointTerminal->currentline = 4;
	printf("%s", "MOTOR SPEED"); 
	pointTerminal->currentline = 5;
	pointTerminal->previousx = 105;  
	printf("%s", "ENCODER"); */

     
    asm("CLI"); 
    
   while(1){
      
      asm("SEI");
       // RS232
       RS232_LENGTH= RS232_COUNTER_OUTSIDE;   // could kill perhaps 
       Local_Process = RS232_Processed_Data_Flag; 
       Local_Message_Storage_Counter =Message_Storage_Counter; 
       Local_Error_Flag_Number = Error_Flag_Number; 
       /// ENCODER 
        Encoder_L_Counter = L_Counter;
        Encoder_R_Counter = R_Counter; 
        Encoder_Watchdog_Flag =  WATCH_DOG_FLAG;
      asm("CLI");
      
          
        if(Local_Error_Flag_Number != 0x00){
          asm("SEI"); 
           ERROR_PRINT_SCREEN_2("RS232 outside of alloted data storage array size",Local_Error_Flag_Number);
        }
      
        if(Local_Process){
          // KILL INTERRUPTS/// 
          asm("SEI"); 
          Local_Message_Storage_Counter  = (Message_Storage_Counter%RS232_MESSAGE_STORAGE_LENGTH); // used to count the number of chars in message array from RS232 


               /// store data in local array for use !!!! 100% NECESSARY FOR FUNCTION//
         for (i=0; i < (Local_Message_Storage_Counter); i++) 
            Local_Message_Storage_Array_RS232[i] =  MessageStorageArray[i]; 
            
             Message_Storage_Counter = 0;       // set main counter to zero 
             RS232_Processed_Data_Flag = 0;     // tell the interrupt process we, processed the dat
          //   Process_RS232(MessageStorageArray,Local_Message_Storage_Counter);  
           asm("CLI");
           
            for (i=0; i < (Local_Message_Storage_Counter); i++) 
              printf("%c", Local_Message_Storage_Array_RS232[i]);
                /// DATA ARRAY MUST BE PROCESSED EACH RECIEVE !!!
            Process_RS232(Local_Message_Storage_Array_RS232,Local_Message_Storage_Counter);  
         
            printf(" LENGTH: %d",  Local_Message_Storage_Counter); 
          
            printf("\n LOAD BOARD FUNCTION: %c", Board_Function);       
           switch(Board_Function) {
            
              /// RUN RS232 TYPE WRITER
              case '0':
                    printf("\nOPENIGN SERIAL TERMINAL"); 
                    RS232_ECD(RS232_Com_PORT);
                    break;
               /// RUN DC MOTOR
              case '1':
                    printf("\nDC MOTOR SHIT");
                    DC_Motor_ECD( Local_Message_Storage_Counter);
                    break;
               // MOVE CAMERA 
              case '2':
                    // printf("\nCAMERA MOVE");
                    Camera_ECD( Local_Message_Storage_Counter);       //Camera_ECD
                    //DC_Motor_Encoder_ECD(Local_Message_Storage_Array_RS232, Local_Message_Storage_Counter); 
                    break;   
              case '3':
                     printf("\nPING");
                    Ping_ECD(Local_Message_Storage_Counter);      
                     //DC_Motor_Encoder_ECD(Local_Message_Storage_Array_RS232, Local_Message_Storage_Counter);       
           
            break;  
           }
     
     }
     
         
      if(Encoder_Watchdog_Flag ==1){
          
           // printf("R %d \n", Encoder_R_Counter); 
           // printf("L %d \n", Encoder_L_Counter); 
           // RESET COUNTERS AND FLAGS
              
              LCD_Fill_Rectangle(335,100,50,50, 0x000000);

     
             	pointTerminal->previousx = 300; 
              pointTerminal->currentline = 12;
            	printf("%s:  %d", "LEFT", Encoder_L_Counter); 
            	
            	pointTerminal->previousx = 300; 
              pointTerminal->currentline = 13;
              printf("%s: %d ", "RIGHT", Encoder_R_Counter);       
            
           DisableInterrupts;
           WATCH_DOG_FLAG =0; 
           L_Counter =0;
           R_Counter =0; 
           EnableInterrupts;
      }
      
      // PASS VARS TO WATCHDOG
      DisableInterrupts;
      WATCH_L_COUNTER =  Encoder_L_Counter;
      WATCH_R_COUNTER =  Encoder_R_Counter; 
      EnableInterrupts; 
      
    //  Accelerometer_Test(); 
  
   }

}

 /*
unsigned char RS232_Send_Node(void){
  struct RS232_Message *Message_Node = &RS232_Message_Node;
   	unsigned int counter =0; 
   	unsigned char hellos[6] = "hello";
  	for(counter= 0; counter < 119; counter++){
  	    Message_Node->MessageStorageArray[counter] = (counter);
  	    printf(" %d", Message_Node->MessageStorageArray[counter] ); 
  	
  	}
  	Message_Node->MessageStorageArray[counter++] = '\0'; 
  	Message_Node->MessageSequenceNumber = 0x01; 
  	Message_Node->lDataLength = counter; 
  	Message_Node->Message_CRC = 0xBEEF; 
  	
   // RS232_Write_String(Message_Node->MessageStorageArray);   //
    printf("\n Data: %s", Message_Node->MessageStorageArray);   // %s doesnt work with storage arrays 
    printf("\n Data: %s", hellos);
   //
    printf("\n MessageSequenceNumber: %d", (Message_Node->MessageSequenceNumber));    // 394 
    printf("\n DataLength: %d", (Message_Node->lDataLength));    // 394 
    printf("\n Message_CRC: %d", (Message_Node->Message_CRC));    // 394    
  
}
*/
