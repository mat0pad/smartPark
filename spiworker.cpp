#include <spiworker.h>

void SPIWorker::run()
{
   qDebug() << "Hello from SPIWorker" << thread()->currentThreadId();

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
