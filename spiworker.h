#ifndef SPIWORKER
#define SPIWORKER
#include <QThread>
#include <QDebug>

class SPIWorker : public QThread
{
    Q_OBJECT

signals:
    void progressChanged(unsigned char imageSelect, unsigned char image);

private:
    void run();

};

#endif // SPIWORKER

