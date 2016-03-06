//
// Created by Lilli Szafranski on 2/28/16.
//

#include <unistd.h>
#include <time.h>
#include "Includes.h"
#include "PatternManager.h"


int serialDevice = -1;

long programStartTime   = 0;
long loopStartTime      = 0;
long idealLoopEndTime   = 0;
long timeAfterRender    = 0;
long drawStartTime      = 0;
int  lastDrawDuration   = 0;

long currentTimeInMicroseconds()
{
    return time(0) * 1000;
}

/* Delta in microseconds between the time value passed in and the time that the program launched (program time delta) */
int ptd(long someTimeVal)
{
    return (int) (someTimeVal - programStartTime);
}

/* Return 0 if successful, 1 otherwise. */
int updateLeds(Dodec& dodec, long frameNumber)
{
    for (int i = 0; i < dodec.getNumBoards(); i++) {
        for (int j = 0; j < dodec.getNumLeds(); j++) {
            LED led = dodec.leds[i][j];

            if (frameNumber > led.getStopTime()) {
                led.setStopTime(PatternManager::getNewDuration(frameNumber));
                led.setStopHSV(PatternManager::getNewHSV(frameNumber));
            }

            dodec.leds[i][j] = led;
        }
    }

    return 0;
}

/* Return 0 if successful, 1 otherwise. */
int draw(Dodec& dodec, long frameNumber)
{
    for (int i = 0; i < dodec.getNumBoards(); i++) {
        for (int j = 0; j < dodec.getNumLeds(); j++) {
            int index = (i * dodec.getNumLeds()) + j;

            LED led = dodec.leds[i][j];
            RGB rgb = led.getCurrentRGB(frameNumber);

            dodec.buffer[index] = rgb;
        }
    }

    /* Status should be equal to the number of bytes sent, or -1 if there was an error. */
    int status = write_data(serialDevice, dodec.buffer, dodec.getNumBoards() * dodec.getNumLeds() * sizeof(RGB));

    if (status < 0) {
        printf("Error writing to serial device!\n");
        return 1;
    }

    return 0;
}

/* Return 0 if successful, 1 otherwise. */
int loop(Dodec& dodec)
{
    int status = 0;
    static long frameNumber = 1;

    while (1) {

        /* Capture the start time of our current loop, and calculate the time when this loop would ideally end,
         * which is the current start time + the ideal loop duration (in MS) - however long our last draw function took. */
        loopStartTime = currentTimeInMicroseconds();
        idealLoopEndTime = loopStartTime + LOOP_TIME - lastDrawDuration;
        printf("Looping. Start time: %i, ideal loop duration: %i, ideal draw time: %i\n",
               ptd(loopStartTime), LOOP_TIME - lastDrawDuration, ptd(idealLoopEndTime));

        status = updateLeds(dodec, frameNumber);
        if (status != 0) {
            return 1;
        }

        /* Now capture the current time, and see if our render function took up the whole duration of our loop. */
        timeAfterRender = currentTimeInMicroseconds();
        printf("Render duration: %li\n", timeAfterRender - loopStartTime);

        /* If it took up the whole duration of our loop, that's bad. Print this. */
        if (timeAfterRender >= idealLoopEndTime) {
            printf("RENDERING TAKING TOO LONG!!\n");
        }

        useconds_t sleepTime = (useconds_t) (idealLoopEndTime > timeAfterRender ? idealLoopEndTime - timeAfterRender : 0);
        printf("Sleep duration: %u\n", sleepTime);

        usleep(sleepTime);

        drawStartTime = currentTimeInMicroseconds();

        status = draw(dodec, frameNumber);
        if (status != 0) {
            return 1;
        }

        lastDrawDuration = (int) (currentTimeInMicroseconds() - drawStartTime);
        printf("Draw duration: %i\n", lastDrawDuration);

        if (lastDrawDuration + (timeAfterRender - loopStartTime) > LOOP_TIME)
            printf("DRAWING TAKING TOO LONG!!\n");

        frameNumber++;
    }
}

int main()
{
    programStartTime = currentTimeInMicroseconds();

    initGlobals();

    serialDevice = new_serial_device("/dev/ttyS0");

    if (serialDevice < 0) {
        printf("Error creating serial device!\n");
        return 1;
    }

    Dodec dodec;

    /* Should only exit on error... */
    int status = loop(dodec);

    return status;
}