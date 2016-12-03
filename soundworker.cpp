#include "soundworker.h"

#define NIVAUE_1_DELAY 600
#define NIVAUE_2_DELAY 400
#define NIVAUE_3_DELAY 200

#define SoundPin 18

#define HIGH 1
#define LOW 0

SoundWorker::SoundWorker():sysgpio_()
{
    setNivaue(0);
    setMusicOn(true);
    sysgpio_.GPIOExport(SoundPin);
    sysgpio_.GPIODirection(SoundPin,1);
}

void SoundWorker::run()
{
    /** DEBUG **/
    qDebug() << "Hello from SOUND Thread" << thread()->currentThreadId();

    while(1)
    {
        if(MusicOn_)
        {
            play();
        }
    }

}

void SoundWorker::play()
{
    switch(Nivaue_){
    case 0:
        sysgpio_.GPIOWrite(SoundPin,LOW);
        break;
    case 1:
        qDebug() << "Playing sound with nivaue" << Nivaue_ << "\n";
        sysgpio_.GPIOWrite(SoundPin,HIGH);
        sleep(NIVAUE_1_DELAY);
        sysgpio_.GPIOWrite(SoundPin,LOW);
        sleep(NIVAUE_1_DELAY);
        break;
    case 2:
        qDebug() << "Playing sound with nivaue" << Nivaue_ << "\n";
        sysgpio_.GPIOWrite(SoundPin,HIGH);
        sleep(NIVAUE_2_DELAY);
        sysgpio_.GPIOWrite(SoundPin,LOW);
        sleep(NIVAUE_2_DELAY);
        break;
    case 3:
        qDebug() << "Playing sound with nivaue" << Nivaue_ << "\n";
        sysgpio_.GPIOWrite(SoundPin,HIGH);
        sleep(NIVAUE_3_DELAY);
        sysgpio_.GPIOWrite(SoundPin,LOW);
        sleep(NIVAUE_3_DELAY);
        break;
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


