#include "menu.h"


#define ACCELEROMETER_TIMER  TC6  


void Timer_INIT(void); 


// display current accelerometer values on screen 
// send out rs232
void Accelerometer_Menu(void){
  struct Terminal_Program_Values	*pointTerminal = &TerminalProperties;
  struct LCD_Geometry *pointCurrent= &Current;
	struct LCD_Properties *pointProperties= &Properties;
  unsigned char *Menu_Function = "Accelerometer Output"; 
  unsigned long Menu_Color = 0x00FFFF;  
   signed long temp_long; 
   signed int accel_out =0;
   unsigned char counter =0; 
   signed int local_degx=0, local_degy=0, local_degz=0;  
   signed int *acc_return; 

   Accelerometer_INIT(); 
   // fill outline 
   LCD_Fill_Rectangle(0,0,pointTerminal->xResolution,pointProperties->yResolution , Menu_Color); //
     /// Disable any currently running interrupts /// 
   LCD_Fill_Rectangle(20,20,pointTerminal->xResolution-40,pointTerminal->yResolution-40, 0x000000);
  
   
  pointCurrent->size = 2;
  pointTerminal->previousx = 24; 
  pointTerminal->currentline = 2;
	printf("%s", Menu_Function); 
	
	
  pointTerminal->previousx = 200; 
  pointTerminal->currentline = 4;
	printf("%s", "X-Output"); 
	
	pointTerminal->previousx = 200; 
  pointTerminal->currentline = 6;
	printf("%s", "Y-Output"); 
	
	pointTerminal->previousx = 200; 
  pointTerminal->currentline = 8;
	printf("%s", "Z-Output"); 
 
	// #define TIOS_ENABLE_PIN(pin)      SETBIT_SHIFT(TIOS,pin);
//#define TIE_ENABLE_PIN(pin) 
// enable interrupts 
	while(1){
	  
       for(accel_out =0; accel_out < 100; accel_out++)
        asm("NOP");
       
         local_degx = 0;
         local_degy = 0;
         local_degz = 0;
     
       acc_return = Accelerometer_Read_Values();
       local_degz =  *(acc_return +0);
       local_degy =  *(acc_return +1);
       local_degx =  *(acc_return +2);
 
    // printf(" %d %d %d",  local_degx,   local_degy,   local_degz);
    // movment detected 
    
    if(  local_degx > Accelerometer_Tollerance ||   local_degy > Accelerometer_Tollerance ||   local_degz > Accelerometer_Tollerance ||
       local_degx < -Accelerometer_Tollerance ||   local_degy < -Accelerometer_Tollerance ||   local_degz < -Accelerometer_Tollerance ){
              
       pointTerminal->previousx = 240; 
       pointTerminal->currentline = 5;
       LCD_Fill_Rectangle(230,139,22,130, 0x000000);
       printf("%d",   local_degx);     
       
       	  
       pointTerminal->previousx = 240; 
       pointTerminal->currentline = 7;
        LCD_Fill_Rectangle(230,100,22,130, 0x000000);
       printf("%d",  local_degy); 
      
 	    pointTerminal->previousx = 240; 
      pointTerminal->currentline = 9; 
      LCD_Fill_Rectangle(230,60,22,130, 0x000000);
      printf("%d",  local_degz); 
      
      
      
      
      // DRAW ARROWS 
      LCD_Fill_Rectangle(40,100,70,130, 0x000000);
       pointTerminal->previousx = 40; 
      pointTerminal->currentline = 5; 
      
        if (  local_degx < -Accelerometer_Tollerance){
          printf("Left Turn");
          pointTerminal->previousx = 60; 
          pointTerminal->currentline = 7;
          pointCurrent->color = 0xFF00FF; 
          printf("    <-");
        }
       if (  local_degx > Accelerometer_Tollerance){
          printf("Right Turn");
          pointTerminal->previousx = 60;
          pointCurrent->color = 0xFF00FF;
          pointTerminal->currentline = 7;
          printf("    ->");
       }  
      
       pointCurrent->color = 0xFFFFFF; 
      Timer_Delay_10ms(10);// ARTIFICIAL DELAY 
        
    }   
     
	}
	
	  return;
}


