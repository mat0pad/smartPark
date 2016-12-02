#include "soundworker.h"

SoundWorker::SoundWorker()
{
    Nivaue_=0;
    MusicOn_=true;
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
            QDebug() << "Playing sound with nivaue" << Nivaue_ << "\n";
            sleep(Nivaue_);
            Qdebug() << "Stopping sound\n";

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

void SoundWorker::playSound(unsigned char Nivaue)
{
    /** DEBUG **/
    setNivaue(Nivaue);
    qDebug() << "You called me and I answer! Range is: " << Nivaue;
}

void SoundWorker::turnOnOff()
{
    setMusicOn(!MusicOn_);
}


