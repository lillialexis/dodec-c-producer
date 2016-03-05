//
// Created by Lilli Szafranski on 2/28/16.
//

#ifndef DODEC_C_PRODUCER_UTIL_H
#define DODEC_C_PRODUCER_UTIL_H

#include <unistd.h>

typedef struct {
	__uint8_t g;
	__uint8_t r;
	__uint8_t b;
} RGB;

typedef struct {
	__uint8_t h;
	__uint8_t s;
	__uint8_t v;
} HSV;

RGB hsvToRgb(HSV hsv);//, RGB rgb);

#endif //DODEC_C_PRODUCER_UTIL_H
