#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <gdcmUIDGenerator.h>
#include <itkCommand.h>
#include "itkImageFileWriter.h"
#include <itkGDCMImageIO.h>
#include "itkMetaDataObject.h"
#include <itkMetaDataDictionary.h>
#include "itkImportImageFilter.h"
#include "itkImage.h"
#include "itkImportImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"


typedef itk::Image< unsigned short , 2>    ImageType;
typedef itk::ImageFileReader< ImageType >  ReaderType1;
typedef itk::ImageFileWriter< ImageType >  WriterType;
//    typedef itk::GDCMImageIO ImageIO;
typedef itk::GDCMImageIO  ImageIOType;
typedef itk::ImportImageFilter<unsigned short , 2>ImportFilterType;


ImportFilterType::Pointer importFilter = ImportFilterType::New();
itk::GDCMImageIO::Pointer dicomIO = itk::GDCMImageIO::New();
//    ImageIOType::Pointer gdcmImageIO = ImageIOType::New();
WriterType::Pointer writer = WriterType::New();
//    ReaderType::Pointer reader = ReaderType::New();
//    ImageType::ConstPointer image;
ImageType::Pointer image;
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

void MainWindow::on_PB_load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* image=new unsigned short[w*h];
    fread(image,1,w*h*sizeof(unsigned short),Img);
    unsigned short* buffer=new unsigned short[w*h];
//    unsigned short* flippedImage = new unsigned short[w*h];
//    for (int y = 0; y < h; y++)
//    for (int x = 0; x < w; x++)
//    {
//        flippedImage[x+(y*w)]=image[((w-1)-x)+(y*w)];
//        flippedImage[((w-1)-x)+(y*w)]=image[x+(y*w)];
//    }
//    memcpy(image,flippedImage,w*h*sizeof(unsigned short));
//    delete[] (unsigned short*) (flippedImage);


