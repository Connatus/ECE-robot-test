#include "Test.h"
/*
Functions to init device, move motor with parameters for speed, direction, full/half step, continuous or fixed number of steps.
Stepping happens in ISR.
Function to get motor's current position and state.   //MessageStorageArray
*/ 

/*Variables used to navitage the DATA ARRAY INPUT*/
/* ALL VARIABLES USE AN OFFSET */

#define RS232_MESSAGE_OFFSET            5
// USED IN STEPPER MOTOR ECD 


// CONVERT FROM ASCII TO DECIMAL 
#define RS232_STM_SPEED               0     // 3DEC 
#define RS232_STM_DEGREE              3     // 3DEC
#define RS232_STM_DIRECTION           6     // 1DEC
#define RS232_STM_GOHOME              7  
                                           // blank space
#define RS232_SERVO_SPEED             8    
#define RS232_SERVO_DEGREE            11  
#define RS232_SERVO_DIRECTION         14   
#define RS232_SERVO_GOHOME            15  

#define RS232_DCMR_SPEED              0    // 3 dec
#define RS232_DCMR_BREAK              3    // 1 dec 
#define RS232_DCMR_DIRECTION          4    // 1 dec 

#define RS232_DCML_SPEED              6
#define RS232_DCML_BREAK              9
#define RS232_DCML_DIRECTION          10   

#define RS232_PING_HIGH               'A'


unsigned int ASCII_TO_DECIMAL(unsigned char *INPUT_ASCII,unsigned int Offset, unsigned int Length);

/*
  SIMPLE PING PROGRAM 
  -----
  When loaded, the function scans the input data for 'A' 
  all characters must be an 'A'
  
  Will SPIT OUT ERROR through RS232 if not all chars match
  Will repeat the number of 'A's recieved to the output. 
*/
//qwer2343AAAAAAAAabcd   
unsigned char Ping_ECD( unsigned int Data_length){
  unsigned char PING_VALUE =0; 
  unsigned char PING_COMPARE = ((Data_length-RS232_MESSAGE_OFFSET -5)); 
  unsigned char PING_FLAG = 0x00;
  
  for(PING_VALUE =0; PING_VALUE < Data_length; PING_VALUE++){
    printf("%d ", Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET+(PING_VALUE))]);   
  }
  
  printf(" %d LENGTH  %d ", Data_length, PING_COMPARE); 
  for(PING_VALUE =0; PING_VALUE < PING_COMPARE; PING_VALUE++){
    if (!((Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET+(PING_VALUE))]) ==  RS232_PING_HIGH))
       PING_FLAG=0;
    printf("\n  %d - %d ", Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET+(PING_VALUE))],RS232_PING_HIGH);   
    printf(" %c", Local_Message_Storage_Array_RS232[PING_VALUE+RS232_MESSAGE_OFFSET ]); 
    PING_FLAG++;
  }
  
  if(PING_FLAG == PING_COMPARE) {
    for(PING_VALUE =0; PING_VALUE < PING_COMPARE; PING_VALUE++)
       RS232_Write('A');
  }
  
  else
    RS232_Write_String("ERROR");

  return 0; 
}


  
  /*  Set Stepper and Servo - Camera Direction 
     
     2234 100 050 R0   100 90 L 
       100 050 R 0  = Stepper - 50DEG R  GO HOME = 0      
       100 90 L     = SERVO 100 speed 90 DEG SET 
  
  */
  //qwer2234100050R010090Labcd
