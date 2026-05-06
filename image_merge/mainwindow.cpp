#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QCoreApplication>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>
#include <itkPasteImageFilter.h>
#include "itkAddImageFilter.h"
#include "itkRawImageIO.h"
#include "itkComposeImageFilter.h"
#include <iostream>

#include <itkRegionOfInterestImageFilter.h>
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


    QString inputImage1 = "D:\\dastagiri\\Rawimage\\proj_1.raw";
    QString inputImage2 ="D:\\dastagiri\\Rawimage\\proj_2.raw";
    QString outputImage = "D:\\dastagiri\\Rawimage\\combinedImage.raw";
    int width = 3072;
    int height = 3072;
    int height1 =6144;


    addImagesRowWise(inputImage1, inputImage2, outputImage, width, height, height1);
}

void MainWindow::addImagesRowWise(const QString &inputImage1, const QString &inputImage2, const QString &outputImage, int width, int height,int height1)
{
    QFile file1(inputImage1);
    QFile file2(inputImage2);

    if (!file1.open(QIODevice::ReadOnly) || !file2.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening input files";
        return;
    }

    // Create output file for the result image
    QFile outputFile(outputImage);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening output file";
        return;
    }

    // Create QDataStream to read and write binary data
    QDataStream in1(&file1);
    QDataStream in2(&file2);
    QDataStream out(&outputFile);

    in1.setByteOrder(QDataStream::LittleEndian);
    in2.setByteOrder(QDataStream::LittleEndian);
    out.setByteOrder(QDataStream::LittleEndian);

    // Set the data type to 16-bit unsigned short
    in1.setVersion(QDataStream::Qt_5_0);
    in2.setVersion(QDataStream::Qt_5_0);
    out.setVersion(QDataStream::Qt_5_0);



    for (int y = 0; y < height1 / 2; ++y) {
            for (int x = 0; x < width; ++x) {
                quint16 pixel;
                in1 >> pixel;

                // Write the pixel to the output file
                out << pixel;
            }
        }

        // Loop through each row of the second image and write to the output file
        for (int y = 0; y < height1 / 2; ++y) {
            for (int x = 0; x < width; ++x) {
                quint16 pixel;
                in2 >> pixel;

                // Write the pixel to the output file
                out << pixel;
            }
        }

        qDebug() << "Image concatenation complete.";
        QString croppedImage = "D:\\dastagiri\\Rawimage\\croppedImage.raw";
        int cropheight = (height1-(height/2));
        cropImage(outputImage, croppedImage, width, height, 0, 0, width, cropheight );


}

void MainWindow::cropImage(const QString &outputImage, const QString &croppedImage, int width, int height, int x, int y, int cropWidth, int cropHeight)
{
    QFile inputFile(outputImage);
    QFile outputFile(croppedImage);

    if (!inputFile.open(QIODevice::ReadOnly) || !outputFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening input/output files for cropping";
        return;
    }

    QDataStream in(&inputFile);
    QDataStream out(&outputFile);

    // Set the byte order to little-endian
    in.setByteOrder(QDataStream::LittleEndian);
    out.setByteOrder(QDataStream::LittleEndian);

    // Set the data type to 16-bit unsigned short
    in.setVersion(QDataStream::Qt_5_0);
    out.setVersion(QDataStream::Qt_5_0);

    // Position the input stream to the start of the crop region
    inputFile.seek(x * sizeof(quint16) + y * width * sizeof(quint16));

    // Loop through each row and column of the crop region
    for (int cropY = height/2; cropY < cropHeight; ++cropY) {
        for (int cropX = 0; cropX < cropWidth; ++cropX) {
            quint16 pixel;
            in >> pixel;

            // Write the pixel to the output file
            out << pixel;
        }

        // Move the input stream position to the start of the next row in the original image
        inputFile.seek((x + cropWidth) * sizeof(quint16) + (y + cropY + 1) * width * sizeof(quint16));
    }

    qDebug() << "Image cropping complete.";
}


