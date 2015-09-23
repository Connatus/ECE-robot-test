
#include "Accelerometer.h"
#include <math.h>
/// outputs ACC  to display 
//// needs to give direction // interrupt driven??? 
/// fuck no thats really complicated//
/// The amplifier gives     
//http://cache.freescale.com/files/sensors/doc/app_note/AN3107.pdf    

// Min = 350   Max = 850 

/*
FLOATS ARE NOT POSSIBLE TOO MUCH CODE SPACE
   IT'S 100% necessary to use 10 bit AD 

REST:              Gain from Amplifier is 1.52 // should result in a max voltage of 5v out from the ACC
  x:      500    == 2.44v   
  y:      611    == 2.98v
  z:      830    == 4.05v  can float around +-5 

/// (0.145*3.3v) per G   // device is 2 g
    http://www.st.com/web/en/resource/technical/document/datasheet/CD00259979.pdf


*/


/*
 X -- Left  = Negative
   X -- Right = Positive 
   
   Y -- TWIST  Clockwise = Negative
   Y -- Twist  Counter CLock = Positive 
   
   Z -- UP  == Positive 
   Z -- DOWN == NEGATIVE


*/ 


/// takes values 
/*
  x = 1 || 'x'
  y = 2 || 'y'
  z = 3 || 'z'
  
*/
signed int Accelerometer_Calc_Val(unsigned int anal_in, char acc_axis, unsigned int refrence){
    unsigned int temp_value; // int 
    temp_value =  anal_in - refrence; 
    
   // if(Accel_Negative_Flag == 1)
    // printf("refr: -%d, ", temp_value);  
    
   // else 
    // printf("refr: %d, ", temp_value);  
     
   return temp_value; 
}


/// should probably read ten values 
void Accelerometer_Val2Degree(void){
    signed long temp_long; 
    signed int accel_out =0; 

 
    Accel_Negative_Flags= 0; // clear flag everytime 
    
    accel_out = Accelerometer_Calc_Val(anal_x, 'x', Accel_X_Zero);
    accel_out *= Accel_Degree_Val; 
    accel_out /= 100;
    // printf("%ul, ", accel_out); 
    deg_x =accel_out; 
   
    accel_out = Accelerometer_Calc_Val(anal_y, 'y', Accel_Y_Zero);
    accel_out *= Accel_Degree_Val; 
    accel_out /= 100; 
   // printf("%ul, ", accel_out);
    deg_y = accel_out;
   
    accel_out = Accelerometer_Calc_Val(anal_z,'z', Accel_Z_Zero);
    accel_out *= Accel_Degree_Val; 
    accel_out /= 100; 
   //  printf("%ul, ", accel_out);
    deg_z = accel_out; 
    
    /*
    if(deg_x > Accelerometer_Tollerance || deg_y > Accelerometer_Tollerance || deg_z > Accelerometer_Tollerance ||
     deg_x < -Accelerometer_Tollerance || deg_y < -Accelerometer_Tollerance || deg_z < -Accelerometer_Tollerance ){
       
       printf("\n MOVEMENT DETECTED \n --------------------\n", deg_x, deg_y, deg_z); 
       printf("\n Degrees: x:%d  y:%d  z:%d \n", deg_x, deg_y, deg_z); 
       if (deg_x < -Accelerometer_Tollerance)
          printf("\n  Right Turn %d deg -- x", deg_x); 
       if (deg_x > Accelerometer_Tollerance)
          printf("\n  Left Turn %d deg  -- x", deg_x);
       
       if (deg_y < -Accelerometer_Tollerance)
          printf("\n  Counter Clockwise Tilt %d deg -- y",deg_y); 

       if (deg_y > Accelerometer_Tollerance)
          printf("\n  Clockwise Tilt %d deg  -- y", deg_y);          
        
       if (deg_z < -Accelerometer_Tollerance)
          printf("\n  Board Upsidedown  %d deg -- z", deg_z); 
       if (deg_z > Accelerometer_Tollerance)
          printf("\n  Board Down %d deg -- z",deg_z); 
       
       Timer_Delay_10ms(100);// ARTIFICIAL DELAY 
       
    } */ 
     
  
    return; 
}


