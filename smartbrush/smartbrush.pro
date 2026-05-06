#-------------------------------------------------
#
# Project created by QtCreator 2023-05-19T15:36:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smartbrush
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    smart.cpp

HEADERS  += mainwindow.h \
    smart.h \
    contours.h

FORMS    += mainwindow.ui
