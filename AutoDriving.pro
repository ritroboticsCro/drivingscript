#-------------------------------------------------
#
# Project created by QtCreator 2018-09-25T15:55:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoDriving
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    roscoreinit.cpp \
    rosnodeinit.cpp \
    killall.cpp \
    JHPWMPCA9685.cpp \
    jetsonGPIO.cpp

HEADERS  += mainwindow.h \
    roscoreinit.h \
    rosnodeinit.h \
    killall.h \
    hcsr04.h \
    JHPWMPCA9685.h \
    jetsonGPIO.h

FORMS    += mainwindow.ui

CONFIG += c++11
