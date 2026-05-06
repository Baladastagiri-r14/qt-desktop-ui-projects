#-------------------------------------------------
#
# Project created by QtCreator 2023-03-21T14:06:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Histogram
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp

HEADERS += mainwindow.h \
        qcustomplot.h

FORMS   += mainwindow.ui
