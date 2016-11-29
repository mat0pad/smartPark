#include "interrupt.h"

Interrupt::Interrupt()
{

}



void Interrupt::myInterruptCamera(void )
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

void Interrupt::myInterruptDisplay(void)
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

void Interrupt::interruptInit(void)
{
    wiringPisetup();
    wiringPiISR(0, INT_EDGE_RISING,&GPIOWorker::myInterruptCamera);
    wiringPiISR(1, INT_EDGE_RISING,&GPIOWorker::myInterruptDisplay);
}
