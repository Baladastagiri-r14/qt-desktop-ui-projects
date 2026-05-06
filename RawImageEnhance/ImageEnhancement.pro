#-------------------------------------------------
#
# Project created by QtCreator 2023-03-02T14:37:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ImageEnhancement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h

FORMS    += mainwindow.ui

INCLUDEPATH += "D:\\TKs\\LibsForGRAY\\Opencv\\include"
LIBS        += -L"D:\\TKs\\LibsForGRAY\\Opencv\\x64\\vc12\\lib" \
            -lopencv_world300\
            -lopencv_ts300
