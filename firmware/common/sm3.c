#include "hal.h"
#include "sm3.h"
#include "defaults.h"

STATE(sm3_init) {
    v2(0);
    if(s21() != s31()) {
        NEXT_STATE(sm3_valve_on);
    }
}
STATE(sm3_valve_on) {
    v2(1);
    if(s32() || s22() || (!s21() && !s31())){
        NEXT_STATE(sm3_valve_off);
    }
}
STATE(sm3_valve_off) {
    v2(0);
    if(!s32() && !s22() || (s21() && s31()))
        NEXT_STATE(sm3_valve_on);
}
STATE(sm3_valve_error) {
    v2(0);
}
