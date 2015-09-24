/*
    (C) Copyright 2007,2008, Stephen M. Cameron.

    This file is part of wordwarvi.

    wordwarvi is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    wordwarvi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with wordwarvi; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 */
#include <stdio.h>
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#define JOYSTICK_DEVNAME "/dev/input/js1"

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */



#define JS_X        0x01
#define JS_A        0x02
#define JS_B        0x03
#define JS_Y        0x04




#define JS_START    0x09
#define JS_BACK     0x0A

#define JS_RT       0x08
#define JS_RB       0x06

#define JS_LT       0x07
#define JS_LB       0x05


#define JS_HAT_LR      0x01
#define JS_HAT_UD      0x02

#define JS_ANALOG_R_LR 0x03
#define JS_ANALOG_R_UD 0x04

#define JS_ANALOG_L_LR 0x05
#define JS_ANALOG_L_UD 0x06



int joy_fd, joy_rc;
int joy_wrc;



// NOT INCLUDING HATS
char *Joystick_Buttons[10];

struct js_event {
	unsigned int time;	/* event timestamp in milliseconds */
	short value;   /* value */
	unsigned char type;     /* event type */
	unsigned char number;   /* axis/button number */
};



struct js_event_processed{
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
	unsigned int time;
};


struct knobPos {
	signed int xPos;
	signed int yPos;
};

extern void process_joystick_event( struct js_event *jse,struct js_event_processed *jsep);

extern void craftServoMessage(int servoDeg,int stepperDeg,struct servoStepperPayload *servoMessage,struct RS232_Message *RS232_Message_Noder,char gohome);
extern void convertInt(int num,char array[]);
//extern void checkCamera(struct knobPos knobvar,int *servoDeg,int *stepperDeg);
extern void updateJSPos(struct knobPos *knobPosVar,int i,signed int value);
extern int open_joystick();
extern int read_joystick_event(struct js_event *jse);
extern void set_joystick_y_axis(int axis);
extern void set_joystick_x_axis(int axis);
extern void close_joystick();
void Logitek_Joystick_Initalize(void);



struct js_event jse;
struct js_event_processed jsep;




#endif
