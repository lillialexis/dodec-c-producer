//
// Created by Lilli Szafranski on 2/28/16.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/termios.h>
#include <sys/fcntl.h>
#include "Serial.h"


/* Returning -1 is bad I think */
int	write_data(int fileDescriptor, const void *data, size_t size)
{
    int n;
    printf("Sending...\n");

    n = (int) write(fileDescriptor, data, size);
    return n;
}

/* Returning -1 is bad I think */
int new_serial_device(const char *devName)
{
    int fd=-1;
    struct termios term;

    printf("new_serial_device: %s\n", devName);
    fd = open(devName, O_RDWR);
    if (fd < 0) return fd;
    if (tcgetattr(fd, &term) < 0) {
        printf("unable to get terminal settings");
        goto fail;
    }
    cfmakeraw(&term);
    if (tcsetattr(fd, TCSANOW, &term) < 0) {
        printf("unable to set terminal settings");
        goto fail;
    }

    return fd;

    fail:
    printf("not recognized\n");
    if (fd > 0) close(fd);
    return -1;
}
