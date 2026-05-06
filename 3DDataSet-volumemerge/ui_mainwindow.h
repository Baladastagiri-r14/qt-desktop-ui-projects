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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *loadVolume;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_XShift_in;
    QLabel *label_9;
    QLineEdit *lineEdit_Roll_in;
    QLineEdit *lineEdit_Yaw_in;
    QLineEdit *lineEdit_YShift_in;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *lineEdit_ZShift_in;
    QLabel *label_20;
    QLabel *label_8;
    QLineEdit *lineEdit_Pitch_in;
    QLabel *label_19;
    QLabel *Axial_label;
    QLabel *Sagittal_label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *Volumelayout;
    QLabel *Frontal_label;
    QPushButton *Tranform_ITK;
    QPushButton *Reset;
    QPushButton *generateVolume;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_SavePAth;
    QLabel *label_Status;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *LineEdit_InputPath;
    QPushButton *GPU_Transform3D;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_fanSelection;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1231, 1000);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(85, 85, 63);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        loadVolume = new QPushButton(centralWidget);
        loadVolume->setObjectName(QStringLiteral("loadVolume"));
        loadVolume->setGeometry(QRect(20, 410, 231, 51));
        loadVolume->setStyleSheet(QLatin1String("font: 75 10pt \"MS Shell Dlg 2\";\n"
"\n"
"background-color: rgb(240, 240, 240);"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 0, 231, 281));
        groupBox_2->setStyleSheet(QStringLiteral("color: rgb(255, 170, 0);"));
        lineEdit_XShift_in = new QLineEdit(groupBox_2);
        lineEdit_XShift_in->setObjectName(QStringLiteral("lineEdit_XShift_in"));
        lineEdit_XShift_in->setGeometry(QRect(70, 140, 141, 20));
        lineEdit_XShift_in->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 130, 41, 29));
        label_9->setStyleSheet(QLatin1String("color: rgb(255, 85, 0);\n"
"font: 75 10pt \"MS Shell Dlg 2\";"));
        lineEdit_Roll_in = new QLineEdit(groupBox_2);
        lineEdit_Roll_in->setObjectName(QStringLiteral("lineEdit_Roll_in"));
        lineEdit_Roll_in->setGeometry(QRect(70, 70, 143, 20));
        lineEdit_Roll_in->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lineEdit_Yaw_in = new QLineEdit(groupBox_2);
        lineEdit_Yaw_in->setObjectName(QStringLiteral("lineEdit_Yaw_in"));
        lineEdit_Yaw_in->setGeometry(QRect(70, 110, 143, 20));
        lineEdit_Yaw_in->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lineEdit_YShift_in = new QLineEdit(groupBox_2);
        lineEdit_YShift_in->setObjectName(QStringLiteral("lineEdit_YShift_in"));
        lineEdit_YShift_in->setGeometry(QRect(70, 180, 141, 20));
        lineEdit_YShift_in->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 170, 51, 21));
        label_21->setStyleSheet(QLatin1String("color: rgb(255, 85, 0);\n"
"font: 75 10pt \"MS Shell Dlg 2\";"));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 200, 51, 29));
        label_22->setStyleSheet(QLatin1String("color: rgb(255, 85, 0);\n"
"font: 75 10pt \"MS Shell Dlg 2\";"));
        lineEdit_ZShift_in = new QLineEdit(groupBox_2);
        lineEdit_ZShift_in->setObjectName(QStringLiteral("lineEdit_ZShift_in"));
        lineEdit_ZShift_in->setGeometry(QRect(70, 210, 141, 20));
        lineEdit_ZShift_in->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(20, 110, 33, 16));
        label_20->setStyleSheet(QLatin1String("color: rgb(255, 85, 0);\n"
"font: 75 10pt \"MS Shell Dlg 2\";"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(22, 32, 27, 16));
        label_8->setStyleSheet(QLatin1String("color: rgb(255, 85, 0);\n"
"font: 75 10pt \"MS Shell Dlg 2\";"));
        lineEdit_Pitch_in = new QLineEdit(groupBox_2);
        lineEdit_Pitch_in->setObjectName(QStringLiteral("lineEdit_Pitch_in"));
        lineEdit_Pitch_in->setGeometry(QRect(70, 30, 141, 20));
        lineEdit_Pitch_in->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(16, 69, 31, 20));
        label_19->setStyleSheet(QLatin1String("color: rgb(255, 85, 0);\n"
"font: 75 10pt \"MS Shell Dlg 2\";"));
        label_20->raise();
        label_8->raise();
        lineEdit_Pitch_in->raise();
        label_19->raise();
        lineEdit_XShift_in->raise();
        label_9->raise();
        lineEdit_Roll_in->raise();
        lineEdit_Yaw_in->raise();
        lineEdit_YShift_in->raise();
        label_21->raise();
        label_22->raise();
        lineEdit_ZShift_in->raise();
        Axial_label = new QLabel(centralWidget);
        Axial_label->setObjectName(QStringLiteral("Axial_label"));
        Axial_label->setGeometry(QRect(690, 10, 411, 411));
        Axial_label->setStyleSheet(QStringLiteral("background-color: rgb(127, 127, 95);"));
        Sagittal_label = new QLabel(centralWidget);
        Sagittal_label->setObjectName(QStringLiteral("Sagittal_label"));
        Sagittal_label->setGeometry(QRect(690, 440, 411, 411));
        Sagittal_label->setStyleSheet(QStringLiteral("background-color: rgb(127, 127, 95);"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(260, 10, 411, 411));
        Volumelayout = new QVBoxLayout(verticalLayoutWidget);
        Volumelayout->setSpacing(6);
        Volumelayout->setContentsMargins(11, 11, 11, 11);
        Volumelayout->setObjectName(QStringLiteral("Volumelayout"));
        Volumelayout->setContentsMargins(0, 0, 0, 0);
        Frontal_label = new QLabel(centralWidget);
        Frontal_label->setObjectName(QStringLiteral("Frontal_label"));
        Frontal_label->setGeometry(QRect(260, 440, 411, 411));
        Frontal_label->setStyleSheet(QStringLiteral("background-color: rgb(127, 127, 95);"));
        Tranform_ITK = new QPushButton(centralWidget);
        Tranform_ITK->setObjectName(QStringLiteral("Tranform_ITK"));
        Tranform_ITK->setGeometry(QRect(20, 530, 231, 51));
        Tranform_ITK->setStyleSheet(QLatin1String("font: 75 10pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(240, 240, 240);\n"
""));
        Reset = new QPushButton(centralWidget);
        Reset->setObjectName(QStringLiteral("Reset"));
        Reset->setGeometry(QRect(20, 650, 231, 31));
        Reset->setStyleSheet(QLatin1String("font: 75 10pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(240, 240, 240);\n"
""));
        generateVolume = new QPushButton(centralWidget);
        generateVolume->setObjectName(QStringLiteral("generateVolume"));
        generateVolume->setGeometry(QRect(20, 752, 231, 51));
        generateVolume->setStyleSheet(QLatin1String("font: 75 10pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(240, 240, 240);\n"
""));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(690, 870, 411, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QLatin1String("color: rgb(0, 0, 0);\n"
"background-color: rgb(240, 240, 240);\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"font: 75 8pt \"MS Shell Dlg 2\";"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_SavePAth = new QLineEdit(layoutWidget);
        lineEdit_SavePAth->setObjectName(QStringLiteral("lineEdit_SavePAth"));
        lineEdit_SavePAth->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout_2->addWidget(lineEdit_SavePAth);

        label_Status = new QLabel(centralWidget);
        label_Status->setObjectName(QStringLiteral("label_Status"));
        label_Status->setGeometry(QRect(26, 852, 221, 61));
        label_Status->setStyleSheet(QLatin1String("color: rgb(0, 0, 255);\n"
"font: 18pt \"Times New Roman\";\n"
"background-color: rgb(255, 255, 255);"));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(260, 870, 411, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("color: rgb(0, 0, 0);\n"
"background-color: rgb(240, 240, 240);\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"font: 75 8pt \"MS Shell Dlg 2\";"));

        horizontalLayout->addWidget(label);

        LineEdit_InputPath = new QLineEdit(layoutWidget1);
        LineEdit_InputPath->setObjectName(QStringLiteral("LineEdit_InputPath"));
        LineEdit_InputPath->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(LineEdit_InputPath);

        GPU_Transform3D = new QPushButton(centralWidget);
        GPU_Transform3D->setObjectName(QStringLiteral("GPU_Transform3D"));
        GPU_Transform3D->setGeometry(QRect(20, 340, 231, 51));
        GPU_Transform3D->setStyleSheet(QLatin1String("font: 75 10pt \"MS Shell Dlg 2\";\n"
"\n"
"background-color: rgb(240, 240, 240);"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(260, 900, 411, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QLatin1String("color: rgb(0, 0, 0);\n"
"background-color: rgb(240, 240, 240);\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"font: 75 8pt \"MS Shell Dlg 2\";"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_fanSelection = new QLineEdit(horizontalLayoutWidget);
        lineEdit_fanSelection->setObjectName(QStringLiteral("lineEdit_fanSelection"));

        horizontalLayout_3->addWidget(lineEdit_fanSelection);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        loadVolume->raise();
        groupBox_2->raise();
        Axial_label->raise();
        Sagittal_label->raise();
        verticalLayoutWidget->raise();
        Frontal_label->raise();
        Tranform_ITK->raise();
        Reset->raise();
        generateVolume->raise();
        layoutWidget->raise();
        label_Status->raise();
        GPU_Transform3D->raise();
        horizontalLayoutWidget->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1231, 21));
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
        loadVolume->setText(QApplication::translate("MainWindow", "Load Volume using VTK", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Inputs", 0));
        lineEdit_XShift_in->setText(QApplication::translate("MainWindow", "0", 0));
        label_9->setText(QApplication::translate("MainWindow", "XShift", 0));
        lineEdit_Roll_in->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_Yaw_in->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_YShift_in->setText(QApplication::translate("MainWindow", "0", 0));
        label_21->setText(QApplication::translate("MainWindow", "-YShift", 0));
        label_22->setText(QApplication::translate("MainWindow", "-ZShift", 0));
        lineEdit_ZShift_in->setText(QApplication::translate("MainWindow", "0", 0));
        label_20->setText(QApplication::translate("MainWindow", "Theta", 0));
        label_8->setText(QApplication::translate("MainWindow", "Pitch", 0));
        lineEdit_Pitch_in->setText(QApplication::translate("MainWindow", "0", 0));
        label_19->setText(QApplication::translate("MainWindow", "-Roll ", 0));
        Axial_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        Sagittal_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        Frontal_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        Tranform_ITK->setText(QApplication::translate("MainWindow", "3DTransformITK", 0));
        Reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        generateVolume->setText(QApplication::translate("MainWindow", "Generate Volume", 0));
        label_2->setText(QApplication::translate("MainWindow", "   Save Path    ", 0));
        lineEdit_SavePAth->setText(QApplication::translate("MainWindow", "D:\\\\TransformCT", 0));
        label_Status->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label->setText(QApplication::translate("MainWindow", "   Input path     ", 0));
        LineEdit_InputPath->setText(QApplication::translate("MainWindow", "D:\\\\1008\\\\Head_1002025_190179_10_6_F_NB_CCW\\\\DICOM", 0));
        GPU_Transform3D->setText(QApplication::translate("MainWindow", "3D GPU Transfrom ", 0));
        label_3->setText(QApplication::translate("MainWindow", "FanSelection (1/2)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
