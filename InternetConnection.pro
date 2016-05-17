#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T16:10:20
#
#-------------------------------------------------

QT       += core gui network dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InternetConnection
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutnetwork.cpp \
    nmdbus.cpp

HEADERS  += mainwindow.h \
    aboutnetwork.h \
    nmdbus.h

FORMS    += mainwindow.ui
