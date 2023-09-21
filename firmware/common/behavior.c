#include "hal.h"
#include "sm1.h"
#include "sm2.h"
#include "sm3.h"
#include "sm4.h"

StateMachine sm1;
StateMachine sm2;
StateMachine sm3;
StateMachine sm4;

void behavior() {
    init_hal();
    INIT(sm1, sm1_init);
    INIT(sm2, sm2_init);
    INIT(sm3, sm3_init);
    INIT(sm4, sm4_init);
    while (1) {
        EXEC(sm1);
        EXEC(sm2);
        EXEC(sm3);
        EXEC(sm4);
    }
}
