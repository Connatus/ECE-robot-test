                      

#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
                                            
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



#include "error.h"

extern FATFS filesystem;
extern FRESULT errCode;
extern UINT read;
extern FIL file;
extern FRESULT rc; /* Result code */
extern DIR dir; /* Directory object */
extern FILINFO fno; /* File information object */
extern UINT bw, br, i;


unsigned char Fat_FS_Error(unsigned char errCode , unsigned char *function);
unsigned char Write_Hello_World(void);
unsigned char Fat_File_Open(char *filename);

char File_Read_Custom_Length(long int location, int length, char *Output_Array);
char File_Read8bytes(long int location);


char File_Write_Custom_Length(long int location, int length, char *Input_Array);
char File_Write(char* filename, long int location, int length, char *Input_Array);
char File_Write_Append(char* filename, int length, char *Input_Array);
///

FRESULT open_append (
    FIL* fp,            /* [OUT] File object to create */
    const char* path    /* [IN]  File name to be opened */
); 

#endif /* L293DD_H_ */