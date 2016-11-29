#ifndef GPIOWORKER_H
#define GPIOWORKER_H
#include <QThread>
#include <QDebug>
#include "camera.h"
#include <wiringPi.h>
#include <QProcess>

void InterruptCamera(void);
void InterruptDisplay(void);

class GPIOWorker: public QThread
{
    Q_OBJECT

public:
    static void myInterruptDisplay(void);
    static void myInterruptCamera(void);
private:
    static void turnOnDisplay(bool shouldTurnOn);
    void interruptInit(void);
    void run();
    static bool CameraOn_;
    static bool DisplayOn_;
    static Camera *currentCamera_;

signals:
    void turnOnSection(bool shouldTurnOn);

};

#endif // GPIOWORKER_H
