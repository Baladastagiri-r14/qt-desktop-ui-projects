#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    unsigned short *imgShort = new unsigned short[1536*1536];
    for(int i=0;i<1536*1536;i++)
    {
        imgShort[i]=0;
    }
    QString path = "C:/Users/ashutosh.r/Downloads/projD1_222.raw";
    FILE *file;
    fopen_s(&file,path.toStdString().c_str(),"rb");
    fread(imgShort,sizeof(unsigned short),1536*1536,file);
    fclose(file);
    QVector<double>x(65536),y(65536);
    double min=65535;     double max=0;
    for(int i=0;i<1536*1536;i++)
    {
        if((double)imgShort[i]<min)
            min=(double)imgShort[i];
        if((double)imgShort[i]>max)
            max=(double)imgShort[i];
        y[(double)imgShort[i]]++;
    }
    double sum=0;
    for(int i=0;i<65536;i++)
    {
        x[i]=i;
        sum += y[i];
        y[i]=round(sum*65535.0/(1536*1536));    // Histogram Equalization
        y[i]=(y[i]-min)*65535.0/(max-min);      // Histogram Normalization
    }
    unsigned char *imgChar = new unsigned char[1536*1536];
    for(int i=0;i<1536*1536;i++)
    {
        imgShort[i]=y[(double)imgShort[i]]++;
        imgChar[i] = imgShort[i]*255.0/65535;
    }
    QImage *image = new QImage(imgChar,1536,1536,QImage::Format_Indexed8);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(0,0,60,60,Qt::KeepAspectRatio);
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x,y);
    ui->widget->xAxis->setRange(0,65536);
    ui->widget->yAxis->setRange(0,65536);
    ui->widget->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
