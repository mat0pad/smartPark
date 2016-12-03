#include "mainwindow.h"
#include "unistd.h"
#include <QtMultimediaKit/QMediaPlayer>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/stud/Desktop/QtSound/temp1.wav"));
    player->setVolume(50);
    for(;;)
    {
    player->play();
    sleep(1);
    player->stop();
    sleep(1);
    }

    return a.exec();
}
