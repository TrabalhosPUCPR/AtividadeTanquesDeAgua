#include "hal.h"
#include "sm2.h"
#include "defaults.h"
#include "chrono.h"

chrono c2;

STATE(sm2_init) {
    p1(0);
    if(s11()) {
        NEXT_STATE(sm2_pump_on);
    } else {
        start_chrono(&c2, minDelay());
        NEXT_STATE(sm2_pump_off);
    }
}
STATE(sm2_pump_on) {
    p1(1);
    if(s22() || !s11()){
        start_chrono(&c2, minDelay());
        NEXT_STATE(sm2_pump_off);
    }
}
STATE(sm2_pump_off) {
    p1(0);
    if(has_time_passed(&c2) && !s22() && s11())
        NEXT_STATE(sm2_pump_on);
}
STATE(sm2_pump_error) {
    p1(0);
}
