
#ifndef UART_H
#define UART_H

#pragma once

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>


//Klassen for Uart, der er ikke blevet implementeret send() funktion
// Da dette ikke er nÃ¸dvendigt uart er kun sat op til at modtage.
class Uart
{
public:
    Uart(unsigned int baudrate = 115200); //construct kalder uartInit
    ~Uart();  // destructor
    void run();  //Run metode
    unsigned int recieve(); //Modtager en char
    void flush(); //fjerner alt data modtaget.
    char UartInit(); // Init Uart pÃ¥ RPI, gjort private sÃ¥ den ikke kan kaldes udefra
    int fd_;
private:
    
    unsigned baudRate_;

};

#endif // UART_H

