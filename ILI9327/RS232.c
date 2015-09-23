/*
Serial libraries -
Serial 
        PS0 - RX
        PS1 - TX 
        
              
*/ 


#include "RS232.h"

 unsigned char RS232_COMPARE; 


/* 
  RS232 - data array 
  Pointer - 
  Termination string - 0xDEAD - 0xBEEF
*/
extern unsigned char RS232_Termination_String[4] = {
 //  0xDE, 0xAD, 0xBE, 0xEF
   'a','b', 'c','d'
};

extern unsigned char RS232_Transmission_String[4] = {
  //  0xFE, 0xED, 0xDE, 0xAD 
   'q','w','e','r'
};


unsigned char RS232_Init(unsigned long baudRate){
   unsigned char rs232_clock=0;
   
    RS232_BAUD_RATE = (unsigned long)baudRate;
   // Set Control register  
    RS232_CONTROL_REG =   RS232_STATUS_N81;  // N81 data
 
    /* bit value meaning
    7   0    LOOPS, no looping, normal
    6   0    WOMS, normal high/low outputs
    5   0    RSRC, not appliable with LOOPS=0
    4   0    M, 1 start, 8 data, 1 stop
    3   0    WAKE, wake by idle (not applicable)
    2   0    ILT, short idle time (not applicable)
    1   0    PE, no parity
    0   0    PT, parity type (not applicable with PE=0) */ 
 
    RS232_CONTROL_REG2 = 0x2C; // (SCICR2_RIE_MASK)   | (SCICR2_RE_MASK | SCICR2_TE_MASK);   // arm only the RDRF
  
    /* bit value meaning
    7   0    TIE, no transmit interrupts on TDRE
    6   0    TCIE, no transmit interrupts on TC
    5   0    RIE, no receive interrupts on RDRF
    4   0    ILIE, no interrupts on idle
    3   1    TE, enable transmitter
    2   1    RE, enable receiver
    1   0    RWU, no receiver wakeup
    0   0    SBK, no send break */ 
  
   //SET BAUDRATE 
  // allow for higher ECLOCKS 
  rs232_clock = (E_CLOCK) / 8000000;  // default is 8MZ
  
  // SCI Baudrate = SCI Clock / (16 * SCIBDL) -- Eclock 8MHZ 
  /// so far so good pretty damn accurate 
  switch(baudRate){
    case 2400:  
      RS232_BAUDLB_REG=(208*rs232_clock); 
      break;
    case 4800:  
      RS232_BAUDLB_REG=(104*rs232_clock); 
      break;
    case 9600:  
      RS232_BAUDLB_REG=(52*rs232_clock);  
      break;
    case 19200:
      RS232_BAUDLB_REG=(26*rs232_clock);  
      break;
    default:    
      RS232_BAUDLB_REG = (52*rs232_clock) ;  // default to 9600 
  }
   RS232_BAUDHB_REG = 0;  // upper bits are 0 
    
    
    
   if (SCISR1 & 0x80){ /*Poll TDRE flag*/
      printf("TDRE OK"); /*TDRE set, return OK*/
    }
    
   else{
    /*TDRE clear, return ERROR*/
      printf("TDRECLEAR ERROR");
      return 0x05;    //EIO      5  /* I/O error */
    }
    
  printf("\n RS232 Setup");   
        
  return 0;
}


char RS232_Write(unsigned char data){
  while(!(RS232_STATUS_REG & SCISR1_TDRE_MASK));    // READ TDRE FLAG
    SCIDRL = data;
  return 0;
}



char RS232_Write_String(unsigned char *data){
  while(*data)
    RS232_Write(*data++);  
 return 0;
}



unsigned char RS232_Read( void )
{
	while(!(SCISR1 & SCISR1_RDRF_MASK));
	return(SCIDRL);
}




     //interrupt 8 void TC0handler(void){
 // RDRF IS ONLY INTERUPTED 
 /*
 13.5.2.2.3 RDRF Description
The RDRF interrupt is set when the data in the receive shift register transfers to the SCI data register. A
RDRF interrupt indicates that the received data has been transferred to the SCI data register and that the
byte can now be read by the MCU. The RDRF interrupt is cleared by reading the SCI status register one
(SCISR1) and then reading SCI data register low (SCIDRL)
 */



