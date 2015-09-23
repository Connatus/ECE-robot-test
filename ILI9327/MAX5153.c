#include "MAX5513.h"



// doesnt pull clock low at thge same time for some reason.///
unsigned char MAX5513_Set_Chan(unsigned char vout, unsigned char channel){
   unsigned char max_chan =0, max_spi_temp=0, max_spi_temp_2=0;
      
   //default to channel 'b'
   if (channel == 'a' || channel == 0x00)
      max_chan = MAX5513_CTL_LOAD_A; 
   else
      max_chan = MAX5513_CTL_LOAD_B; 
   
   
  // refrence voltage = 66 = 1.29 v
   max_spi_temp = ((max_chan << 4)&0xF0) | ((vout >> 4)&0x0F);
   max_spi_temp_2 =   ((vout << 4)&0xF0);
//   printf("max1 %d max2 %d ", max_spi_temp, max_spi_temp_2); 
    
   MAX5513_CS_LOW();
   SPIDR = max_spi_temp;
   while((SPISR & 0xA0)!= 0xA0);

   

   SPIDR = max_spi_temp_2;   
   while((SPISR & 0xA0)!= 0xA0);
   asm("nop");       // delay necessary for accurate transfer of data //  clock out of sync otherwise  
   MAX5513_CS_HIGH();

 //  max_spi_temp = Analog_Read(0x7);
//   printf(" \n %d ", max_spi_temp); 
    
  

  return 0; 

}

    // 9 // and fff 
unsigned char MAX5513_Send_CMD(unsigned char command, unsigned char data){
    unsigned char max_chan =0, max_spi_temp=0, max_spi_temp_2=0;
     MAX5513_CS_LOW();
     
     max_spi_temp = ((command << 4)&0xF0) | ((data >> 4)&0x0F);
     max_spi_temp_2 =   ((data << 4)&0xF0);
     SPI_Send_Char(max_spi_temp);
     while((SPISR & 0xA0)!= 0xA0);
   
      
    
     SPI_Send_Char(max_spi_temp_2); 
     while((SPISR & 0xA0)!= 0xA0);
     asm("nop");       // delay necessary for accurate transfer of data 
   
    MAX5513_CS_HIGH();
   
   return 0; 
 }


unsigned char MAX5513_Set_Read(unsigned char vout, unsigned char channel, unsigned char analog_in_pin){
  unsigned char analog_in =0;
  
   MAX5513_Set_Chan(vout,channel);
   
   if (analog_in_pin < 8)
     analog_in = Analog_Read(analog_in_pin);

   else  
    analog_in = Analog_Read(0x7);
 
   
    printf(" \n %d ",  Analog_Read(analog_in_pin));   

  return analog_in;
}