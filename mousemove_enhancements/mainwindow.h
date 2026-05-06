#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtWidgets>
#include <QWidget>
#include "mouse.h"
#include <QSlider>
#include <QAbstractSlider>
#include <QScrollBar>
#include "qcustomplot.h"
#include <QDialog>


#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include <gdcmImageReader.h>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include<QDebug>
#include "itkFlipImageFilter.h"
#include "itkAffineTransform.h"
#include "itkResampleImageFilter.h"
#include "itkNearestNeighborInterpolateImageFunction.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
//    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent = nullptr);
    int width = 3072;
    int height = 3072;
    int offset = 16;
    unsigned short* buf=NULL;
    unsigned char* str=NULL;
    unsigned short* reader=NULL;
    QImage Img;
    QPixmap Pix;
    QGraphicsPixmapItem *itm=NULL;
    unsigned short* buf1=NULL;
    unsigned char* str1=NULL;
    QImage Img1;
    QPixmap Pix1;
    QGraphicsPixmapItem *itm1=NULL;
    QGraphicsScene *sene;
    mouse *sne;
    int val;
    int wid;
    int cur;
    int brightness;
    float contrast;
    QGraphicsPixmapItem *itm2=NULL;
    QPixmap Pix2;
    QGraphicsPixmapItem *itm3=NULL;
    QPixmap Pix3;
    int hei;
    short* hist=NULL;
    int min = NULL;
    int max = NULL;
    unsigned short* norm;
    float maxmin;
//    int mn;
//    int mx;
    bool button;
    void normalze();
    QVBoxLayout *VLayout;
    QSlider * slide;
    QSlider * slider;
    QLineEdit *label;
    QLineEdit *label1;
    FILE* pInput  = NULL;
    int imagemax = NULL;
//     SlidersGroup *horizontalSliders;

    ~MainWindow();
    QDialog *dialog;
    void setupQuadraticDemo(QCustomPlot *customPlot,int x,int x1);
    QCustomPlot *customPlot;

protected:
     void wheelEvent(QWheelEvent *event);

signals:
     void minimumvalue();
     void maximumvalue();

private slots:
    void on_pushButton_clicked();
    void onRightClicked();
    void onDoubleClicked();
    void normalize();
//    void on_horizontalSlider_actionTriggered(int action);
//    void on_horizontalSlider_2_actionTriggered(int action);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_pushButton_2_clicked();
    void on_progressBar_valueChanged(int value);
    void on_progressBar_2_valueChanged(int value);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString demoName;
};

#endif // MAINWINDOW_H
