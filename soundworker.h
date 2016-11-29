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

public slots:
    void playSound(unsigned int range);
};

#endif // SOUNDWORKER_H
