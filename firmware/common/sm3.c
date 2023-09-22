#include "hal.h"
#include "sm3.h"
#include "defaults.h"
#include "chrono.h"

chrono c3;

STATE(sm3_init) {
    v2(0);
    if(s21() != s31()) {
        NEXT_STATE(sm3_valve_on);
    } else {
        NEXT_STATE(sm3_valve_off);
    }
}
STATE(sm3_valve_on) {
    v2(1);
    if(s32() && s22()){
        start_chrono(&c3, veryShortDelay());
        NEXT_STATE(sm3_valve_off);
    }
}
STATE(sm3_valve_off) {
    v2(0);
    if(has_time_passed(&c3) && (!s32() && !s22()))
        NEXT_STATE(sm3_valve_on);
}
STATE(sm3_valve_error) {
    v2(0);
}
