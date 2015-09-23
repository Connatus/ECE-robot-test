#include "error.h"

unsigned char ERROR_PRINT_SCREEN_2(unsigned char *errorlocation, unsigned char ERRORNO){
 	struct Terminal_Program_Values	*pointTerminal = &TerminalProperties;
  struct LCD_Geometry *pointCurrent= &Current;
	struct LCD_Properties *pointProperties= &Properties;
	unsigned int ACCD_=0, INDEXX=0, INDEXY=0, IP_=0, PC_=0, SP_=0;
	unsigned char ACCA_=0, ACCB_=0, PPAGE_=0, CCR_=0; 

// if incoming error == 0 // No error occured
   if(!ERRORNO)
    return 0; 
   
   /// Disable any currently running interrupts /// 
   LCD_Fill_Rectangle(0,0,pointTerminal->xResolution,pointTerminal->yResolution, 0x000000);
   // fill outline 
   LCD_Fill_Rectangle(0,pointProperties->xResolution-100,100,pointProperties->yResolution ,0xFF00FF); //
   LCD_Fill_Rectangle(10,pointProperties->xResolution-90,80,pointProperties->yResolution-20 ,0x000000); // 

   // give errors  
  
  pointTerminal->previousx = 20; 
  pointTerminal->currentline = 2;
	pointCurrent->color = 0xFF00FF;
	pointCurrent->size = 2;
	
	
	printf("FATAL SOFTWARE ERROR");  
	pointTerminal->currentline = 3;
  pointTerminal->previousx = 20; 
	printf("ERROR NUMBER: %d", ERRORNO);

  pointTerminal->currentline = 4;
  pointTerminal->previousx = 20; 
	printf("SEE LINUX ERRONO DOCUMENTATION");
	  	
	  pointTerminal->currentline = 9; 
    pointTerminal->previousx = 15;
    printf("%s", errorlocation);

	pointCurrent->size = 3;	
   while(1){
     pointTerminal->currentline = 5;
     pointTerminal->previousx = 15;     	pointCurrent->color = 0xFF00FF;
  	 printf("IT'S SAFE TO PANIC");
  	 Timer_Delay_10ms(20);
  	
  	 pointTerminal->currentline = 5;
     pointTerminal->previousx = 15;     	pointCurrent->color = 0x000000;
     printf("IT'S SAFE TO PANIC");
     Timer_Delay_10ms(20);
  	
     continue; 
   }

   return 0; 
 
 }
 

// Holds on error // Can never be escaped unless 
unsigned char ERROR_PRINT_SCREEN(unsigned char ERRORNO){
	struct Terminal_Program_Values	*pointTerminal = &TerminalProperties;
  struct LCD_Geometry *pointCurrent= &Current;
	struct LCD_Properties *pointProperties= &Properties;
	unsigned int ACCD_=0, INDEXX=0, INDEXY=0, IP_=0, PC_=0, SP_=0;
	unsigned char ACCA_=0, ACCB_=0, PPAGE_=0, CCR_=0; 

// if incoming error == 0 // No error occured
   if(!ERRORNO)
    return 0; 
   
   /// Disable any currently running interrupts /// 
   LCD_Fill_Rectangle(0,0,pointTerminal->xResolution,pointTerminal->yResolution, 0x000000);
   // fill outline 
   LCD_Fill_Rectangle(0,pointProperties->xResolution-100,100,pointProperties->yResolution ,0xFF00FF); //
   LCD_Fill_Rectangle(10,pointProperties->xResolution-90,80,pointProperties->yResolution-20 ,0x000000); // 

   // give errors  
  
  pointTerminal->previousx = 20; 
  pointTerminal->currentline = 2;
	pointCurrent->color = 0xFF00FF;
	pointCurrent->size = 2;
	
	
	printf("FATAL SOFTWARE ERROR");  
	pointTerminal->currentline = 3;
  pointTerminal->previousx = 20; 
	printf("ERROR NUMBER: %d", ERRORNO);

  pointTerminal->currentline = 4;
  pointTerminal->previousx = 20; 
	printf("SEE LINUX ERRONO DOCUMENTATION");
	

		pointCurrent->size = 3;	
   while(1){
     pointTerminal->currentline = 5;
    pointTerminal->previousx = 15;     	pointCurrent->color = 0xFF00FF;
  	printf("IT'S SAFE TO PANIC");
  	Timer_Delay_10ms(20);
  	
  	 pointTerminal->currentline = 5;
    pointTerminal->previousx = 15;     	pointCurrent->color = 0x000000;
  	printf("IT'S SAFE TO PANIC");
  	Timer_Delay_10ms(20);
  	
     continue; 
   }

  return 0; 
}
 
    
   // give details // 
  /*
   pointCurrent->size = 1; 
  pointTerminal->currentline = 15;
  pointTerminal->previousx = 5; 
  //asm("LDX  ACCD_");
  asm("STD  ACCD_");
  
  asm("STAA ACCA_");
  asm("STAB ACCB_");
  /// 
  asm("STX INDEXX");   
  asm("STY INDEXY");
  asm("STS SP_");  
 // asm("TFR CCR, CCR_"); 


 
	printf("ACCD: 0x%x ACCA: 0x%x ACCB: 0x%x",ACCD_, ACCA_, ACCB_ );
	
	pointTerminal->currentline = 16;
  pointTerminal->previousx = 20; 
	printf("IX: 0x%x IY: 0x%x ",INDEXX,INDEXY);
	
	pointTerminal->currentline =17;
  pointTerminal->previousx = 20; 
	printf("IP: 0x%x PC: 0x%x PPAGE_: 0x%x ",IP_,PC_, PPAGE_);
		*/