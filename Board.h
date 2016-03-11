//
// Created by Lilli Szafranski on 3/5/16.
//

#ifndef DODEC_C_PRODUCER_BOARD_H
#define DODEC_C_PRODUCER_BOARD_H

#include "Includes.h"

typedef enum
{
    ORIENTATION_UP,
    ORIENTATION_DOWN,
} BoardOrientation;

class Board {
public:
    BoardOrientation orientation;
    
    int numberOfGroups;
    Group groups[];


    Board(int numberOfGroups) : numberOfGroups(numberOfGroups) {
        groups = new Group[numberOfGroups];
    }


    virtual ~Board() {

    }


    const BoardOrientation &getOrientation() const {
        return orientation;
    }

    void setOrientation(const BoardOrientation &orientation) {
        Board::orientation = orientation;
    }

    int getNumberOfGroups() const {
        return numberOfGroups;
    }

    void setNumberOfGroups(int numberOfGroups) {
        Board::numberOfGroups = numberOfGroups;
    }

    const Group *getGroups() const {
        return groups;
    }
};


#endif //DODEC_C_PRODUCER_BOARD_H
