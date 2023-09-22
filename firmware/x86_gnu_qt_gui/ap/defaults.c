#include "../../common/defaults.h"

#define d 3000
#define d2 1500
#define max_temp 5000

double ambient_temp = 2500;

uint32_t minDelay() {
    return d;
}

uint32_t veryShortDelay() {
    return d2;
}

uint32_t maxTemp() {
    return max_temp;
}

uint32_t ambientTemp() {
    return ambient_temp;
}

float fromFakeDecimal(uint32_t f) {
    return (float) (f / 100);
}

uint32_t toFakeDecimal(float a) {
    return (uint32_t) (a * 100);
}
