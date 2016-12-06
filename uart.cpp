#include "uart.h"


char Uart::UartInit()
{
    int fd;
    if ((fd = serialOpen("/dev/ttyAMA0", baudRate_)) < 0)
    {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        return -1;
    }
    fd_ = fd;
    return 1;
}


Uart::Uart(unsigned int baudrate)
{
    // Mangler checks for om baudrate findes
    baudRate_ = baudrate;
    if (UartInit() < 0) {
      qDebug() << "Uartinit called\n";
    }
}

unsigned int Uart::recieve()
{
    return serialGetchar(fd_);
}

Uart::~Uart()
{
    serialClose(fd_);
}


