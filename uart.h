#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>


//Klassen for Uart, der er ikke blevet implementeret send() funktion
// Da dette ikke er nÃ¸dvendigt uart er kun sat op til at modtage.
class Uart
{
    Q_OBJECT

public:
    Uart(unsigned int baudrate = 115200); //construct kalder uartInit
    ~Uart();  // destructor
    unsigned int recieve(); //Modtager en char
    void flush(); //fjerner alt data modtaget.

    int fd_;
private:
    char UartInit(); // Init Uart pÃ¥ RPI, gjort private sÃ¥ den ikke kan kaldes udefra
    unsigned baudRate_;

};

#endif // UART_H

