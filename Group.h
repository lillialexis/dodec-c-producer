//
// Created by Lilli Szafranski on 3/5/16.
//

#ifndef DODEC_C_PRODUCER_GROUP_H
#define DODEC_C_PRODUCER_GROUP_H

#include "Includes.h"

class Group {

    long stopTime;
    HSV stopHSV;

    int staticMaster;
    int dynamicMaster;

public:

    Group();
    ~Group();

    long getStopTime() const {
        return stopTime;
    }

    void setStopTime(long stopTime) {
        Group::stopTime = stopTime;
    }

    const HSV &getStopHSV() const {
        return stopHSV;
    }

    void setStopHSV(const HSV &stopHSV) {
        Group::stopHSV = stopHSV;
    }

    int getStaticMaster() const {
        return staticMaster;
    }

    void setStaticMaster(int staticMaster) {
        Group::staticMaster = staticMaster;
    }

    int getDynamicMaster() const {
        return dynamicMaster;
    }

    void setDynamicMaster(int dynamicMaster) {
        Group::dynamicMaster = dynamicMaster;
    }
};


#endif //DODEC_C_PRODUCER_GROUP_H
