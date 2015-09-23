
#include "RS232.h"
unsigned char RS232_Termination_String[4] = {
  //0xDE, 0xAD, 0xBE, 0xEF
  'a','b', 'c', 'd'
};

unsigned char RS232_Transmission_String[4] = {
 //0xFE, 0xED, 0xDE, 0xAD
   'q','w','e','r'
};



void RS232_Initalize(void){
/*  RS232 Initalize */
  port = "/dev/ttyUSB0";
  baud = 9600;

/// OPENING PORT !

	printf ("attempt to open %s with baud rate %d\n", port, baud);
	fd = EIA232Init (port, baud);
	if (fd == -1) {
		printf ("Error: cannot open serial port %s\n", port);
		return 1;
	}
	printf ("successful open of %s with baud rate %d\n", port, baud);
///
    return;
}




int mygetch ( void ){
  int ch;
  struct termios oldt, newt;

  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

  return ch;
}





int EIA232Init (char *device, int baudrate)
{
	int fd;
	struct termios config;

	// translate "human readable" baudrate
	// into Linux OS flag for baudrate,
	// as the baud rate value is NOT the same
	// as the configuration flag!

	switch (baudrate) {
	case 300: baudrate = B300; break;
	case 600: baudrate = B600; break;
	case 1200: baudrate = B1200; break;
	case 2400: baudrate = B2400; break;
	case 4800: baudrate = B4800; break;
	case 9600: baudrate = B9600; break;
	case 19200: baudrate = B19200; break;
	case 38400: baudrate = B38400; break;
	case 57600: baudrate = B57600; break;
	case 115200: baudrate = B115200; break;
	default: baudrate = B9600;
	}	/* end switch */

	// open the device (in the /dev folder are devices)
	// and check for errors
	fd = open (device, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd <= 0) {
		return -1;
	}

	// configure the terminal device attributes (raw in/out)
	// (you might want to research tcsetattr() for details
	// on configuring terminal (serial port) settings)
	// note: the serial port is configured to be non-blocking
	// for input purposes, hence, when you attempt to read,
	// there may be no data - pay attention to the return value
	// of read() as a result!

	memset (&config, 0, sizeof (config));
	cfsetispeed (&config, baudrate);
	cfsetospeed (&config, baudrate);
	config.c_cflag |= CS8 | CLOCAL | CREAD;
	config.c_iflag = IGNPAR | ICRNL;
	config.c_oflag = 0;
	config.c_lflag = 0;
	config.c_cc[VMIN] = 0;
	config.c_cc[VTIME] = 1;

	tcflush (fd, TCIFLUSH);
	tcsetattr (fd, TCSANOW, &config);

	// return file handle to serial device

	return fd;
}	/* end EIA232Init */

void RS232_Print_Node(struct RS232_Message *RS232_Message_Node){
    int x;
    for(x=0;x<4;x++)
        printf("%c",RS232_Message_Node->Transmission_String[x]);
    printf("\n ");
    printf("%d",RS232_Message_Node->RS232_Com_PORT);
    printf("%d",RS232_Message_Node->Board_Function);
    printf("%d",RS232_Message_Node->MessageSequenceNumber);
    printf("%d",RS232_Message_Node->lDataLength);
    printf("\n Data(chars): ");
    for(x=0;x<RS232_Message_Node->lDataLength;x++)
        printf("%c",RS232_Message_Node->MessageStorageArray[x]);
    printf("\n ");
    printf("%d",RS232_Message_Node->Message_CRC);

    for(x=0;x<4;x++)
        printf("%c",RS232_Message_Node->Termination_String[x]);

}


void RS232_Send_Node(struct RS232_Message *RS232_Message_Node){
unsigned char RS232_Header[4];

    write(fd, RS232_Message_Node->Transmission_String, sizeof(RS232_Message_Node->Transmission_String) );
    RS232_Header[0]  = RS232_Message_Node->RS232_Com_PORT;
    RS232_Header[1]  = RS232_Message_Node->Board_Function;
    RS232_Header[2]  = RS232_Message_Node->RS232_Com_PORT;
    RS232_Header[3]  = RS232_Message_Node->lDataLength;

    write(fd, RS232_Header, 4 );
    write(fd, RS232_Message_Node->MessageStorageArray, RS232_Message_Node->lDataLength);
    write(fd, RS232_Message_Node->Message_CRC, sizeof(RS232_Message_Node->Message_CRC) );
    write(fd, RS232_Message_Node->Termination_String, sizeof(RS232_Message_Node->Termination_String) );
    usleep(250000);
    return;
}
