#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T15:47:39
#
#-------------------------------------------------

INCLUDEPATH += /usr/include/QtMultimediaKit
INCLUDEPATH += /usr/include/QtMobility

QT       += core gui

CONFIG += mobility
MOBILITY = multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
