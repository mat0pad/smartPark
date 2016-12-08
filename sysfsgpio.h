#ifndef SYSFSGPIO_H
#define SYSFSGPIO_H

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SoundPIN 2


class SysfsGpio
{
public:
    SysfsGpio(int pin = SoundPIN);
    ~SysfsGpio();
    int GPIOExport();
    int GPIOUnexport();
    int GPIODirection(int dir);
    int GPIOWrite(int value);
    int getPin() const;
private:
    int pin_;
    int file_exist(char *filename);

};

#endif // SYSFSGPIO_H
