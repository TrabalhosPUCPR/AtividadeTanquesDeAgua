#ifndef HAL_H
#define HAL_H

#include <stdint.h>

void init_hal();
uint32_t now();
uint8_t s11();
uint8_t s12();
uint8_t v1(uint8_t state);


#endif // HAL_H
