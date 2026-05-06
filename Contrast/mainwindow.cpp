#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    unsigned short *imgShort = new unsigned short[1536*1536];
    QString path= "C:/Users/ashutosh.r/Downloads/projD1_222.raw";
    FILE *file;
    fopen_s(&file,path.toStdString().c_str(),"rb");
    fread(imgShort,sizeof(unsigned short),1536*1536,file);
    fclose(file);
    QVector<double>x(256),y(256);
    imgChar = new unsigned char[1536*1536];
    for(int i=0;i<1536*1536;i++)
    {
        imgChar[i] = imgShort[i]*255.0/65535;
        y[(double)imgChar[i]]++;
    }
    for(int i=0;i<256;i++)
    {
        x[i]=i;
        y[i]=y[i]*255.0/(1536*1536);
    }
    image = new QImage(imgChar,1536,1536,QImage::Format_Indexed8);
    item  = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
    scene = new QGraphicsScene;
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(0,0,60,60,Qt::KeepAspectRatio);
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x,y);
    ui->widget->xAxis->setRange(0,256);
    ui->widget->yAxis->setRange(0,256);
    ui->widget->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    double a = static_cast<double>(value);
    double b = static_cast<double>(ui->horizontalScrollBar_2->value());
    qDebug()<<"a1: "<<a;
    qDebug()<<"b1: "<<b;
    QVector<double>x(256),y(256);
    int min=127-value;
    int max=127+value;
    if(min>=max)
        max=min+1;
    for(int i=0;i<256;i++)
    {
        x[i]=i;
        y[i]=a*((x[i]-min)*255.0/(max-min))+b;
    }
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::magenta));
    ui->widget->graph(1)->setData(x,y);
    ui->widget->xAxis->setRange(0,256);
    ui->widget->yAxis->setRange(0,256);
    ui->widget->replot();
}

void MainWindow::on_horizontalScrollBar_2_valueChanged(int value)
{
    double a = static_cast<double>(ui->horizontalScrollBar->value());
    double b = static_cast<double>(value);
    qDebug()<<"a2: "<<a;
    qDebug()<<"b2: "<<b;
    QVector<double>x(256),y(256);
    for(int i=0;i<256;i++)
    {
        x[i]=i;
        y[i]=a*(x[i]+(127-value))+b;
    }
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::magenta));
    ui->widget->graph(1)->setData(x,y);
    ui->widget->xAxis->setRange(0,256);
    ui->widget->yAxis->setRange(0,256);
    ui->widget->replot();
}
