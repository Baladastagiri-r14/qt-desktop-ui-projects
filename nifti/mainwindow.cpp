#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vtkSmartPointer.h>
#include <vtkDICOMMetaData.h>
#include <vtkDICOMWriter.h>
#include <vtkNIFTIImageReader.h>
#include <vtkImageReslice.h>
#include <vtkImageData.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>
#include <QDebug>
#include <iostream>
#include <sys/stat.h>
#include <sstream>
#include <vtkImageCast.h>
#include <thread>
#include <vtkExtractVOI.h>
#include <vtkImageExtractComponents.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageImport.h>


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
    vtkSmartPointer<vtkNIFTIImageReader> niftiReader = vtkSmartPointer<vtkNIFTIImageReader>::New();
    niftiReader->SetFileName("D:\\New folder\\Fov_trimmed.nii");
    niftiReader->Update();

    vtkSmartPointer<vtkDICOMWriter> writer = vtkSmartPointer<vtkDICOMWriter>::New();
    vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
    reslice->SetInputData(niftiReader->GetOutput());
//    reslice->Update();


    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();

//    reslice->Update();

//    writer->SetInputConnection(reslice->GetOutputPort());

    int numSlices = niftiReader->GetOutput()->GetDimensions()[2];
    qDebug()<< "constructor Imageviewer"<<numSlices;
    for (int sliceIdx = 0; sliceIdx < numSlices; sliceIdx++)
    {

        double sliceNormal[3] = {0, 0, 1};
        double origin[3] = {0, 0, sliceIdx};
        vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
        transform->Identity();
        transform->Translate(origin);
        transform->RotateX(90.0);
        transform->GetMatrix(matrix);
        transform->Update();
        reslice->SetResliceTransform(transform);
        reslice->Update();

        writer->SetInputConnection(reslice->GetOutputPort());


        const char* outputDirectory = "D:\\New folder";
        std::stringstream filenameStream;
        filenameStream << outputDirectory << "/slice_" << std::setfill('0') << std::setw(4) << sliceIdx << ".dcm";
        std::string filename = filenameStream.str();
        writer->SetFileName(filename.c_str());

//        writer->SetFilePrefix("Dicomimage");
//        writer->SetFilePattern("%s.dcm");
//        writer->Update();


        qDebug()<< "constructor Imageviewer2"<<filename.c_str();


        //        vtkSmartPointer<vtkImageData> imageData = reslice->GetOutput();
        //        if (!imageData)
        //        {
        //            std::cerr << "No valid image data." << std::endl;
        //        }
        //        int x = 120;  // Replace with the desired X coordinate
        //        int y = 125;  // Replace with the desired Y coordinate
        ////        int sliceIdx = 425;  // Replace with the desired slice index
        //        double pixelValue = imageData->GetScalarComponentAsDouble(x, y, sliceIdx, 0);
        //        std::cout << "  slice " << sliceIdx << ": "<<pixelValue << std::endl;


        try {
//            writer->UpdateDataObject();
//            writer->Update();
            qDebug()<< "constructor Imageviewer2";
        } catch (...) {
            qDebug()<< "constructor Imageviewer3";

        }

//        writer->Write();
//        writer->WriteFile(reslice->GetOutput());


    }
}

void MainWindow::on_pushButton_2_clicked()
{
    vtkNIFTIImageReader* reader = vtkNIFTIImageReader::New();
    reader->SetFileName("D:\\New folder\\Fov_trimmed.nii");
    reader->Update();

    vtkImageData* niftiImage = reader->GetOutput();

    // Get the dimensions of the NIfTI image
    int* dims = niftiImage->GetDimensions();
    int numSlices = dims[2];

    qDebug()<< "constructor Imageviewer"<<numSlices;
    for (int sliceIdx = 0; sliceIdx < numSlices; sliceIdx++) {
            // Create an ExtractVOI filter for each slice
            vtkSmartPointer<vtkExtractVOI> extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
            extractVOI->SetInputData(niftiImage);
            extractVOI->SetVOI(0, dims[0] - 1, 0, dims[1] - 1, sliceIdx, sliceIdx); // Specify the slice to extract
            extractVOI->Update();

            vtkSmartPointer<vtkDICOMWriter> dicomWriter = vtkSmartPointer<vtkDICOMWriter>::New();

            // Save the slice as DICOM
            dicomWriter->SetInputConnection(extractVOI->GetOutputPort());

            const char* outputDirectory = "D:\\New folder";
            std::stringstream filenameStream;
            filenameStream << outputDirectory << "\\slice_" << std::setfill('0') << std::setw(4) << sliceIdx << ".dcm";
            std::string filename = filenameStream.str();
            dicomWriter->SetFileName(filename.c_str());
            qDebug() <<filename.c_str();
            try {
                dicomWriter->Write();
                qDebug() << "Slice " << sliceIdx << " saved as DICOM.";
                dicomWriter->SetInputConnection(nullptr);
                dicomWriter->SetFileName(nullptr);
            }
            catch (...) {
                // Handle any exceptions that may be thrown during DICOM writing.
                qDebug() << "Error writing DICOM: " ;
            }
        }
        qDebug()<< "constructor";


//        dicomWriter->Delete();
//        extractVOI->Delete();


}


