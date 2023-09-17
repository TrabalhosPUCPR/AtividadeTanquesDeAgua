#ifndef BEHAVIORTHREAD_H
#define BEHAVIORTHREAD_H

#include <QThread>

class BehaviorThread : public QThread
{
public:
    BehaviorThread(QObject *parent = nullptr);
    void run();
};

#endif // BEHAVIORTHREAD_H
