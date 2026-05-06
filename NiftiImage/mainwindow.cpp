#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <itkImageSeriesReader.h>
#include <QVector>
#include "itkImageFileReader.h"
#include "itkImage.h"
#include "itkNiftiImageIO.h"
#include "itkImageIOFactory.h"
#include <itkImageRegionIterator.h>
#include "itkImageFileWriter.h"
#include "itkExtractImageFilter.h"
#include <itkCastImageFilter.h>
#include "itkImageSeriesWriter.h"
#include <map>
#include <itkImageToVTKImageFilter.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageCast.h>
#include <vtkXMLImageDataWriter.h>
#include <QDebug>
#include "Dicomwrite.h"
#include <QDebug>
#include <QtXml/qdom.h>
#include <QXmlStreamReader>
#include <QFile>
#include "gdcmUIDGenerator.h"
#include <mutex>

#include "vtkDICOMCTGenerator.h"



std::mutex writer1Mutex;

extern QString Position;
QList<DicomTagElements> tagList;
//vtkImageImport *volume;
//int* dim;
//short *v;
//unsigned short *v1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString path = "D:\\dastagiri\\NiftiImage\\ITKImages\\ConvertedDICOM";
   dicomWrite1(path);

}



bool MainWindow::readTags(const QString vFileName)
{
       qDebug()<<"i am crashing";
        QDomDocument xmlBOM;
    //    if(!tagList){
    //        tagList=new QList<DicomTagElements>;
    //    }
        QFile file(vFileName);
        qDebug()<<"i am crashing"<<vFileName;

        if (!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug()<<"File not open";
            return false;
        }
        // Set data into the QDomDocument before processing
        xmlBOM.setContent(&file);
        file.close();
        qDebug()<<"File closed";

        // Read the root tag
        // Extract the root markup
        QDomElement root=xmlBOM.documentElement();
        // Read data
        QDomElement FirstNodeTag = root.firstChildElement();
        FirstNodeTag = FirstNodeTag.nextSibling().toElement();
        // Get the first child of the component
        QDomElement Component=FirstNodeTag.firstChildElement();
        //    DicomTagElements *curTag=new DicomTagElements;
        // Loop while there is a child

        qDebug()<<"before while!!!"<<Component.isNull()<<Component.tagName();


        while(!Component.isNull()){
            // Check if the child tag name is COMPONENT
            if (Component.tagName()=="header"){
                DicomTagElements *curTag=new DicomTagElements;

                // Read and append the component Group
                curTag->Group=Component.attribute("Group","No Group").toInt(0,16);
                curTag->Element=Component.attribute("Elem","No Elem").toInt(0,16);
                curTag->No=Component.attribute("No","No No").toInt(0,10);
                curTag->VRKey=Component.attribute("VRKey","No VRKey").toStdString();
                curTag->Data=Component.firstChild().toText().data().toStdString();

                tagList.append(*curTag);  //*curTag

                delete curTag;

            }

            // Next component
            Component = Component.nextSiblingElement();
        }
        return true;
    }

void MainWindow::dicomWrite1(QString filepath)
{
    qDebug()<<"Entering writer::"<<filepath;



    vtkSmartPointer <vtkDICOMCTGenerator> generator;
    generator =vtkSmartPointer <vtkDICOMCTGenerator>::New();
    vtkSmartPointer<vtkMatrix4x4> m = vtkSmartPointer<vtkMatrix4x4>::New();
    m->SetElement(0,0,1);
    m->SetElement(0,1,0);
    m->SetElement(0,2,0);
    m->SetElement(0,3,0);
    m->SetElement(1,0,0);
    m->SetElement(1,1,1);
    m->SetElement(1,2,0);
    m->SetElement(1,3,0);
    m->SetElement(2,0,0);
    m->SetElement(2,1,0);
    m->SetElement(2,2,1);
    m->SetElement(2,3,0);
    m->SetElement(3,0,0);
    m->SetElement(3,1,0);
    m->SetElement(3,2,0);
    m->SetElement(3,3,1);
    // Plug the generator and meta data into the writer.
    vtkSmartPointer <vtkDICOMWriter> writer =vtkSmartPointer <vtkDICOMWriter>:: New ();
    //volume->SetDataScalarTypeToShort();

    typedef short PixelType;
    typedef float PixelTypef;
    typedef itk::Image<PixelType,3> ImageType3D;



    using ImageType = itk::Image<PixelType, 3>;
    using ReaderType = itk::ImageFileReader<ImageType>;

    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName("D:\\dastagiri\\NiftiImage\\ITKImages\\ConvertedDICOM\\Normalized_dicom\\output_resampled.nii");
    typedef itk::NiftiImageIO imageIOg;
    imageIOg::Pointer niiio = imageIOg::New();
    reader->SetImageIO(niiio);

    try
    {
        reader->Update();
        qDebug() << "File has been read sucssesfully";
    }
    catch(...)
    {
        qDebug() << "File has not been read sucssesfully";
    }

    ImageType::Pointer inputImage = reader->GetOutput();

    // Convert the output image to vtkImageData
    using ConverterType = itk::ImageToVTKImageFilter<ImageType>;
    ConverterType::Pointer converter = ConverterType::New();
    converter->SetInput(inputImage);
    converter->Update();

    // Get the converted vtkImageData
    vtkImageData* vtkImage = converter->GetOutput();

    writer -> SetInputData(/*converter3D->GetOutput()*/vtkImage);
    writer->SetMemoryRowOrderToFileNative();
    writer -> SetGenerator (generator);
    writer -> SetFilePattern ("%s/slice -%04.4d.dcm");//pattern is fixed.
    writer -> SetFilePrefix (filepath.toStdString().c_str());
    writer->SetPatientMatrix(m);
    qDebug() << " Write the file.";
    try
    {
        writer ->Write ();
        qDebug() << "File has been written sucssesfully";
    }
    catch(std::exception &e)
    {
        qDebug() << "File has not been written sucssesfully",e;
    }


}
