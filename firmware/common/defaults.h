#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <stdint.h>
#include <float.h>

uint32_t minDelay();
uint32_t veryShortDelay();
uint32_t maxTemp();
uint32_t ambientTemp();
uint32_t toFakeDecimal(float a);
float fromFakeDecimal(uint32_t f);

#endif // DEFAULTS_H
