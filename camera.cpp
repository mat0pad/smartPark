#include "camera.h"

Camera::Camera(QString width, QString height, QString posX, QString posY)
{
    height_ = height;
    width_ = width;
    posX_ = posX;
    posY_ = posY;
}

void Camera::run()
{
    QString script = "raspivid -w " + width_ + " -h " + height_ + " -t 0 -p " + posX_ + "," + posY_ + "," + width_+ "," + height_ + "'";

    qDebug() << script;

    QProcess::execute(script);

    while(1)
    {
        Camera::sleep(1);
        qDebug() << "I'm still alive it must have been a miracle!";
    }
}
