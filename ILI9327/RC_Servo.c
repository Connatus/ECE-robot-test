#include "RC_Servo.h" 

 
    // NEEDS TO BEINIT    SHITS NEEDED TO GET DONE SON

#define RCSERVO_TIMER     TC2

#define TCTL_1_2 ((*(volatile word * const) & TCTL1))
#define SET_OC_ACTION(chnl,action)    FORCE_WORD(TCTL_1_2, 0x03 << (chnl*2), ((action) << ((chnl)* 2)))


// board has a range of 135 degrees 

  
void RC_SERVO_INIT(void){
  unsigned int counter =0;
  OC2_Output_Flag=0; 
  Pulse_High =75;
  Pulse_Low  =2500; 
  TIOS_OUTPUT_PIN(TIOS_IOS2_MASK);  
  TIE_ENABLE_PIN(TIE_C2I_MASK);
    
   EnableInterrupts; 
  
  
    /*
     while(1){
        counter = (counter+10)%RC_DEGREE_RANGE; 
        
        RCServo_Set_Degrees_Sweep(counter%RC_DEGREE_RANGE);
        printf(" \n Sweeping %d degrees ", counter); 
      
  
        continue; 
    }     */

}


 
unsigned int RCServo_Degrees_Calulate(unsigned char degrees){
 unsigned int degree_calculate =0; 
     degree_calculate = (PULSE_MAX - PULSE_MIN);
     degree_calculate = ((degree_calculate*100)/(RC_DEGREE_RANGE));
     degree_calculate *= (degrees%(RC_DEGREE_RANGE+1));          // dont allow for degrees beyond range !
     degree_calculate /= 100;  
     degree_calculate += PULSE_MIN; 
    
     return degree_calculate; 
}   

unsigned int RCServo_Set_Degrees_Sweep(unsigned char degrees){
    unsigned int degree_calculate =0; 
    unsigned int previous_value=0; 
    signed int degree_loop=0; 
    unsigned char negative_flag =0; 
    
    
    signed int calc=0; 
    degree_calculate = RCServo_Degrees_Calulate(degrees); 
     
     DisableInterrupts;
     previous_value =Pulse_High; 
     EnableInterrupts; 
     
     degree_loop=  (degree_calculate-previous_value);
     if(degree_loop < 0){
        degree_loop = ((previous_value - degree_calculate)%PULSE_MAX);
        negative_flag = 1;
      }
   
     for(; degree_loop >0; degree_loop--){
       
       if(negative_flag == 0)
         previous_value++; 
       else
         previous_value--;
       
       DisableInterrupts;
           Pulse_High = previous_value; 
       EnableInterrupts; 
       Timer_Delay_10ms(1);
     
     }
     /// DO MAFFF
     
     return degree_calculate; 
}



unsigned char RCServo_Set_Degrees(unsigned char degrees){
 unsigned int degree_calculate =0; 
     degree_calculate = RCServo_Degrees_Calulate(degrees);
    
     DisableInterrupts;
     Pulse_High = degree_calculate; 
     EnableInterrupts;
}   

// 600us 1500us 2400us   // 187
void interrupt 10 OC2_isr(void){
    TFLG1 = TFLG1_C2F_MASK; // clear the flag 
   
      
   if (!(OC2_Output_Flag)){
    
       SET_OC_ACTION(2,0x02); // set OC0 pin action to pull low
      // RCSERVO_TIMER  += (Pulse_High); // start a new OC0 operation 
      RCSERVO_TIMER += (Pulse_High); // start a new OC0 operation 
   }
   
   else {

   	 SET_OC_ACTION(2,0x03); // /* set OC0 pin action to pull high /
     //RCSERVO_TIMER  += (Pulse_Low- Pulse_High); ///* start a new OC0 operation /
     RCSERVO_TIMER  += (Pulse_Low- Pulse_High); ///* start a new OC0 operation /
   }
     OC2_Output_Flag = ~OC2_Output_Flag;  
        
}