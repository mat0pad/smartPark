#ifndef SOUNDWORKER_H
#define SOUNDWORKER_H
#include <QThread>
#include <QDebug>
#include "sysfsgpio.h"

class SoundWorker : public QThread
{
    Q_OBJECT

public:
    SoundWorker();
    void run();
    void setNivaue(unsigned char Nivaue);
    void setMusicOn(bool);
    void play();
private:
    unsigned char Nivaue_;
    bool MusicOn_;
    sysfsgpio sysgpio_;

public slots:
    void currentNivaue(unsigned char Nivaue);
    void turnOnOff(bool);
};

#endif // SOUNDWORKER_H
