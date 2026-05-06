/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *pushButton_LoadImage;
    QPushButton *pushButton_FreeHand;
    QPushButton *pushButton_2;
    QPushButton *pushButton_BrushTool;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1169, 910);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(129, 129, 129);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(50, 20, 821, 821));
        graphicsView->setStyleSheet(QStringLiteral("background-color: rgb(88, 88, 88);"));
        pushButton_LoadImage = new QPushButton(centralWidget);
        pushButton_LoadImage->setObjectName(QStringLiteral("pushButton_LoadImage"));
        pushButton_LoadImage->setGeometry(QRect(1014, 90, 61, 61));
        pushButton_FreeHand = new QPushButton(centralWidget);
        pushButton_FreeHand->setObjectName(QStringLiteral("pushButton_FreeHand"));
        pushButton_FreeHand->setGeometry(QRect(940, 180, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(940, 290, 75, 23));
        pushButton_BrushTool = new QPushButton(centralWidget);
        pushButton_BrushTool->setObjectName(QStringLiteral("pushButton_BrushTool"));
        pushButton_BrushTool->setGeometry(QRect(940, 240, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1169, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_LoadImage->setText(QApplication::translate("MainWindow", "Load", 0));
        pushButton_FreeHand->setText(QApplication::translate("MainWindow", "FreeHand", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Eraser", 0));
        pushButton_BrushTool->setText(QApplication::translate("MainWindow", "Brush", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
