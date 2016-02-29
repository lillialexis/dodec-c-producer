//
// Created by Lilli Szafranski on 2/28/16.
//

#include <unistd.h>
#include "Includes.h"
#include "Serial.h"
#include "LED.h"


void updateLeds()
{
    static __uint8_t hue = 1;

    for (int i = 0; i < NUM_LEDS; i++) {
        //LED led = leds[i];
        leds[i].r = hue;
        leds[i].g = hue;
        leds[i].b = hue;
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

        sleep(1);
    }

    return 0;
}