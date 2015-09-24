// Init Value for Cmear
#include "applications.h"

#include <math.h>

#define Init_Camera_X   45  // degrees
#define Init_Camera_Y   45  // degrees
#define Init_Camera_Speed 100

#define Camera_X_Max  135
#define Camera_Y_Max  150

unsigned int Camera_X_Incriment  = 15;
unsigned int  Camera_Y_Incriment = 15;

unsigned char *Motor_Direction_R= {"0F0"};

unsigned char *Motor_Direction_L= {"0F0"};
unsigned char Motor_Direction[3] = {"0B0"};


unsigned char *Camera_X_Degrees= {"100"};
unsigned char *Camera_Y_Degrees = {"100"};
unsigned char *Camera_X_Speed = {"100"};
unsigned char *Camera_Y_Speed = {"100"};

unsigned char Camera_Direction[2]  = {"R0"};

extern void (*function_pointer[5])(struct js_event_processed *jsep) = { Process_Camera, Process_Picture, Process_Audio, Process_Ping,Process_Motor };

void Init_Nodes(void){

   /// camera init
   Camera_Parameters_Node.X_Degrees = Init_Camera_X;
   Camera_Parameters_Node.Y_Degrees = Init_Camera_Y;
   Camera_Parameters_Node.X_Speed = Init_Camera_Speed;
   Camera_Parameters_Node.Y_Speed = Init_Camera_Speed;

    return;
}

void Process_Camera(struct js_event_processed *jsep){
    unsigned char Axis =0;
    signed int Axis_Value = 0;
    unsigned char Direction =0;
    int x=0;
    unsigned int shit =0;

    Axis = jsep->Axis;
    Axis_Value= jsep->Axis_Value;

    if(Axis == JS_HAT_UD){

        if(Axis_Value < 0 && (Camera_Parameters_Node.Y_Degrees != 0)){
            Camera_Parameters_Node.Y_Degrees = ((Camera_Parameters_Node.Y_Degrees) - Camera_Y_Incriment);
              Camera_X_Incriment = 0;
         }
         else if (( Axis_Value > 0) && (Camera_Parameters_Node.Y_Degrees != Camera_Y_Max)){
            Camera_Parameters_Node.Y_Degrees = (Camera_Parameters_Node.Y_Degrees) + Camera_Y_Incriment;
              Camera_X_Incriment = 0;
         }


    }
      // NEEDS DIRECTION
    else if(Axis == JS_HAT_LR){
        if(Axis_Value > 0 && (Camera_Parameters_Node.X_Degrees != 0)){
            Camera_Parameters_Node.X_Degrees = (Camera_Parameters_Node.X_Degrees) - Camera_X_Incriment;
            Camera_Direction[0] = 'L'; /// move LEFT
              Camera_X_Incriment = 15;
        }
         else if (Axis_Value < 0 &&(Camera_Parameters_Node.X_Degrees != Camera_X_Max))
        {
           Camera_Parameters_Node.X_Degrees = (Camera_Parameters_Node.X_Degrees) + Camera_X_Incriment;
           Camera_Direction[0] = 'R'; /// move RIGHT
           Camera_X_Incriment = 15;
        }

    }

    printf("\n Camera X-Deg: %d  Y-Deg: %d", Camera_Parameters_Node.X_Degrees,Camera_Parameters_Node.Y_Degrees );

       strncpy(RS232_Message_Node.Transmission_String,RS232_Transmission_String, sizeof(RS232_Transmission_String) );

        RS232_Message_Node.RS232_Com_PORT = (RS232_COMPORT +0x30);
        RS232_Message_Node.Board_Function = (Board_Function_Camera+0x30);
        RS232_Message_Node.MessageSequenceNumber = 0;/// FILLER
        RS232_Message_Node.lDataLength = Function_Camera_Data_Length;

        Camera_X_Speed = Int_to_Array_2((Camera_Parameters_Node.X_Speed),3);
        strcpy(RS232_Message_Node.MessageStorageArray, Camera_X_Speed);

        Camera_X_Degrees = Int_to_Array_2((Camera_X_Incriment),3);
        strcat(RS232_Message_Node.MessageStorageArray, Camera_X_Degrees);

        strcat(RS232_Message_Node.MessageStorageArray, Camera_Direction);

        Camera_Y_Speed = Int_to_Array_2((Camera_Parameters_Node.Y_Speed),3);
        strcat(RS232_Message_Node.MessageStorageArray, Camera_Y_Speed);

        Camera_Y_Degrees = Int_to_Array_2((Camera_Parameters_Node.Y_Degrees),3);
        strcat(RS232_Message_Node.MessageStorageArray, Camera_Y_Degrees);

        strncpy(RS232_Message_Node.Termination_String, RS232_Termination_String, sizeof(RS232_Termination_String));

       printf("\nPrinting Message Node\n ");
       RS232_Print_Node(&RS232_Message_Node);
       RS232_Send_Node(&RS232_Message_Node);

    return;
}