void Encoder_menu(void){
  struct Terminal_Program_Values	*pointTerminal = &TerminalProperties;
  struct LCD_Geometry *pointCurrent= &Current;
	struct LCD_Properties *pointProperties= &Properties;
  unsigned char *Menu_Function = "Motor Encoder"; 
  unsigned long Menu_Color = 0xFF00FF;  
   signed long temp_long; 
   signed int accel_out =0;
   unsigned char counter =0;  
    unsigned char shit =0; 
   ///
	 unsigned char Error =0;
   int Encoder_L_Counter =0;
   int Encoder_R_Counter =0; 
   unsigned char Encoder_Watchdog_Flag =0; 
     

   // fill outline 
   LCD_Fill_Rectangle(0,0,pointTerminal->xResolution,pointProperties->yResolution , Menu_Color); //
     /// Disable any currently running interrupts /// 
   LCD_Fill_Rectangle(20,20,pointTerminal->xResolution-40,pointTerminal->yResolution-40, 0x000000);
  
   
  pointCurrent->size = 2;
  pointTerminal->previousx = 24; 
  pointTerminal->currentline = 2;
	printf("%s", Menu_Function); 
	
	
  pointTerminal->previousx = 200; 
  pointTerminal->currentline = 4;
	printf("%s", "L-ENCODER"); 
	
	pointTerminal->previousx = 200; 
  pointTerminal->currentline = 6;
	printf("%s", "R-ENCODER"); 
	  
	 
    Encoder_Init(); 
    EnableInterrupts;
 
    
       for (;;){
        // PASS ENCODER VARS TO MAIN
        DisableInterrupts;
        Encoder_L_Counter = L_Counter;
        Encoder_R_Counter = R_Counter; 
        Encoder_Watchdog_Flag =  WATCH_DOG_FLAG;
        EnableInterrupts;
        
        if(Encoder_Watchdog_Flag ==1){
             
             pointTerminal->previousx = 240; 
             pointTerminal->currentline = 5;
             LCD_Fill_Rectangle(230,139,22,130, 0x000000);
             printf("%d", Encoder_L_Counter);     
             
             	  
             pointTerminal->previousx = 240; 
             pointTerminal->currentline = 7;
              LCD_Fill_Rectangle(230,100,22,130, 0x000000);
             printf("%d",Encoder_R_Counter); 
            
                   
             // RESET COUNTERS AND FLAGS
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
        
    }      
}



/*
//READ ACC EVERY 10ms 
interrupt 14 void TC6handler(void){
   TFLG1 = TFLG1_C6F_MASK; // clear the flag 

  
  /// read ACC values here // 
   Accelerometer_Read(); 
   //

  ACCELEROMETER_TIMER = TCNT + 1000; // read every 10ms
}

*/

/*


   if(!ERRORNO)
    return 0; 
   
   /// Disable any currently running interrupts /// 
   LCD_Fill_Rectangle(0,0,pointTerminal->xResolution,pointTerminal->yResolution, 0x000000);
   // fill outline 
   LCD_Fill_Rectangle(0,pointProperties->xResolution-100,100,pointProperties->yResolution ,0xFF00FF); //
   LCD_Fill_Rectangle(10,pointProperties->xResolution-90,80,pointProperties->yResolution-20 ,0x000000); // 

   // give errors  
  
  pointTerminal->previousx = 20; 
  pointTerminal->currentline = 2;
	pointCurrent->color = 0xFF00FF;
	pointCurrent->size = 2;
	
	
	printf("FATAL SOFTWARE ERROR");  
	pointTerminal->currentline = 3;
  pointTerminal->previousx = 20; 
	printf("ERROR NUMBER: %d", ERRORNO);

  pointTerminal->currentline = 4;
  pointTerminal->previousx = 20; 
	printf("SEE LINUX ERRONO DOCUMENTATION");
	  	
	  pointTerminal->currentline = 9; 
    pointTerminal->previousx = 15;
    printf("%s", errorlocation);

	pointCurrent->size = 3;	
   while(1){
     pointTerminal->currentline = 5;
     pointTerminal->previousx = 15;     	pointCurrent->color = 0xFF00FF;
  	 printf("IT'S SAFE TO PANIC");
  	 Timer_Delay_10ms(20);
  	
  	 pointTerminal->currentline = 5;
     pointTerminal->previousx = 15;     	pointCurrent->color = 0x000000;
     printf("IT'S SAFE TO PANIC");
     Timer_Delay_10ms(20);
  	
     continue; 
   }


*/