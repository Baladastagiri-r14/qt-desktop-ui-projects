#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <string.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QHoverEvent>
#include <QScrollArea>
#include <iostream>
#include <QCoreApplication>
#include <opencv/cv.h>
#include <QGraphicsSceneMouseEvent>
#include <QSlider>
#include <QAbstractSlider>
#include <QScrollBar>
#include <QDialog>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#  include <QDesktopWidget>
#endif
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    customPlot = new QCustomPlot;


    dialog = new QDialog(ui->centralWidget);
    dialog->setGeometry(750,250,400,400);
//    dialog->setParent(ui->centralWidget);
    VLayout = new QVBoxLayout();
    slide= new QSlider(Qt::Horizontal );
    slider= new QSlider(Qt::Horizontal );
    label = new QLineEdit();
    label->setText("MINIMUM");
    label->setFixedWidth(60);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addSpacing(20);
    layout->addWidget(label);
      layout->addSpacing(20);
    label->setAlignment(Qt::AlignCenter);
    label1 = new QLineEdit();
    label1->setText("MAXIMUM");
    label1->setFixedWidth(60);
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addSpacing(20);
    layout1->addWidget(label1);
    layout1->addSpacing(20);
    label1->setAlignment(Qt::AlignCenter);

//    label->setEnabled(false);
//    label1->setEnabled(false);
    slide->setRange(0,65535);
    slider->setRange(0,65535);
    VLayout->addWidget(customPlot);
    VLayout->addWidget(slide);
    VLayout->addLayout(layout);
//    VLayout->addWidget(label);
    VLayout->addWidget(slider);
    VLayout->addLayout(layout1);
