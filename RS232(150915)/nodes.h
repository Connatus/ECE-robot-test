#ifndef NODES_H_INCLUDED
#define NODES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "joystick.h"


// not really global but it can be used externally
struct Camera_Parameters{
    unsigned char Capture_Image;
    unsigned int  X_Degrees;
    unsigned int  Y_Degrees;
    unsigned int  X_Speed; // Stepper speed
    unsigned int  Y_Speed; // RC Servo Speed
};


// not really global but it can be used externally
struct DC_Motor_Parameters{
    unsigned int  R_Speed; // Stepper speed
    unsigned int  L_Speed; // RC Servo Speed
    unsigned char R_Direction;
    unsigned char L_Direction;
};


/// NOT SET
struct Motor_Parameters{
    unsigned int  R_Speed; // Stepper speed
    unsigned int  L_Speed; // RC Servo Speed
    unsigned char R_Direction;
    unsigned char L_Direction;
};

/// NOT SET
struct Audio_Parameters{
    unsigned int NullValue;
};

/// NOT SET

struct Ping_Parameters{
    unsigned int NullValue;
};

struct DC_Motor_Parameters DC_Motor_Parameter_Node;
struct Camera_Parameters Camera_Parameters_Node;
struct Motor_Parameters Motor_Parameters_Node;
struct Audio_Parameters Audio_Parameters_Node;
struct Ping_Parameters Ping_Parameters_Node;

#endif // NODES_H_INCLUDED
