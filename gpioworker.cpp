#include "gpioworker.h"

//Needs a GPIOWorker pointer to call the toogleMusic signals, since signals can't be static.
GPIOWorker *GPIOWorker::GPIOPtr_ = NULL;


GPIOWorker::GPIOWorker()
{
    // pointer to the class so the interrupts function can call the class function
    GPIOWorker::GPIOPtr_ = this;
}



void GPIOWorker::run()
{
    /** DEBUG **/
    //qDebug() << "Hello from GPIO Thread" << thread()->currentThreadId();

    interruptInit(); //init interrupts

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
        currentCamera_->start(); //Start Camera thread
        CameraOn_ = true;  // Camera on
        sleep(1);
    }
    else
    {
        /** DEBUG **/
        //qDebug() << "Turning off Camera\n";s
        currentCamera_->terminate(); //destorys Camera thread
        currentCamera_ = NULL; //NO floating pointers!
        CameraOn_ = false;  //Camera off
    }
}

void GPIOWorker::myInterruptDisplay(void)
{
    if(DisplayOn_)
    {
        DisplayOn_ = false;
        turnOnDisplay(DisplayOn_); //turns off display
    }
    else
    {
        DisplayOn_ = true;
        turnOnDisplay(DisplayOn_); //turns on display
    }
     //Signaling soundworker with turning on music
     emit toggleMusic(DisplayOn_);

}

void GPIOWorker::interruptInit(void)
{
    setenv("WIRINGPI_GPIOMEM", "1", 1); //makes sure that is 1 at GPIOMEN
    wiringPiSetup();  //Calls wiriringpiSetup
     //Set pin 17 to trigger at rising edge, and to call InterruptCamera
    wiringPiISR(0, INT_EDGE_RISING,&InterruptCamera);
     //Set pin 18 to trigger at rising edge, and to call InterruptCamera
    wiringPiISR(1, INT_EDGE_RISING,&InterruptDisplay);
}

void InterruptCamera(void)
{
   GPIOWorker::GPIOPtr_->myInterruptCamera(); //kalder interrruptCamera

}

void InterruptDisplay(void)
{
    GPIOWorker::GPIOPtr_->myInterruptDisplay(); //kalder interruptDisplay

}



