#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <sleeper.h>
#include <spiworker.h>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    // All imges is invisible
    w.setAllImages2Zero();

    qDebug() << "Hello from GUI thread" << app.thread()->currentThreadId();

    SPIWorker worker;

    // QObject::connect(&clockThread, SIGNAL(sendTime(QString)), label, SLOT(setText(QString)), Qt::QueuedConnection);

    //QObject::connect()

    QObject::connect(&worker,
                     SIGNAL(progressChanged(unsigned char, unsigned char)), &w,
                     SLOT(onProgressChanged(unsigned char,unsigned char)), Qt::QueuedConnection);

    // Setup callback for cleanup when it finishes
   // QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    worker.start();


    app.exec();

    worker.wait();

    return 0;
}
