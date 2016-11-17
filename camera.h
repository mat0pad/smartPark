#ifndef CAMERA_H
#define CAMERA_H
#include <QThread>
#include <QString>
#include <QProcess>
#include <QDebug>

class Camera : public QThread
{
    Q_OBJECT

public:
    Camera(QString width = "437", QString height = "582", QString posX = "0", QString posY_ = "49");

private:
    void run();
    QString height_;
    QString width_;
    QString posX_;
    QString posY_;

signals:

public slots:
};

#endif // CAMERA_H
