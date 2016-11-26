#include "gpioworker.h"

bool GPIOWorker::CameraOn_ = false;
bool GPIOWorker::DisplayOn_ = true;
Camera *GPIOWorker::currentCamera_ = NULL;


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
    if(!GPIOWorker::CameraOn_)
    {
        qDebug() << "Starting Camera\n";
        GPIOWorker::currentCamera_ = new Camera();
        GPIOWorker::currentCamera_->start();
        GPIOWorker::CameraOn_ = false;
        GPIOWorker::sleep(1);
    }
    else{
        qDebug() << "Turning off Camera\n";
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
    setenv("WIRINGPI_GPIOMEM", "1", 1);
    wiringPiSetup();
    wiringPiISR(0, INT_EDGE_RISING,&InterruptCamera);
    wiringPiISR(1, INT_EDGE_RISING,&InterruptDisplay);
}

void InterruptCamera(void)
{
    GPIOWorker::myInterruptCamera();
}

void InterruptDisplay(void)
{
    GPIOWorker::myInterruptDisplay();
}



