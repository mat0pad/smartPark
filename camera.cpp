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
    QString script = "raspivid -p '" + posX_ + "," + posY_ + "," + width_+ "," + height_ + "' -t 0";
    QProcess::execute(script);

    qDebug() << "I'm still alive it must have been a miracle!";
}