//    FILE* Fp8001_flipped;
//    fopen_s(&Fp8001_flipped, "D:\\Flipped.raw", "wb+");
//    fwrite(/*TeledyneDetector::radMammobuf*/image, sizeof(unsigned short), w * h, Fp8001_flipped);
//    fclose(Fp8001_flipped);

    buffer=image;
    qDebug()<<"Buff"<<buffer[1];

    ImportFilterType::SizeType  size;
    size[0] = w;  // size along X
    size[1] = h;  // size along Y
    ImportFilterType::IndexType start;
    start.Fill(0);
    ImportFilterType::RegionType region;
    region.SetIndex(start);
    region.SetSize(size);
    importFilter->SetRegion(region);
    const itk::SpacePrecisionType origin[2] = { 0.0, 0.0 };
    importFilter->SetOrigin(origin);
    const itk::SpacePrecisionType  spacing[2] = { 1.0, 1.0 };
    importFilter->SetSpacing(spacing);
    const bool importImageFilterWillOwnTheBuffer = false;

    importFilter->SetImportPointer(image,h*w,importImageFilterWillOwnTheBuffer);
    //    if(img.data)
    //    {
    //        streamOff <<"save image: CV image data is there"<<endl;
    //        img.convertTo(res,CV_16U,255);
    //        const bool importImageFilterWillOwnTheBuffer = false;
    //        importFilter->SetImportPointer((unsigned short*)res.data,width*height,importImageFilterWillOwnTheBuffer);
    //        importFilter->Update();
    //    }
    importFilter->Update();
    itk::MetaDataDictionary dict ;

    QString date=QString(QDate::currentDate().toString("yyyyMMdd"));
    QString time=QString(QTime::currentTime().toString("hhmmss.zzzzzzz"));

    itk::EncapsulateMetaData<std::string>(dict, "0008|0008", "ORIGINAL\\PRIMARY"); //imageType
    itk::EncapsulateMetaData<std::string>(dict, "0008|0020", date.toStdString().c_str()); // studyDate

    itk::EncapsulateMetaData<std::string>(dict, "0008|0022", date.toStdString().c_str());//acquisitionDate
    itk::EncapsulateMetaData<std::string>(dict, "0008|0023", date.toStdString().c_str());//contentDate

    itk::EncapsulateMetaData<std::string>(dict, "0008|002A", time.toStdString().c_str());//acquisitionDateTime
    itk::EncapsulateMetaData<std::string>(dict, "0008|0030", time.toStdString().c_str());//studtTime
    itk::EncapsulateMetaData<std::string>(dict, "0008|0033", time.toStdString().c_str());//contentTime

    itk::EncapsulateMetaData<std::string>(dict, "0008|0060", "MG");//modality
    itk::EncapsulateMetaData<std::string>(dict, "0008|0070", "Panacea Medical Technologies");//manufacturer
    itk::EncapsulateMetaData<std::string>(dict, "0008|0080", "BARC");//institutionName
    itk::EncapsulateMetaData<std::string>(dict, "0008|0081", "Mumbai");//institutionAddress

    itk::EncapsulateMetaData<std::string>(dict, "0008|0090", "DR.VENKAT");//referringPhysicianName

    itk::EncapsulateMetaData<std::string>(dict, "0008|1010", "PMH-AWS");//stationName
    itk::EncapsulateMetaData<std::string>(dict, "0008|1040", "Oncology");//institutionalDepartmentName

    itk::EncapsulateMetaData<std::string>(dict, "0008|1070", "user");//operatorsName

    itk::EncapsulateMetaData<std::string>(dict, "0008|1090", "LILAC");//manufacturerModelName
    itk::EncapsulateMetaData<std::string>(dict, "0010|0010", "R S Geetha");//PatName
    itk::EncapsulateMetaData<std::string>(dict, "0010|0020", "10/2382B");//PatientID
    itk::EncapsulateMetaData<std::string>(dict, "0010|1010", "51");//patientAge

    itk::EncapsulateMetaData<std::string>(dict, "0010|0040", "F");//PatientGender
    itk::EncapsulateMetaData<std::string>(dict, "0020|0020", "LMLO");//PatientView

    itk::EncapsulateMetaData<std::string>(dict, "0018|0015", "Breast");//BodyPartExamined
    itk::EncapsulateMetaData<std::string>(dict, "0018|0060", "29");//KVP
    itk::EncapsulateMetaData<std::string>(dict, "0018|1000", "1234");//DeviceSerialNum
    itk::EncapsulateMetaData<std::string>(dict, "0018|1020", "LILAC 7.0.6");//softwareVersion
    itk::EncapsulateMetaData<std::string>(dict, "0018|1110", "650");//distanceSourceToDetector
    itk::EncapsulateMetaData<std::string>(dict, "0018|1111", "645");//distanceSourceToPatient
    itk::EncapsulateMetaData<std::string>(dict, "0018|1114", "1");//Estimated Radiographic Magnification Factor
    itk::EncapsulateMetaData<std::string>(dict, "0018|1147", "Rectangle");//FieldOfViewShape
    itk::EncapsulateMetaData<std::string>(dict, "0018|1149", "229");//fieldOfViewDimensions

    itk::EncapsulateMetaData<std::string>(dict, "0018|1151", "110");//XrayTubeCurrent mA
    itk::EncapsulateMetaData<std::string>(dict, "0018|1150", "450");//Duration of X-Ray exposure in msec.

    itk::EncapsulateMetaData<std::string>(dict, "0018|1166", "NONE");//grid
    itk::EncapsulateMetaData<std::string>(dict, "0018|1191", "TUNGSTEN");//AnodeTargetMaterial //Tungsten
    itk::EncapsulateMetaData<std::string>(dict, "0018|11A0", "34");//bodypartthickness
    itk::EncapsulateMetaData<std::string>(dict, "0018|11A2", "198");//compressionForce
    itk::EncapsulateMetaData<std::string>(dict, "0018|1405", "62");//RelativeXRayExposure
    itk::EncapsulateMetaData<std::string>(dict, "0018|1508", "MAMMOGRAPHIC");//PositionType

    itk::EncapsulateMetaData<std::string>(dict, "0018|1510", "0");//positionerPrimaryAngle
