//
// Created by Lilli Szafranski on 2/28/16.
//

#include <unistd.h>
#include <time.h>
#include "Includes.h"

int serialDevice = -1;

long programStartTime   = 0;
long loopStartTime      = 0;
long idealLoopEndTime   = 0;
long timeAfterRender    = 0;
long sampleStartTime    = 0;
int  lastSampleDuration = 0;
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

/* Print milliseconds */
int pms(int someTimeVal) {
    return someTimeVal;
}

/* Return 0 if successful, 1 otherwise. */
int updateLeds()
{
    static __uint8_t hue = 1;
    static HSV hsv;
    hsv.h = hue;
    hsv.s = 255;
    hsv.v = 255;

    RGB rgb = hsvToRgb(hsv);

    for (int i = 0; i < NUM_LEDS; i++) {
        //LED led = leds[i];
        leds[i].r = rgb.r;
        leds[i].g = rgb.g;
        leds[i].b = rgb.b;
        //leds[i].a = 255;

        //leds[i] = led;
    }

    hue = (__uint8_t) ((hue + 1) % 255);

    return 0;
}

/* Return 0 if successful, 1 otherwise. */
int draw()
{
    /* Status should be equal to the number of bytes sent, or -1 if there was an error. */
    int status = write_data(serialDevice, leds, NUM_LEDS * sizeof(LED));

    if (status < 0) {
        printf("Error writing to serial device!\n");
        return 1;
    }

    return 0;
}

///* Return 0 if successful, 1 otherwise. */
//int sample()
//{
//    /* This is where we would sample anything like sounds or something,
//     * which I guess we're only sampling between the rendering and the
//     * drawing. Probably not the best design, but since we're not even
//     * sampling anything at all right now, I don't really care. */
//    return 0;
//}

/* Return 0 if successful, 1 otherwise. */
int loop()
{
    int status = 0;

    while (1) {

        /* Capture the start time of our current loop, and calculate the time when this loop would ideally end,
         * which is the current start time + the ideal loop duration (in MS) - however long our last draw function took. */
        loopStartTime = currentTimeInMicroseconds();
        idealLoopEndTime = loopStartTime + LOOP_TIME - lastDrawDuration;
        printf("Looping. Start time: %i, ideal loop duration: %i, ideal draw time: %i\n",
               ptd(loopStartTime), LOOP_TIME - lastDrawDuration, ptd(idealLoopEndTime));

        status = updateLeds();
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

//        /* Assuming we didn't take up the whole duration of our loop (as the 'while' check will immediately fail if
//         * we did), sleep for tiny increments until we get to less than one increment away from our ideal draw time,
//         * sampling whatever it is that we want to sample. Hopefully sampling doesn't take a whole lot longer than
//         * our sleep increment, or this will slow our loop down. Honestly, I feel like sampling should probably
//         * just take place on a separate thread, since what's the point of sampling a bunch of times between
//         * rendering frames. We'd only end up using the data from the last sample anyway. But whatevs. */
//        while (currentTimeInMicroseconds() < (idealLoopEndTime - CLOCK_SLEEP_INTERVAL)) {
//            sampleStartTime = currentTimeInMicroseconds();
//
//            status = sample();
//            if (status != 0) {
//                return 1;
//            }
//
//            lastSampleDuration = (int) (currentTimeInMicroseconds() - sampleStartTime);
//            printf("Sample duration: %i, clock sleep interval: %u, remaining interval: %i\n",
//                   pms(lastSampleDuration), CLOCK_SLEEP_INTERVAL, CLOCK_SLEEP_INTERVAL - lastSampleDuration);
//
//            if (CLOCK_SLEEP_INTERVAL - lastSampleDuration > 0)
//                usleep(CLOCK_SLEEP_INTERVAL - lastSampleDuration);
//            else
//                printf("SAMPLING TAKING TOO LONG!!\n");
//        }

        useconds_t sleepTime = (useconds_t) (idealLoopEndTime > timeAfterRender ? idealLoopEndTime - timeAfterRender : 0);
        printf("Sleep duration: %u\n", sleepTime);

        usleep(sleepTime);

        drawStartTime = currentTimeInMicroseconds();

        status = draw();
        if (status != 0) {
            return 1;
        }

        lastDrawDuration = (int) (currentTimeInMicroseconds() - drawStartTime);
        printf("Draw duration: %i\n", lastDrawDuration);

        if (lastDrawDuration + (timeAfterRender - loopStartTime) > LOOP_TIME)
            printf("DRAWING TAKING TOO LONG!!\n");
    }
}

int main()
{
    programStartTime = currentTimeInMicroseconds();

    initGlobals();
    initLEDs();

    serialDevice = new_serial_device("/dev/ttyS0");

    if (serialDevice < 0) {
        printf("Error creating serial device!\n");
        return 1;
    }

//    while (1) {
//        static int loopResult = 0;
//
//        loopResult = loop();
//
//        if (loopResult != 0)
//            return loopResult;
//    }

    /* Should only exit on error... */
    int status = loop();

    return status;
}