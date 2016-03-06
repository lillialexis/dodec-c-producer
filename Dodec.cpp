//
// Created by Lilli Szafranski on 3/5/16.
//

#include <stdlib.h>
#include "Dodec.h"


Dodec::Dodec() {
    num_boards = NUM_BOARDS;
    num_leds   = NUM_LEDS;
    max_groups = MAX_GROUPS;

    boards = new Board[num_boards];

    staticMasterGroups = new Group[max_groups];
    dynamicMasterGroups = new Group[max_groups];

    buffer = (RGB *) malloc(num_boards * num_leds * sizeof(RGB));
    memset(buffer, '\0', (num_boards * num_leds * sizeof(RGB)));

//    buffer = new RGB[num_boards * num_leds];

    leds = new LED*[num_boards];

    for (int i = 0; i < num_boards; i++) {
        leds[i] = new LED[num_leds];

        for (int j = 0; j < num_leds; j++) {
            leds[i][j] = LED();
        }

        boards[i] = Board();
    }

    for (int i = 0; i < max_groups; i++) {
        staticMasterGroups[i] = Group();
        dynamicMasterGroups[i] = Group();
    }
}

Dodec::~Dodec() {

}

int Dodec::getNumLeds() {
    return num_leds;
}

int Dodec::getNumBoards() {
    return num_boards;
}

int Dodec::getMaxGroups() {
    return max_groups;
}
