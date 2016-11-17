#ifndef GPIOWORKER_H
#define GPIOWORKER_H
#include <QThread>
#include <QDebug>
#include "camera.h"

class GPIOWorker: public QThread
{
    Q_OBJECT

public:
    void turnOnDisplay(bool shouldTurnOn);

private:
    void run();

signals:
    void turnOnSection(bool shouldTurnOn);

};

#endif // GPIOWORKER_H
