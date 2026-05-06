#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgraphicsscene.h>
#include <iostream>
#include "customscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_LoadImage_clicked();


    void on_pushButton_BrushTool_clicked();

    void on_pushButton_FreeHand_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    CustomScene *myScene;
    unsigned short* rawImage;
    unsigned char* charImage;
    unsigned int imageSize[2];

};

#endif // MAINWINDOW_H
