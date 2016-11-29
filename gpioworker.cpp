#include "gpioworker.h"




void GPIOWorker::run()
{
    qDebug() << "Hello from GPIO Thread" << thread()->currentThreadId();
    GPIOWorker::CameraOn_ = false;
    GPIOWorker::DisplayOn_ = true;
    GPIOWorker::currentCamera_ = NULL;
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
    if(!GPIOWorker::CameraOn_)
    {
        GPIOWorker::currentCamera_ = new Camera();
        GPIOWorker::currentCamera_->start();
        GPIOWorker::CameraOn_ = false;
    }
    else{
        GPIOWorker::currentCamera_->terminate();
        GPIOWorker::currentCamera_ = NULL;
        GPIOWorker::CameraOn_ = true;
    }
}

void GPIOWorker::myInterruptDisplay(void)
{
    if(GPIOWorker::DisplayOn_)
    {
        GPIOWorker::DisplayOn_ = false;
        GPIOWorker::turnOnDisplay(GPIOWorker::DisplayOn_);
    }
    else{
    GPIOWorker::DisplayOn_ = true;
    GPIOWorker::turnOnDisplay(GPIOWorker::DisplayOn_);
    }
}

void GPIOWorker::interruptInit(void)
{
    wiringPisetup();
    wiringPiISR(0, INT_EDGE_RISING,&GPIOWorker::InterruptCamera);
    wiringPiISR(1, INT_EDGE_RISING,&GPIOWorker::InterruptDisplay);
}

void InterruptCamera(void)
{
    GPIOWorker::myInterruptCamera();
}

void InterruptDisplay(void)
{
    GPIOWorker::myInterruptDisplay();
}



