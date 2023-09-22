#include "chrono.h"
#include "hal.h"

void start_chrono(chrono *c, uint32_t deltaT) {
    *c = now() + deltaT;
}

uint8_t has_time_passed(chrono *c) {
    return now() >= *c;
}
