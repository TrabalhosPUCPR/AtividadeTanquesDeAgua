#include "sm1.h"
#include "hal.h"

#include <stdio.h>

STATE(sm1_init) {
    v1(0);
    if(s12())
        NEXT_STATE(sm1_v1_off);
    else
        NEXT_STATE(sm1_v1_on);
}
STATE(sm1_v1_on) {
    v1(1);
    if(s12()) // desliga caso a valvula for desligada por fora
        NEXT_STATE(sm1_v1_off);
}
STATE(sm1_v1_off) {
    v1(0);
    if(!s12())
        NEXT_STATE(sm1_v1_on);
    else if(!s11())
        NEXT_STATE(sm1_v1_error);
}
STATE(sm1_v1_error) {
    v1(0);
}
