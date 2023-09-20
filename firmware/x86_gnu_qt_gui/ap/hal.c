#include "../../common/hal.h"
#include <time.h>

void init_hal() {

}


// ------------ tank 1 ------------
uint8_t pin_s11 = 0;
uint8_t pin_s12 = 0;
uint8_t pin_v1 = 0;

uint32_t now() {
    return (clock() / 1000);
}
uint8_t s11() {
    return pin_s11;
}
uint8_t s12() {
    return pin_s12;
}
uint8_t v1(uint8_t state) {
    pin_v1 = state;
}

// ------------ tank 2 ------------
uint8_t pin_s21 = 0;
uint8_t pin_s22 = 0;
uint8_t pin_p1 = 0;

uint8_t s21() {
    return pin_s21;
}
uint8_t s22() {
    return pin_s22;
}
uint8_t p1(uint8_t state) {
    pin_p1 = state;
}

// ------------ tank 3 ------------
uint8_t pin_s31 = 0;
uint8_t pin_s32 = 0;
uint8_t pin_v2 = 0;

uint8_t s31() {
    return pin_s31;
}
uint8_t s32() {
    return pin_s32;
}
uint8_t v2(uint8_t state) {
    pin_v2 = state;
}
