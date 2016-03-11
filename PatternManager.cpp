//
// Created by Lilli Szafranski on 3/5/16.
//

#include "PatternManager.h"

HSV PatternManager::getNewHSV(long frameNumber) {
    static HSV hsv;
    hsv.h = (__uint8_t) frameNumber;
    hsv.s = 255;
    hsv.v = 255;

    return hsv;
}

long PatternManager::getNewDuration(long frameNumber) {
    return frameNumber + 1;
}
