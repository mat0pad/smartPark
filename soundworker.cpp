#include "soundworker.h"

// Delays for each Nivaue, the delay is in ms
#define NIVAUE_1_DELAY 600
#define NIVAUE_2_DELAY 400
#define NIVAUE_3_DELAY 200


#define HIGH 1
#define LOW 0

#define OUT 1
/*
 *  Constructor for Soundworker, sets start Nivaue to 0 and Music is true,
 *  Set pin to sysfsgpio and set the pin to output
 */

SoundWorker::SoundWorker(int pin):sysgpio_(pin)
{

    setNivaue(0);
    setMusicOn(true);
    sysgpio_.GPIODirection(OUT);
}

/*
 *  Main function for Soundworker thread, keeps running and calling play as long
 * MusicOn_ is true which only can be changed from a signal by GPIOWorker
 */

void SoundWorker::run()
{
    /** DEBUG **/
    //qDebug() << "Hello from SOUND Thread" << thread()->currentThreadId();

    while(1)
    {
        if(MusicOn_)
        {
            play();
        }
    }

}

/*
 * Play function check stage Nivaue and set Writes to SoundPIN apporiate
 * to what Nivaue  is, if the Nivaue is 0 it goes low and
 */

void SoundWorker::play()
{
    switch(Nivaue_){
    case 0:
        // Nivuae = 0, no sound
        sysgpio_.GPIOWrite(LOW);
        setNivaue(4); // Sends to case 4 so we dont try to write low when it already is low.
        break;
    case 1:
        //Nivaue = 1, sound with highest delay
        //qDebug() << "Playing sound with nivaue" << Nivaue_ << "\n";
        sysgpio_.GPIOWrite(HIGH);
        msleep(NIVAUE_1_DELAY);
        sysgpio_.GPIOWrite(LOW);
        msleep(NIVAUE_1_DELAY);
        break;
    case 2:
        //Nivaue = 2, Sound with medicore delay
        //qDebug() << "Playing sound with nivaue" << Nivaue_ << "\n";
        sysgpio_.GPIOWrite(HIGH);
        msleep(NIVAUE_2_DELAY);
        sysgpio_.GPIOWrite(LOW);
        msleep(NIVAUE_2_DELAY);
        break;
    case 3:
        //Nivaue 3, sound with small delay
        //qDebug() << "Playing sound with nivaue" << Nivaue_ << "\n";
        sysgpio_.GPIOWrite(HIGH);
        msleep(NIVAUE_3_DELAY);
        sysgpio_.GPIOWrite(LOW);
        msleep(NIVAUE_3_DELAY);
        break;
    case 4:
        break;
    }

}
/*
 * Set Nivaue take Nivaue as parameter and checks if it is valid value
 */

void SoundWorker::setNivaue( unsigned char Nivaue)
{
    if(Nivaue < 5)
        Nivaue_=Nivaue;

}
/*
 * Set MusicOn, set bool as value no need for any checks
 */

void SoundWorker::setMusicOn(bool MusicOn)
{
    MusicOn_=MusicOn;
}

/*
 * Slots method for recieving signal from Uartworker,
 * recieve Nivaue and calls setNivaue method
 */
void SoundWorker::currentNivaue(unsigned char Nivaue)
{
    setNivaue(Nivaue);
    /** DEBUG **/
    //qDebug() << "You called me and I answer! Range is: " << Nivaue;
}

/*
 * SLots method for recieving signal from GPioWorker,
 * recieve MusicOn and calls setMusicOn method
 */
void SoundWorker::turnOnOff(bool MusicOn)
{
    setMusicOn(MusicOn);
    /** DEBUG **/
    //qDebug() << "Called from GPIO\n";
}


