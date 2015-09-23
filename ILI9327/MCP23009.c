#include "MCP23009.h"


 /*
  
 
 */ 
 
 
unsigned char MCP23009_TEST(void){
   unsigned int i =0;
   unsigned char Error =0;
  
   SPI_INIT(400000);
   SPI_Toggle_MasterSS(0); // disable CS on SD // 
   MCP23009_INIT_DDR();

 // set ddr on chip 
   MCP23009_Register_Write(MCP23009_IODIR, 0xFF);
 //  Timer_Delay_10us(1);
   MCP23009_Register_Write(MCP23009_OLAT, 0x00);

   MCP23009_Register_Write(MCP23009_IPOL, 0x00);  	
   
   MCP23009_Register_Write(MCP23009_GPPU, 0x00);
   
   MCP23009_Register_Write(MCP23009_GPIO, 0x00);
 
  // Error = MCP23009_Register_Read(MCP23009_GPIO, 0x00);
  //    Error = MCP23009_Register_Read(MCP23009_IODIR, 0x00);
   
 //  printf(" %d ", Error);  

        
    while(1){
    
     MCP23009_Register_Write(MCP23009_GPIO, 0x00);
    // Timer_Delay_10us(1);
    // Error = MCP23009_Register_Read(MCP23009_OLAT);
     Timer_Delay_10us(50);
     MCP23009_Register_Write(MCP23009_GPIO, 0xFF);

      Timer_Delay_10us(50);
       
    }

}





/*
The SPI write operation is started by lowering CS   The
write command (slave address with R/W bit cleared) is
then clocked into the device. The opcode is followed by
an address and at least one data byt

*/

unsigned char MCP23009_Register_Write(unsigned char Register, unsigned char Data){

   MCP23009_CS_LOW(); 
   // Send Write/ Read Command 
   // Send register op code
   // SEnd address  
   SPI_Send_Char(MCP23009_OPCODE_WRITE);
   SPI_Send_Char(Register);
   SPI_Send_Char(Data); 
   
   
   MCP23009_CS_HIGH(); 	
}



/*The SPI read operation is started by lowering CS SPI read command (slave address with R/W bit set) is
then clocked into the device. The opcode is followed by
an address, with at least one data byte being clocked
out of the device*/

unsigned char MCP23009_Register_Read(unsigned char Register){
   unsigned char MCP23009_Read =0; 
   asm("NOP");  
   MCP23009_CS_LOW(); 
   // Send Write/ Read Command 
   // Send register op code
   // SEnd address  
   SPI_Send_Char(MCP23009_OPCODE_READ);
   SPI_Send_Char(Register);
   MCP23009_Read = SPI_Recieve_Char(0xFF);  
   MCP23009_CS_HIGH();
   asm("NOP");  	
    
   return MCP23009_Read; 	
}
    