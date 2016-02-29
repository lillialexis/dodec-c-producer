//
// Created by Lilli Szafranski on 2/28/16.
//

#ifndef DODEC_C_PRODUCER_LED_H
#define DODEC_C_PRODUCER_LED_H

#include <unistd.h>

#define NUM_LEDS 181

typedef struct
{
    __uint8_t r;
    __uint8_t g;
    __uint8_t b;
//    __uint8_t a;
} LED;

 LED *leds;

void initLEDs();

//LED *newLed();

//void setRed  (LED *led, __uint8_t red);
//void setGreen(LED *led, __uint8_t red);
//void setBlue (LED *led, __uint8_t red);
//void setAlpha(LED *led, __uint8_t red);
//__uint8_t getRed  (LED *led, __uint8_t red);
//__uint8_t getGreen(LED *led, __uint8_t red);
//__uint8_t getBlue (LED *led, __uint8_t red);
//__uint8_t getAlpha(LED *led, __uint8_t red);




#endif //DODEC_C_PRODUCER_LED_H
