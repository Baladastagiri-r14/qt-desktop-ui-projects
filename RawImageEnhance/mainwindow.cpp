#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgShort = new unsigned short[1536*1536];
    for(int i=0;i<1536*1536;i++)
    {
        imgShort[i]=0;
    }
    QString img = "C:/Users/ashutosh.r/Downloads/projD1_222.raw";
    FILE *file;
    fopen_s(&file,img.toStdString().c_str(),"rb");
    fread(imgShort,sizeof(unsigned short),1536*1536,file);
    fclose(file);
    imgChar = new unsigned char[1536*1536];
    for(int i=0;i<1536*1536;i++)
    {
        imgChar[i] = imgShort[i]*255.0/65535;
    }
    image = new QImage(imgChar,1536,1536,QImage::Format_Indexed8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
    scene = new QGraphicsScene;
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(0,0,60,60,Qt::KeepAspectRatio);
    displayHistogram(imgChar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayImage(unsigned char *imgChar)
{
    image= NULL;
    item = NULL;
    scene= NULL;

    image = new QImage(imgChar,1536,1536,QImage::Format_Indexed8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
    scene = new QGraphicsScene;
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(0,0,1536,1536,Qt::KeepAspectRatio);
    displayHistogram(imgChar);
}

void MainWindow::displayHistogram(unsigned char *imgChar)
{
    if(ui->widget->graph())
        ui->widget->removeGraph(0);

    int min=255;    int max=0;
    for(int i=0;i<1536*1536;i++)
    {
        if(min>(int)imgChar[i])
            min=(int)imgChar[i];
        if(max<(int)imgChar[i])
            max=(int)imgChar[i];
    }
    QVector<double>x(256),y(256);
    for(int i=0;i<1536*1536;i++)
    {
        y[(int)imgChar[i]]++;
    }
    for(int i=0;i<256;i++)
    {
        x[i]=i;
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x,y);
    ui->widget->xAxis->setRange(0,256);
    ui->widget->yAxis->setRange(0,256000);
    ui->widget->replot();
}

void MainWindow::on_ContrastScrollBar_valueChanged(int value)
{
    double alpha = static_cast<double>(value);
    double beta  = static_cast<double>(ui->BrightnessScrollBar->value());

    Mat imgNew;
    Mat imgBuf = Mat(1536,1536,CV_8UC1,imgChar);
    imgBuf.convertTo(imgNew,-1,alpha,beta);
    uchar *imgOut = new uchar [1536*1536];
    for(int i=0;i<1536*1536;i++)
    {
        imgOut[i]=imgNew.data[i];
    }
    displayImage(imgOut);
}

void MainWindow::on_BrightnessScrollBar_valueChanged(int value)
{
    double alpha = static_cast<double>(ui->ContrastScrollBar->value());
    double beta  = static_cast<double>(value);

    Mat imgNew;
    Mat imgBuf = Mat(1536,1536,CV_8UC1,imgChar);
    imgBuf.convertTo(imgNew,-1,alpha,beta);
    uchar *imgOut = new uchar [1536*1536];
    for(int i=0;i<1536*1536;i++)
    {
        imgOut[i]=imgNew.data[i];
    }
    displayImage(imgOut);
}
