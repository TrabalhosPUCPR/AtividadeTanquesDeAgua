#include "sm1.h"
#include "hal.h"
#include "defaults.h"
#include "chrono.h"

chrono c1;

STATE(sm1_init) {
    v1(0);
    if(s12())
        NEXT_STATE(sm1_v1_off);
    else
        NEXT_STATE(sm1_v1_on);
}
STATE(sm1_v1_on) {
    v1(1);
    if(s12()){
        start_chrono(&c1, minDelay());
        NEXT_STATE(sm1_v1_off);
    }
}
STATE(sm1_v1_off) {
    v1(0);
    if(has_time_passed(&c1) && !s12())
        NEXT_STATE(sm1_v1_on);
}
STATE(sm1_v1_error) {
    v1(0);
}
