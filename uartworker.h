#ifndef UARTWORKER
#define UARTWORKER
#include <QThread>
#include <QDebug>


class UARTWorker : public QThread
{
    Q_OBJECT

signals:
    void progressChanged(unsigned char imageSelect, unsigned char image);
    void onSoundPlay(unsigned char Nivaue);

private:
    void run();

};

#endif // UARTWORKER