unsigned char Camera_ECD( unsigned int Data_length){
  
  // moves both stepper motor and CAMEAR
    unsigned char STM_SPEED = 0;         
    unsigned char STM_DEGREE= 0;       
    unsigned char STM_DIRECTION= 0;     
    unsigned char STM_GOHOME =0;                                
    unsigned char SERVO_SPEED= 0;   
    unsigned char SERVO_DEGREE  = 0;     
    unsigned char SERVO_DIRECTION= 0;
    
      STM_SPEED =     ASCII_TO_DECIMAL((Local_Message_Storage_Array_RS232), (RS232_MESSAGE_OFFSET + RS232_STM_SPEED), (3)); 
      STM_DEGREE =     ASCII_TO_DECIMAL((Local_Message_Storage_Array_RS232), (RS232_MESSAGE_OFFSET + RS232_STM_DEGREE ), (3)); 
      STM_DIRECTION = (Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET +  RS232_STM_DIRECTION)]); 
      STM_GOHOME = (Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET +  RS232_SERVO_GOHOME )]); 
      
      SERVO_SPEED =     ASCII_TO_DECIMAL((Local_Message_Storage_Array_RS232), (RS232_MESSAGE_OFFSET + RS232_SERVO_SPEED), (3)); 
      SERVO_DEGREE =     ASCII_TO_DECIMAL((Local_Message_Storage_Array_RS232), (RS232_MESSAGE_OFFSET + RS232_SERVO_DEGREE), (3)); 
      SERVO_DIRECTION = (Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_SERVO_DIRECTION)]); 
     
    // printf("\n-------------------------------------\n");
    // printf("\n STEPPER MOTOR:    SP: %d   DEG: %d   DIRECTION: %c    GOHOME: %c", STM_SPEED, STM_DEGREE, STM_DIRECTION,  STM_GOHOME ); 
    // printf("\n SERVO MOTOR:    SP: %d   DEG: %d    ",SERVO_SPEED,SERVO_DEGREE); 
      
     
     STMOTOR_MOVE_DEGREES(STM_DEGREE, STM_DIRECTION);
     RCServo_Set_Degrees_Sweep(SERVO_DEGREE%(RC_DEGREE_RANGE+1));
     
  return 0; 
} 

/*
Open-loop Motor() function as on Handy Board Interactive C
- can move both motors in both directions
       //0600F00400
          060 0 F  - Right MOTOR - 60%max 0 break Forward
           0  
           0400B   - Left Motor - 40% max 0 break Backward 
*/                  //qwer11340600F00400Babcd 

unsigned char DC_Motor_ECD( unsigned int Data_length){ 
    unsigned char DCMR_SPEED;              
    unsigned char DCMR_BREAK;           
    unsigned char DCMR_DIRECTION;       

    unsigned char DCML_SPEED;              
    unsigned char DCML_BREAK;            
    unsigned char DCML_DIRECTION;
     
                 
    DCMR_SPEED = ASCII_TO_DECIMAL((Local_Message_Storage_Array_RS232), (RS232_MESSAGE_OFFSET + RS232_DCMR_SPEED), (3)); 
    DCMR_BREAK = (Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET  + RS232_DCMR_BREAK )]) - 0x30;
    DCMR_DIRECTION = (Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_DCMR_DIRECTION)]) - 0x30; 
     
      printf("\n RIGHT MOTOR:    SP: %d   BR: %d   DR: %c ", DCMR_SPEED,  DCMR_BREAK, DCMR_DIRECTION+0x30); 
    
    DCML_SPEED = ASCII_TO_DECIMAL((Local_Message_Storage_Array_RS232), (RS232_MESSAGE_OFFSET + RS232_DCML_SPEED ), (3)); 
    DCML_BREAK = (Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET  + RS232_DCML_BREAK )] ) - 0x30;
    DCML_DIRECTION = (Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_DCML_DIRECTION)]) - 0x30; 
     
      printf("\n LEFT MOTOR:    SP: %d   BR: %d   DR: %c ", DCML_SPEED,  DCML_BREAK, DCML_DIRECTION+0x30);
    
       DC_L_SETSPEED_PERCENTAGE( DCML_SPEED ); 
       DC_R_SETSPEED_PERCENTAGE( DCMR_SPEED );
 
       if((DCML_DIRECTION == 1) || (DCML_DIRECTION == ('F'-0x30))){
           DC_L_FORWARD_DIRECTION;
       }
       else 
           DC_L_REVERSE_DIRECTION; 
       
       if((DCMR_DIRECTION == 1) || (DCMR_DIRECTION == ('F'-0x30))){
           DC_R_FORWARD_DIRECTION;
       }
       else 
           DC_R_REVERSE_DIRECTION; 
        
    if(DCMR_BREAK == 1 || DCMR_BREAK == ('B'-0x30))
       DC_R_BREAK;
     
      if(DCML_BREAK == 1 || DCML_BREAK == ('B'-0x30))
       DC_L_BREAK;  
    
                       
      return 0; 
} 

