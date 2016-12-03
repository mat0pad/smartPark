#ifndef UARTWORKER
#define UARTWORKER
#include <QThread>
#include "Uart.h"
#include "rangedefiner.h"
#include <QDebug>


class UARTWorker : public QThread
{
    Q_OBJECT
public:
    UARTWorker(unsigned int baudrate=115200):uart_(baudrate){}
signals:
    void progressChanged(unsigned char imageSelect, unsigned char image);
    void onSoundPlay(unsigned char Nivaue);

private:
    void run();
    bool rangeDefinerFunc(unsigned char SensorNumber, unsigned int rangeInput);

    UART uart_;

    unsigned char SensorNivaue_[6] = {0};


};

#endif // UARTWORKER

