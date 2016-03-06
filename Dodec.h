//
// Created by Lilli Szafranski on 3/5/16.
//

#ifndef DODEC_C_PRODUCER_DODEC_H
#define DODEC_C_PRODUCER_DODEC_H

#include "Includes.h"


class Dodec {


//    LED leds[NUM_BOARDS][NUM_LEDS];
//
//    Board boards[NUM_BOARDS];
//
//    Group staticMasterGroups[MAX_GROUPS];
//    Group dynamicMasterGroups[MAX_GROUPS];

    int num_leds;
    int num_boards;
    int max_groups;

public:

    LED **leds;

    Board *boards;

    Group *staticMasterGroups;
    Group *dynamicMasterGroups;

    RGB *buffer;

    Dodec();
    ~Dodec();

    int getNumLeds();
    int getNumBoards();
    int getMaxGroups();

    int currentlyRendering();
};


#endif //DODEC_C_PRODUCER_DODEC_H