unsigned char *Process_RS232(unsigned char *RS232_INPUT, unsigned char Length){
   // unsigned char RS232_OUTPUT[RS232_MESSAGE_STORAGE_LENGTH]; 
    unsigned char counter = 0; 
    
  
      for(counter=1; counter < Length; counter++){
          
         switch(counter){
          case 1:
             // COMPORT
            RS232_Com_PORT =  RS232_INPUT[counter];
          //  printf("\n ComPort: %c", RS232_Com_PORT); 
            break;
          case 2: 
             // Board Function
             Board_Function =    RS232_INPUT[counter];
            // printf("\nBoard_Function: %c ", Board_Function);
             break;
          case 3:
             // Data Sequence 
             MessageSequenceNumber=   RS232_INPUT[counter];
           //  printf("\nMessageSequenceNumber: %c", MessageSequenceNumber);
            break;
          case 4:
            // Packet length
            lDataLength =   RS232_INPUT[counter];
          //  printf("\nLdatalenghtL: %d\n DATA:", lDataLength); 
            break;  
         }  
        
         
        if(counter >= 4){
        
         //  printf("%c",  RS232_INPUT[counter]); 
        }
      }
     
      

  return; //RS232_OUTPUT;
}


     /*
     13.5.2.2.3 RDRF Description
The RDRF interrupt is set when the data in the receive shift register transfers to the SCI data register. A
RDRF interrupt indicates that the received data has been transferred to the SCI data register and that the
byte can now be read by the MCU. The RDRF interrupt is cleared by reading the SCI status register one
(SCISR1) and then reading SCI data register low (SCIDRL)
     */
/// non ideal code should only analyze the termination, and transmission // 
interrupt 20 void SCIhandler(void){
     
    
     RS232_Counter_ = (RS232_Counter%4);
     // Check Flag for RDRF // INPUT READ 
     //   cleared by reading the SCI status register one
     //(SCISR1) and then reading SCI data register low (SCIDRL)
     // 
   if ((SCISR1 & SCISR1_RDRF_MASK)){
     RS232_Data_Input[RS232_Counter_] = SCIDRL;             
     data_in = SCISR1;    // clear flag 
     RS232_Write(RS232_Data_Input[RS232_Counter_]); 
     // printf("%c", RS232_Data_Input[RS232_Counter_]); //       not useful delay large!
   }
   
    // read for starting string //
    ///Costly if statment only compare if Recieve flag =0 
   if(!RS232_Recieve_Flag){
    
    RS232_COMPARE =RS232_Data_Input[(RS232_Counter_)]; 
    
     if((RS232_Transmission_Flag ==3) && (RS232_COMPARE == RS232_Transmission_String[3]))  {
            RS232_Transmission_Flag =4;
          //  printf("FLAG 4");
     }
      else if(RS232_Transmission_Flag ==3) 
            RS232_Transmission_Flag =0;
     
     
       if((RS232_Transmission_Flag ==2) && (RS232_COMPARE == RS232_Transmission_String[2])) {
            RS232_Transmission_Flag =3;
        //   printf("FLAG 3");
     }
      else if(RS232_Transmission_Flag ==2) 
            RS232_Transmission_Flag =0 ;
     
      if((RS232_Transmission_Flag ==1 ) && (RS232_COMPARE == RS232_Transmission_String[1])) {
            RS232_Transmission_Flag =2;
        // printf("FLAG 2");
     }
      else if(RS232_Transmission_Flag ==1) 
            RS232_Transmission_Flag =0; 

      if(RS232_COMPARE == RS232_Transmission_String[0])
            RS232_Transmission_Flag =1;
     
            if (RS232_Transmission_Flag ==4){
                 //printf("FLAG Get SET"); 
                 Message_Storage_Counter =0; // reset counter
                 RS232_Transmission_Flag =0;   
                 RS232_Recieve_Flag = 1; 
        
              }   
   }
        
        
      
   if(RS232_Recieve_Flag == 1){
      
   // Record incoming rs232 message   
        MessageStorageArray[Message_Storage_Counter++] = RS232_Data_Input[(RS232_Counter_)]; 
        
           
      // printf("%c ",MessageStorageArray[Message_Storage_Counter-1]); 

   /// messy // if termination flag =0 it compares all values of termination string with current data input// 
   /// not  nice but fast // 
      if((MessageStorageArray[(Message_Storage_Counter-1)] == RS232_Termination_String[3] )&& 
      (MessageStorageArray[(Message_Storage_Counter-2)]  == RS232_Termination_String[2])&&  
      (MessageStorageArray[(Message_Storage_Counter-3)]  == RS232_Termination_String[1]) && 
      (MessageStorageArray[(Message_Storage_Counter-4)]  == RS232_Termination_String[0]) ){
          
           RS232_Recieve_Flag = 0; 
           RS232_Processed_Data_Flag= 1; // set processed flag high for main 
           RS232_COUNTER_OUTSIDE = RS232_Counter; 
           RS232_Counter =0;
        
           return; 
     }
 

     
   }
  
  ///
  if (Message_Storage_Counter > (RS232_MESSAGE_STORAGE_LENGTH)){
       Error_Flag_Number = 12;
       RS232_Recieve_Flag = 0; 
       RS232_Processed_Data_Flag= 0; // set processed flag high for main 
       RS232_Counter =0;   
      return; 
  }
  // put in case for if Message_Storage counter  > 120 
      
  RS232_Counter++;    
  return; 
}  
