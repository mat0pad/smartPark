#include "sysfsgpio.h"

#define IN 0
#define OUT 1
#define LOW 0

#define BUFFER_MAX 3
#define DIRECTION_MAX 35
#define VALUE_MAX 30



/*
* Constuctor for SysfsGpio, makes sure it is a valid pin
* Makes sure that pin_ is exported to user space.
*/
SysfsGpio::SysfsGpio(int pin)
{
    if(0 < pin)
        pin_=pin;
    else{
        pin_=SoundPIN;
    }
    GPIOExport(); //Makes sure the pin is exported to userspace
    sleep(1); //Delay for at sikker sig at sysfs kan følge med
    GPIODirection(OUT);

}

/*
* Deconstructor makes sure the Pin_ is removed from userspace.
*/
SysfsGpio::~SysfsGpio()
{
    GPIOUnexport(); //Makes sure the pin is reversed to kernel
}


/*
* Export the Gpio pin to userspace,
* So it can be used by the application
* return 0 on succes, -1 on failure
*/
int SysfsGpio::GPIOExport()
{
    char buffer[BUFFER_MAX]; //BUFFER_MAX = 3
    ssize_t bytes_written;
    int fd; // File description

    //Opens gpio Export file, with  only write  permission
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (-1 == fd) { // check if open failed
        fprintf(stderr, "Failed to open export for writing!\n");
        return -1;
    }

    //writes pin_ to bytes written
    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin_);
    //write bytes_written to unexport file.
    write(fd, buffer, bytes_written);    // Writes pin Number to the file
    close(fd); //close file after use
    return 0;
}

/*
* Reverse export the Gpio pin to userspace,
* So it no longer it can be used.
* return 0 on succes, -1 on failure
*/
int SysfsGpio::GPIOUnexport()
{
    char buffer[BUFFER_MAX]; //Buffer = 3
    ssize_t bytes_written;
    int fd;
     //Opens gpio Export file, with  only write  permission
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (-1 == fd) { //check if open failed
        fprintf(stderr, "Failed to open unexport for writing!\n");
        return(-1);
    }
    //writes pin_ to bytes written
    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin_);
    //write bytes_written to unexport file.
    write(fd, buffer, bytes_written);
    close(fd);
    return(0);
}


/*
* Set Pin_ direction with dir parameter, 0=input, 1=output.
* return -1 on error, return 0 on succes
*/
int SysfsGpio::GPIODirection(int dir)
{
    static const char s_directions_str[]  = "in\0out";


    char path[DIRECTION_MAX];
    int fd;

    // writes "/sys/class/gpio/gpio%d/direction" to path, with pin_ replace %d
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin_);
    fd = open(path, O_WRONLY); //Open the file with write permission.
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio direction for writing!\n");
        return(-1);
    }

    if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
        fprintf(stderr, "Failed to set direction!\n");
        return(-1);
    }

    close(fd);
    return(0);
}

/*
* writes to the pin_ if it sat to output, value defines what to write
* 1 = HIGH, 0 = LOW
* return -1 on error, return 0 on succes
*/
int SysfsGpio::GPIOWrite(int value)
{
    static const char s_values_str[] = "01";

    char path[VALUE_MAX];
    int fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin_);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio value for writing!\n");
        return(-1);
    }

    if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
        fprintf(stderr, "Failed to write value!\n");
        return(-1);
    }

    close(fd);
    return(0);
}

/*
 * Returns GPIO Number
 */
int SysfsGpio::getPin() const
{
    return pin_;
}


