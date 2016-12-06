#include "gpioworker.h"

//Needs a GPIOWorker pointer to call the toogleMusic signals, since signals can't be static.
GPIOWorker *GPIOWorker::GPIOPtr_ = NULL;


GPIOWorker::GPIOWorker()
{
    GPIOWorker::GPIOPtr_ = this;
}



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
    if(!CameraOn_)
    {
        /** DEBUG **/
        //qDebug() << "Starting Camera\n";
        currentCamera_ = new Camera();
        currentCamera_->start();
        CameraOn_ = true;
        sleep(1);
    }
    else
    {
        /** DEBUG **/
        //qDebug() << "Turning off Camera\n";s
        currentCamera_->terminate();
        currentCamera_ = NULL;
        CameraOn_ = false;
    }
}

void GPIOWorker::myInterruptDisplay(void)
{
    if(DisplayOn_)
    {
        DisplayOn_ = false;
        turnOnDisplay(DisplayOn_);
    }
    else
    {
        DisplayOn_ = true;
        turnOnDisplay(DisplayOn_);
    }
     //Signaling soundworker with turning on music
     emit toggleMusic(DisplayOn_);

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
    GPIOWorker::GPIOPtr_->myInterruptCamera();
}

void InterruptDisplay(void)
{
    GPIOWorker::GPIOPtr_->myInterruptDisplay();
}