//    VLayout->addWidget(label1);
    dialog->setLayout(VLayout);

    dialog->hide();

    ui->pushButton_2->setEnabled(false);
    sne = new mouse();


    wid=QApplication::desktop()->screenGeometry().width()/2;
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QObject::connect(sne,SIGNAL(buttonclick()),this,SLOT(onRightClicked()));
    QObject::connect(sne,SIGNAL(doubleclick()),this,SLOT(onDoubleClicked()));
    QObject::connect(this,SIGNAL(minimumvalue()),this,SLOT(normalize()));
    QObject::connect(this,SIGNAL(maximumvalue()),this,SLOT(normalize()));

    QObject::connect(slide,SIGNAL(valueChanged(int)),this,SLOT(on_horizontalSlider_valueChanged(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),this,SLOT(on_horizontalSlider_2_valueChanged(int)));
    ui->progressBar->setValue(0);
    ui->progressBar_2->setValue(0);
    ui->progressBar->setFixedWidth(900);
    ui->progressBar_2->setFixedWidth(900);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupQuadraticDemo(QCustomPlot *customPlot, int x, int x1)
{
    qDebug()<<"entered";
    {
    demoName = "Quadratic Demo";
    QVector<double> w(65535), h(65535);
    for (int i=0; i<65535; ++i)
    {
      w[i] = i ;
      h[i]=hist[i];
    }
    qDebug()<<"hist enter"<<h[0];
    customPlot->addGraph();
    customPlot->graph(0)->setData(w, h);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(0, 65535);
    customPlot->yAxis->setRange(0,3000);

    QVector<double> x(2), y(2);
    for (int i=0; i<2; ++i)
    {
        if(i==0)
        {
           x[i]= min;
           y[i]=0;
        }
        else
        {
            x[i] = min;
            y[i] = 2500;
        }


      }
     customPlot->addGraph();
     customPlot->graph(1)->setPen(QPen(Qt::red));
     customPlot->graph(1)->setData(x,y);

     QVector<double> x1(2), y1(2);
     for (int i=0; i<2; ++i)
     {
         if(i==0)
         {
            x1[i]= max;
            y1[i]=0;
         }
         else
         {
             x1[i] = max;
             y1[i] = 2500;
         }
     }
     customPlot->addGraph();
     customPlot->graph(2)->setPen(QPen(Qt::red));
     customPlot->graph(2)->setData(x1,y1);
     customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

     QVector<double> x2(2), y2(2);
     for (int i=0; i<2; ++i)
     {
         if(i==0)
         {
            x2[i]= min;
            y2[i]=2500;
         }
         else
         {
             x2[i] = max;
             y2[i] = 2500;
         }
     }
     customPlot->addGraph();
     customPlot->graph(3)->setPen(QPen(Qt::red));
     customPlot->graph(3)->setData(x2,y2);

//     qApp->processEvents();
//     customPlot->replot();


//     qDebug()<<min<<max<<max-min<<"values";

     QVector<double> mi(65535), ma(65535);
     for (int i=min; i<max; ++i)
     {
       mi[i] = i ;
       ma[i]=hist[i];
     }
     for (int i=0; i<min; ++i)
     {
       mi[i] = i ;
       ma[i]=0;
     }



//     qDebug()<<"hist enter"<<min<<max;
     customPlot->addGraph();
     customPlot->graph(4)->setData(mi, ma);
     customPlot->graph(4)->setPen(QPen(Qt::green));
     customPlot->replot();


    }

    qDebug()<<"hist exited";

}

void MainWindow::onRightClicked()
{
    if(sne->angleInDegrees >=45)
    {
        if(sne->angleInDegrees <=135)
        {
            sne->vartical = true;
        }
        else
        {
            sne->vartical=false;
        }
    }
    if(sne->angleInDegrees >=0)
    {
        if(sne->angleInDegrees<=44)
        {
            sne->horizantal= true;
        }
        else
        {
            sne->horizantal=false;
        }
    }
    if(sne->angleInDegrees  >=136)
    {
        if(sne->angleInDegrees  <=180)
        {
            sne->horizantal= true;
        }
        else
        {
            sne->horizantal=false;
        }
    }

    if(sne->vartical==true)
    {
    }
    if(sne->horizantal==true)
    {
    }
    cv::Mat image=cv::Mat(width,height,CV_8UC1,str);
    brightness = sne->heigh+sne->deltaY;
    contrast  = sne->widh+sne->deltaX;
    if(brightness>=100)
    {
        brightness=100;
    }
    if(brightness<=0)
    {
        brightness=0;
    }
    if(contrast>=5)
    {
        contrast=5;
    }
    if(contrast<=0)
    {
        contrast=0.5;
    }
    ui->progressBar->setValue(brightness);
    ui->progressBar_2->setValue(contrast);

    Mat imageBrighnessHigh100;
    if(sne->vartical==true)
    {
        image.convertTo(imageBrighnessHigh100, -1,1,brightness);
    }
    else
    {
        image.convertTo(imageBrighnessHigh100, -1,/*sne->widh*/contrast+0.3,1);
    }
    QImage imgIn= QImage((uchar*) imageBrighnessHigh100.data,width,height,QImage::Format_Grayscale8);
    Pix2 = QPixmap::fromImage(imgIn);
    itm2 = new QGraphicsPixmapItem(Pix2);
    sne->addItem(itm2);

}
void MainWindow::onDoubleClicked()
{

    ui->graphicsView->fitInView(itm,Qt::KeepAspectRatio);
    sne->addItem(itm);
    min = min+1;
    slide->setValue(1);
    slider->setValue(65535);
}

void MainWindow::normalize()
{

//    norm = new unsigned short[width*height];
//    qDebug()<<"befrore normalization"<<"max"<<max<<"min"<<min;
//    maxmin=max-min;
//    for(int i=0;i<width*height;i++)
//    {
//        norm[i] =(((buf[i]-min)/maxmin)*65535.0);
//    }
////  qDebug()<<buf[0]/*-min)/max-min)*65535.0*/<<((buf[52]-min)/65535.0)*65535<<"round"<<norm[52];

//    for (int i = 0; i < width*height; i++)
//    {
//        str[i] = (norm[i]/65535.0)*255;
//    }
//    Img = QImage(str, height, height, QImage::Format_Grayscale8);
//    Pix = QPixmap::fromImage(Img);
//    itm = new QGraphicsPixmapItem(Pix);
//    ui->graphicsView->setScene(sne);
//    ui->graphicsView->fitInView(itm,Qt::KeepAspectRatio);
//    sne->addItem(itm);



    unsigned short* norm = new unsigned short[width * height];
    double maxmin = max - min;


//    for (int i = 0; i < width * height; ++i) {
//        if (buf[i] >= min && buf[i] <= max) {
//            norm[i] = static_cast<unsigned short>(((buf[i] - min) / maxmin) * 65535.0);
//        } else {
//            norm[i] = 0; // Assign out-of-range values to 0 (black)
//        }
//    }

    for (int i = 0; i < width * height; ++i) {
        if (buf[i] < min) {
            norm[i] = 0;
        } else if (buf[i] > max) {
            norm[i] = 65535;
        } else {
            norm[i] = static_cast<unsigned short>(((buf[i] - min) / maxmin) * 65535.0);
        }
    }

    unsigned char* str = new unsigned char[width * height];
    for (int i = 0; i < width * height; i++) {
        str[i] = (norm[i] / 65535.0) * 255;
    }

    QImage Img(str, width, height, QImage::Format_Grayscale8);
    QPixmap Pix = QPixmap::fromImage(Img);
    QGraphicsPixmapItem* itm = new QGraphicsPixmapItem(Pix);

    sne->clear();
    sne->addItem(itm);
    ui->graphicsView->setScene(sne);
    ui->graphicsView->fitInView(itm, Qt::KeepAspectRatio);

    delete[] norm;
    delete[] str;



}
void MainWindow::wheelEvent(QWheelEvent *event)
{
    val = event->delta();
    cur = this->cursor().pos().x();
    double scaleFactor =1.1;
    if(cur<=wid)
    {

        if(event->delta()>0)
        {
            ui->graphicsView->scale(scaleFactor,scaleFactor);
        }
        else
        {
            ui->graphicsView->scale(1.0/scaleFactor,1.0/scaleFactor);
        }
    }
    else
    {
        if(event->delta()>0)
        {
            ui->graphicsView_2->scale(scaleFactor,scaleFactor);
        }
        else
        {
            ui->graphicsView_2->scale(1.0/scaleFactor,1.0/scaleFactor);
        }
    }

}
void MainWindow::on_pushButton_clicked()
{

    hist= new short[65535];
    for (int i=0; i<65535;i++)
    {
        hist[i]=0;
    }

    buf = new unsigned short[width*height];
    pInput  = fopen( "E:\\dastagiri\\14-11-24\\ImageMath\\proj_2.raw","r" );
    fread(buf,sizeof(unsigned short),width*height,pInput);
    fclose(pInput);
    str = new unsigned char[width*height];
    sene = new QGraphicsScene(/*this*/);
    max = buf[0];
    min = buf[0];
    for(int i = 1;i<width*height;i++)
    {
        if(max<buf[i])
        {
            max = buf[i];
        }
        if(min>buf[i])
        {
            min=buf[i];
        }
    }
    qDebug()<<"min"<<min<<"max"<<max;

        for(int i=0;i<width*height;i++)
        {
          hist[buf[i]]= hist[buf[i]]+1;
        }
    for (int i = 0; i < width*height; i++)
    {
        str[i] = (buf[i]/65535.0)*255;
    }

    Img = QImage(str, width, height, QImage::Format_Grayscale8);
    Pix = QPixmap::fromImage(Img);
    itm = new QGraphicsPixmapItem(Pix);

    ui->graphicsView->setScene(sne);
    ui->graphicsView->fitInView(itm,Qt::KeepAspectRatio);
    sne->addItem(itm);





//    typedef itk::Image<short, 2> ImageType;
//    typedef itk::ImageFileReader<ImageType> ReaderType;
//    ReaderType::Pointer reader = ReaderType::New();
//    typedef itk::GDCMImageIO ImageIoType;

//    try {
//        qDebug() << "Enter Filename set::";
//        reader->SetFileName("D:\\cbct_images\\Resampled_CT_X_Y_Z_-11_2_65cm\\slice -0424.dcm");
//        qDebug() << "Filename set::";
//    } catch (itk::ExceptionObject &e) {
//        std::cerr << "exception in file reader " << std::endl;
//        std::cerr << e << std::endl;
//        qDebug() << "error";
//    }

//    try {
//        ImageIoType::Pointer gdcmImageIO = ImageIoType::New();
//        reader->SetImageIO(gdcmImageIO);
//    } catch (itk::ExceptionObject &e) {
//        std::cerr << "exception in file reader " << std::endl;
//        std::cerr << e << std::endl;
//        qDebug() << "error";
//    }

//    qDebug() << "ImageIO set::";
//    try {
//        reader->Update();
//    } catch (itk::ExceptionObject &e) {
//        std::cerr << "exception in file reader " << std::endl;
//        std::cerr << e << std::endl;
//        qDebug() << "error";
//    }
//    qDebug() << "Image updated::";

//    ImageType::Pointer image = reader->GetOutput();
//    short* buf = image->GetBufferPointer();

//    // Get image size
//    ImageType::RegionType region = image->GetLargestPossibleRegion();
//    ImageType::SizeType size = region.GetSize();
//    int totalPixels = size[0] * size[1];

//    max = buf[0];
//    min = buf[0];
//    qDebug() << "Initial imin and imax:" << min << max;

//    for (int i = 1; i < 512*512; ++i) {
//        if (buf[i] < min) {
//            min = buf[i];
//        } else if (buf[i] > max) {
//            max = buf[i];
//        }
//    }

//    qDebug() << "imax:" << max << "imin:" << min << "max & min--------";




//    qDebug()<<"buffer"<<min<<max;
//    str = new unsigned char[512*512];
//    for(int i=0;i<512*512;i++)
//    {
//        hist[buf[i]]= hist[buf[i]]+1;
//    }

//    for (int i = 0; i < 512*512; i++)
//    {
//        str[i] = (buf[i]/65535.0)*255;
//    }

//    Img = QImage(str, 512,512, QImage::Format_Grayscale8);
//    Pix = QPixmap::fromImage(Img);
//    itm = new QGraphicsPixmapItem(Pix);
//    ui->graphicsView->setScene(sne);
//    ui->graphicsView->fitInView(itm,Qt::KeepAspectRatio);
//    sne->addItem(itm);
//    qDebug()<<"image displayed";





    FILE* pInput1  = NULL;
    buf1 = new unsigned short[3072*3072];
    pInput1  = fopen( "E:\\dastagiri\\14-11-24\\wheel\\proj_1.raw","r" );
    fread(buf1,sizeof(unsigned short),3072*3072,pInput1);
    fclose(pInput1);
    str1 = new unsigned char[3072*3072];
    sene = new QGraphicsScene(/*this*/);
    for (int i = 0; i < 3072*3072; i++)
    {
        str1[i] = (buf1[i]/65535.0)*255;
    }
    Img1 = QImage(str1, 3072, 3072, QImage::Format_Grayscale8);
    Pix1 = QPixmap::fromImage(Img1);
    itm1 = new QGraphicsPixmapItem(Pix1);
    ui->graphicsView_2->setScene(sene);
    ui->graphicsView_2->fitInView(itm1,Qt::KeepAspectRatio);
    sene->addItem(itm1);
    qDebug()<<"image 2 displayed";

    this->setupQuadraticDemo(customPlot,min,max);
    ui->pushButton_2->setEnabled(true);
}
void MainWindow::on_horizontalSlider_valueChanged(int value)
{

   min= value;

   this->setupQuadraticDemo(customPlot,min,max);
   qApp->processEvents();

   customPlot->replot();
   emit minimumvalue();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{

     max= value;

     this->setupQuadraticDemo(customPlot,min,max);
     qApp->processEvents();

     customPlot->replot();

     emit maximumvalue();
}

void MainWindow::on_pushButton_2_clicked()
{

    min = min+1;
    slide->setValue(min);


    slider->setValue(max);

    dialog->show();


    qDebug()<<"set min and max values done"<<min<<max;
//    imagemax = max;
}


void MainWindow::on_progressBar_valueChanged(int value)
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
}

void MainWindow::on_progressBar_2_valueChanged(int value)
{
    ui->progressBar_2->setMinimum(0);
    ui->progressBar_2->setMaximum(5);

}

void MainWindow::on_pushButton_3_clicked()
{

}
