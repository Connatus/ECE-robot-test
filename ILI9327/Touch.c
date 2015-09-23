#include "Touch.h"
#if LCD_ANALOG_TOUCH 
                               // assume 10 bits // anything less is dumb
                               // no float 
                               
                               
unsigned int * Touch_Screen_XY_Res(void){
    unsigned char error =0, pol_x= TOUCH_POLL, pol_y= TOUCH_POLL, pol_;
    unsigned int  Touch_Y= 0; 
    unsigned int  Touch_X= 0; 
    unsigned int  xy_return[2];
    
    
   for(pol_ =0; pol_ < TOUCH_POLL; pol_++) 
    Touch_Y += Touch_Screen_Y(); 
    
   for(pol_ =0; pol_ < TOUCH_POLL; pol_++) 
    Touch_X += Touch_Screen_X(); 
     
    Touch_X = (Touch_X/ TOUCH_POLL);
    Touch_Y = (Touch_Y/ TOUCH_POLL);
   
    Touch_X = (TOUCH_X_MAX - Touch_X) -20; 
    Touch_Y = (Touch_Y-TOUCH_Y_MIN)- 20;
    Touch_X /= 2;//2.5;
    Touch_Y /= 3;//4.2;
    
    
    if(Touch_X > TOUCH_X_RES && Touch_X )
      Touch_X = TOUCH_X_RES; 
    
    if(Touch_Y > TOUCH_Y_RES && Touch_Y)
      Touch_Y = TOUCH_Y_RES; 
     
    xy_return[0] = Touch_X;
    xy_return[1] = Touch_Y; 
    
    return xy_return;
}



/*
readY  = xp & xm = input  (Read) 
        yp = high   ym = low
        
readX  = yp & ym = input  (Read) 
        xp = high   xm = low
*/        

unsigned int Touch_Screen_Y(void){
   unsigned int read_y ,read_x  =0;
    
   XP_INPUT();
   XM_INPUT();
   
   ///XM_LOW();
  /// XP_LOW();
   
   YP_OUTPUT();
   YP_HIGH();
   
   YM_OUTPUT();
   YM_LOW();
   
   read_y = Analog_Read(1);

   // reset back to output// 
  
   ILI9327_INIT_COM(); // Set COM pins 
   ILI9327_INIT_DATA(); // Set data pins 2- 7 
   
 //  printf("\n y: %d", read_y); 
  
   return read_y; 
}


unsigned int Touch_Screen_X(void){
unsigned int read_x =0;
// would be more effective if i were to read ddr for both and write it back

   YP_INPUT();
   YM_INPUT();
   
  // YM_LOW();
  // YP_LOW();
   
   XP_OUTPUT();
   XP_HIGH();
   
   XM_OUTPUT();
   XM_LOW();
   
   read_x = Analog_Read(2);
   
   // reset back to output// 
 
   ILI9327_INIT_COM(); // Set COM pins 
  ILI9327_INIT_DATA(); // Set data pins 2- 7 
   
//  printf("  x: %d ", read_x); 
   return read_x;
}

#endif 