#define DC_Motor_Theshold   15
void Process_Motor(struct js_event_processed *jsep){
    unsigned char Axis =0;
    signed int Axis_Value = 0;
    unsigned char Direction =0;
    int x=0;
    unsigned int shit =0;
    unsigned char DC_R_Direction_Y = 0;
    unsigned char DC_L_Direction_Y = 0;
    unsigned char DC_L_Speed = 0;
    unsigned char DC_R_Speed = 0;
    unsigned char DC_R_Break = 0;
    unsigned char DC_L_Break = 0;
    signed int DC_R_Current =0;
    signed int DC_L_Current =0;
    Axis = jsep->Axis;
    Axis_Value= jsep->Axis_Value;

        //printf("PROCESS MOTOR");
        //printf("\n RS: %d %d \n LS: %d %d \n PS: %d %d", jsep->stickR_x, jsep->stickR_y, jsep->stickL_x, jsep->stickL_y, jsep->Pad_x, jsep->Pad_y);
        /// negative = forward in y
        /// Move forward // move backward
      /*
        if(jsep->stickL_y < 0){
             DC_R_Direction_Y  = 'F';
             DC_L_Direction_Y  = 'F';
             printf("FORWARD");

        }
        else if(jsep->stickL_y > 0)
        {
             DC_R_Direction_Y  = 'B';
             DC_L_Direction_Y  = 'B';
               printf("BACKWARD");
        }
        // if  -15 < x < 15 // set speed to 0
        if((jsep->stickL_y <= 15 ) && (jsep->stickL_y >= -15 ) ){
              Motor_Parameters_Node.L_Speed = 0;
              Motor_Parameters_Node.R_Speed = 0;
              DC_R_Direction_Y  = 'F';
             DC_L_Direction_Y  = 'F';
              DC_R_Break = '1';
              DC_L_Break = '1';
                printf("ZERO SPEED");

        }

        else{
                Motor_Parameters_Node.L_Speed  = abs(jsep->stickL_y%100);
                Motor_Parameters_Node.R_Speed  = abs(jsep->stickL_y%100);
                DC_R_Break = '0';
                DC_L_Break = '0';
                printf("SPEED: %d %d", Motor_Parameters_Node.L_Speed, Motor_Parameters_Node.R_Speed);
        }

    */
        //printf("SPEED: %d %d\n", Motor_Parameters_Node.L_Speed, Motor_Parameters_Node.R_Speed);
        DC_L_Current  =((jsep->stickL_y*(-1))+jsep->stickL_x);
        DC_R_Current  =((jsep->stickL_y*(-1))-jsep->stickL_x);
        if((DC_L_Current>Motor_Parameters_Node.L_Speed)&&(Motor_Parameters_Node.L_Speed<=99))
            Motor_Parameters_Node.L_Speed++;
        else if ((DC_L_Current<Motor_Parameters_Node.L_Speed)&&(Motor_Parameters_Node.L_Speed>=-99))
            Motor_Parameters_Node.L_Speed--;

        if((DC_R_Current>Motor_Parameters_Node.R_Speed)&&(Motor_Parameters_Node.R_Speed<=99))
            Motor_Parameters_Node.R_Speed++;
        else if ((DC_R_Current<Motor_Parameters_Node.R_Speed)&&(Motor_Parameters_Node.R_Speed>=-99))
            Motor_Parameters_Node.R_Speed--;

        if(Motor_Parameters_Node.L_Speed==0)
            DC_L_Break='1';
        else
            DC_L_Break='0';
        if(Motor_Parameters_Node.R_Speed==0)
            DC_R_Break='1';
        else
            DC_R_Break='0';

        strncpy(RS232_Message_Node.Transmission_String,RS232_Transmission_String, sizeof(RS232_Transmission_String) );
        RS232_Message_Node.RS232_Com_PORT = (RS232_COMPORT +0x30);
        RS232_Message_Node.Board_Function = (Board_Function_Motor+0x30);
        RS232_Message_Node.MessageSequenceNumber = 0;/// FILLER
        RS232_Message_Node.lDataLength = Function_Motor_Data_Length;

      //  Motor_Parameters_Node.R_Speed = 100;
      //  Motor_Parameters_Node.L_Speed = 100;

   // printf("%d    %d\n",(abs(Motor_Parameters_Node.R_Speed)),Motor_Parameters_Node.R_Speed);

            Motor_Direction_R = Int_to_Array_2((abs(Motor_Parameters_Node.R_Speed)),3);

        if(Motor_Parameters_Node.L_Speed>0){
            DC_L_Direction_Y='F';}
        else
            DC_L_Direction_Y='B';


        if(Motor_Parameters_Node.R_Speed>0){
            DC_R_Direction_Y='F';}
        else
            DC_R_Direction_Y='B';


        strcpy(RS232_Message_Node.MessageStorageArray, Motor_Direction_R);

        Motor_Direction_R[0] = DC_R_Break;

        Motor_Direction_R[1] = DC_R_Direction_Y;

        Motor_Direction_R[2] = '0';

        strcat(RS232_Message_Node.MessageStorageArray, Motor_Direction_R);

        Motor_Direction_L = Int_to_Array_2(abs(Motor_Parameters_Node.L_Speed),3);

       strcat(RS232_Message_Node.MessageStorageArray, Motor_Direction_L);
        Motor_Direction_L[0] =  DC_L_Break;
        Motor_Direction_L[1] =  DC_L_Direction_Y;
        Motor_Direction_L[2] = '0';

        strcat(RS232_Message_Node.MessageStorageArray, Motor_Direction_L);



       //  strcat(RS232_Message_Node.MessageStorageArray, Motor_Direction);

        strncpy(RS232_Message_Node.Termination_String, RS232_Termination_String, sizeof(RS232_Termination_String));

       printf("\nPrinting Message Node\n ");
       RS232_Print_Node(&RS232_Message_Node);
       //RS232_Send_Node(&RS232_Message_Node);



    return;
}




