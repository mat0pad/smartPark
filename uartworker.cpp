#include <uartworker.h>
#include <uart.h>

void UARTWorker::run()
{
   /** DEBUG **/
   //qDebug() << "Hello from UART Thread" << thread()->currentThreadId();
   unsigned char addr; //Addresse pÃ¥ Sensor
   unsigned char  length[2]; //  [0] er Msb 8 bit, [1] LSB 8 BIT

   while(1)
   {

        addr = uart_.recieve(); //Address
        if(  0 < addr && addr < 7) { // hvis addressen ikke er mellem intervallet [1-6],
                                     // tallene [1-7] kan nemlig ikke forekomme i de 2 databit, da der blev right shiftet med 3
            length[0] = uart_.recieve();  //MSb 8bit
            length[1] = uart_.recieve();  //LSB 8bit
            qDebug()  << "addr er: " << addr << "\n";
            qDebug() << "data er: " << (length[0]*32+length[1])/10 << "cm\n";

            rangeDefinerFunc(addr-1,length[0]*32+length[1]);
            addr = 0;
        }

        /** DEBUG **/
        UARTWorker::sleep(2);
        rangeDefinerFunc(0,100);
        UARTWorker::sleep(2);
        rangeDefinerFunc(1,50);
        UARTWorker::sleep(2);
        rangeDefinerFunc(2,200);
        UARTWorker::sleep(2);
        rangeDefinerFunc(3,5000);
        UARTWorker::sleep(2);
        rangeDefinerFunc(4,50);
        emit onSoundPlay(2);
   }
}

void UARTWorker::rangeDefinerFunc(unsigned char SensorNumber, unsigned int rangeInput)
{
    //Bestemmer hvilket niveau input er på
    if (rangeInput < 200) {
        if (3 != SensorNivaue_[SensorNumber]) {
            SensorNivaue_[SensorNumber] = 3;
            emit progressChanged(SensorNumber+1,3);
        }
    }
    else if (rangeInput >= 200 && rangeInput < 600) {
        if (2 != SensorNivaue_[SensorNumber]) {
            SensorNivaue_[SensorNumber] = 2;
            emit progressChanged(SensorNumber+1,2);
        }
    }
    else if (rangeInput >= 600 && rangeInput < 1500) {
        if (1 != SensorNivaue_[SensorNumber]) {
            SensorNivaue_[SensorNumber] = 1;
            emit progressChanged(SensorNumber+1,1);
        }
    }
    else {
        if (0 != SensorNivaue_[SensorNumber]) {
            SensorNivaue_[SensorNumber] = 0;
            emit progressChanged(SensorNumber+1,0);
        }
        return false;
    }
} //Funktion stop