void MainWindow::mergeRawImages(const char *inputRawImage1, const char *inputRawImage2, const char *outputRawImage, unsigned int width, unsigned int height, unsigned int height1)
{
    using PixelType = unsigned short;
    const unsigned int Dimension = 2;
    using ImageType = itk::Image<PixelType, Dimension>;

    // Read raw data from the first image
    FILE* file1 = fopen(inputRawImage1, "rb");
    if (!file1)
    {
        return;
    }
    std::vector<PixelType> buffer1(width * height);
    fread(buffer1.data(), sizeof(PixelType), width * height, file1);
    fclose(file1);

    // Read raw data from the second image
    FILE* file2 = fopen(inputRawImage2, "rb");
    if (!file2)
    {
        return;
    }

    std::vector<PixelType> buffer2(width * height);
    fread(buffer2.data(), sizeof(PixelType), width * height, file2);
    fclose(file2);

    ImageType::Pointer image1 = ImageType::New();
    ImageType::RegionType region1;
    ImageType::IndexType start1;
    start1.Fill(0);
    region1.SetIndex(start1);

    ImageType::SizeType size1;
    size1[0] = width;
    size1[1] = height;
    region1.SetSize(size1);

    image1->SetRegions(region1);
    image1->SetBufferedRegion(region1);
    image1->SetLargestPossibleRegion(region1);
    image1->Allocate();
    std::copy(buffer1.begin(), buffer1.end(), image1->GetBufferPointer());

    ImageType::Pointer image2 = ImageType::New();
    ImageType::RegionType region2;
    ImageType::IndexType start2;
    start2.Fill(0);
    region2.SetIndex(start2);

    ImageType::SizeType size2;
    size2[0] = width;
    size2[1] = height;
    region2.SetSize(size2);

    image2->SetRegions(region2);
    image2->SetBufferedRegion(region2);
    image2->SetLargestPossibleRegion(region2);
    image2->Allocate();
    std::copy(buffer2.begin(), buffer2.end(), image2->GetBufferPointer());


    ImageType::Pointer mergedImage = ImageType::New();

    ImageType::RegionType mergedRegion;
    ImageType::IndexType start;
    start.Fill(0);
    mergedRegion.SetIndex(start);

    ImageType::SizeType size;
    size[0] = width;
    size[1] = height1;
    mergedRegion.SetSize(size);

    mergedImage->SetRegions(mergedRegion);
    mergedImage->SetBufferedRegion(mergedRegion);
    mergedImage->SetLargestPossibleRegion(mergedRegion);
    mergedImage->Allocate();

    itk::ImageRegionConstIterator<ImageType> iterator1(image1, region1);
    itk::ImageRegionIterator<ImageType> iteratorMerged(mergedImage, mergedRegion);

    while (!iterator1.IsAtEnd())
    {
        iteratorMerged.Set(iterator1.Get());
        ++iterator1;
        ++iteratorMerged;
    }

    itk::ImageRegionConstIterator<ImageType> iterator2(image2, region2);
    while (!iterator2.IsAtEnd())
    {
        iteratorMerged.Set(iterator2.Get());
        ++iterator2;
        ++iteratorMerged;
    }
    qDebug() << "Save the merged image to a raw file";
    FILE* outputFile = fopen(outputRawImage, "wb");
    if (!outputFile)
    {
        return;
    }


    fwrite(mergedImage->GetBufferPointer(), sizeof(PixelType), width * height1, outputFile);
    fclose(outputFile);
    qDebug() << "Image Save complete.";

    const char* outputRawImage1 = "D:\\dastagiri\\Rawimage\\proj_mreged_crop.raw";
    unsigned int cropX = 0;
    unsigned int cropY = (height/2);
    unsigned int cropWidth = 3072;
    unsigned int cropHeight = 3072;

    cropMergedImage(outputRawImage, outputRawImage1, width, height1, cropX, cropY, cropWidth, cropHeight);


}

