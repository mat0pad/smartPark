#include "gpioworker.h"




void GPIOWorker::run()
{
    qDebug() << "Hello from GPIO Thread" << thread()->currentThreadId();

    interruptInit();

    while(1)
    {
    }
}

void GPIOWorker::turnOnDisplay(bool shouldTurnOn)
{
    // Turn off/on display here'
    if(shouldTurnOn)
        QProcess::execute("sudo bash -c \"echo 0 > /sys/class/backlight/rpi_backlight/bl_power\"");
    else
            QProcess::execute("sudo bash -c \"echo 1 > /sys/class/backlight/rpi_backlight/bl_power\"");

}

void GPIOWorker::myInterruptCamera(void )
{
    if(!CameraOn_)
    {
        currentCamera_ = new Camera();
        currentCamera_->start();
        CameraOn = false;
    }
    else{
        currentCamera_->terminate();
        currentCamera_ = NULL;
        CameraOn_ = true;
    }
}

void GPIOWorker::myInterruptDisplay(void)
{
    if(DisplayOn_)
    {
        DisplayOn_ = false;
        turnOnDisplay(DisplayOn_);
    }
    else{
    DisplayOn_ = true;
    turnOnDisplay(DisplayOn_);
    }
}

void GPIOWorker::interruptInit(void)
{
    wiringPisetup();
    wiringPiISR(0, INT_EDGE_RISING,&GPIOWorker::myInterruptCamera);
    wiringPiISR(1, INT_EDGE_RISING,&GPIOWorker::myInterruptDisplay);
}




