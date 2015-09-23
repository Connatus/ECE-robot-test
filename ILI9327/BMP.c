#include "BMP.h"


// DOESNT WORK // 
/// NEEDS A LOT OF WORK 
  /*
int draw_bmp(int x, int y, char *filename){
	//Open file for reading! 
		printf("\n Opening %s", filename);
	errCode = f_open(&file, filename , FA_READ);
	if (errCode != FR_OK)
	{
		printf("Error: f_open failed, error code: %d\r", errCode);
		return; 
	}

	errCode = f_lseek(&file, 1 );
		
		// BMP SHIZ
	BMP_SD_READ(x,y);
		
	errCode = f_close(&file);
	if (errCode != FR_OK)
	{
		printf("Error: f_close failed, error code: %d\r", errCode);
	}
	return 0;
}

void BMP_SD_READ(int x, int y){
	// bmp must be 32bit dont like it suck my fucking cock 
	// assumes padding is 0 
	struct LCD_Properties *pointProperties = &Properties;
	struct LCD_Geometry *pointCurrent = &Current;
	long unsigned int bmp_start =0, bmp_width=0, bmp_height=0, bmp_raw_data=0, width_loop=0, height_loop=0;
 	int padding=0; 
	int vertical_count =0, horizontal_count=0;   
	char color_array[3];
  unsigned long color_out, red,blue,green; 
	
	// BMP READ ROUTINE // 
   if( File_Read8bytes(0) != 0x42 || File_Read8bytes(1) != 0x4D)return;
	//Get BMP Start ( start of image RR-GG-BB)
	bmp_start = (File_Read8bytes(13) << 24) +(File_Read8bytes(12) << 16)+ (File_Read8bytes(11) << 8)+ File_Read8bytes(10);
	// Get Width and Height
	bmp_width =  (File_Read8bytes(0x15) << 24)+ (File_Read8bytes(0x14) << 16)+ (File_Read8bytes(0x13) << 8)+ File_Read8bytes(0x12);
	bmp_height = (File_Read8bytes(0x19) << 24) + (File_Read8bytes(0x18) << 16)+ (File_Read8bytes(0x17) << 8)+ File_Read8bytes(0x16);
	bmp_raw_data =(File_Read8bytes(0x25) << 24) + (File_Read8bytes(0x24) << 16)+ (File_Read8bytes(0x23) << 8)+ File_Read8bytes(0x22);
	
  	padding =  bmp_raw_data - (bmp_width*bmp_height*3); 
  	padding = padding/ bmp_height; 


	height_loop = bmp_height;
	width_loop = bmp_width;
	
	// This is used to draw images that are larger than the screen draw only the first 320x240 of the image  
	if (bmp_width > pointProperties->yResolution) {
		width_loop = pointProperties->yResolution;
	}
	if (bmp_height > pointProperties->xResolution){
		height_loop = pointProperties->xResolution; 	
	}
	
	// Put display in landscape mode swap the height and width values
	pointCurrent->mem_xPosition= y;
	pointCurrent->mem_x1Position = ((y+height_loop)-1);
	pointCurrent->mem_yPosition= x;
	pointCurrent->mem_y1Position = ((x+width_loop)-1);

printf(" RREED"); 
//int ILI9327_ADDRESS_SET(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2){
	for (vertical_count = 0; vertical_count < height_loop; vertical_count++)
	{
		// Read one line from the SD card (store it in the color array BB - GG - RR) 
	//	File_Read_Custom_Length((bmp_start+(padding*vertical_count)+(vertical_count*3*bmp_width)) , (width_loop*3), color_array); 

		for (horizontal_count = 0;  horizontal_count < width_loop; horizontal_count++ ) 	
		{		
		   //ILI9327_WRITE_DATA(
		   color_out = (bmp_start+(padding*vertical_count)+(vertical_count*3*bmp_width)+(horizontal_count*3)); 
		   File_Read_Custom_Length(color_out, 3, color_array); 
		   red = color_array[(horizontal_count)+2];
		   red  <<= 16;
		   blue = color_array[(horizontal_count)+1];
		   blue  <<= 8; 
		   green = color_array[(horizontal_count)];
		   
		   color_out = red+blue+green;
		   //  printf("r: %x g: %x b: %x", color_array[(horizontal_count*3)], color_array[(horizontal_count*3)+1], color_array[(horizontal_count*3)+2]);
		   
		    ILI9327_SendPixel(horizontal_count,vertical_count, color_out);
		
		}
	}	
	return;
}


              */