void MainWindow::cropMergedImage(const char *outputRawImage, const char *outputRawImage1, unsigned int width, unsigned int height1, unsigned int cropX, unsigned int cropY, unsigned int cropWidth, unsigned int cropHeight)
{
    using PixelType = unsigned short;
    const unsigned int Dimension = 2;
    using ImageType = itk::Image<PixelType, Dimension>;

    qDebug() << " enterd Image Save cropMergedImage";
    // Read raw data from the merged image
    FILE* inputFile = fopen(outputRawImage, "rb");
    if (!inputFile)
    {
        // Handle error
        return;
    }

    std::vector<PixelType> buffer(width * height1);
    fread(buffer.data(), sizeof(PixelType), width * height1, inputFile);
    fclose(inputFile);

    // Create an ITK image from the raw data
    ImageType::Pointer mergedImage = ImageType::New();
    ImageType::RegionType region;
    ImageType::IndexType start;
    start.Fill(0);
    region.SetIndex(start);

    ImageType::SizeType size;
    size[0] = width;
    size[1] = height1;
    region.SetSize(size);

    mergedImage->SetRegions(region);
    mergedImage->SetBufferedRegion(region);
    mergedImage->SetLargestPossibleRegion(region);
    mergedImage->Allocate();
    std::copy(buffer.begin(), buffer.end(), mergedImage->GetBufferPointer());

    // Define the cropping region
    ImageType::IndexType cropStart;
    cropStart[0] = cropX;
    cropStart[1] = cropY;

    ImageType::SizeType cropSize;
    cropSize[0] = cropWidth;
    cropSize[1] = cropHeight;

    ImageType::RegionType cropRegion;
    cropRegion.SetIndex(cropStart);
    cropRegion.SetSize(cropSize);

    // Create a region of interest filter
    using ROIFilterType = itk::RegionOfInterestImageFilter<ImageType, ImageType>;
    ROIFilterType::Pointer roiFilter = ROIFilterType::New();
    roiFilter->SetInput(mergedImage);
    roiFilter->SetRegionOfInterest(cropRegion);
    roiFilter->Update();

    // Save the cropped image to a raw file
    FILE* outputFile = fopen(outputRawImage1, "wb");
    if (!outputFile)
    {
        // Handle error
        return;
    }

    fwrite(roiFilter->GetOutput()->GetBufferPointer(), sizeof(PixelType), cropWidth * cropHeight, outputFile);
    fclose(outputFile);
    qDebug() << " end Image Save cropMergedImage";
}

