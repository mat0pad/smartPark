#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startCamera();
    void setImage(unsigned char imageSelect, unsigned char image = 0);
    void setAllImages2Zero();

private:
    Ui::MainWindow *ui;

// Define slot:
public slots:
        void onSensorChanged(unsigned char imageSelect, unsigned char image);
        void onSectionChanged(bool shouldTurnOn);
};

#endif // MAINWINDOW_H
