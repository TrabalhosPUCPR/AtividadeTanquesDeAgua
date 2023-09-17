#include "behaviorthread.h"

extern "C" {
    #include "../../common/behavior.h"
}

BehaviorThread::BehaviorThread(QObject *parent)
    : QThread{parent}
{

}

void BehaviorThread::run(){
    behavior();
}
