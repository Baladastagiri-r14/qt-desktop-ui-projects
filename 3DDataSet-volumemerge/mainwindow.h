#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

#include <QGraphicsPixmapItem>
#include <QPixmap>

#include <QMessageBox>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkGDCMImageIO.h>

#include <itkImageSeriesReader.h>

#include <itkMetaDataDictionary.h>
#include <itkMetaDataObject.h>
#include <itkEuler2DTransform.h>
#include <itkResampleImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkEuler3DTransform.h>
#include <itkGDCMSeriesFileNames.h>
#include <vtkColorTransferFunction.h>
#include <itkLinearInterpolateImageFunction.h>
#include <itkMatrix.h>


/*writing volume*/
#include <itkImageToVTKImageFilter.h>
#include <vtkDICOMCTGenerator.h>
#include <vtkDICOMWriter.h>
#include <vtkMatrix4x4.h>



/*Additional used*/
#include <itkExtractImageFilter.h>
#include <itkImageSeriesReader.h>
#include <itkGDCMSeriesFileNames.h>


/*Rendering*/
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkInteractionStyle)


#include <vtkSmartPointer.h>

#include <vtkImageImport.h>

#include <vtkGPUVolumeRayCastMapper.h>


#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkResliceImageViewer.h>
#include <vtkCamera.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <QVTKWidget.h>

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include <vtkAutoInit.h>


/*rendering additional*/
#include <vtkAxesActor.h>



/*vtk reading volume*/
#include <vtkDICOMReader.h>
#include <vtkDICOMDirectory.h>
#include <vtkDICOMMetaData.h>
#include <vtkImageCast.h>


#include <itkVTKImageToImageFilter.h>

#include <QTime>
#include "dicomwrite.h"






#define PI 3.141519

//For Reading and Loading the Image
// typedef unsigned short PixelType;
typedef short PixelType;
typedef float PixelTypef;

typedef itk::Image<PixelType,3> ImageType3D;

typedef itk::Image<PixelTypef,3> ImageType3Df;
typedef itk::Image<PixelTypef,2> ImageType2Df;

typedef itk::ImageSeriesReader< ImageType3D > SeriesReaderType;

typedef itk::CastImageFilter<ImageType3D,ImageType3Df> CastImageFilterType3D;

typedef itk::GDCMImageIO gdcmIO;

typedef itk::LinearInterpolateImageFunction<ImageType3Df,double> LinearInteroplatorType;

typedef itk::Euler3DTransform<double> TransformType3D;

typedef itk::ResampleImageFilter<ImageType3Df,ImageType3Df> ResampleFilterType3D;


typedef itk::CastImageFilter<ImageType3Df,ImageType3D> ReverseCastImageFilterType3D;
typedef itk::ImageToVTKImageFilter<ImageType3D> ConverterType3D;
typedef itk::VTKImageToImageFilter<ImageType3D> ConverterReverseType3D;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    dicomwrite *dicom;
    explicit MainWindow(QWidget *parent = 0);
    QString fanselect;
    unsigned short *ExtBuffer;
    double ct_y_shift;
    int center_ct_y=0;
    int ct_count=0;


    ~MainWindow();

private slots:
    void on_loadVolume_clicked();

    void on_Transform3DGPU_clicked();

    void on_Tranform_ITK_clicked();

    void on_Reset_clicked();

    void on_generateVolume_clicked();

    void on_GPU_Transform3D_clicked();

private:
    Ui::MainWindow *ui;

    QString fileName;


    gdcmIO::Pointer imgIO = NULL;


    TransformType3D::Pointer transform3D= NULL;

    TransformType3D::ParametersType parameters3D=NULL;

    ResampleFilterType3D::Pointer resampler3D=NULL;


    SeriesReaderType::Pointer seriesReader=NULL;

    CastImageFilterType3D::Pointer caster3D = NULL;
    ReverseCastImageFilterType3D::Pointer revCaster3D=NULL;

    LinearInteroplatorType::Pointer interpolator3D = NULL;



    ImageType3D::Pointer  fixedImage3D  = NULL;
    ImageType3Df::Pointer fixedImage3Df = NULL;
    ImageType3Df::Pointer fixedImage3Df2 = NULL;

    ImageType3Df::Pointer movingImage3Df = NULL;
    ImageType3Df::Pointer movingImage3Df2 = NULL;


    ConverterType3D::Pointer converter3D =NULL;
    ConverterReverseType3D::Pointer revConverter3D =NULL;


    vtkSmartPointer<vtkDICOMReader> CTReader;
    vtkSmartPointer<vtkDICOMReader> CTReader_1;
    CastImageFilterType3D::Pointer caster3D_1 = NULL;
    ConverterReverseType3D::Pointer revConverter3D_1 =NULL;
    ImageType3D::Pointer  fixedImage3D_1  = NULL;
    ImageType3Df::Pointer fixedImage3Df_1 = NULL;
    ImageType3Df::Pointer fixedImage3Df2_1 = NULL;

    ImageType3Df::Pointer movingImage3Df_1 = NULL;
    ImageType3Df::Pointer movingImage3Df2_1 = NULL;


    ConverterType3D::Pointer converter3D_1 =NULL;




    float* dispVolume=NULL;
    float* dispVolume_1=NULL;


    float upperThreshold;
    float lowerThreshold;

    unsigned char *charImg = NULL;
    QImage image = NULL;



   /*3D variables*/
    int   size3D[3];
    float spacing3D[3];
    float origin3D[3];
    float outputorigin3D[3];

    int   size3D_1[3];
    float spacing3D_1[3];
    float origin3D_1[3];
    float outputorigin3D_1[3];


    /*vtk display*/
    vtkImageImport* volumeImport=NULL;
    QVTKWidget          *vtkWidget=NULL;
    vtkRenderer         *ren=NULL;
    vtkColorTransferFunction *colorFunc=NULL;
    vtkPiecewiseFunction *alphaChannelFunc=NULL;


    unsigned int volumeCount;

    void DisplayVolume(float *mergedBufferVolume);

    void getAxialSlice(float *vol, int value);
    void getFrontalSlice(float *vol, int value);
    void getSagitalSlice(float *vol, int value);
    void dicomWrite(QString filepath);
    void loadVTKVolume();
    void loadVolume();
    void m_resampleCtData();
    int FanSelection=0;
//    bool readTags(const QString vFileName);
//    QList<DicomTagElements> *tagList;



};



#endif // MAINWINDOW_H
