#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <uartworker.h>
#include <QDebug>
#include <gpioworker.h>
#include <soundworker.h>

int main(int argc, char *argv[])
{
    // Create GUI Thread
    QApplication app(argc, argv);

    /** DEBUG **/
    //qDebug() << "Hello from GUI thread" << app.thread()->currentThreadId();

    // Setup UI
    MainWindow w;

    w.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    w.showFullScreen();

    // All senosr images invisible at start
    w.setAllImages2Zero();

    // Enable camera
    QProcess::execute("sudo modprobe bcm2835-v4l2");

    /** UART THREAD SETUP START **/
    // Create UART Thread
    UARTWorker uartWorker;

    // Setup connection between UART thread & GUI thread
    QObject::connect(&uartWorker,
                     SIGNAL(progressChanged(unsigned char, unsigned char)), &w,
                     SLOT(onSensorChanged(unsigned char,unsigned char)), Qt::QueuedConnection);

    // Setup callback for cleanup when it finishes
    QObject::connect(&uartWorker, SIGNAL(finished()), &w, SLOT(deleteLater()));

    // Start -> calls run()
    uartWorker.start();
    /** UART THREAD SETUP END **/

    /** GPIO THREAD SETUP START **/
    // Create GPIO Thread
    GPIOWorker gpioWorker;

    // Start -> calls run()
    gpioWorker.start();
    /** GPIO THREAD SETUP END **/


    /** SOUND THREAD SETUP START **/
    // Create SOUND Thread
    SoundWorker soundworker;

    // Setup connection between UART thread & SOUND thread
    QObject::connect(&uartWorker,
                     SIGNAL(onSoundPlay(unsigned char)), &soundworker,
                     SLOT(currentNivaue(unsigned char)), Qt::QueuedConnection);



    // Setup callback for cleanup when it finishes
    QObject::connect(&uartWorker, SIGNAL(finished()), &soundworker, SLOT(deleteLater()));

    //Setup connection between GPIO thread & SOUND thread
    QObject::connect(&gpioWorker,
                     SIGNAL(toggleMusic(bool)), &soundworker,
                     SLOT(turnOnOff(bool)), Qt::QueuedConnection);

    QObject::connect(&gpioWorker, SIGNAL(finished()), &soundworker, SLOT(deleteLater()));
    // Start -> calls run()
    soundworker.start();
    /** SOUND THREAD SETUP END **/

    app.exec();

    soundworker.wait();
    uartWorker.wait();
    gpioWorker.wait();

    return 0;
}
