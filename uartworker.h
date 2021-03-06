#ifndef UARTWORKER
#define UARTWORKER
#include <QThread>
#include "uart.h"
#include <QDebug>
#define NUM_OF_SENSORS 7


class UARTWorker : public QThread
{
    Q_OBJECT
public:
    UARTWorker(unsigned int baudrate=9600):uart_(baudrate)
    {
        for(unsigned char i=0;i<NUM_OF_SENSORS;++i)
            sensorNivaue_[i]=0;
        currentSoundNivaue_ = 0;
    }

    unsigned char getNiveau(unsigned char SensorNumber);

signals:
    void progressChanged(unsigned char imageSelect, unsigned char image);
    void onSoundPlay(unsigned char Nivaue);

private:
    void run();
    void rangeDefinerFunc(unsigned char SensorNumber, unsigned int rangeInput);
    void soundFunc(void);


    Uart uart_;
    unsigned char sensorNivaue_[NUM_OF_SENSORS];
    unsigned char currentSoundNivaue_;
};

#endif // UARTWORKER

