#ifndef GPIOWORKER_H
#define GPIOWORKER_H
#include <QThread>
#include <QDebug>
#include "camera.h"
#include <wiringPi.h>
#include <QProcess>

class GPIOWorker: public QThread
{
    Q_OBJECT

public:
    void turnOnDisplay(bool shouldTurnOn);

private:
    void myInterruptDisplay(void);
    void myInterruptCamera(void);
    void interruptInit(void);
    void run();
    bool CameraOn_ = false;
    bool DisplayOn_ = true;
    Camera *currentCamera_ = NULL;

signals:
    void turnOnSection(bool shouldTurnOn);

};

#endif // GPIOWORKER_H
