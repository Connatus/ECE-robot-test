
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>

#include "RS232.h"
#include "nodes.h"
#include "macros.h"


#ifndef APPLICATIONS_H_INCLUDED
#define APPLICATIONS_H_INCLUDED


#define NUMBEROFAPPLICATIONS 5
/// Board Define
#define Board_Function_Motor 1
#define Board_Function_Camera  2
#define Board_Function_Ping  3
#define Function_Camera_Data_Length 14
#define Function_Motor_Data_Length 12

// WEBCAM DEFINES
#define SIZE 307200 // number of pixels (640x480 for my webcam)



/// Handles the cameras X,Y and
void Process_Camera(struct js_event_processed *jsep);
void Process_Motor(struct js_event_processed *jsep);
void Process_Audio(struct js_event_processed *jsep);
void Process_Ping(struct js_event_processed *jsep);
void Process_Picture(struct js_event_processed *jsep);


void Init_Nodes(void);

extern void (*function_pointer[5])(struct js_event_processed *jsep);

#endif // APPLICATIONS_H_INCLUDED
