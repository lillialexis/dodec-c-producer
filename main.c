//
// Created by Lilli Szafranski on 2/28/16.
//

#include <unistd.h>
#include "Includes.h"
#include "Serial.h"
#include "LED.h"
#include "Util.h"

#define FRAME_RATE 30.0

void updateLeds()
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
}

int main()
{
    initLEDs();

    int serialDevice = new_serial_device("/dev/ttyS0");

    if (serialDevice < 0) {
        printf("Error creating serial device!\n");
        return 1;
    }

    __uint8_t i = 0;
    while (1) {
        printf("Looping...\n");

        updateLeds();
        int status = write_data(serialDevice, leds, NUM_LEDS * sizeof(LED));

        if (status < 0) {
            printf("Error writing to serial device!\n");
            return 1;
        }

        i++;

        usleep(10 * 1000);
    }

    return 0;
}