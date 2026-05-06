#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QFile>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include "itkImageFileReader.h"
#include "itkImage.h"
#include "itkNumericTraits.h"
#include "itkGDCMImageIO.h"
#include "itkMinimumMaximumImageFilter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent =  nullptr);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    bool readTags(const QString vFileName);
    void dicomWrite1(QString filepath);


};

#endif // MAINWINDOW_H
