#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new smart(this);
    //scene->addEllipse(0,0,100,100);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   //open
   FILE *input=NULL;
   int w=3072,h=3072;
   unsigned short* raw16= new unsigned short[w*h];
   unsigned char* raw8= new unsigned char[w*h];
   input=fopen("D:/PRITAM/QT/task2(display and edit 8bit raw img)/Qgraphicsrawimage/rawImage_23_09_2019_10_34_15.raw","r");
   if(input){
       fread(raw16,(w*h*sizeof(short)),1,input);
   }
   for(int i=0;i<w*h;i++){
       raw8[i]=(raw16[i]*255)/65535;
   }
   QImage myimage(&raw8[0],w,h,QImage::Format_Grayscale8);
   scene->addPixmap(QPixmap::fromImage(myimage));
   ui->graphicsView->setScene(scene);
   ui->graphicsView->show();
   ui->graphicsView->fitInView(0,0,3072,3072,Qt::KeepAspectRatio);
}

void MainWindow::on_pushButton_2_clicked()
{
    //close
    FILE *input=NULL;
    int w=3072,h=3072;
    unsigned short* raw16= new unsigned short[w*h];
    unsigned char* raw8= new unsigned char[w*h];
    input=fopen("D:/PRITAM/QT/task2(display and edit 8bit raw img)/Qgraphicsrawimage/rawImage_23_09_2019_10_34_15.raw","r");
    if(input){
        fread(raw16,(w*h*sizeof(short)),0,input);
    }
    for(int i=0;i<w*h;i++){
        raw8[i]=(raw16[i]*255)/65535;
    }
    QImage myimage(&raw8[0],w,h,QImage::Format_Grayscale8);
    scene->addPixmap(QPixmap::fromImage(myimage));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    ui->graphicsView->fitInView(0,0,3072,3072,Qt::KeepAspectRatio);
}

void MainWindow::on_pushButton_3_clicked()
{
    //delete all
    QList<QGraphicsItem*> allitem =scene->items();
    for(int i=0;i<allitem.size()-2;i++){
        QGraphicsItem *graphic=allitem[i];
        scene->removeItem(graphic);
        scene->update();
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{

}
void MainWindow::on_pushButton_4_clicked()
{
    //brush

}
