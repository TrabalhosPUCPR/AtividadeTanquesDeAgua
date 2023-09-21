#include "hal.h"
#include "sm4.h"
#include "defaults.h"

uint32_t start4;

STATE(sm4_init) {
    b1(0);
    if(!bs1() && s31())
        NEXT_STATE(sm4_boiler_on);
}
STATE(sm4_boiler_on) {
    b1(1);
    if(bs1() || !s31()) {
        start4 = now();
        NEXT_STATE(sm4_boiler_off);
    }
}
STATE(sm4_boiler_off) {
    b1(0);
    if(now() - start4 > minDelay() && !bs1() && s31()) {
        NEXT_STATE(sm4_boiler_on);
    }
}
STATE(sm4_boiler_error) {

}
