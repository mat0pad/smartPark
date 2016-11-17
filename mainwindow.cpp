#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <uartworker.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startCamera()
{

}


void MainWindow::setImage(unsigned char imageSelect, unsigned char image)
{
    QString prefix = ":/new/images/";

    switch (imageSelect)
    {
        case 1:
        {
            prefix += (image == 0 ? "side-empty.png": (image == 1 ? "1-front_l.png" : (image == 2 ? "2-front_l.png" : "3-front_l.png")));
            QPixmap mypix(prefix);
            ui->front_l->setPixmap(mypix);
            break;
        }
        case 2:
        {
            prefix += (image == 0 ? "empty.png": (image == 1 ? "1-up.png" : (image == 2 ? "2-up.png" : "3-up.png")));
            QPixmap mypix(prefix);
            ui->front_m->setPixmap(mypix);
            break;
        }
        case 3:
        {
            prefix += (image == 0 ? "side-empty.png": (image == 1 ? "1-front_r.png" : (image == 2 ? "2-front_r.png" : "3-front_r.png")));
            QPixmap mypix(prefix);
            ui->front_r->setPixmap(mypix);
            break;
        }
        case 4:
        {
            prefix += (image == 0 ? "side-empty.png": (image == 1 ? "1-bottom_r.png" : (image == 2 ? "2-bottom_r.png" : "3-bottom_r.png")));
            QPixmap mypix(prefix);
            ui->bottom_r->setPixmap(mypix);
            break;
        }
        case 5:
        {
        prefix += (image == 0 ? "empty.png": (image == 1 ? "1-down.png" : (image == 2 ? "2-down.png" : "3-down.png")));
            QPixmap mypix(prefix);
            ui->bottom_m->setPixmap(mypix);
            break;
        }
        case 6:
        {
            prefix += (image == 0 ? "side-empty.png": (image == 1 ? "1-bottom_l.png" : (image == 2 ? "2-bottom_l.png" : "3-bottom_l.png")));
            QPixmap mypix(prefix);
            ui->bottom_l->setPixmap(mypix);
            break;
        }

        default: break;
    }
}

void MainWindow::onSensorChanged(unsigned char imageSelect, unsigned char image)
{
        // Processing code
        qDebug() << "GUI Thread: Changing sensor data";

        setImage(imageSelect,image);
}


void MainWindow::onSectionChanged(bool shouldTurnOn)
{
    // Processing code
    qDebug() << "GUI Thread: Changing section visiblity";
    if(shouldTurnOn)
    {
        qDebug() << "Section visible";
    }
    else
    {
        qDebug() << "Section invisible";
    }
}

void MainWindow::setAllImages2Zero()
{
    setImage(1,0);
    setImage(2,0);
    setImage(3,0);
    setImage(4,0);
    setImage(5,0);
    setImage(6,0);
}