void Process_Audio(struct js_event_processed *jsep){
	pid_t pid, pid2;
	char *cmd[]={"/usr/bin/arecord", "-f", "cd", "/tmp/Sample.wav", NULL};

	pid = fork();

	if(pid==0){
		//fprintf(stdout, "Starting audio capture...\n");
		execv("/usr/bin/arecord", cmd);
	}

	else{
        pid2=fork();
        if(pid2==0)
        {
            sleep(5);
            kill(pid, SIGKILL);
            exit(0);
        }
	}

	return(0);
}



void Process_Picture(struct js_event_processed *jsep){
float data[SIZE];
     FILE *picture,*grab;
     printf("\n Process picture ");
     picture=fopen("/dev/video0", "rb");
     grab=fopen("grabass.raw", "wb");
     fread(data, sizeof(data[0]), SIZE, picture);
     fwrite(data, sizeof(data[0]), SIZE, grab);
     fclose(picture);
     fclose(grab);
    return;
}



/// Processes a simple ping
void Process_Ping(struct js_event_processed *jsep){
    unsigned char Ping_Length =8;
    unsigned char counter =0;

       printf("\n Process Ping");
       strncpy(RS232_Message_Node.Transmission_String,RS232_Transmission_String, sizeof(RS232_Transmission_String) );
       RS232_Message_Node.RS232_Com_PORT =(RS232_COMPORT+0x30);
       RS232_Message_Node.Board_Function = (Board_Function_Ping+0x30);
       RS232_Message_Node.MessageSequenceNumber = 4; /// FILLER NOT USED
       RS232_Message_Node.lDataLength = Ping_Length;

    for( counter =0; counter < (RS232_Message_Node.lDataLength); counter++)
        RS232_Message_Node.MessageStorageArray[counter] = 'A';


       strncpy(RS232_Message_Node.Termination_String, RS232_Termination_String, sizeof(RS232_Termination_String));
       printf("\nPrinting Message Node\n ");

       RS232_Print_Node(&RS232_Message_Node);
       RS232_Send_Node(&RS232_Message_Node);
    return;
}


