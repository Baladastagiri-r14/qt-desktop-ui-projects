#-------------------------------------------------
#
# Project created by QtCreator 2020-01-16T10:22:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartContour
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customscene.cpp

HEADERS  += mainwindow.h \
    customscene.h

FORMS    += mainwindow.ui



LIBS += -lAdvapi32

LIBS += "Rpcrt4.lib"
LIBS += "WS2_32.lib"

