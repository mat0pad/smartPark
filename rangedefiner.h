#ifndef RANGEDEFINER_H
#define RANGEDEFINER_H
#include <stdio.h>


// Nivaue 3 er mellem 0-20, Nivaue 2 er mellem 20-60,Nivaue 3 er mellem 60-150 cm
class rangeDefiner
{

public:
    bool rangeDefinerFunc(unsigned char SensorNumber, unsigned int rangeInput) {

        //Bestemmer hvilket niveau input er på
        if (rangeInput < 200) {
            if (3 != SensorNivaue_[SensorNumber]) {
                SensorNivaue_[SensorNumber] = 3;
                return true;
            }
            return false;
        }
        else if (rangeInput >= 200 && rangeInput < 600) {
            if (2 != SensorNivaue_[SensorNumber]) {
                SensorNivaue_[SensorNumber] = 2;
                return true;
            }
            return false;
        }
        else if (rangeInput >= 600 && rangeInput < 1500) {
            if (1 != SensorNivaue_[SensorNumber]) {
                SensorNivaue_[SensorNumber] = 1;
                return true;
            }
            return false;
        }
        else {
            if (0 != SensorNivaue_[SensorNumber]) {
                SensorNivaue_[SensorNumber] = 0;
                return true;
            }
            return false;
        }
    } //Funktion stop

    unsigned char getNiveaue(char SensorNumber)
    {
        return SensorNivaue_[SensorNumber];
    }

private:
    unsigned char SensorNivaue_[6] = {0};
};

#endif // RANGEDEFINER_H
