#ifndef SYSFSGPIO_H
#define SYSFSGPIO_H

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



class sysfsgpio
{
public:

    int GPIOExport(int pin);
    int GPIOUnexport(int pin);
    int GPIODirection(int pin,int dir);
    int GPIOWrite(int pin,int value);


};

#endif // SYSFSGPIO_H
