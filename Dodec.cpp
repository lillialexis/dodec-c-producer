//
// Created by Lilli Szafranski on 3/5/16.
//

#include <stdlib.h>
#include "Dodec.h"


Dodec::Dodec() {
    num_boards = NUM_BOARDS;
    num_leds   = NUM_LEDS;
    max_groups = MAX_GROUPS;

    boards = new Board[num_boards](max_groups);

    staticMasterGroups = new Group[max_groups];
    dynamicMasterGroups = new Group[max_groups];

    buffer = (RGB *) malloc(num_boards * num_leds * sizeof(RGB));
    memset(buffer, '\0', (num_boards * num_leds * sizeof(RGB)));

//    buffer = new RGB[num_boards * num_leds];

    leds = new LED*[num_boards];

    for (int i = 0; i < num_boards; i++) {
        leds[i] = new LED[num_leds];

        for (int j = 0; j < num_leds; j++) {
            LED led;

            int foo = j % 36;
            if (foo == 0) {
                led.setGroup(0);
            } else if (foo <= 8) {
                led.setGroup(1);
            } else if (foo <= 15) {
                led.setGroup(2);
            } else if (foo <= 21) {
                led.setGroup(3);
            } else if (foo <= 26) {
                led.setGroup(4);
            } else if (foo <= 30) {
                led.setGroup(5);
            } else if (foo <= 33) {
                led.setGroup(6);
            } else if (foo <= 35) {
                led.setGroup(7);
            }

            leds[i][j] = led;
        }
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

int Dodec::currentlyRendering() {
    return num_leds * NUMBER_RENDERING;
}
