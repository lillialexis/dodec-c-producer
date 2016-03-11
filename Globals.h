//
// Created by Lilli Szafranski on 3/5/16.
//

#ifndef DODEC_C_PRODUCER_GLOBALS_H
#define DODEC_C_PRODUCER_GLOBALS_H

#include <sys/types.h>

#define NUM_LEDS   181
#define NUM_BOARDS 12
#define MAX_GROUPS 20

#define NUMBER_RENDERING 12

extern uint FRAME_RATE                ;
extern useconds_t LOOP_TIME           ; /* In microseconds: 1,000,000 / FRAME_RATE */
extern useconds_t CLOCK_SLEEP_INTERVAL; /* In microseconds; the tiny increments the main loop should sleep after rendering and before the next frame */

void initGlobals();

#endif //DODEC_C_PRODUCER_GLOBALS_H
