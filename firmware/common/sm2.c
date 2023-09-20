#include "hal.h"
#include "sm2.h"
#include "defaults.h"

uint32_t start2;

STATE(sm2_init) {
    p1(0);
    if(s11()) {
        NEXT_STATE(sm2_pump_on);
    } else {
        start2 = now();
        NEXT_STATE(sm2_pump_off);
    }
}
STATE(sm2_pump_on) {
    p1(1);
    if(s22() || !s11()){
        start2 = now();
        NEXT_STATE(sm2_pump_off);
    }
}
STATE(sm2_pump_off) {
    p1(0);
    if(now() - start2 > minDelay() && !s22() && s11())
        NEXT_STATE(sm2_pump_on);
}
STATE(sm2_pump_error) {
    p1(0);
}