//    if(TubeHeadCurrentPosition>0)
//        itk::EncapsulateMetaData<std::string>(dict, "0018|9559", "CW");//PositionerPrimaryAngleDirection
//    else
    itk::EncapsulateMetaData<std::string>(dict, "0018|9559", "CC");//PositionerPrimaryAngleDirection

    itk::EncapsulateMetaData<std::string>(dict, "0018|1530", "0");//DetectorPrimaryAngle
    itk::EncapsulateMetaData<std::string>(dict, "0018|1700", "RECTANGULAR"); //CollimatorShape
    itk::EncapsulateMetaData<std::string>(dict, "0018|1702", "0");//CollimatorLeftVerticalEdge
    itk::EncapsulateMetaData<std::string>(dict, "0018|1704", "0");//CollimatorRightVerticalEdge
    itk::EncapsulateMetaData<std::string>(dict, "0018|1706", "0");//CollimatorUpperHorizontalEdge
    itk::EncapsulateMetaData<std::string>(dict, "0018|1708", "0");//CollimatorLowerHorizontalEdge
    itk::EncapsulateMetaData<std::string>(dict, "0018|6000", "0.012931217");//Sensitivity
    itk::EncapsulateMetaData<std::string>(dict, "0018|7000", "YES");//detectorConditionsNominalFlag
    itk::EncapsulateMetaData<std::string>(dict, "0018|7001", "35.099998");//detectorTemperature
    itk::EncapsulateMetaData<std::string>(dict, "0018|7004", "SCINTILLATOR");//detectorType
    itk::EncapsulateMetaData<std::string>(dict, "0018|7005", "AREA");//detectorConfiguration
    itk::EncapsulateMetaData<std::string>(dict, "0018|700A", "PM21_04");//detectorId
    itk::EncapsulateMetaData<std::string>(dict, "0018|701A", "1");//detectorBinning
    itk::EncapsulateMetaData<std::string>(dict, "0018|7020", "192");//detectorElementPhysicalSize
    itk::EncapsulateMetaData<std::string>(dict, "0018|7022", "0.1");//detectorElementSpacing
    itk::EncapsulateMetaData<std::string>(dict, "0018|7024", "RECTANGLE");//detectorActiveShape
    itk::EncapsulateMetaData<std::string>(dict, "0018|7026", "192");//detectorActiveDimension
    itk::EncapsulateMetaData<std::string>(dict, "0018|7030", "5");//fieldOfViewOrigin
    itk::EncapsulateMetaData<std::string>(dict, "0018|7032", "0");//fieldOfViewRotation
    itk::EncapsulateMetaData<std::string>(dict, "0018|7034", "NO");//fieldOfViewHorizontalFlip
//    if(filter==1)
    itk::EncapsulateMetaData<std::string>(dict, "0018|7050", "ALUMINIUM");//FilterMaterial
//    else if(filter==2)
//        itk::EncapsulateMetaData<std::string>(dict, "0018|7050", "SILVER");
//    else if(filter==3)
//        itk::EncapsulateMetaData<std::string>(dict, "0018|7050", "MOLYBDENUM");
//    else if(filter==5)
//        itk::EncapsulateMetaData<std::string>(dict, "0018|7050", "RHODIUM");
//    else if(filter==4)
//        itk::EncapsulateMetaData<std::string>(dict, "0018|7050", "No Filter");//FilterMaterial
    itk::EncapsulateMetaData<std::string>(dict, "0018|9332", "20");//EposureInmAS
    itk::EncapsulateMetaData<std::string>(dict, "0020|000E", "1234");//seriesInstanceUID
    itk::EncapsulateMetaData<std::string>(dict, "0020|0010", "1");//studyId
    itk::EncapsulateMetaData<std::string>(dict, "0020|0011", "800");//SeriesNumber
    itk::EncapsulateMetaData<std::string>(dict, "0020|0013", "4");//InstanceNumber
    itk::EncapsulateMetaData<std::string>(dict, "0020|0020", "LMLO");//PatientOrientation

//    ImageLaterality;
//    if(!strcmp(ImageLaterality,"L"))
        itk::EncapsulateMetaData<std::string>(dict, "0020|0062", "L");//imageLaterality//Left
