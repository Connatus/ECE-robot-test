#include "file.h"


 /*
http://elm-chan.org/fsw/ff/en/rc.html
*/
#if _FATFSENABLE != 0

unsigned char Write_Hello_World(void){

    printf("\nCreate a new file (hello.txt).\n");
    errCode = f_open(&file, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
    Fat_FS_Error(errCode,"f_open");
       

    printf("\nWrite a text data. (Hello world!)\n");
    rc = f_write(&file, "Hello world!\r\n", 14, &bw);
    Fat_FS_Error(errCode,"f_write");
    
    printf("%u bytes written.\n", bw);
    printf("\nClose the file.\n");
    rc = f_close(&file);
    Fat_FS_Error(errCode,"f_close");
    
    File_Write("HELLO.TXT", 10, 14,"NOTAHELLOWORLD");
    File_Write_Append("HELLO.TXT",14,"APPENDAPPENDAPPEND");  
}


//// Forever wait /// should probably use the error function // 
unsigned char Fat_FS_Error(unsigned char errCode , unsigned char *function){

    if (errCode != FR_OK)
    {
    
    ERROR_PRINT_SCREEN_2(function,errCode);
   // printf("Error: %s  failed, error code: %d\r",function, errCode);
  //  printf("Please refer to error list");
    while (1); 
    }

}



//File_Write_CSV 

/// VERY FUCKING IMPORTANT !!
/// (create txt file,  length , append flag, buffer)
//File_Write_.txt (file txt 


char File_Write(char* filename, long int location, int length, char *Input_Array){ 
	  
	  printf("\n opening file (%s) at %l, for %d \n", filename, location, length);
	  
    errCode = f_open(&file, filename, FA_WRITE | FA_CREATE_ALWAYS);
    Fat_FS_Error(errCode,"f_open");
    
    File_Write_Custom_Length(location,length,Input_Array); 

    
    f_close(&file); 
    Fat_FS_Error(errCode,"f_close"); 
}


char File_Write_Append(char* filename, int length, char *Input_Array){ 
	  
	  printf("\n opening file (%s) for %d \n", filename, length);
	  
    errCode = open_append(&file, filename);
    Fat_FS_Error(errCode,"f_open");
    
    errCode = f_write(&file, Input_Array, length , &bw);
    Fat_FS_Error(errCode,"f_write");

    
    f_close(&file); 
    Fat_FS_Error(errCode,"f_close"); 
}

       // f_write(&file, "Hello world!\r\n", 14, &bw);
char File_Write_Custom_Length(long int location, int length, char *Input_Array){ 
	
	errCode = f_lseek(&file, location);
  Fat_FS_Error(errCode,"f_lseek");
	
	errCode = f_write(&file, Input_Array, length , &bw);
  Fat_FS_Error(errCode,"f_write");
	return 0; 	
}


char File_Read_Custom_Length(long int location, int length, char *Output_Array){ 
	
	errCode = f_lseek(&file, location);
	Fat_FS_Error(errCode,"f_lseek");
	
	errCode = f_read(&file, Output_Array, length , &read);
  Fat_FS_Error(errCode,"f_read");
  
	return 0; 	
}


char File_Read8bytes(long int location){
	unsigned char filebyte[1];  
	
	errCode = f_lseek(&file, location);
  Fat_FS_Error(errCode,"f_lseek");
	
	errCode = f_read(&file, filebyte, 1, &read);
  Fat_FS_Error(errCode,"f_read");

	
	return filebyte[0]; 	
}



FRESULT open_append (
    FIL* fp,            /* [OUT] File object to create */
    const char* path    /* [IN]  File name to be opened */
)
{
    FRESULT fr;

    /* Opens an existing file. If not exist, creates a new file. */
    fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
    if (fr == FR_OK) {
        /* Seek to end of the file to append data */
        fr = f_lseek(fp, f_size(fp));
        if (fr != FR_OK)
            f_close(fp);
    }
    return fr;
}

#endif /* FATFS_ENABLE*/

