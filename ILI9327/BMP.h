#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED
                                            
#include <stdio.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/*******************************************/
// SD and FAT Libraries 
/*******************************************/
#include "ff.h" // use FatFs from Elm-Chan.org
#include "ffconf.h"
#include "integer.h"
#include "diskio.h" // use FatFs from Elm-Chan.org (diskio used for disk initialization)
#include "file.h"



/*******************************************/
// LCD Libraries
/*******************************************/
#include "ILI9327.h" // EL _CD DRIVERSZ
#include "LCD_Draw.h"
#include "LCD_Config.h"
#include "Touch.h"
#include "Terminal.h" // printf 
#include "SD.h" // Sd INIT and File Handlers // needs more work  // broken 
 

int draw_bmp(int x, int y, char *filename);
void BMP_SD_READ(int x, int y);

#endif /* BMP_ */