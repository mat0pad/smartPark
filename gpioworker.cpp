#include "gpioworker.h"

void GPIOWorker::run()
{
    qDebug() << "Hello from GPIO Thread" << thread()->currentThreadId();

    emit turnOnSection(true);

    GPIOWorker::sleep(5);

    emit turnOnSection(false);

    while(1)
    {
            Camera cTest;

            cTest.start();

            GPIOWorker::sleep(15);

            cTest.terminate();

            GPIOWorker::sleep(5);

            turnOnDisplay(true);

            GPIOWorker::sleep(5);

            turnOnDisplay(false);
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


