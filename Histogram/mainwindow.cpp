#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    unsigned short *imgShort = new unsigned short[1536*1536];
    for(int i=0;i<1536;i++)
    {
        for(int j=0;j<1536;j++)
        {
            imgShort[1536*i+j] = 0;
        }
    }
    QString img= "C:/Users/ashutosh.r/Downloads/projD1_222.raw";
    FILE *file;
    fopen_s(&file,img.toStdString().c_str(),"rb");
    fread(imgShort,sizeof(unsigned short),1536*1536,file);
    fclose(file);
    unsigned char *imgChar= new unsigned char[1536*1536];
    for(int i=0;i<1536;i++)
    {
        for(int j=0;j<1536;j++)
        {
            imgChar[1536*i+j]=imgShort[1536*i+j] *255.0/65535;
        }
    }
    double min=255;
    double max=0;
    for(int i=0;i<1536*1536;i++)
    {
        if(min>(double)imgChar[i])
            min=(double)imgChar[i];
        if(max<(double)imgChar[i])
            max=(double)imgChar[i];
    }
    qDebug()<<"min: "<<min;
    qDebug()<<"max: "<<max;
    //---------------------Calculate Histogram-------------------------------------
    QVector<double>x(256),y(256),z(256),n(256);
    double f=0;
    for(int i=0;i<1536;i++)
    {
        for(int j=0;j<1536;j++)
        {
            f = (double)imgChar[1536*i+j];
            y[f] = y[f]+1;
        }
    }
    for(int i=0;i<256;i++)
    {
        x[i]=i;
        y[i]=y[i]*255.0/(1536*1536);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(Qt::magenta));
    ui->widget->graph(0)->setData(x,y);
    ui->widget->xAxis->setRange(0,256);
    ui->widget->yAxis->setRange(0,256);
    ui->widget->replot();
    //----------------------Histogram Equalization-------------------------------
    double sum=0;
    for(int i=0;i<256;i++)
    {
        sum=sum+y[i];
        z[i]=round(sum);
    }
    qDebug()<<"sum: "<<sum;
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::cyan));
    ui->widget->graph(1)->setData(x,z);
    ui->widget->xAxis->setRange(0,256);
    ui->widget->yAxis->setRange(0,256);
    ui->widget->replot();
    //---------------------Histogram Normalization-----------------------------
    for(int i=0;i<1536*1536;i++)
    {
        imgChar[i]=(imgChar[i]-min)*255.0/(max-min);
        n[imgChar[i]]++;
    }
    for(int i=0;i<256;i++)
    {
        n[i]=n[i]*255.0/(1536*1536);
    }
    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(Qt::green));
    ui->widget->graph(2)->setData(x,n);
    ui->widget->xAxis->setRange(0,256);
    ui->widget->yAxis->setRange(0,256);
    ui->widget->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