unsigned int ASCII_TO_DECIMAL(unsigned char *INPUT_ASCII, unsigned int Offset, unsigned int Length){
   unsigned int counter =0;
   unsigned int value =1;  
   unsigned char multiply=0; 
   unsigned int DECIMAL_OUT =0; 
   
   for(multiply =1; multiply < Length ; multiply++)
      value *= 10; 
   
   
   for(counter =0; counter < Length; counter++){
     DECIMAL_OUT += ((INPUT_ASCII[(Offset + counter)] -0x30)*value);
     value /= 10;  
   }
   
   return DECIMAL_OUT; 

}


unsigned char Stepper_Motor_ECD( unsigned int Data_length){ 
    unsigned int i =0;
    
    for(i=0; i < Data_length; i++)
      printf("%d", Local_Message_Storage_Array_RS232[i]);
    
    printf("\n STEPPER MOTOR"); 
return 0; 
} 

 /*
Function to init device, set position of servo.  
Sweep function with final position and time as parameters  (uses ISR)
*/  
unsigned char RC_Servo_ECD( unsigned int Data_length){ 
   printf("RUNNING SERVO AND STEPPER  SHIT"); 
   
     for(i=0; i < Data_length; i++)
      printf("%d", Local_Message_Storage_Array_RS232[i]);
      
      printf("\n STEPPER MOTOR:    SP: %d   DEG: %d   HOME: %d ", Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_STM_SPEED )], 
      Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_STM_DEGREE )],Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_STM_DIRECTION )]); 
      
      printf("\n SERVO MOTOR:    SP: %d   DEG: %d   HOME: %d ", Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_SERVO_SPEED)], 
      Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_SERVO_DEGREE )],Local_Message_Storage_Array_RS232[(RS232_MESSAGE_OFFSET + RS232_SERVO_DIRECTION  )]); 
      
 return 0;
 } 
 

/*
  Adding to the basic techniques,
- can correctly handle a wide range of motor speeds in both directions
- can measure both motor speeds simultaneously
- Motor() function capable of handling changes in direction automatically
(stop, wait for encoder, restart in other direction)
- handles timer wrap correctly

*/ 
unsigned char DC_Motor_Encoder_ECD(unsigned int Data_length){ 
     printf("ENKOTOR "); 
     
        /// NOT REALLY NECESSARY            

    for(i=0; i < Data_length; i++)
      printf("%c", Local_Message_Storage_Array_RS232[i]);
 return 0; 
}


unsigned char RS232_ECD(unsigned char COM_PORT){
  
   unsigned char RS232_Input =0; 
   terminalemulator(); //reset current terminal emulator 
    printf("\n INTERRUPTS DISABLED !!!!!!\n"); 
    printf("\n Begin Communication with COM%d",COM_PORT);
    printf("\n BaudRate: %lu ", RS232_BAUD_RATE);   
    printf("\n Control Reg 1: %d     Control Reg 2: %d",RS232_CONTROL_REG, RS232_CONTROL_REG2); 
    printf("\n Begin Input: ");
    asm("SEI"); // DISABLE INTERRUPTS FOR RS232  
   for(;;){
     RS232_Input = RS232_Read();
     printf("%c", RS232_Input); 
   }

  return 0; 
} 

