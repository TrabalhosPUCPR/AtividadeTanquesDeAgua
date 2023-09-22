#include "hal.h"
#include "sm4.h"
#include "defaults.h"
#include "chrono.h"

chrono c4;

STATE(sm4_init) {
    b1(0);
    if(s31())
        NEXT_STATE(sm4_boiler_on);
}
STATE(sm4_boiler_on) {
    b1(1);
    if(bs1() > maxTemp() || !s31()) {
        start_chrono(&c4, minDelay());
        NEXT_STATE(sm4_boiler_off);
    }
}
STATE(sm4_boiler_off) {
    b1(0);
    if(has_time_passed(&c4) && bs1() < maxTemp() && s31()) {
        NEXT_STATE(sm4_boiler_on);
    }
}
STATE(sm4_boiler_error) {

}
