#include <uartworker.h>

void UARTWorker::run()
{
   qDebug() << "Hello from SPI Thread" << thread()->currentThreadId();

   while(1)
   {
        QThread::sleep(1);

        emit progressChanged(1, 1);

        QThread::sleep(1);

        emit progressChanged(1, 2);

        QThread::sleep(1);

        emit progressChanged(1, 3);

        QThread::sleep(1);

        emit progressChanged(1, 2);

        QThread::sleep(1);

        emit progressChanged(1, 1);

        QThread::sleep(1);

        emit progressChanged(1, 0);
   }
}