/*
Interrupt Rx, Polled Tx, functions to init device, send/receive strings (like puts/gets)
*/
unsigned char SerialTerminal_ECD(void){

 return 0;
} 
  
 
/*
Function to get the ADC value of a particular channel (like analog() function in IC).  
Function to read all 3 axes of the accelerometer and return in an array (passed in as a parameter)
 as engineering units with fixed point representation. 
*/ 
unsigned char Accelerometer_ECD(void){
    Accelerometer_Test_2(); 
 return 0; 
} 


/*
Function to init SPI port and DAC.  Write a specified value to the specified DAC channel.
Demonstrate by generating a waveform and sending to the DAC.  Display on scope
*/
unsigned char DAC_ECD(void){
    MAX5513_Test(); 
 return 0; 
} 



/// LCD TEST, ACCELEROMETER TEST, SPI TEST, RS232_TEst , TOUCH_SCREEN TEST 
/// NEEDS MOTOR TESTS, SD Test, encoders etc. MORE NEEDED



void ILI9327_INIT(void){
     ILI9327_INITALIZE();   
      
  terminalemulator();            
     return; 
}

void Touch_Test(void){
  unsigned int *touch_xy;
  unsigned char *test;
  	Analog_Init(0);
        
  for(;;){

  /// its pretty okay //no float // so not exact but pretty damn close 
   touch_xy = Touch_Screen_XY_Res();
    printf("\n x: %d  y: %d ", *(touch_xy +0), *(touch_xy + 1)); 
  
    Timer_Delay_10ms(30);
  }
}

void MAX5513_Test(void){
  unsigned char countx =0; 
	unsigned char MAX5513_INPUT = 7; 
	Analog_Init(1);
  ANALOG_ENABLE_PIN(MAX5513_INPUT);
  ANALOG_ENABLE_PIN(MAX5513_INPUT-1);
  printf("\nAnalog On PIN #%d", MAX5513_INPUT);
  printf("\nAnalog On PIN #%d", MAX5513_INPUT-1);  
  
  SPI_INIT(400000);
  SPI_Toggle_MasterSS(0);  // disable slave select from master                                          
  MAX5513_ON_3_4V(); // max voltage  
	MAX5513_INIT_DDR();
	  
	// Make Square // Make Triangle  
	   for(;;){
	      
	       MAX5513_Set_Chan(0xFF,2);
	       MAX5513_Set_Chan(countx++,1); //   make forever triangle
         Timer_Delay_10us(1);
         MAX5513_Set_Chan(0x00,2);
	       Timer_Delay_10us(1); 
	   }

  return;         
}




   // use null modem // 9600 baud     
void Test_RS232(void){
  unsigned char x=0, y=0;
   RS232_Init(9600);
   while(1){
      x++; 
       RS232_Write(x);
       printf("\n RS232 Write= 0x%x", x); 
     y= RS232_Read();
       printf(" Read= 0x%x",y); 
   }

  return; 
}
 
void testanal(void){

    DDRAD = 0xFF; 
    //ATDDIEN = 0x00;
  
  while(1){
      
      ILI9327_RESET_HIGH();
       ILI9327_CS_HIGH();
        ILI9327_RS_HIGH();
        ILI9327_WR_HIGH();  
         ILI9327_RD_HIGH();
         
    	Timer_Delay_1ms(5);
      
        ILI9327_CS_LOW() ; 
       ILI9327_RS_LOW();  
       ILI9327_WR_LOW();
       ILI9327_RD_LOW();  
      ILI9327_RESET_LOW() ;
      
    	Timer_Delay_1ms(5);
  
  }    
   

}
         


 // Short Mosi and MISo // should yield the same result 
void TEST_SPI(void){
   unsigned char Error =0; 
   SPI_INIT(400000);
   SPI_Toggle_MasterSS(0); 
   
  while(1){
     SPI_Send_Char(0xA5); 
    Error =  SPI_Recieve_Char(0x00);
    printf(" %x ", Error); 
    Error = 0x00; 
  }
   


}
