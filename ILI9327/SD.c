#include "SD.h"

#if _FATFSENABLE != 0
    /*
    
    http://www.sandisk.com/media/File/OEM/Manuals/SD_SDIO_specsv1.pdf
    
    ////
    CODE
    http://alumni.cs.ucr.edu/~amitra/sdcard/Additional/sdcard_appnote_foust.pdf
    */


char SD_CMD0[6]= {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};  // Initialize
char SD_CMD1[6]= {0x41, 0x00, 0x00, 0x00, 0x00, 0x01};  // Idle State


// SEND IDLE COMMANDS 
//char SD_CMD8[6] = {0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};   /// idle and illegal command
//char SD_CMD58[6] = {0x7A, 0x00, 0x00, 0x00, 0x00, 0xFD};   /// idle and illegal command
//char SD_CMD13[6] = {0x4D, 0x00, 0x00, 0x00, 0x00, 0x0D};   /// idle and illegal command

//char SD_CMD55[6]= {0x77, 0x00, 0x00, 0x00, 0x00, 0x01}; // Idle State
//char SD_CMD41[6]= {0x69, 0x00, 0x00, 0x00, 0x00, 0x01}; // Idle State
char SD_CMD16[6]= {0x50, 0x00, 0x00, 0x02, 0x00, 0x01}; // Set block size (1-512 in arguement)

//char SD_CMD17[6]= {0x51, 0x00, 0x0F, 0x40, 0x00, 0x01}; // Read single block
//char SD_CMD24[6]= {0x58, 0x00, 0x0F, 0x40, 0x00, 0x01}; // Write single block


// http://elm-chan.org/docs/mmc/gx1/sdinit.png// 

unsigned char SD_INIT(void){
  unsigned int count =0;
  char byte;
  char i; 

 /// cant get the card to communicate properly // 
  SPI_INIT(40000);  // slower speed still problems 
  SPI_Toggle_MasterSS(0); // use master ss 
  // enable CS on SD // 
  SD_INIT_DDR(); 
   SD_CS_LOW();
   Timer_Delay_1ms(5); /// wait 1ms  
 
 
 
 // Set DI and CS high and apply 74 clocks 
   SD_CS_HIGH(); 
  /* Init the card in SPI mode by sending at least 72 clocks Data and CS lines must be set to 1*/
	for(i = 0; i < 10; i++) 
	  SPI_Master_Transmit_Recieve(0xFF); /// send FF pull the data line high
 SD_CS_LOW();
 
 	printf("Successfully Sent Dummy Clocks \r");

 /* Init the CS output */
  printf("Turning on Chip \r");

   Timer_Delay_10ms(100); // DELAY 
   
    
    
	/* Send CMD0 GO_IDLE_STATE - Resets the card puts it in idle state if CS is pulled low and CMD0 is sent the card is put in 
	spi mode*/
	SPI_Master_Transmit_Bytes(SD_CMD0, MMC_CMD_SIZE); 
  if (SDRead_Response_R1(0x01)) // MMC responds with a R1 response     Idle State bit (0x01)
	{
		printf("CMD0 timeout Exiting!\r"); 
		return 1;
	}

	//SPI mode, the CRC feature is disabled and the CRC 
	
	printf("Successfully sent CMD0- device is in idle mode\r");

  
	/* Send some dummy clocks after GO_IDLE_STATE */
	SD_CS_HIGH();
	SPI_Recieve_Char(0xFF); 
	SD_CS_LOW()

	printf("send CMD1\r");
	/* Send CMD1 SEND_OP_COND until response is 0 */
	i = 0xFF; 
	while((SDRead_Response_R1(0xFF) != 0) && (i > 0))
	{
		SPI_Master_Transmit_Bytes(SD_CMD1, MMC_CMD_SIZE);
		i--;
	}
	
	if (i == 0){
		printf("CMD1 timeout\r");
		return 2;
	}

	/* Send some dummy clocks after GO_IDLE_STATE */
	SD_CS_HIGH();
	SPI_Recieve_Char(0xFF);
	SD_CS_LOW()

	

SPI_Master_Transmit_Bytes(SD_CMD16, MMC_CMD_SIZE);
if ((SDRead_Response_R1(0xFF)) == 1)printf("CMD16 timeout\r");
else printf("CMD16 Sent 512 bytes \r");

	SD_CS_HIGH();
	SPI_Recieve_Char(0x00);

	printf("mmc_init end\r");
 
  return 0; 
}


unsigned char SDRead_Response_R1(char response){
	char result;
	unsigned int count; 
		
	for (count=0; count < MMC_TIMEOUT; count++){
	//	result = SPI_Master_Transmit_Recieve(0xFF); // send dummy to read response
		   result = SPI_Master_Transmit_Recieve(0xFF); 
		if (result == response)
			return 0; // success
		
	}
	return 1; // time out error
}



#endif
