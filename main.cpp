#include "mainwindow.h"
#include <QApplication>
#include <uartworker.h>
#include <QDebug>
#include <gpioworker.h>

int main(int argc, char *argv[])
{
    // Create GUI Thread
    QApplication app(argc, argv);
    qDebug() << "Hello from GUI thread" << app.thread()->currentThreadId();

    // Setup UI
    MainWindow w;

    w.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    w.showFullScreen();

    // All images is invisible
    w.setAllImages2Zero();

    /** SPI THREAD SETUP START **/
    // Create SPI Thread
    UARTWorker uartWorker;

    // Setup connection between SPI thread & GUI thread
    QObject::connect(&uartWorker,
                     SIGNAL(progressChanged(unsigned char, unsigned char)), &w,
                     SLOT(onSensorChanged(unsigned char,unsigned char)), Qt::QueuedConnection);

    // Setup callback for cleanup when it finishes
    QObject::connect(&uartWorker, SIGNAL(finished()), &w, SLOT(deleteLater()));

    // Start -> calls run()
    uartWorker.start();

    /** SPI THREAD SETUP END **/

    /** GPIO THREAD SETUP START **/
    // Create GPIO Thread
    GPIOWorker gpioWorker;

    // Setup connection between GPIO thread & GUI thread
    QObject::connect(&gpioWorker,
                     SIGNAL(turnOnSection(bool)), &w,
                     SLOT(onSectionChanged(bool)), Qt::QueuedConnection);

    // Setup callback for cleanup when it finishes
    QObject::connect(&gpioWorker, SIGNAL(finished()), &w, SLOT(deleteLater()));

    // Start -> calls run()
    gpioWorker.start();

    /** GPIO THREAD SETUP END **/

    app.exec();

    uartWorker.wait();
    gpioWorker.wait();

    return 0;
}