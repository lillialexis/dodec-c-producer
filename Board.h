//
// Created by Lilli Szafranski on 3/5/16.
//

#ifndef DODEC_C_PRODUCER_BOARD_H
#define DODEC_C_PRODUCER_BOARD_H

//#include "Includes.h"

typedef enum
{
    ORIENTATION_UP,
    ORIENTATION_DOWN,
} BoardOrientation;

class Board {
    BoardOrientation orientation;
    
    int numberOfGroups;
    Group groups[];
};


#endif //DODEC_C_PRODUCER_BOARD_H
