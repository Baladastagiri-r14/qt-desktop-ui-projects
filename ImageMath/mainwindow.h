#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void slid(int a,int b,int c,int d,int e);
    void histogram(int a, int b);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_horizontalScrollBar_valueChanged(int value);
    void on_horizontalScrollBar_2_valueChanged(int value);
    void on_horizontalScrollBar_3_valueChanged(int value);
    void on_horizontalScrollBar_4_valueChanged(int value);


private:
    Ui::MainWindow *ui;
    int width    = 3072;
    int height   = 3072;
    int threshold= 65535;
    int a, b, c, d, e, f;
    double min, max, alpha, beta;
    unsigned short *imgShort = nullptr;
};

#endif // MAINWINDOW_H
