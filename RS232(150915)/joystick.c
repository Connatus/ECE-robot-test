#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "joystick.h"

#define JOYSTICK_DEVNAME "/dev/input/js1"

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */


#define JS_EVENT_ANALOG         0x02




static int joystick_fd = -1;
/// NEEDS TO BE RE WRITTEN
extern void process_joystick_event(struct js_event *jse,struct js_event_processed *jsep){

 /// Check if data has been processed if not, dont process data
    if(jsep->process_data== 1)
        return 0;


/// Set Process Data Flag HIGH
    jsep->process_data = 1;
/// Clear Previous values

    jsep->Axis =0;
    jsep->Axis_Value = 0;
    jsep->Button =0;
    jsep->Button_Value = jse->value;
    jsep->time = jse->time;

 //  printf(" \n %d %d %d  T: %d ", jse->number, jse->type, jse->value, jse->time);
   if((jse->type == JS_EVENT_BUTTON) && (jse->value == 0))
   {

        jsep->Button = (jse->number + 1); // increment button by 1
        jsep->Button_Value = jse->value;
   }
   else if ((jse->type == JS_EVENT_ANALOG))
    {

        jsep->Axis = (jse->number + 1);  /// increment by 1
        jsep->Axis_Value = ((jse->value) /327) ;

        if(jsep->Axis_Value <= 30 || jsep->Axis_Value >= -30)
            jsep->Axis_Value = 0;

        // Right stick  = 3 & 4  - left 1 & 2   pad = 5 & 6
        switch(jsep->Axis){
            case 0x01:
                jsep->stickR_x = jsep->Axis_Value;
                break;
            case 0x02:
                jsep->stickR_y = jsep->Axis_Value;
                break;
            case 0x03:
                jsep->stickL_x = jsep->Axis_Value;
                break;
            case 0x04:
                jsep->stickL_y = jsep->Axis_Value;
                break;
            case 0x05:
                jsep->Pad_x = jsep->Axis_Value;
                break;
            case 0x06:
                jsep->Pad_y = jsep->Axis_Value;
                break;
            default:
                break;
        }


    }

     //printf("\n RS: %d %d \n LS: %d %d \n PS: %d %d", jsep->stickR_x, jsep->stickR_y, jsep->stickL_x, jsep->stickL_y, jsep->Pad_x, jsep->Pad_y);
    return 0;

}


int open_joystick()
{
	joystick_fd = open(JOYSTICK_DEVNAME, O_RDONLY | O_NONBLOCK); /* read write for force feedback? */
	if (joystick_fd < 0)
		return joystick_fd;

	/* maybe ioctls to interrogate features here? */

	return joystick_fd;
}


int read_joystick_event(struct js_event *jse)
{
	int bytes;

	bytes = read(joystick_fd, jse, sizeof(*jse));

	if (bytes == -1)
		return 0;

	if (bytes == sizeof(*jse))
		return 1;

	printf("Unexpected bytes from joystick:%d\n", bytes);

	return -1;
}

void close_joystick()
{
	close(joystick_fd);
}


void Logitek_Joystick_Initalize(void){
  	joy_fd = open_joystick();
	if (joy_fd < 0) {
		printf("open failed.\n");
		exit(1);
	}
    printf("Opended Joystick \n");

  return;
}

#if 0
/* a little test program */
int main(int argc, char *argv[])
{
	int fd, rc;
	int done = 0;

	struct js_event jse;

	fd = open_joystick();
	if (fd < 0) {
		printf("open failed.\n");
		exit(1);
	}

	while (!done) {
		rc = read_joystick_event(&jse);
		usleep(1000);
		if (rc == 1) {
			printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n",
				jse.time, jse.value, jse.type, jse.number);
		}
	}
}
#endif
