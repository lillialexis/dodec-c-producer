//
// Created by Lilli Szafranski on 3/5/16.
//

#ifndef DODEC_C_PRODUCER_GLOBALS_H
#define DODEC_C_PRODUCER_GLOBALS_H

#include <sys/types.h>

#define NUM_LEDS 181

uint FRAME_RATE                ;
useconds_t LOOP_TIME           ; /* In microseconds: 1,000,000 / FRAME_RATE */
useconds_t CLOCK_SLEEP_INTERVAL; /* In microseconds; the tiny increments the main loop should sleep after rendering and before the next frame */

void initGlobals();

#endif //DODEC_C_PRODUCER_GLOBALS_H