void MainWindow::addImages(const QString &inputImage11, const QString &inputImage22, QString &inputImage13, QString &inputImage24, const QString &outputImage, int width, int height, int height1, int width1)
{

      unsigned short *imagein1 = new unsigned short[width*height];
      unsigned short *imagein2 = new unsigned short[width*height];
      unsigned short *imagein3 = new unsigned short[width*height];
      unsigned short *imagein4 = new unsigned short[width*height];


      FILE* Fp_in1;
      fopen_s(&Fp_in1, "D:\\dastagiri\\Rawimage\\proj_1.raw", "rb+");
      fread(imagein1, sizeof(unsigned short), width * height, Fp_in1);
      fclose(Fp_in1);

      FILE* Fp_in2;
      fopen_s(&Fp_in2, "D:\\dastagiri\\Rawimage\\proj_2.raw", "rb+");
      fread(imagein2, sizeof(unsigned short), width * height, Fp_in2);
      fclose(Fp_in2);

      FILE* Fp_in3;
      fopen_s(&Fp_in3, "D:\\dastagiri\\Rawimage\\proj_3.raw", "rb+");
      fread(imagein3, sizeof(unsigned short), width * height, Fp_in3);
      fclose(Fp_in3);

      FILE* Fp_in4;
      fopen_s(&Fp_in4, "D:\\dastagiri\\Rawimage\\proj_4.raw", "rb+");
      fread(imagein4, sizeof(unsigned short), width * height, Fp_in4);
      fclose(Fp_in4);

    qDebug() << "Image addition 1";
      unsigned short **one_img = new unsigned short*[height];

      for (int i = 0; i < height; i++)
          one_img[i] = new unsigned short[width];
        int p = 0;

       for (int i = 0; i < height; i++)
       {
            for (int j = 0; j < width ; j++)
           {
              one_img[i][j] = imagein1[p];
              p = p + 1;
           }
       }
    qDebug() << "Image addition2 ";

       unsigned short **two_img = new unsigned short*[height];

       for (int i = 0; i < height; i++)
           two_img[i] = new unsigned short[width];
         int p1 = 0;

        for (int i = 0; i < height; i++)
        {
             for (int j = 0; j < width ; j++)
            {
               two_img[i][j] = imagein2[p1];
               p1 = p1 + 1;
            }
        }

        qDebug() << "Image addition 3";

        unsigned short **three_img = new unsigned short*[height];

        for (int i = 0; i < height; i++)
            three_img[i] = new unsigned short[width];
          int p2 = 0;

         for (int i = 0; i < height; i++)
         {
              for (int j = 0; j < width ; j++)
             {
                three_img[i][j] = imagein3[p2];
                p2 = p2 + 1;
             }
         }

         qDebug() << "Image addition 4";

         unsigned short **four_img = new unsigned short*[height];

         for (int i = 0; i < height; i++)
             four_img[i] = new unsigned short[width];
           int p3 = 0;
           int m=0;int n=0;

          for (int i = 0; i < height; i++)
          {
               for (int j = 0; j < width ; j++)
              {
                 four_img[i][j] = imagein4[p3];
                 p3 = p3 + 1;
              }
          }
          qDebug() << "Image addition5 ";


          unsigned short **Fin_img = new unsigned short*[height1];

          for (int i = 0; i < height1; i++)
              Fin_img[i] = new unsigned short[width1];


            for (int i = 0; i < height; i++)
            {
                 for (int j = 0; j < width ; j++)
                {
                   Fin_img[i][j] = one_img[i][j];
                }
            }
            qDebug() << "Image addition6 ";


            for (int i = 0; i < height; i++)
            {
                 for (int j = width; j < width1 ; j++)
                {
//                   qDebug()<<i<<j<<m<<n;
                   Fin_img[i][j] = two_img[m][n];
                   n=n+1;
                   if(n==3072)
                   {
                       n=0;
                   }

                }
                m=m+1;
                if(m==3072)
                {
                    m=0;
                }
            }
            m=0;
            n=0;

            qDebug() << "Image addition7 ";

            for (int i = height; i < height1; i++)
            {
                 for (int j = 0; j < width ; j++)
                {
                   Fin_img[i][j] = three_img[m][n];
                   n=n+1;
                   if(n==3072)
                   {
                       n=0;
                   }
                }
                 m=m+1;
                 if(m==3072)
                 {
                     m=0;
                 }
            }
            qDebug() << "Image addition8 ";
            m=0;
            n=0;

            for (int i = height; i < height1; i++)
            {
                 for (int j = width; j < width1 ; j++)
                {
                   Fin_img[i][j] = four_img[m][n];
                   n=n+1;
                   if(n==3072)
                   {
                       n=0;
                   }
                }
                m=m+1;
                if(m==3072)
                {
                    m=0;
                }
            }
            m=0;
            n=0;
            qDebug() << "Image addition9";
            unsigned short *Fin_img_buffer = new unsigned short[width1*height1];     // Conversion of 2_Dimension to 1_Dimension_________________________
            for(int i=0;i<height1;i++)
            {
                for(int j=0;j<width1;j++)
                {
                    Fin_img_buffer[i*width1+j]=Fin_img[i][j];
                }
            }

            FILE* Fp831_cropped;
            fopen_s(&Fp831_cropped, "D:\\dastagiri\\Rawimage\\Inputimg_cropped.raw", "wb+");
            fwrite(Fin_img_buffer, sizeof(unsigned short), width1 * height1, Fp831_cropped);

            fclose(Fp831_cropped);
            qDebug() << "Image addition complete.";

            const char* outputImage = "D:\\dastagiri\\Rawimage\\Inputimg_cropped.raw";
            const char* outputRawImage1 = "D:\\dastagiri\\Rawimage\\proj_mreged_crop.raw";
            unsigned int cropX = (width/2);
            unsigned int cropY = (height/2);
            unsigned int cropWidth = 3072;
            unsigned int cropHeight = 3072;

            cropMergedImage1(outputImage, outputRawImage1, width1, height1, cropX, cropY, cropWidth, cropHeight);


}


