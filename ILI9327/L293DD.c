#include "L293DD.h"

#include "Timer.h"





unsigned char Stepper_Motor_Array[8] ={
	0x80,
	0xA0,
	0x20,
	0x60,
	0x40,
	0x50,
	0x10,
	0x90
}; 
 
 /*
 
 unsigned char Stepper_Motor_Array[8] ={
  0x80,     //    1000
  0xA0,     //    1100
  0x40,     //    0100
  0x60,     //    0110
  0x20,     //    0010
  0x30,     //    0011
  0x10,     //    0001
  0x90      //    1001
}; 
 

unsigned char Stepper_Motor_Array[8] ={
  0x80,     //    1000
  0xA0,     //    1100
  0x20,     //    0010
  0x60,     //    0110
  0x40,     //    0100
  0x50,     //    0101
  0x10,     //    0001
  0x90      //    1001
}; */
  volatile unsigned char Motor_Count=0;
    
    
 // THIS ISNT COMPLETELY BLACK BOX NEEDS TO READ INTERUPT FLAGS FROM OUTSIDE // 
 // WILL KILL INTERUPPTS OTHERWISE // 
unsigned char STMOTOR_COMPLETE_MOTION(unsigned char Steps, unsigned char Direction){
  unsigned int Local_Stepper_Count=0;
  
     DisableInterrupts;
       Stepper_Direction_Flag = Direction; 
       Stepper_Steps = Steps; 
     EnableInterrupts; 

  // needs to wait untill complete 
   while(1){
       DisableInterrupts; 
       Local_Stepper_Count = Stepper_Steps;
       EnableInterrupts; 
    if( Local_Stepper_Count == 0){ 
     DisableInterrupts; // kill interrupts// -- should only kill the watch dog though  
     return 0;
    }  
   }

}

      
// needs a homing position, 
/// count steps to left, count steps to right, then left again // add right+ left last divide by 4 and step to the middle //       
unsigned char STMOTOR_TEST(void){
    
    char step =0; 
    unsigned char Local_Stepper_Direction_Flag =0; 
   STMOTOR_INIT(); 
   STMOTOR_FIND_HOME(); 
    
    printf("found Home"); 
   
    STMOTOR_MOVE_DEGREES(50, 'R'); 
   
    STMOTOR_MOVE_DEGREES(50, 'L'); 
    
    printf(" END OF STEPPER_TEST" ); 

    return 0;
}

 /// INITS INTERRUPT, PORTS , Sets flags // 
 /// IDEALY SPEED IS MEDIUM
unsigned char STMOTOR_INIT(void){
 // init ddr  ports // pins and set the watchdog timer
 // RESET FLAGS AND INTERRUPT VARIABLES 
    Stepper_Direction_Flag =0; 
    Stepper_WholeStep_Flag =0;
    Stepper_Count_Steps =0; 
    Stepper_Steps =0;
    Stepper_Speed; // delay by 4us idealy set inbetween 300-1000 
    STMOTOR_INIT_ENABLE_DDR();
    STMOTOR_INIT_DDR(); 
    STMOTOR_ENABLE(); 
	  Stepper_Speed = STEPPER_SPEED_SLOW; 
    TIOS_OUTPUT_PIN(PTP_PTP7_MASK);
	  TIE_ENABLE_PIN(PTP_PTP7_MASK);  
	  
  return 0; 
}

// moves degrees from far right // 
  // should move either all the way left then move //degrees
  //based on input //
  // set direction Right    
  
unsigned char STMOTOR_MOVE_DEGREES_FROM_FAR_RIGHT(unsigned char degrees){
  unsigned int Local_Stepper_Count=0;
  unsigned char Local_Stepper_Flag =0;
  unsigned char Previous_Stepper_Flag =0; 
  unsigned int Local_Stepper_Degree =0; 

   Stepper_Direction_Flag = 'R';
   Stepper_Steps = 300; 
  
    // calc degrees value here 
   Local_Stepper_Degree =  ((STEPPER_FULL_SWEEP_STEPS *100)/ STEPPER_FULL_SWEEP_DEGREES );
   Local_Stepper_Degree *= degrees;  
   Local_Stepper_Degree /= 100;

  Previous_Stepper_Flag = 'R'; 
 
  while(1){
      // read flag //    
   DisableInterrupts;
   Local_Stepper_Flag =  Stepper_Direction_Flag; 
   EnableInterrupts; 
    
   if((Previous_Stepper_Flag == 'R') && (Local_Stepper_Flag == 'L'))
      break; 
  
  }
  
   STMOTOR_COMPLETE_MOTION(Local_Stepper_Degree, 'L'); 
  
  return 0; 
}

