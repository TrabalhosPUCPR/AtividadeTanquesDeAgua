#include "hal.h"
#include "sm3.h"

STATE(sm3_init) {
    p2(0);
    if(s32() || !s21()) {
        NEXT_STATE(sm3_pump_off);
    } else {
        NEXT_STATE(sm3_pump_on);
    }
}
STATE(sm3_pump_on) {
    p2(1);
    if(s32() || !s21())
        NEXT_STATE(sm3_pump_off);
}
STATE(sm3_pump_off) {
    p2(0);
    if(!s32() && s21())
        NEXT_STATE(sm3_pump_on);
}
STATE(sm3_pump_error) {
    p2(0);
}
