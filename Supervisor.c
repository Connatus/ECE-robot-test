#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

using namespace std;

struct knobPos {
	signed int xPos;
	signed int yPos;
	
	knobPos()
	{
		xPos=0;
		yPos=0;
	}
};


int manual(void);
int updateJSPos(struct knobPos&,int,signed int);




int main(){
	int i;
	for(;;){
		i=0;
		cout<<"Please enter \"1\" for manual mode and \"2\" for automatic"<<endl;	
		cin>>i;
		if(i==1)
			manual();
		else if(i==2)
			cout<<"There's nothing here..."<<endl;
		else	
			return 0;
	}
}






int manual()
{
	struct js_event jsStruct;
	struct knobPos knobPosVar[3];
	int js;
	int i;

	if((js = open ("/dev/input/js1",O_RDWR)) < 0){//open joystick file
		cout<<"error open"<<endl;//if open fails print error and return
		return 1;
	}
	while(1){
		if(read(js,&jsStruct,sizeof(struct js_event)) != sizeof(struct js_event)){//read gamepad event
		cout<<"error reading"<<endl;//if reading fails print error and close program
		return 1;
		}
		if(jsStruct.type==0x01)//Event type is button
		{
			if(jsStruct.value==1)//only issue commands if button is pressed
			{
				if(jsStruct.number==0x00)
				{
					cout<<"X pressed"<<endl;
				}
				else if(jsStruct.number==0x01)
				{
					cout<<"A pressed"<<endl;
				}
				else if(jsStruct.number==0x02)
				{
					cout<<"B pressed"<<endl;
				}
				else if(jsStruct.number==0x03)
				{
					cout<<"Y pressed"<<endl;
				}
				else if(jsStruct.number==0x04)
				{
					cout<<"LB pressed"<<endl;
				}
				else if(jsStruct.number==0x05)
				{
					cout<<"RB pressed"<<endl;
				}
				else if(jsStruct.number==0x06)
				{
					cout<<"LT pressed"<<endl;
				}
				else if(jsStruct.number==0x07)
				{
					cout<<"RT pressed"<<endl;
				}
				else if(jsStruct.number==0x08)
				{
					cout<<"exit"<<endl;
					return 0;
				}
				else if(jsStruct.number==0x09)
				{
					cout<<"Start pressed"<<endl;
				}

			}
		}
		else if(jsStruct.type==0x02){//Joystick event is an axis change
			if(jsStruct.number==0x00){//Event is at 1st Stick in X plane
				updateJSPos(knobPosVar[0],0,jsStruct.value);}
			if(jsStruct.number==0x01){//Event is at 1st Stick in Y plane
				updateJSPos(knobPosVar[0],1,jsStruct.value);}
			if(jsStruct.number==0x02){//Event is at second Stick in X plane
				updateJSPos(knobPosVar[1],0,jsStruct.value);}
			if(jsStruct.number==0x03){//Event is at second Stick in Y plane
				updateJSPos(knobPosVar[1],1,jsStruct.value);}
			if(jsStruct.number==0x04){//Event is at D-pad in X plane
				updateJSPos(knobPosVar[2],0,jsStruct.value);}
			if(jsStruct.number==0x05){//Event is at D-pad in Y plane
				updateJSPos(knobPosVar[2],1,jsStruct.value);}


		cout<<"Stick 1     "<< knobPosVar[0].xPos<<"  "<<knobPosVar[0].yPos<<endl;
		cout<<"Stick 2     "<< knobPosVar[1].xPos<<"  "<<knobPosVar[1].yPos<<endl;		
		cout<<"D-pad       "<< knobPosVar[2].xPos<<"  "<<knobPosVar[2].yPos<<endl;		
		}		
	}
}

int updateJSPos(struct knobPos& knobPosVar,int i,signed int value){
	if(i){
		knobPosVar.yPos=value/-328;}
	else{
		knobPosVar.xPos=value/328;}
	return 0;
}


