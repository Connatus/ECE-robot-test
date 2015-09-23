

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// we need the following for serial port support ...
#include <sys/types.h>
#include <fcntl.h>
#include <termios.h>

#include "nodes.h"

#ifndef RS232_H_INCLUDED
#define RS232_H_INCLUDED



#define MESSAGE_ARRAY_SIZE 100

#define RS232_COMPORT       3
unsigned char RS232_Transmission_String[4];
unsigned char RS232_Termination_String[4];


//// MAKE ME A STRUCT
unsigned long baud;
char *port;
int fd;

struct RS232_Message{
    char   Transmission_String[4];
    char   RS232_Com_PORT;
    char   Board_Function;
    char   MessageSequenceNumber;  //  Place in packet   in a message package of 430 bytes( 2 - 140- 279)
    char   lDataLength;     // size of message sent after the heade
    char   MessageStorageArray[MESSAGE_ARRAY_SIZE]; //
    char   Message_CRC;	//
    char   Termination_String[4];
};

struct RS232_Message RS232_Message_Node;

void RS232_Initalize(void);
int mygetch ( void );
int EIA232Init (char *device, int baudrate);


/// RS232 PROTOTYPES
void RS232_Send_Node(struct RS232_Message *RS232_Message_Node);
void RS232_Print_Node(struct RS232_Message *RS232_Message_Node);
void RS232_Set_Default_Node(struct RS232_Message *RS232_Message_Node);







#endif // APPLICATIONS_H_INCLUDED
