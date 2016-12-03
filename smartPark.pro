#-------------------------------------------------
#
# Project created by QtCreator 2016-11-08T12:25:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smartPark
TEMPLATE = app
LIBS += -L/usr/local/lib -lwiringPi
INCLUDEPATH    += /usr/local/include

SOURCES += main.cpp\
        mainwindow.cpp \
    gpioworker.cpp \
    uartworker.cpp \
    camera.cpp \
    uart.cpp \
    soundworker.cpp \
    sysfsgpio.cpp

HEADERS  += mainwindow.h \
    gpioworker.h \
    uartworker.h \
    camera.h \
    rangedefiner.h \
    uart.h \
    soundworker.h \
    sysfsgpio.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

DISTFILES +=
