#ifndef MAINTHREAD
#define MAINTHREAD

#include <QThread>
#include "mainwindow.h"

class MainThread : public QThread
{
    Q_OBJECT

public:
   //explicit MainThread();

protected:
    void run();

private:
   // MainWindow w;

};

/*MainThread::MainThread()
{}*/

void MainThread::run()
{
   /* w.setImage(1,0);
    w.setImage(2,0);
    w.setImage(3,0);
    w.setImage(4,0);
    w.setImage(5,0);
    w.setImage(6,0);

    while(true)
    {
        sleep(4);

        w.setImage(4,1);

        sleep(2);

        w.setImage(4,2);
        w.setImage(5,1);

        sleep(6);

        w.setImage(4,3);
        w.setImage(5,2);

        sleep(4);

        w.setImage(4,2);
        w.setImage(5,1);
    }
*/
}

#endif // MAINTHREAD

