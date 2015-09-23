#include "L2665.h" 
   
   

// NEEDS power from external power source// not the axeman PSU
void DCM_INIT(void){
   unsigned char value=0;
 
   DCM_INIT_ENABLE_DDR();
   DCM_INIT_DDR(); 

   PWM_INIT();
  // RESET COUNTERS   
   PWMCNT5 = 0x00;
   PWMCNT4 = 0x00;
  
   DCM_PORT |= 0x0A;
   return; 
}


unsigned char PWM_PERCENTAGE_CONVERSION(unsigned char percentage){
   unsigned long value =0; 
   value = ((PWM_DUTY_16) * percentage);
   value /= 100;
  
  return (unsigned char)value; 
}


/*
    PWM duty cycle  is 130ms

*/
void PWM_INIT(void){
    // ENABLE PWM PORT
     SETBIT(PWME, (DC_ENABLE_A | DC_ENABLE_B));
      PWME |= 0x30; 
    // SET BOTH PINS TO HIGH AT DEFAULT // LOW WHEN DUTY IS REACHED
     SETBIT(PWMPOL, (DC_ENABLE_A | DC_ENABLE_B));  // HIGH then low when duty is reached // 
     SETBIT(PWMCLK, (DC_ENABLE_A | DC_ENABLE_B));  // uses SA CLOCK (clock /512)
     
     //  
     PWMPRCLK  = 0x06;    // chjange this lATER

     PWMSCLA =  PWM_CLOCKSA;     
     // USE SA ON BOTH A AND B 
     SETBIT(PWMCLK, (DC_ENABLE_A | DC_ENABLE_B)); // center alighn both channels 
      // SET PERIOD TO 255
     PWMPER4 = PWM_DUTY_16;  // set period 255
     PWMPER5 = PWM_DUTY_16;   // set period 255

}
   // stepper motor    //
// use a timer PINT / 
// motor should read from the switches via interrupt//


