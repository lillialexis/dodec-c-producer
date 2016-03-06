//
// Created by Lilli Szafranski on 3/5/16.
//

#ifndef DODEC_C_PRODUCER_PATTERNMANAGER_H
#define DODEC_C_PRODUCER_PATTERNMANAGER_H

#include "Includes.h"


class PatternManager {
public:
    static long getNewDuration(long frameNumber);
    static HSV getNewHSV(long frameNumber);
};


#endif //DODEC_C_PRODUCER_PATTERNMANAGER_H
