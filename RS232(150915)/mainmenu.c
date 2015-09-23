#include "mainmenu.h"
//////
#define Time_Ignore 10 // not sure if seconds
 unsigned int previous_time =0;
 void menu_event( struct js_event_processed *jsep){
 int option =0;
 unsigned int time_difference =0;


   // if we need to process data  //
   // ie button has been pressed but not processed  ///
  if ( jsep->process_data  == 1){

            /// if button or axis is triggered
        if(jsep->Button !=0  || (jsep->Axis !=0 ))
                option = jsep->Button;
                time_difference = jsep->time - previous_time ;

                /// Load applications from button press

                if ((option>= 1)&& (option <= NUMBEROFAPPLICATIONS )){

                    (*function_pointer[(option-1)])(&jsep);
                }

                /// LOad the specific STEPPER MOTOR APPLICATION
                /// FOR AXIS PRESS
                if (( jsep->Axis == 1  || jsep->Axis == 2 ) && jsep->Axis_Value != 0){
                  //  printf("\n Process Camera A:%d AV:%d",jsep->Axis, jsep->Axis_Value);
                 (*function_pointer[0])(jsep);
                //  Process_Camera(jsep);

                }

                /// Artificial delay, ignore jsep updates less than 40ms
                if( ((jsep->stickL_x != 0) || (jsep->stickL_y != 0))  && ((time_difference ) >=   Time_Ignore) ){
                    /// RUN MOTOR FUNCTION
                    (*function_pointer[4])(jsep);

                }
                //

              printf("\n %d %d %d", jsep->Button, jsep->Axis,jsep->Axis_Value);
            /// set process data to 0 so process joystick event can process a new KEY!
           // sleep(1);
              jsep->process_data  = 0;
              previous_time = jsep->time;
        }

    return;
}



/*struct js_event_processed{
    unsigned char Button;
    unsigned char Button_Value;
    unsigned char Axis;
    unsigned int Axis_Value;
    signed int   stickR_x;
    signed int  stickR_y;
	signed int  stickL_x;
	signed int  stickL_y;
	signed int  Pad_x;
	signed int  Pad_y;
	unsigned char process_data;
};

*/
