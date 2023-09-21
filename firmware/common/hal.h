#ifndef HAL_H
#define HAL_H

#include <stdint.h>

void init_hal();
uint32_t now();

// tanque 1
uint8_t s11();
uint8_t s12();
uint8_t v1(uint8_t state);

// tanque 2
uint8_t s21();
uint8_t s22();
uint8_t p1(uint8_t state);

// tanque 3
uint8_t s31();
uint8_t s32();
uint8_t bs1();
uint8_t v2(uint8_t state);
uint8_t b1(int8_t state);

#endif // HAL_H
