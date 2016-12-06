#include <uartworker.h>
#include <uart.h>

#define UPPER_LIMIT_NIVAUE_1 200
#define UPPER_LIMIT_NIVAUE_2 600
#define UPPER_LIMIT_NIVAUE_3 1500

void UARTWorker::run()
{
   /** DEBUG **/
   //qDebug() << "Hello from UART Thread" << thread()->currentThreadId();
   uart_.UartInit();
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
            addr-=1;
            rangeDefinerFunc(addr,length[0]*32+length[1]);
            soundFunc();
            addr = 0;
        }
       /** DEBUG **/
       // UARTWorker::sleep(2);
       //emit onSoundPlay(2);
   }
}

void UARTWorker::rangeDefinerFunc(unsigned char SensorNumber, unsigned int rangeInput)
{
    //Bestemmer hvilket niveau input er på
    if (rangeInput < UPPER_LIMIT_NIVAUE_1) {
        if (3 != sensorNivaue_[SensorNumber]) {
            sensorNivaue_[SensorNumber] = 3;
            emit progressChanged(SensorNumber+1,3);
        }
    }
    else if (rangeInput >= UPPER_LIMIT_NIVAUE_1 && rangeInput < UPPER_LIMIT_NIVAUE_2) {
        if (2 != sensorNivaue_[SensorNumber]) {
            sensorNivaue_[SensorNumber] = 2;
            emit progressChanged(SensorNumber+1,2);
        }
    }
    else if (rangeInput >= UPPER_LIMIT_NIVAUE_2 && rangeInput < UPPER_LIMIT_NIVAUE_3) {
        if (1 != sensorNivaue_[SensorNumber]) {
            sensorNivaue_[SensorNumber] = 1;
            emit progressChanged(SensorNumber+1,1);
        }
    }
    else {
        if (0 != sensorNivaue_[SensorNumber]) {
            sensorNivaue_[SensorNumber] = 0;
            emit progressChanged(SensorNumber+1,0);
        }
    }
} //Funktion stop

void UARTWorker::soundFunc(void)
{
    unsigned char temp = 0;
     for(unsigned char i = 0;i<NUM_OF_SENSORS;++i){
         if(currentSoundNivaue_ < sensorNivaue_[i]){
             currentSoundNivaue_ = sensorNivaue_[i];
             emit onSoundPlay(currentSoundNivaue_);
             qDebug() << "Sound increasing value to " << currentSoundNivaue_ << endl;
             return;
         }
         else if(temp < sensorNivaue_[i]){
             temp = sensorNivaue_[i];
         }

     }
     if(temp < currentSoundNivaue_){
         currentSoundNivaue_ = temp;
         emit onSoundPlay(currentSoundNivaue_);
         qDebug() << "Sound decreasing value to " << currentSoundNivaue_ << endl;
     }
     else{
         qDebug() << "Nothing changed.." << endl;
     }

}


unsigned char UARTWorker::getNiveau(char SensorNumber)
{
    return sensorNivaue_[SensorNumber];
}

