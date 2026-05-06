#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myScene=new CustomScene();file:///P:/DUMPS/Rohith Reddy/New_Jan_Dicom_Server
    ui->graphicsView->setScene(myScene);

    imageSize[0]=3072;
    imageSize[1]=3072;

    rawImage =new unsigned short[imageSize[0]*imageSize[1]];
    charImage =new unsigned char[imageSize[0]*imageSize[1]];

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_LoadImage_clicked()
{
   const char *fileName = "D:\\dastagiri\\proj_2.raw";

   std::cout<<fileName<<std::endl;

   FILE    *fp;
   fopen_s(&fp, fileName, "rb");
   if(fp)
   {

       fread(rawImage, sizeof(unsigned short),imageSize[0]*imageSize[1], fp);
       fclose(fp);
   }


   for(int i=0;i<imageSize[0]*imageSize[1];i++){
        charImage[i]=(65535-rawImage[i])*255.0/65535;
   }


   QImage img(charImage,imageSize[0],imageSize[1], QImage::Format_Grayscale8);


   myScene->addPixmap(QPixmap::fromImage(img,Qt::ColorOnly).scaled(ui->graphicsView->geometry().width(),ui->graphicsView->geometry().height(),Qt::KeepAspectRatio, Qt::SmoothTransformation));


}

void MainWindow::on_pushButton_BrushTool_clicked()
{

    myScene->setMode(CustomScene::Mode::Brush);

}

void MainWindow::on_pushButton_FreeHand_clicked()
{
    myScene->setMode(CustomScene::Mode::Freehand);
}

void MainWindow::on_pushButton_2_clicked()
{
    myScene->clear();
}