void MainWindow::cropMergedImage1(const char *outputRawImage, const char *outputRawImage1, unsigned int width1, unsigned int height1, unsigned int cropX, unsigned int cropY, unsigned int cropWidth, unsigned int cropHeight)
{
    using PixelType = unsigned short;
    const unsigned int Dimension = 2;
    using ImageType = itk::Image<PixelType, Dimension>;

    qDebug() << " enterd Image Save cropMergedImage";
    // Read raw data from the merged image
    FILE* inputFile = fopen(outputRawImage, "rb");
    if (!inputFile)
    {
        // Handle error
        return;
    }

    std::vector<PixelType> buffer(width1 * height1);
    fread(buffer.data(), sizeof(PixelType), width1 * height1, inputFile);
    fclose(inputFile);

    // Create an ITK image from the raw data
    ImageType::Pointer mergedImage = ImageType::New();
    ImageType::RegionType region;
    ImageType::IndexType start;
    start.Fill(0);
    region.SetIndex(start);

    ImageType::SizeType size;
    size[0] = width1;
    size[1] = height1;
    region.SetSize(size);

    mergedImage->SetRegions(region);
    mergedImage->SetBufferedRegion(region);
    mergedImage->SetLargestPossibleRegion(region);
    mergedImage->Allocate();
    std::copy(buffer.begin(), buffer.end(), mergedImage->GetBufferPointer());

    // Define the cropping region
    ImageType::IndexType cropStart;
    cropStart[0] = cropX;
    cropStart[1] = cropY;

    ImageType::SizeType cropSize;
    cropSize[0] = cropWidth;
    cropSize[1] = cropHeight;

    ImageType::RegionType cropRegion;
    cropRegion.SetIndex(cropStart);
    cropRegion.SetSize(cropSize);

    // Create a region of interest filter
    using ROIFilterType = itk::RegionOfInterestImageFilter<ImageType, ImageType>;
    ROIFilterType::Pointer roiFilter = ROIFilterType::New();
    roiFilter->SetInput(mergedImage);
    roiFilter->SetRegionOfInterest(cropRegion);
    roiFilter->Update();

    // Save the cropped image to a raw file
    FILE* outputFile = fopen(outputRawImage1, "wb");
    if (!outputFile)
    {
        // Handle error
        return;
    }

    fwrite(roiFilter->GetOutput()->GetBufferPointer(), sizeof(PixelType), cropWidth * cropHeight, outputFile);
    fclose(outputFile);
    qDebug() << " end Image Save cropMergedImage";
}


void MainWindow::on_pushButton_2_clicked()
{

    const char* inputRawImage1 = "D:\\dastagiri\\Rawimage\\proj_1.raw";
    const char* inputRawImage2 = "D:\\dastagiri\\Rawimage\\proj_2.raw";
    const char* outputRawImage = "D:\\dastagiri\\Rawimage\\proj_mreged.raw";
    unsigned int width = 3072;
    unsigned int height = 3072;
    unsigned int height1 = 6144;

    mergeRawImages(inputRawImage1, inputRawImage2, outputRawImage, width, height, height1);


}

void MainWindow::on_pushButton_3_clicked()
{

    QString inputImage11 = "D:\\dastagiri\\Rawimage\\proj_1.raw";
    QString inputImage22 ="D:\\dastagiri\\Rawimage\\proj_2.raw";
    QString inputImage13 = "D:\\dastagiri\\Rawimage\\proj_4.raw";
    QString inputImage24 ="D:\\dastagiri\\Rawimage\\proj_3.raw";

    QString outputImage = "D:\\dastagiri\\Rawimage\\combinedImage.raw";
    int width = 3072;
    int height = 3072;
    int height1 =6144;
    int width1 =6144;


    addImages(inputImage11, inputImage22, inputImage13,inputImage24,outputImage, width, height, height1,width1);
}
