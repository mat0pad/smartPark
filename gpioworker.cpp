#include "gpioworker.h"

// Init static vars
bool GPIOWorker::CameraOn_ = false;
bool GPIOWorker::DisplayOn_ = true;
Camera *GPIOWorker::currentCamera_ = NULL;
//Needs a GPIOWorker pointer to call the toogleMusic signals, since signals can't be static.
//GPIOWorker *GPIOWorker::GPIOptr = new GPIOWorker();


void GPIOWorker::run()
{
    /** DEBUG **/
    //qDebug() << "Hello from GPIO Thread" << thread()->currentThreadId();

    interruptInit();

    while(1)
    {}
}

void GPIOWorker::turnOnDisplay(bool shouldTurnOn)
{
    // Turn off/on display here
    if(shouldTurnOn)
        QProcess::execute("sudo bash -c \"echo 0 > /sys/class/backlight/rpi_backlight/bl_power\"");
    else
        QProcess::execute("sudo bash -c \"echo 1 > /sys/class/backlight/rpi_backlight/bl_power\"");

}

void GPIOWorker::myInterruptCamera(void )
{
    if(!GPIOWorker::CameraOn_)
    {
        /** DEBUG **/
        //qDebug() << "Starting Camera\n";

        GPIOWorker::currentCamera_ = new Camera();
        GPIOWorker::currentCamera_->start();
        GPIOWorker::CameraOn_ = true;
        GPIOWorker::sleep(1);
    }
    else
    {
        /** DEBUG **/
        //qDebug() << "Turning off Camera\n";

        GPIOWorker::currentCamera_->terminate();
        GPIOWorker::currentCamera_ = NULL;
        GPIOWorker::CameraOn_ = false;
    }
}

void GPIOWorker::myInterruptDisplay(void)
{
    if(GPIOWorker::DisplayOn_)
    {
        GPIOWorker::DisplayOn_ = false;
        GPIOWorker::turnOnDisplay(GPIOWorker::DisplayOn_);
    }
    else
    {
        GPIOWorker::DisplayOn_ = true;
        GPIOWorker::turnOnDisplay(GPIOWorker::DisplayOn_);
    }
     //SIgnaling soundworker with turning on music
     emit toggleMusic(GPIOWorker::DisplayOn_);
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



