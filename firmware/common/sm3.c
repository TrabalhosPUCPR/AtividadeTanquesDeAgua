#include "hal.h"
#include "sm3.h"
#include "defaults.h"

uint32_t start3;

STATE(sm3_init) {
    v2(0);
    if(s21()) {
        NEXT_STATE(sm3_pump_on);
    }
}
STATE(sm3_pump_on) {
    v2(1);
    if(s32() || !s21()){
        start3 = now();
        NEXT_STATE(sm3_pump_off);
    }
}
STATE(sm3_pump_off) {
    v2(0);
    if(now() - start3 > minDelay() && !s32() && s21())
        NEXT_STATE(sm3_pump_on);
}
STATE(sm3_pump_error) {
    v2(0);
}
