#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qcustomplot.h"
#include <QDebug>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayImage(unsigned char *imgChar);
    void displayHistogram(unsigned char *imgChar);

private slots:
    void on_ContrastScrollBar_valueChanged(int value);
    void on_BrightnessScrollBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QImage             *image=NULL;
    QGraphicsPixmapItem *item=NULL;
    QGraphicsScene     *scene=NULL;
    unsigned char    *imgChar=NULL;
    unsigned short  *imgShort=NULL;
};

#endif // MAINWINDOW_H
