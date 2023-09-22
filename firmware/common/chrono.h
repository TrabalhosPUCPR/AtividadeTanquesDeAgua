#ifndef CHRONO_H
#define CHRONO_H

#include <stdint.h>

typedef uint32_t chrono;

void start_chrono(chrono *c, uint32_t deltaT);
uint8_t has_time_passed(chrono *c);

#endif // CHRONO_H
