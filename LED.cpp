//
// Created by Lilli Szafranski on 2/28/16.
//

#include <stdlib.h>
#include "Includes.h"

LED *leds;

LED newLed()
{
    LED led;

    led.r = 0;
    led.g = 0;
    led.b = 0;
    //led.a = 255;

    return led;
}

void initLEDs()
{
    leds = (LED *) malloc(NUM_LEDS * sizeof(LED));

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = newLed();
    }
}
