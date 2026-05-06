#-------------------------------------------------
#
# Project created by QtCreator 2023-05-25T14:41:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ImageMath
TEMPLATE = app

# Add your source files here
SOURCES += main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp

# Add your header files here
HEADERS  += mainwindow.h \
         qcustomplot.h

# Add your UI files here
FORMS    += mainwindow.ui

# Include path for OpenCV headers
INCLUDEPATH += "D:\\TKs\\LibsForGRAY\\Opencv\\include"

# Link against OpenCV libraries
LIBS        += -L"D:\\TKs\\LibsForGRAY\\Opencv\\x64\\vc12\\lib" \
               -lopencv_world300 \
               -lopencv_ts300
