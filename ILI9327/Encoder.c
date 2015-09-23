#include "Encoder.h"

/*
  Encoder is completely unstable around 8v and higher   //timer is not triggered on random pulses // 
             VIN   HIGH (ms)    LOW                                              COUNT           ACTUAL COUNT X2 
  Encoder at 4v    1             1ms                        2.30 AVG   - approx  43.4
             5v    0.89          0.89                       1.82 AVG             54.94
             6v    0.7           0.7                        1.45 AVG             68.96
             7v    0.65          0.65                       1.24 AVG             80.64
             8v    0.5           0.68                       1.07 AVG             93.45
             9v    0.25          0.68                       0.92 AVG             108.69
             10v   0.2           0.68                       0.83 AVG             120.48
             11v   0.15          0.68
             12v   0.11          0.65  
                                                         
*/ 

void Encoder_Init(void){
    TIOS_INPUT_PIN((TIOS_IOS0_MASK | TIOS_IOS1_MASK));
    TIOS_OUTPUT_PIN(TIOS_IOS4_MASK); 
    TIE_ENABLE_PIN(((TIE_C0I_MASK) |(TIE_C1I_MASK) | (TIE_C4I_MASK)));    
   
    SET_TIMER_CLOCK_EDGE(0,TIMER_CHNL_CAPTURE_BOTH); 
    SET_TIMER_CLOCK_EDGE(1,TIMER_CHNL_CAPTURE_BOTH); 
   
  
    
    EN_L_Pulse_Flag =0;
    EN_R_Pulse_Flag =0;
    L_TIMER =0;
    R_TIMER =0; 
    L_Counter =0;
    R_Counter =0; 
     
    WATCH_L_COUNTER =0;
    WATCH_R_COUNTER =0;
    WATCH_DOG_FLAG =0; 
}

void ENCODER(void){
   unsigned char Error =0;
   int Encoder_L_Counter =0;
   int Encoder_R_Counter =0; 
   unsigned char Encoder_Watchdog_Flag =0; 
     
    Encoder_Init(); 
    EnableInterrupts;
    // get interrupt point 
     for (;;){
        // PASS ENCODER VARS TO MAIN
        DisableInterrupts;
        Encoder_L_Counter = L_Counter;
        Encoder_R_Counter = R_Counter; 
        Encoder_Watchdog_Flag =  WATCH_DOG_FLAG;
        EnableInterrupts;
        
        if(Encoder_Watchdog_Flag ==1){
            
             printf("R %d", Encoder_R_Counter); 
              printf("L %d", Encoder_L_Counter); 
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

// LEFT ENCODER 
// Count both high and low // gives more accurate values 
interrupt 8 void TC0handler(void){
  L_TIMER = ENCODER_LEFT_TIMER	; // Read timer value 
  
     /// IF High, get rest of pulse width//
    if(!(ENC_A_CHECK ) && (EN_L_Pulse_Flag == 0)){
        EN_L_Pulse_Flag=1; // when low 
        L_Counter++; 
    } 
    
    else if( (ENC_A_CHECK ) && (EN_L_Pulse_Flag == 1)){
       EN_L_Pulse_Flag =0;
       L_Counter++; 
    }       
}


// RIGHT ENCODER    Doesnt work for some reason 
interrupt 9 void TC1handler(void){

  
     /// IF High, get rest of pulse width//
    if(!(ENC_B_CHECK ) && ( EN_R_Pulse_Flag== 0)){
        EN_R_Pulse_Flag =1; // when low 
        R_Counter++;
    } 
    
    else if( (ENC_B_CHECK ) && ( EN_R_Pulse_Flag == 1)){
       EN_R_Pulse_Flag =0;
       R_Counter++; 
    }         
  R_TIMER = ENCODER_RIGHT_TIMER	; // Read timer value 
}




// USED FOR Clearing the count variable 
interrupt 12 void TC4handler(void){
      TFLG1 = TFLG1_C4F_MASK; // clear the flag 
 
      WATCH_DOG_FLAG = 1; 
      WATCHDOG_TIMER = TCNT + 12500; ///feed dog 100ms delay      
}
