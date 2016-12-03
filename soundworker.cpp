#include "soundworker.h"

SoundWorker::SoundWorker()
{
    setNivaue(0);
    setMusicOn(true);
}

void SoundWorker::run()
{
    /** DEBUG **/
    qDebug() << "Hello from SOUND Thread" << thread()->currentThreadId();

    while(1)
    {
        if(Nivaue_ > 0 && MusicOn_)
        {
            sleep(Nivaue_);
            qDebug() << "Playing sound with nivaue" << Nivaue_ << "\n";
            sleep(Nivaue_);
            qDebug() << "Stopping sound\n";

        }

    }

}

void SoundWorker::setNivaue(unsigned char Nivaue)
{
    if(Nivaue < 4)
        Nivaue_=Nivaue;

}

void SoundWorker::setMusicOn(bool MusicOn)
{
    MusicOn_=MusicOn;
}

void SoundWorker::currentNivaue(unsigned char Nivaue)
{
    /** DEBUG **/
    setNivaue(Nivaue);
    qDebug() << "You called me and I answer! Range is: " << Nivaue;
}

void SoundWorker::turnOnOff(bool MusicOn)
{
    qDebug() << "Called from GPIO\n";
    setMusicOn(MusicOn);
}


