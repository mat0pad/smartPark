#-------------------------------------------------
#
# Project created by QtCreator 2016-11-08T12:25:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smartPark
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spiworker.cpp \
    gpioworker.cpp

HEADERS  += mainwindow.h \
    spiworker.h \
    gpioworker.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

DISTFILES +=
