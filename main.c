//
// Created by Lilli Szafranski on 2/28/16.
//

#include <unistd.h>
#include "Includes.h"
#include "Serial.h"

//#include <iostream>
//#include <sys/fcntl.h>
//#include <sys/termios.h>


int main() {

    int serialDevice = new_serial_device("/dev/ttyS0");

    if (serialDevice < 0) {
        printf("Error creating serial device!\n");
        return 1;
    }

    while (1) {
        printf("Looping...\n");

        char foo[] = {0, 0, 0, 0};
        int status = write_data(serialDevice, foo, 4);

        if (status < 0) {
            printf("Error writing to serial device!\n");
            return 1;
        }

        sleep(1);
    }

    return 0;
}