// write to file 
//http://cache.freescale.com/files/sensors/doc/app_note/AN3107.pdf
//http://www.st.com/web/en/resource/technical/document/datasheet/CD00259979.pdf
void Accelerometer_INIT(void){
  unsigned char anal_count;
  
  printf("Please Allow the Board To remain Steady for 3 seconds");  
  Analog_Init(0);
  ANALOG_ENABLE_PIN(0x5);
  
  ACCELEROMETER_INIT_DDR(); 
  ACCELEROMETER_ENABLE(); 
  
  Accelerometer_Read();  
 
  
  printf("\n x:%d y:%d z:%d", (anal_x), (anal_y), (anal_z));  

   
   if(!anal_x || !anal_y || !anal_z)
      ERROR_PRINT_SCREEN_2("Analog Or Accel Init Error - Accel out =0v", 5); 
   
   if(anal_x > 680 || anal_x < 550 || anal_z < 750 || anal_y > 700 || anal_y < 550)
     ERROR_PRINT_SCREEN_2("Calibration Error please place on flat surface", 5);     
   
   
    Accel_X_Zero  = anal_x;
    Accel_Y_Zero  = anal_y;
    Accel_Z_Zero  = anal_z;
    
   printf("\n\n Steady state values \n \n x:%d y:%d z:%d", Accel_X_Zero, Accel_Y_Zero, Accel_Z_Zero);

   
   #if (ACCELEROMETER_INTERRUPT) 
      
      TIOS_OUTPUT_PIN(PTT_PTT6_MASK);
    	TIE_ENABLE_PIN(PTT_PTT6_MASK); 
    	
    	EnableInterrupts; 

   #endif
   
   return; 
  
}


void Accelerometer_Read(void){
   unsigned char anal_count =0; 

  anal_x = 0;
  anal_y =0;
  anal_z =0;
  
  for(anal_count =0; anal_count < Accelerometer_Tollerance; anal_count++) {
  
  
  /// Read X   
   ACCELEROMETER_X();  
     anal_x+= Analog_Read(0x5);
      Timer_Delay_1ms(1);
  /// Read Y
   ACCELEROMETER_Y();  
     anal_y+= Analog_Read(0x5);
      Timer_Delay_1ms(1);
  /// Read Z 
   ACCELEROMETER_Z();  
     anal_z+= Analog_Read(0x5);
     Timer_Delay_1ms(1);
     
  }
  
   anal_x =  anal_x/Accelerometer_Tollerance;
   anal_y =  anal_y/Accelerometer_Tollerance;
   anal_z =  anal_z/Accelerometer_Tollerance;
   
 //  printf("\n x:%d y:%d z:%d", (anal_x), (anal_y), (anal_z));  
     
   return; 
}



void Accelerometer_Test_2(void){
 // char *filename = "ACCEL.txt"; 
  unsigned int anal_count =0; 
  signed int local_degx=0, local_degy=0, local_degz=0;  
  signed int Local_Accelerometer_Tollerance= 4; 
  signed int *acc_return;

  Accelerometer_INIT(); 


  while(1){
  
      
       acc_return = Accelerometer_Read_Values();
       local_degz =  *(acc_return +0);
       local_degy =  *(acc_return +1);
       local_degx =  *(acc_return +2);

       
       if(  local_degx > Accelerometer_Tollerance ||   local_degy > Accelerometer_Tollerance ||   local_degz > Accelerometer_Tollerance ||
         local_degx < -Accelerometer_Tollerance ||   local_degy < -Accelerometer_Tollerance ||   local_degz < -Accelerometer_Tollerance ){
               printf("\n x: %d  y: %d  z: %d ", local_degx,local_degy,local_degz); 
       }
  
  }
  
  return;
}




void Accelerometer_Test(void){


//  DDRP = 0xFF; 
  Analog_Init(0);
  ANALOG_ENABLE_PIN(7);
  
  ACCELEROMETER_INIT_DDR(); 
  ACCELEROMETER_ENABLE(); 

 //   anal_x  =asin(2);
    ANALOG_ENABLE_PIN(0x5);
  
  for(;;) {
  
   ACCELEROMETER_X();  
     anal_x= Analog_Read(0x5);
      Timer_Delay_1ms(1);
   ACCELEROMETER_Y();  
     anal_y= Analog_Read(0x5);
      Timer_Delay_1ms(1);
   ACCELEROMETER_Z();  
     anal_z= Analog_Read(0x5);  
   
    Timer_Delay_1ms(1);
     printf("\n x:%d y:%d z:%d", anal_x, anal_y, anal_z);         
   
  }
  
     // READ VALUES CONVERT TO DEGREES MOVEMENT

  
  
  return;
     

}



                               // no float 
                               
signed int * Accelerometer_Read_Values(void){
   signed int  acc_return[3];
    
    // READ VALUES CONVERT TO DEGREES MOVEMENT
   
   #if !(ACCELEROMETER_INTERRUPT) 
    Accelerometer_Read(); 
   #endif
     
   
   #if (ACCELEROMETER_INTERRUPT)
     DisableInterrupts; 
   #endif 
        Accelerometer_Val2Degree(); 
        acc_return[0] = deg_x;
        acc_return[1] = deg_y;
        acc_return[2] = deg_z; 
   #if ACCELEROMETER_INTERRUPT
     EnableInterrupts;
   #endif 
   
    return acc_return;
}

/*
//READ ACC EVERY 10ms 
interrupt 14 void TC6handler(void){
   TFLG1 = TFLG1_C6F_MASK; // clear the flag 

  
  /// read ACC values here // 
   Accelerometer_Read();    //kindof slow
  //
  TC6 = TCNT + 10000; // read every 100ms
}
  */ 



