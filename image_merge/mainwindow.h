#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QCoreApplication>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int height = 3072;
    int width = 3072;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
       void addImagesRowWise(const QString &inputImage1, const QString &inputImage2, const QString &outputImage, int width, int height,int height1);
       void cropImage(const QString &outputImage, const QString &croppedImage, int width, int height, int x, int y, int cropWidth, int cropHeight);
       void mergeRawImages(const char* inputRawImage1, const char* inputRawImage2, const char* outputRawImage, unsigned int width, unsigned int height, unsigned int height1);
       void cropMergedImage(const char *outputRawImage, const char *outputRawImage1, unsigned int width, unsigned int height1, unsigned int cropX, unsigned int cropY, unsigned int cropWidth, unsigned int cropHeight);
       void addImages(const QString &inputImage11, const QString &inputImage22,QString &inputImage13,QString &inputImage24, const QString &outputImage, int width, int height,int height1,int width1);
       void cropMergedImage1(const char* outputRawImage, const char* outputRawImage1, unsigned int width1, unsigned int height1, unsigned int cropX, unsigned int cropY, unsigned int cropWidth, unsigned int cropHeight);

};
#endif // MAINWINDOW_H
