#include "sm1.h"
#include "hal.h"
#include "defaults.h"

uint32_t start;

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
        start = now();
        NEXT_STATE(sm1_v1_off);
    }
}
STATE(sm1_v1_off) {
    v1(0);
    if(now() - start > minDelay() && !s12())
        NEXT_STATE(sm1_v1_on);
}
STATE(sm1_v1_error) {
    v1(0);
}
