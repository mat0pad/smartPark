#include <uartworker.h>
#include <uart.h>
#include <rangedefiner.h>

void UARTWorker::run()
{
   /** DEBUG **/
   //qDebug() << "Hello from UART Thread" << thread()->currentThreadId();

   Uart u(115200);
   rangeDefiner RD;
   unsigned char addr; //Addresse pÃ¥ Sensor
   unsigned char  length[2]; //  [0] er Msb 8 bit, [1] LSB 8 BIT

   while(1)
   {

        addr = u.recieve(); //Address
        if(  0 < addr && addr < 7) { // hvis addressen ikke er mellem intervallet [1-6],
                                     // tallene [1-7] kan nemlig ikke forekomme i de 2 databit, da der blev right shiftet med 3
            length[0] = u.recieve();  //MSb 8bit
            length[1] = u.recieve();  //LSB 8bit
            qDebug()  << "addr er: " << addr << "\n";
            qDebug() << "data er: " << (length[0]*32+length[1])/10 << "cm\n";

            if(RD.rangeDefinerFunc(addr,length[0]*32+length[1]))
            {
                emit progressChanged(addr,RD.getNiveaue(addr));
            }
            addr = 0;
        }

        /** DEBUG **/
        UARTWorker::sleep(2);
        emit onSoundPlay(2);
   }
}


