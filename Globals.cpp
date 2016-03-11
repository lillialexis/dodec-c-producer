//
// Created by Lilli Szafranski on 3/5/16.
//

#include "Globals.h"

uint FRAME_RATE                 = 0;
useconds_t LOOP_TIME            = 0;
useconds_t CLOCK_SLEEP_INTERVAL = 0;


void initGlobals()
{
    FRAME_RATE = 30;
    CLOCK_SLEEP_INTERVAL = 30;

    LOOP_TIME = 1000000 / 30;

}