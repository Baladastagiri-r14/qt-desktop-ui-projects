#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
}
void MainWindow::setupQuadraticDemo(QCustomPlot *customPlot)
{
   demoName = "Quadratic Demo";

//    qDebug()<<"hist enter";
  QVector<double> x(101), y(101); // initialize with entries 0..100
//  qDebug()<<"hist enter";
  for (int i=0; i<101; ++i)
  {
    x[i] = i/50.0 - 1; // x goes from -1 to 1
    y[i] = x[i]*x[i];  // let's plot a quadratic function
  }
//  qDebug()<<"hist enter";
  // create graph and assign data to it:
  customPlot->addGraph();
  qDebug()<<"hist enter";
  customPlot->graph(0)->setData(x, y);
  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-1, 1);
  customPlot->yAxis->setRange(0, 1);
}



SecDialog::~SecDialog()
{
    delete ui;
}