/* Even though i know the full range of steps is 197, its better to count the steps and find home maually.  
   Enables interrupts // Disables interrupts 
          Step 0: move from current position to position RIGHT //
          Step 1: move from RIGHT TO LEFT count values and store //
          Step 2: move from LEFT TO RIGHT count values and store // 
          Step 3: Exit, divide count by 4 and move left by that number 
*/
unsigned char STMOTOR_FIND_HOME(void){
   unsigned int Local_Stepper_Count=0;
   unsigned int Stepper_Home =0; 
   unsigned char Local_Stepper_Flag =0; 
   unsigned char Previous_Stepper_Flag =0; 
   unsigned char Local_Stepper_Direction_Flag= 0; 
   unsigned char Flag_Set_Count=0; // flag should be set     
   
 
   Stepper_Count_Steps =0;
    
   // set direction Right    
   Stepper_Direction_Flag = 'R';
   Stepper_Steps = 3000; 
   Stepper_WholeStep_Flag =0;
   
   EnableInterrupts; 
 
   Previous_Stepper_Flag = 'R'; 
 

  while(Flag_Set_Count != 3){
    
  // read flag //    
   DisableInterrupts;
   Local_Stepper_Flag =  Stepper_Direction_Flag; 
   EnableInterrupts; 

       
     // R & L serve as exclusive states 
      // will only be triggered when button L is pressed 
   if((Previous_Stepper_Flag == 'R') && (Local_Stepper_Flag == 'L')) {  
     
     // only read counter when necessary
      DisableInterrupts; 
      Local_Stepper_Count= Stepper_Count_Steps;
      Stepper_Count_Steps =0;       // reset value 
      EnableInterrupts; 
     
      Previous_Stepper_Flag = Local_Stepper_Flag;  
    
        if(Flag_Set_Count == 2)        // only store the 2nd State - state 0 is useless 
            Stepper_Home +=  Local_Stepper_Count;     
      
         Flag_Set_Count++;     
    }
    
     // will only be triggered at the instance when button R is pressed 
   else if((Previous_Stepper_Flag == 'L') && (Local_Stepper_Flag== 'R')) {
     
      DisableInterrupts; 
      Local_Stepper_Count= Stepper_Count_Steps;
      Stepper_Count_Steps =0;  
      EnableInterrupts; 
      Previous_Stepper_Flag = Local_Stepper_Flag; 

     if(Flag_Set_Count == 1)    // only store state 1 
        Stepper_Home +=  Local_Stepper_Count; 

        Flag_Set_Count++;                                  
    }   
    
    if(Previous_Stepper_Flag != 'R' && Previous_Stepper_Flag != 'L')
      ERROR_PRINT_SCREEN_2("Stepper Flag Not Set Properly", 22); 
    if(Flag_Set_Count > 1 && Local_Stepper_Count == 0)
       ERROR_PRINT_SCREEN_2("Stepper Count = 0 Check Connection", 22);   
  }


   DisableInterrupts; 
   Stepper_Steps = 0; 
   EnableInterrupts;  
   Stepper_Home /= 4; 

   
   
   STMOTOR_COMPLETE_MOTION(Stepper_Home, 'L');
   
   return 0;
}


// direction should give either R or L // 
unsigned char STMOTOR_MOVE_DEGREES(unsigned char degrees, unsigned char direction){
    unsigned int Local_Stepper_Degree =0; 
    
    // calc degrees value here 
   Local_Stepper_Degree =  ((STEPPER_FULL_SWEEP_STEPS *100)/ STEPPER_FULL_SWEEP_DEGREES );
   Local_Stepper_Degree *= degrees;  
   Local_Stepper_Degree /= 100;

   STMOTOR_COMPLETE_MOTION(Local_Stepper_Degree, direction);
}


/*
    Handles the button detection, navigating through arrays and blocking steps
    // would write code outside to take care of this, however i want the motor to move 
    on its own while i am doing other things 

*/
interrupt 15 void TC7handler(void){
   TFLG1 = TFLG1_C7F_MASK; // clear the flag 

      // Motor hits left button 
      if(!(PTS &PTS_PTS3_MASK )) 
           Stepper_Direction_Flag = 'R'; // move the motor RIGHT 
      
      /// Motor hits right button   
      else if(!(PTS &PTS_PTS2_MASK))
          Stepper_Direction_Flag = 'L'; // move the motor RIGHT 
   
          
      /// only step motor if flag is set;  
      if (Stepper_Direction_Flag == 'L' || Stepper_Direction_Flag == 'l'){
        if(Stepper_WholeStep_Flag == 1)
          Motor_Count +=B_HSB;
        else 
          Motor_Count +=B_FSB; 
      }
      else if (Stepper_Direction_Flag == 'R' || Stepper_Direction_Flag == 'r' ){
       if(Stepper_WholeStep_Flag == 1) 
          Motor_Count +=B_HSF; 
       else 
          Motor_Count +=B_FSF;
      }
      
     
   // Continue to step until value is zero 
   // approx full cycle is 246 for 180 deg 
  if(Stepper_Steps !=0 ){
     Stepper_Count_Steps++; 
     STEPPER_MOTOR_STEP = Stepper_Motor_Array[Motor_Count%8]; 
     Stepper_Steps--;  
  }

  // Set port val here // 
  STM_PORT &= 0x0F;
  STM_PORT |= STEPPER_MOTOR_STEP; 
      
  STEPPER_WATCHDOG_TIMER = TCNT + Stepper_Speed; ///feed dog  
}          