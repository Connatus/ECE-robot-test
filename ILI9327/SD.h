#ifndef SD_H_INCLUDED
#define SD_H_INCLUDED
                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "macros.h" 
#include "SPI.h"
#include "Timer.h"


/*******************************************/
// SD and FAT Libraries 
/*******************************************/
#include "ff.h" // use FatFs from Elm-Chan.org
#include "ffconf.h"
#include "integer.h"
#include "diskio.h" // use FatFs from Elm-Chan.org (diskio used for disk initialization)



   // 8Bit IO expander with open drain outputs  //
   //http://ww1.microchip.com/downloads/en/DeviceDoc/20002121C.pdf 
  

#define SD_INIT_DDR() { SETBIT(SD_DDR,SD_CS  );}
#define SD_CS_LOW()  {  CLEARBIT( SD_PORT,SD_CS  );	} 
#define SD_CS_HIGH() {  SETBIT( SD_PORT, SD_CS  );	}	




#define    SD_DDR    DDRM
#define    SD_PORT   PTM
#define    SD_CS     PTM_PTM3_MASK



#define MMC_CMD_SIZE 6
#define MMC_TIMEOUT  0xFF
#define MMC_BLOCK_SIZE 512

/* Definitions for MMC/SDC command */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define CMD13	(13)		/* SD_STATUS (SDC) */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* SET ERASE START BLOCK */
#define CMD33	(33)		/* SET ERASE FINISH BLOCK */
#define CMD38	(38)		/* EXECUTE ERASE BLOCK ON CMD32 & CMD33 BLOCKS */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */



 

unsigned char  mmc_response(unsigned char  response);
// return error //
unsigned char SD_INIT(void);
void mmc_read_block(unsigned int  block_number, unsigned char * block_address);



unsigned char SDcart_disk_read(unsigned char  *buffer_array, unsigned long long block_number);
unsigned char  SDSend_CMD(char command,  unsigned long argument);
unsigned char  SDCard_Read(unsigned char  *buffer_array, unsigned long length);
unsigned char  SDCard_Disk_Write(unsigned char  *buffer_array, unsigned long long block_number);
unsigned char  SDCard_Write(unsigned char  *buffer_array, unsigned int  length);
unsigned char  SDRead_Response_R1(char response);
;


#endif /* SWITCHES_ */