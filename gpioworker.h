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
    GPIOWorker(GPIOWorker *GPIOPtr);
    void myInterruptDisplay(void);
    void myInterruptCamera(void);
    static GPIOWorker *GPIOPtr_;
private:
    void turnOnDisplay(bool shouldTurnOn);
    void interruptInit(void);
    void run();
    bool CameraOn_;
    bool DisplayOn_;
    Camera *currentCamera_;

signals:
    void turnOnSection(bool shouldTurnOn);
    void toggleMusic(bool MusicOn);

};

#endif // GPIOWORKER_H
