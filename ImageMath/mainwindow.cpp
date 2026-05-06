#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = "D:\\dastagiri\\14-11-24\\ImageMath\\proj_2.raw";
    imgShort = new unsigned short[height * width];

    FILE *file;
    fopen_s(&file, path.toStdString().c_str(), "rb");
    fread(imgShort, sizeof(unsigned short), height * width, file);
    fclose(file);

    min = max = imgShort[0];
    for (int i = 0; i < height * width; i++)
    {
        if (imgShort[i] < min)
            min = imgShort[i];
        if (imgShort[i] > max)
            max = imgShort[i];
    }

    f = 1;
    ui->horizontalScrollBar->setRange(min, max);
    ui->horizontalScrollBar_2->setRange(min, max);
    ui->horizontalScrollBar_3->setRange(min, max);
    ui->horizontalScrollBar_4->setRange(min, max);

    ui->label->setNum(min);
    ui->label_2->setNum(max);

    ui->horizontalScrollBar->setValue(min);
    ui->horizontalScrollBar_2->setValue(max);
    ui->horizontalScrollBar_3->setValue(round((max + min) / 2.0));
    ui->horizontalScrollBar_4->setValue(round((max + min) / 2.0));
    f = 0;

}

void MainWindow::histogram(int a, int b)


{
      if (a == b)
          alpha = (max - min);
      else
          alpha = (max - min) * 1.0 / (b - a);

      beta = min - a * alpha;

      cv::Mat imgBuff = cv::Mat(height, width, CV_16UC1, imgShort);

      cv::Mat imgNew;
      imgBuff.convertTo(imgNew, -1, alpha, beta);

      cv::Mat imgOne;
      cv::convertScaleAbs(imgNew, imgOne, 255.0 / std::numeric_limits<uint16_t>::max());



      uchar *imgOut = new uchar[height * width];
      for (int i = 0; i < height * width; i++)
      {
          imgOut[i] = imgOne.data[i];
      }

      QImage *image = new QImage(imgOut, width, height, QImage::Format_Indexed8);

      QGraphicsScene *scene = new QGraphicsScene;
      scene->clear();
      QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
      scene->addItem(item);
      ui->graphicsView->setScene(scene);
      ui->graphicsView->fitInView(item);

      const int maxIntensity = 65535;
      QVector<double> x(maxIntensity + 1), y(maxIntensity + 1, 0);

      for (int i = 0; i < height * width; i++)
      {
          uint16_t pixelValue = reinterpret_cast<uint16_t*>(imgShort)[i]; // Access 16-bit pixel value
          y[pixelValue]++;
      }

      for (int i = 0; i <= maxIntensity; i++)
      {
          x[i] = i;
      }

      ui->widget->clearGraphs();
      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x, y);
      ui->widget->xAxis->setRange(0, maxIntensity);
      ui->widget->yAxis->setRange(0, *std::max_element(y.begin(), y.end()));
      ui->widget->replot();

      delete[] imgOut;
      delete image;
}

void MainWindow::slid(int a, int b, int c, int d, int e)
{
    f++;
    if (f == 1)
    {
        switch (e) {
        case 1:
            if (b < a)
                b = a;

            c = min + round((max + (max - b) - a) / 2);
            d = round((max + (max - b) + a) / 2);

            if (a < 0)
                ui->label->setNum(0);

            else
                ui->label->setNum(a);

            if (b > threshold)
                ui->label_2->setNum(threshold);

            else
                ui->label_2->setNum(b);

            ui->horizontalScrollBar_2->setValue(b);
            ui->horizontalScrollBar_3->setValue(c);
            ui->horizontalScrollBar_4->setValue(d);
            histogram(a, b);
            f = 0;
            break;

        case 2:
            if (b < a)
                a = b;

            c = min + round((max + (max - b) - a) / 2);
            d = round((max + (max - b) + a) / 2);

            if (a < 0)
                ui->label->setNum(0);

            else
                ui->label->setNum(a);

            if (b > threshold)
                ui->label_2->setNum(threshold);

            else
                ui->label_2->setNum(b);

            ui->horizontalScrollBar->setValue(a);
            ui->horizontalScrollBar_3->setValue(c);
            ui->horizontalScrollBar_4->setValue(d);
            histogram(a, b);
            f = 0;
            break;

        case 3:
            a = min + d - c;
            b = max + (max + min - d - c);

            if (a < 0)
                ui->label->setNum(0);

            else
                ui->label->setNum(a);

            if (b > threshold)
                ui->label_2->setNum(threshold);

            else
                ui->label_2->setNum(b);

            ui->horizontalScrollBar->setValue(a);
            ui->horizontalScrollBar_2->setValue(b);
            histogram(a, b);
            f = 0;
            break;

        case 4:
            a = min + d - c;
            b = max + (max + min - d - c);

            if (a < 0)
                ui->label->setNum(0);

            else
                ui->label->setNum(a);

            if (b > threshold)
                ui->label_2->setNum(threshold);

            else
                ui->label_2->setNum(b);

            ui->horizontalScrollBar->setValue(a);
            ui->horizontalScrollBar_2->setValue(b);
            histogram(a, b);
            f = 0;
            break;

        default:
            ui->label->setNum(a);
            ui->label_2->setNum(b);
            ui->horizontalScrollBar->setValue(a);
            ui->horizontalScrollBar_2->setValue(b);
            ui->horizontalScrollBar_3->setValue(c);
            ui->horizontalScrollBar_4->setValue(d);
            histogram(a, b);
            f = 0;
            break;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    a = min;
    b = max;
    c = round((max + min) / 2.0);
    d = round((max + min) / 2.0);
    e = 0;
    f = 0;
    slid(a, b, c, d, e);
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    a = static_cast<int>(value);
    b = static_cast<int>(ui->horizontalScrollBar_2->value());
    c = static_cast<int>(ui->horizontalScrollBar_3->value());
    d = static_cast<int>(ui->horizontalScrollBar_4->value());
    e = 1;
    slid(a, b, c, d, e);
}

void MainWindow::on_horizontalScrollBar_2_valueChanged(int value)
{
    a = static_cast<int>(ui->horizontalScrollBar->value());
    b = static_cast<int>(value);
    c = static_cast<int>(ui->horizontalScrollBar_3->value());
    d = static_cast<int>(ui->horizontalScrollBar_4->value());
    e = 2;
    slid(a, b, c, d, e);
}

void MainWindow::on_horizontalScrollBar_3_valueChanged(int value)
{
    a = static_cast<int>(ui->horizontalScrollBar->value());
    b = static_cast<int>(ui->horizontalScrollBar_2->value());
    c = static_cast<int>(value);
    d = static_cast<int>(ui->horizontalScrollBar_4->value());
    e = 3;
    slid(a, b, c, d, e);
}

void MainWindow::on_horizontalScrollBar_4_valueChanged(int value)
{
    a = static_cast<int>(ui->horizontalScrollBar->value());
    b = static_cast<int>(ui->horizontalScrollBar_2->value());
    c = static_cast<int>(ui->horizontalScrollBar_3->value());
    d = static_cast<int>(value);
    e = 4;
    slid(a, b, c, d, e);
}

