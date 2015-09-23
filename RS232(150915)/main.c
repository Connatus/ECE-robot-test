#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h> /// for POW function

#include <signal.h>




#include "mainmenu.h"

#include "joystick.h"
#include "applications.h"
#include "RS232.h"
#include "nodes.h"
 /// AUDIO IS SAVED UNDER TEMP/AUDIOCAPTURE.wav

int main (int argc, char *argv[])
{
    RS232_Initalize();
    Logitek_Joystick_Initalize();
    Init_Nodes();


    while (1) {
        /// Delay necessary else button press is laggy and un
        /// responsive, should be a thread
        usleep(1000);
        /// Constantly Read JStick Event  ///
        joy_rc = read_joystick_event(&jse);
        //joy_wrc = get_joystick_status(&wjse);

        // When controller button is pressed //
        if (joy_rc == 1) {

             process_joystick_event(&jse, &jsep);
             menu_event(&jsep); // responsible for selecting the menu item
            /// reset joysick event
          //  wjse.process_data = 0;

        }
    }
}

