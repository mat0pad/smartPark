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

            GPIOWorker::sleep(30);

            cTest.exit();

            GPIOWorker::sleep(30);
    }
}

void GPIOWorker::turnOnDisplay(bool shouldTurnOn)
{
    // Turn off/on display here'

}


