#include "soundworker.h"

SoundWorker::SoundWorker()
{
}

void SoundWorker::run()
{
    /** DEBUG **/
    qDebug() << "Hello from SOUND Thread" << thread()->currentThreadId();

    while(1)
    {}
}

void playSound(unsigned int range)
{
    /** DEBUG **/
    qDebug() << "You called me and I answer! Range is: " << range << thread()->currentThreadId();
}
