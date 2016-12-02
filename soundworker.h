#ifndef SOUNDWORKER_H
#define SOUNDWORKER_H
#include <QThread>
#include <QDebug>

class SoundWorker : public QThread
{
    Q_OBJECT

public:
    SoundWorker();
    void run();
    void setNivaue(unsigned char Nivaue);
    void setMusicOn(bool);
private:
    unsigned char Nivaue_;
    bool MusicOn_;


public slots:
    void playSound(unsigned char Nivaue);
    void turnOnOff(bool);
};

#endif // SOUNDWORKER_H
