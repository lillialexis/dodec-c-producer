//
// Created by Lilli Szafranski on 2/28/16.
//

#include <stdlib.h>
#include "LED.h"

//LED *leds;
//
//LED newLed()
//{
//    LED led;
//
//    led.r = 0;
//    led.g = 0;
//    led.b = 0;
//    //led.a = 255;
//
//    return led;
//}
//
//void initLEDs()
//{
//    leds = (LED *) malloc(NUM_LEDS * sizeof(LED));
//
//    for (int i = 0; i < NUM_LEDS; i++) {
//        leds[i] = newLed();
//    }
//}

/* Are we going to move up through our hue values or down through our hue values? */
UpdateDirection determineHueDirection(__uint8_t startHue, __uint8_t stopHue)
{
    int delta = stopHue - startHue;

    if (stopHue > startHue) {
        if (delta < 255 / 2)
            return RISING;
        else
            return FALLING;
    } else { // if (stopHue < startHue)
        if (delta < 255 / 2)
            return FALLING;
        else
            return RISING;
    }
}

UpdateDirection determineValueDirection(__uint8_t startValue, __uint8_t stopValue)
{
    if (startValue < stopValue)
        return RISING;
    else
        return FALLING;
}

void LED::setStopHSV(HSV newStopHSV) {
    startHSV = stopHSV;
    stopHSV = newStopHSV;

    hueDirection = determineHueDirection(startHSV.h, stopHSV.h);
    valueDirection = determineValueDirection(startHSV.v, stopHSV.v);
}

void LED::setStopTime(long newStopTime) {
    startTime = stopTime;
    stopTime = newStopTime;
}

RGB LED::getCurrentRGB(long frameNumber) {

    if (frameNumber < startTime || frameNumber > stopTime) {
        throw ; // TODO: Error!!
    }

    int currentStep = (int) (stopTime - frameNumber);
    int totalSteps  = (int) (stopTime - startTime);

    double percentageThrough = totalSteps ? ((double)currentStep / (double)totalSteps) : 1.0;

    int deltaH = stopHSV.h - startHSV.h;
    int deltaV = stopHSV.v - startHSV.v;

    __uint8_t newHue = (__uint8_t)(startHSV.h + (hueDirection * deltaH * percentageThrough));
    __uint8_t newVal = (__uint8_t)(startHSV.v + (valueDirection * deltaV * percentageThrough));

    return hsvToRgb({ newHue, 255, newVal });
}

long LED::getStopTime() {
    return stopTime;
}