//    else if(!strcmp(ImageLaterality,"R"))
//        itk::EncapsulateMetaData<std::string>(dict, "0020|0062", "R");//imageLaterality//Right
//    else if(!strcmp(ImageLaterality,"B"))
//        itk::EncapsulateMetaData<std::string>(dict, "0020|0062", "B");//imageLaterality // Left&Right
//    else
//        itk::EncapsulateMetaData<std::string>(dict, "0020|0062", "U");//imageLaterality // Unpaired

    itk::EncapsulateMetaData<std::string>(dict, "0028|0002", "1");//samplesPerPixel
    itk::EncapsulateMetaData<std::string>(dict, "0028|0004", "NO");//photoMetricInterpretation
    itk::EncapsulateMetaData<std::string>(dict, "0028|0008", "1");//numberofFrames
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|0010", "Rows");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|0011", "Columns");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|0100", "BitsAllocated");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|0101", "BitsStored");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|0102", "HighBit");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|0103", "PixelRepresentation");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|0106", "SmallestImagePixelValue");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|0107", "LargestImagePixelValue");
    itk::EncapsulateMetaData<std::string>(dict, "0028|1050", "33000");//WindowCenter
    itk::EncapsulateMetaData<std::string>(dict, "0028|1051", "64000");//WindowWidth
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|1052", "RescaleIntercept");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|1053", "RescaleSlope");
    //    itk::EncapsulateMetaData<std::string>(dict, "0028|1054", "RescaleType");
    itk::EncapsulateMetaData<std::string>(dict, "0028|1055", "WINDOW1\WINDOW2");//WindowCenterWidthExplanation
    itk::EncapsulateMetaData<std::string>(dict, "0040|8302", "40.9");//EntranceDose
    itk::EncapsulateMetaData<std::string>(dict, "0040|0316", "0.0224");//AverageOrganDose
    itk::EncapsulateMetaData<std::string>(dict, "0040|0306", "648");//DistanceSourceToEntrance
    itk::EncapsulateMetaData<std::string>(dict, "0040|0310", "14%");//CommentsOnRadiationDose
    itk::EncapsulateMetaData<std::string>(dict, "300A|011E", "0");//GantryAngle
    //    itk::EncapsulateMetaData<std::string>(dict, "7FE0|0010", "PixelData");

    gdcm::UIDGenerator suid;
    std::string seriesUID = suid.Generate();
    gdcm::UIDGenerator fuid;
    std::string frameOfReferenceUID = fuid.Generate();
    gdcm::UIDGenerator sopuid;
    std::string sopInstanceUID = sopuid.Generate();

    itk::EncapsulateMetaData<std::string>(dict,"0020|000d", seriesUID);
    itk::EncapsulateMetaData<std::string>(dict,"0020|000e", frameOfReferenceUID);
    itk::EncapsulateMetaData<std::string>(dict,"0020|0052", seriesUID);//frame of reference
    itk::EncapsulateMetaData<std::string>(dict,"0008|0005", "ISO_IR 100");
    itk::EncapsulateMetaData<std::string>(dict,"0002|0003", sopInstanceUID);//sopInstanceUID
    itk::ExposeMetaData<std::string>(dict, "0008|0016", sopInstanceUID);
    itk::EncapsulateMetaData<std::string>(dict,"0008|0018", sopInstanceUID);//sopInstanceUID
    itk::EncapsulateMetaData<std::string>(dict, "0020|0052", seriesUID);
    itk::EncapsulateMetaData<std::string>(dict,"0008|1150", sopInstanceUID);
    itk::EncapsulateMetaData<std::string>(dict,"0008|1155", sopInstanceUID);

    using RescaleFilterType = itk::RescaleIntensityImageFilter<ImageType, ImageType >;

    RescaleFilterType::Pointer rescaler = RescaleFilterType::New();

    rescaler->SetOutputMinimum( 0 );
    rescaler->SetOutputMaximum( 65535 );

    QString path = ("D:\\BRCC");
    qDebug()<<"path"<<path;

    writer->SetFileName((path+"\\LCC_"+QString::number(1)+".dcm").toStdString().c_str());
    importFilter->GetOutput()->SetMetaDataDictionary(dict);
    importFilter->Update();
    rescaler->SetInput( importFilter->GetOutput() );

    writer->SetInput(importFilter->GetOutput());
    typedef itk::GDCMImageIO ImageIOType1;
    ImageIOType1::Pointer gdcmImageIO1 = ImageIOType1::New();
    writer->SetImageIO(gdcmImageIO1);
    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject & err )
    {
        std::cerr << "ExceptionObject caught !" << std::endl;
        std::cerr << err << std::endl;
        //return EXIT_FAILURE;
    }

//        QString path = ("D:\\BRCC");
//        qDebug()<<"path"<<path;
//        writer.SetFileName((path+"\\Img_"+QString::number(count+1)+".dcm").toStdString().c_str());
//        writer.SetFile(file);
//        if( !writer.Write())
//        {
//            qDebug("Dicom Image Write Error!");
//        }
//        qDebug()<<"done";
}
