#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QThread>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QWidget>
#include <QtWidgets>
#include <QFileDialog>

#include <itkImageToVTKImageFilter.h>
#include "itkVTKImageImport.h"
#include "itkVTKImageExport.h"

#include <itkImage.h>
#include <itkPoint.h>
#include <itkImageSliceIteratorWithIndex.h>
#include <itkImageIteratorWithIndex.h>
#include <itkPointSetToImageFilter.h>
#include <itkExtractImageFilter.h>
#include <itkGroupSpatialObject.h>
#include <itkSpatialObjectToImageFilter.h>
#include <itkPolygonSpatialObject.h>
#include <itkImageFileWriter.h>
#include <itkImageFileReader.h>
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include <gdcmTypes.h>
#include <gdcmReader.h>
#include <gdcmSmartPointer.h>
#include <gdcmAttribute.h>
#include <gdcmSequenceOfItems.h>
#include <gdcmFileMetaInformation.h>
#include "itkRGBPixel.h"
#include "itkPNGImageIO.h"
#include "itkNiftiImageIO.h"
#include "itkNiftiImageIOFactory.h"
#include <nifti1_io.h>
#include <itkAndImageFilter.h>
#include <gdcmUIDGenerator.h>

using namespace  gdcm;
//gdcm
#include "gdcmImage.h"
#include "gdcmReader.h"
#include "gdcmFile.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmWriter.h"
#include "gdcmItem.h"
#include "gdcmTag.h"
#include "gdcmImageWriter.h"
#include "gdcmAttribute.h"
#include "gdcmImageReader.h"
#include <gdcmSmartPointer.h>

#include <QTimer>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    int i;
    QImage q_image;
    const int w=2816,h=3528;
    int Rows;
    int Cols;
    QString treatmentMachineName;
//    double imaginPixelSpacing=0.1;
    unsigned char *dispImg;
    int count;
    ~MainWindow();

private slots:
    void on_PB_load_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;
};

#endif // MAINWINDOW_H
