#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
//#include "RegistrationFunctions.cuh"

//#include "ImageOperations.cuh"  // GPU Library Include
#include <QFile>
#include <vtkImageReslice.h>
#include <vtkNIFTIImageWriter.h>
#include <vtkMetaImageWriter.h>
#include <vtkStringArray.h>
#include <itkNiftiImageIO.h>
#include <itkNiftiImageIOFactory.h>
#include <nifti1_io.h>
#include <itkImageFileWriter.h>
#include <itkImageFileReader.h>
#include "itkImage.h"
#include "itkExceptionObject.h"
#include "itkNiftiImageIOFactory.h"
#include <vtkDICOMDirectory.h>
#include <vtkSmartPointer.h>
#include <vtkExtractVOI.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageImport.h>
#include <QMessageBox>






bool imageFlag=0;//AP-0,LAT-1;

int regFlag=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    vtkWidget = new QVTKWidget(this,QFlag(0));
    ui->Volumelayout->addWidget(vtkWidget);


    imgIO = gdcmIO::New();
    dicom = new dicomwrite();
    itk::NiftiImageIOFactory::RegisterOneFactory();




//    volumeImport = vtkImageImport::New();
//    alphaChannelFunc = vtkPiecewiseFunction::New();
//    colorFunc = vtkColorTransferFunction::New();
//    ren = vtkRenderer::New();

    caster3D = CastImageFilterType3D::New();

    interpolator3D = LinearInteroplatorType::New();


//    charImg =new unsigned char[2880*2880];
//    image;

    seriesReader=SeriesReaderType::New();

    fixedImage3D   = ImageType3D::New();
    fixedImage3Df  = ImageType3Df::New();
    fixedImage3Df2 = ImageType3Df::New();

    movingImage3Df = ImageType3Df::New();


    upperThreshold =1000;//by default
    lowerThreshold =-2000;//by default


//      dispVolume = new float[512*512*512];
//      drrBuf1    = new float[1440*1440];
//      drrBuf2    = new float[1440*1440];
//      projBuf1   = new float[1440*1440];
//      projBuf2   = new float[1440*1440];
//      tempProjBuf1 = new float[1440*1440];

//    spacing3D[3];
//    size3D[3];
//    origin3D[3];

     transform3D=TransformType3D::New();


//     revCaster3D=ReverseCastImageFilterType3D::New();
//     converter3D=ConverterType3D::New();

     movingImage3Df2=ImageType3Df::New();

     CTReader= vtkSmartPointer<vtkDICOMReader>::New();
     revConverter3D =ConverterReverseType3D::New();

     ui->label_Status->setText("Welcome...");

     volumeCount=0;

     caster3D_1 = CastImageFilterType3D::New();





     fixedImage3D_1   = ImageType3D::New();
     fixedImage3Df_1  = ImageType3Df::New();
     fixedImage3Df2_1 = ImageType3Df::New();

     movingImage3Df_1 = ImageType3Df::New();


      movingImage3Df2_1=ImageType3Df::New();

      CTReader_1= vtkSmartPointer<vtkDICOMReader>::New();
      revConverter3D_1 =ConverterReverseType3D::New();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSagitalSlice(float* vol,int value)
{
      try
    {
        unsigned char* sagitalSlice =new unsigned char[size3D[1]*size3D[2]];

        for(int j=0;j<size3D[2];j++)
        {
            for(int i=0;i<size3D[1];i++)
            {
                sagitalSlice[i+j*size3D[1]]= (unsigned char) (vol[value+i*size3D[0]+(size3D[2]-1-j)*size3D[0]*size3D[1]]);
            }
        }
        qDebug()<<"Print 3";

        /*colour table*/
         QVector<QRgb> color_table;
        /*fill color table*/
        for (int i = 0; i < 256; ++i) {
            color_table.push_back(qRgb(i,i,i)); // Fill the color table for Fixed Image
        }

        /*Qt QLabel display module*/
        QImage Image =QImage(sagitalSlice,size3D[1],size3D[2],QImage::Format_Indexed8);//QImage::Format_Indexed8//QImage::Format_Grayscale8

        ui->Sagittal_label->clear();
        Image=Image.scaled(751,751);
        Image.setColorTable(color_table);
//        ui->axialLabel->setScaledContents(true);

        ui->Sagittal_label->setPixmap(QPixmap::fromImage(Image));
        ui->Sagittal_label->setScaledContents(true);

        delete[] sagitalSlice;
        sagitalSlice=NULL;
    }
    catch(std::exception &e)
    {
        std::cout<<"Error found";
    }
        return ;

}

void  MainWindow::getFrontalSlice(float* vol,int value)
{
    try
    {
        unsigned char* frontalSlice =new unsigned char[size3D[0]*size3D[2]];

        for(int j=0;j<size3D[2];j++){
            for( int i=0;i<size3D[0];i++){
                frontalSlice[i+j*size3D[0]]= (unsigned char) (vol[(size3D[0]-1-i)+value*size3D[0]+j*size3D[0]*size3D[1]]);

            }
        }
        qDebug()<<"Print 2";

        /*colour table*/
         QVector<QRgb> color_table;
        /*fill color table*/
        for (int i = 0; i < 256; ++i) {
            color_table.push_back(qRgb(0,i,0)); // Fill the color table for Fixed Image
        }

        /*Qt QLabel display module*/
        QImage Image =QImage(frontalSlice,size3D[0],size3D[2],QImage::Format_Indexed8);//QImage::Format_Indexed8//QImage::Format_Grayscale8

        ui->Frontal_label->clear();
        Image=Image.scaled(751,751);
        Image.setColorTable(color_table);

        ui->Frontal_label->setPixmap(QPixmap::fromImage(Image));
        ui->Frontal_label->setScaledContents(true);

        delete[] frontalSlice;
        frontalSlice=NULL;
    }
    catch(std::exception &e)
    {
        std::cout<<"Exception found";
    }
        return ;
}

void MainWindow::getAxialSlice(float *vol, int value)
{

    try
    {
            unsigned char* axialSlice =new unsigned char[size3D[0]*size3D[1]];

            for(int j=0;j<size3D[1];j++){
                for(int i=0;i<size3D[0];i++){
                    axialSlice[i+j*size3D[0]]= (unsigned char) (vol[i+/*(size3D[1]-1-*/j/*)*/*size3D[0]+value*size3D[0]*size3D[1]]);
                }
            }
            qDebug()<<"Print 1";

            /*colour table*/
             QVector<QRgb> color_table;
            /*fill color table*/
            for (int i = 0; i < 256; ++i) {
                color_table.push_back(qRgb(0,i,i)); // Fill the color table for Fixed Image
            }

            /*Qt QLabel display module*/
            QImage Image =QImage(axialSlice,size3D[0],size3D[1],QImage::Format_Indexed8);//QImage::Format_Indexed8//QImage::Format_Grayscale8


            ui->Axial_label->clear();
            Image=Image.scaled(751,751);
            Image.setColorTable(color_table);

            ui->Axial_label->setPixmap(QPixmap::fromImage(Image));
            ui->Axial_label->setScaledContents(true);

            delete[] axialSlice;
            axialSlice=NULL;

    }
    catch(std::exception &e)
    {
        std::cout<<"exception found";
    }
            return ;
}

void MainWindow::DisplayVolume(float*dispVolume)
{

    if(dispVolume==NULL)
      return;

    /*import filter*/
    volumeImport = vtkImageImport::New();
    volumeImport->CopyImportVoidPointer(dispVolume, sizeof(float)*size3D[0]*size3D[1]*1024);
    volumeImport->SetWholeExtent(0,size3D[0]-1,0,size3D[1]-1,0,1024-1);
    //volumeImport->SetDataScalarTypeToUnsignedChar();
    volumeImport->SetDataScalarTypeToFloat();
    volumeImport->SetNumberOfScalarComponents(1);
    volumeImport->SetDataExtentToWholeExtent();
    //volumeImport->SetWholeExtent(0,param->nOutputPixels-1,0,param->nOutputPixels-1,0,param->nOutputPixels-1);
    volumeImport->SetDataSpacing(spacing3D[0], spacing3D[1], spacing3D[2]);
    volumeImport->Update();
    qDebug()<<"Debuggg"<<spacing3D[0]<<spacing3D[1]<<spacing3D[2];
//    vtkImageGaussianSmooth *gaussFilter = vtkImageGaussianSmooth::New();
//    gaussFilter->SetInputConnection(volumeImport->GetOutputPort());
//    gaussFilter->SetRadiusFactors(1.5, 1.5, 1.5);
//    gaussFilter->SetStandardDeviations(1.0, 1.0, 1.0);
//    gaussFilter->Update();


    /*mapper*/
    vtkGPUVolumeRayCastMapper *volumeGPUmapper = vtkGPUVolumeRayCastMapper::New();
    volumeGPUmapper->SetInputConnection(volumeImport->GetOutputPort());//gaussFilter->GetOutputPort()
    //volumeGPUmapper->SetInputData(gaussFilter->GetOutput());


    vtkVolume *VTKvolume = vtkVolume::New();
    //VTKvolume->SetMapper(volumeGPUmapper);
    VTKvolume->SetMapper(volumeGPUmapper);

    qDebug()<<"Debuggg";

    /*RGBA*/
    double skinOnBlueMap[4][5] =
    {

          {381,     0.2,                 1,               0,               0.1},
          {512,  0.89,                 0.855,               0.788,               0.1},

//        {100,  0,                 1.0,               1,               0.1},
//        {200,  1.0,                 0,               0,               0.1},

    };
    /*
        {100,  1,                 1.0,               0,               0.1},
        {150,  0,                 1.0,               1,               0.1},
        {255,  1.0,                 0,               0,               0.1},
    */

    /*
        {100,  1,                 1.0,               1,               0.1},
        {200,  1,                 1.0,               1,               0.1},
        {255,  1.0,                 0,               0,               0.1},
    */

    alphaChannelFunc = vtkPiecewiseFunction::New();
    colorFunc = vtkColorTransferFunction::New();
    for(int i = 0; i < sizeof(skinOnBlueMap)/(5*sizeof(double)); i++)
    {
        colorFunc->AddRGBPoint(skinOnBlueMap[i][0], skinOnBlueMap[i][1], skinOnBlueMap[i][2], skinOnBlueMap[i][3]);
        alphaChannelFunc->AddPoint(skinOnBlueMap[i][0], skinOnBlueMap[i][4]);
    }

    qDebug()<<"Debuggg1";

    /*edit properties*/
    vtkVolumeProperty   *volumeProperty = vtkVolumeProperty::New();
    volumeProperty->SetColor(colorFunc);
    volumeProperty->SetScalarOpacity(alphaChannelFunc);
    volumeProperty->SetAmbient(0.9);
    volumeProperty->SetInterpolationTypeToNearest();

    VTKvolume->SetProperty(volumeProperty);

    qDebug()<<"Debuggg2";


    /*camera*/
    vtkSmartPointer<vtkCamera> camera =
       vtkSmartPointer<vtkCamera>::New();
    camera->Roll(0);
    camera->Yaw(0);

    vtkSmartPointer<vtkAxesActor> axes =
      vtkSmartPointer<vtkAxesActor>::New();
    axes->SetTotalLength(100,100,100);

    qDebug()<<"Debuggg3";


    /*rendering*/
    ren = vtkRenderer::New();
    //ren->AddActor(axes);
    ren->AddVolume(VTKvolume);
    ren->SetBackground(255, 255, 204);
    vtkWidget->GetRenderWindow()->AddRenderer(ren);
    ren->SetActiveCamera(camera);
    ren->ResetCamera();
    vtkWidget->GetRenderWindow()->Render();

    qDebug()<<"Debuggg4"<<vtkWidget->geometry();

    /*clearing*/
    //gaussFilter->Delete();
    //volumeGPUmapper->Delete();
    VTKvolume->Delete();
    volumeProperty->Delete();
    volumeImport->Delete();
    colorFunc->Delete();
    alphaChannelFunc->Delete();
    ren->Delete();

    /*Display axial,frontal and sagital views*/
     this->getAxialSlice(dispVolume,/*256*/64);
     this->getFrontalSlice(dispVolume,256);
     this->getSagitalSlice(dispVolume,256);

}

void MainWindow::on_loadVolume_clicked()
{
    //this->loadVolume();

    this->loadVTKVolume();

    ui->label_Status->setText("Volume Loaded");

}


void MainWindow::on_Transform3DGPU_clicked()
{

   try
    {
    float h_angle3D[3];
    h_angle3D[0]=ui->lineEdit_Pitch_in->text().toDouble();
    h_angle3D[1]=ui->lineEdit_Roll_in->text().toDouble();
    h_angle3D[2]=ui->lineEdit_Yaw_in->text().toDouble();

    float translation3D[3];
    translation3D[0]=ui->lineEdit_XShift_in->text().toDouble();
    translation3D[1]=ui->lineEdit_YShift_in->text().toDouble();
    translation3D[2]=ui->lineEdit_ZShift_in->text().toDouble();

    qDebug()<<"translation3D:"<<translation3D[0]<<translation3D[1]<<translation3D[3];

    ////rigidTransformation3D(fixedImage3Df->GetBufferPointer(),(unsigned int*)size3D,spacing3D,h_angle3D,translation3D,movingImage3Df->GetBufferPointer());



    for (int k=0;k<size3D[2];k++)
    {
       for (int j=0;j<size3D[1];j++)
       {
           for (int i=0;i<size3D[0];i++)
           {
                dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]]=0;
                if((fixedImage3Df->GetBufferPointer()[(size3D[0]-1-i)+(size3D[2]-1-k)*size3D[0]+(size3D[1]-1-j)*size3D[0]*size3D[1]]<upperThreshold) && (fixedImage3Df->GetBufferPointer()[(size3D[0]-1-i)+(size3D[2]-1-k)*size3D[0]+(size3D[1]-1-j)*size3D[0]*size3D[1]]>lowerThreshold))
                dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]] = (fixedImage3Df->GetBufferPointer()[(size3D[0]-1-i)+(size3D[2]-1-k)*size3D[0]+(size3D[1]-1-j)*size3D[0]*size3D[1]]-lowerThreshold)*255/(upperThreshold-lowerThreshold);

           }
       }
    }




    this->DisplayVolume(dispVolume);
    }
    catch(std::exception &e)
    {
        std::cout<<"Exception found"<<&e;
        return;
    }
}


void MainWindow::on_Tranform_ITK_clicked()
{
    if(fixedImage3Df.IsNull()){
        return;
    }

    //-----------------------------------written for testing-------------------------------------//

//    QString cbctwritepath=/*CT_DICOM_Path*/ui->lineEdit_SavePAth->text()+"\\volume1";
    QString cbctwritepath=ui->LineEdit_InputPath->text();


    vtkSmartPointer <vtkDICOMDirectory> dicomdir =
            vtkSmartPointer <vtkDICOMDirectory>:: New ();
    dicomdir -> SetDirectoryName (cbctwritepath.toStdString().c_str());

    ExtBuffer = new unsigned short[512*512*866];

    try
    {
        dicomdir ->Update ();
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
        //return;
    }

     QDir directory(cbctwritepath);
     int fileCount = 0;
     QFileInfoList fileInfoList = directory.entryInfoList(QDir::Files);
     foreach (QFileInfo fileInfo, fileInfoList) {
         fileCount++;
     }
     qDebug()<<"filecount::"<<fileCount;

    vtkSmartPointer<vtkDICOMReader> reader1 = vtkSmartPointer<vtkDICOMReader>::New();

       int  numSeries=dicomdir->GetNumberOfSeries();
       qDebug()<<"dicomseries::"<<dicomdir->GetNumberOfSeries()<<cbctwritepath;

       vtkStringArray *sortedFiles;

       qDebug()<<"Number of Series found :"<<numSeries;

       if(numSeries>1 || numSeries == 0)
           qDebug()<<"error";//QMessage Box to be added


       sortedFiles = dicomdir -> GetFileNamesForSeries (numSeries-1);


    for(int i=0;i<sortedFiles->GetNumberOfValues();i++){
   //        qDebug()<<"entering for::"<<i;

           if(reader1->CanReadFile(sortedFiles->GetValue(i))){

               reader1->SetFileName(sortedFiles->GetValue(i));
               reader1->SetGlobalWarningDisplay(true);

               try
               {
                   reader1->Update();
               }
               catch(...)
               {
                   qDebug()<<"Exception  reading dicom files";
                    //return;
               }

               if(QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(
                                             vtkDICOMTag(0x0008,0x0060)).AsString()).compare("RTIMAGE")==0)
               {
                   //return;
               }

               if(QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(
                                             vtkDICOMTag(0x0008,0x0060)).AsString()).compare("RTSTRUCT")==0){

                   //qDebug()<<"RTSTRUCT available"<<rtStructFile;

               }

           }
       }


    QString recon_dia = QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0018,0x1100)).AsString());
    qDebug()<<"recon dia:::"<<recon_dia;
    double recon_diameter = recon_dia.toDouble();
    double half_recon_diameter = recon_diameter/2;
    qDebug()<<"recon dia:::"<<recon_diameter<<half_recon_diameter;

    QString Top_left = QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0020,0x0032)).AsString());
    qDebug()<<"TopLeft_coordinates::"<<Top_left;
    QStringList splitvalue = Top_left.split("\\");
    QString x_value = splitvalue.at(0);
//    QString y_value = splitvalue.at(2);
    QString z_value = splitvalue.at(1);

    double xval = x_value.toDouble();
    double zval = z_value.toDouble();
//    double yval = y_value.toDouble();

    qDebug()<<"x_split value & y_spilit value::"<<xval<<zval;

    double center_x = xval+half_recon_diameter;
    double center_z = zval+half_recon_diameter;

    qDebug()<<"center_coordinates::"<<center_x<<center_z;


    qDebug()<<"filecount::"<<fileCount;

    QString slicethickness_1 = QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0018,0x0050)).AsString());
    qDebug()<<"slicethickness:::"<<slicethickness_1<<fileCount;


    double thickness_1 = slicethickness_1.toDouble();
    double scan_length_1 = (fileCount)*thickness_1;
    qDebug()<<"Thicness & scan length::"<<thickness_1<<scan_length_1;
    double scan_length_1_center = scan_length_1/2;
    qDebug()<<"scan_length_center_1::"<<scan_length_1_center;
    double center_slicenumber = scan_length_1_center/thickness_1;
    int center_SN = center_slicenumber;
    int center_roundedValue = qRound(center_slicenumber);
    qDebug()<<"center_slicenumber::"<<center_SN<<center_slicenumber<<center_roundedValue;
    center_ct_y = center_roundedValue;
    ct_count = fileCount;


    vtkSmartPointer<vtkDICOMReader> reader22=NULL;
    reader22 =vtkSmartPointer<vtkDICOMReader>::New();
    reader22->SetFileName(sortedFiles->GetValue(center_roundedValue-1));
    reader22->SetGlobalWarningDisplay(true);
    try
    {
        reader22->Update();
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
         //return;
    }

    QString Second_Top_left = QString::fromStdString(reader22->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0020,0x0032)).AsString());
    qDebug()<<"second_top_left::"<<Second_Top_left;
    QStringList splitvalueY = Second_Top_left.split("\\");
    QString y_value = splitvalueY.at(2);
    double center_y = y_value.toDouble();

    qDebug()<<"Y_center::"<<center_y;
    qDebug()<<"center_coordinates::"<<center_x<<center_y<<center_z;

//    double XShift =
    //----------------------------Origin from text doc-------------------------------//

    QString shiftfile = "D:\\Treatment_center.txt";

    QFile filename1(shiftfile);

    QString line;
    QString t_xshift;
    QString t_yshift;
    QString t_zshift;


    if(filename1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&filename1);
        bool posFind=false;
        int posCnt=0;

        while( !in.atEnd())
        {
            line = in.readLine();
            if (line.contains("Shift_values"))
            {
                posFind=true;
            }
            if(posFind && posCnt<4)
            {
                if(line.contains("x"))
                {
                   QStringList splitD = line.split("=");
                   t_xshift = splitD.at(1);
                }
                if(line.contains("y"))
                {
                   QStringList splitD = line.split("=");
                   t_yshift = splitD.at(1);
                }
                if(line.contains("z"))
                {
                    QStringList splitD = line.split("=");
                    t_zshift = splitD.at(1);
                }

                posCnt++;
                if(posCnt==4)
                    break;
            }

    }
    }
    qDebug()<<"shift_values"<<t_xshift<<t_yshift<<t_zshift;

    double t_x_shift = t_xshift.toDouble();
    double t_y_shift = t_yshift.toDouble();
    double t_z_shift = t_zshift.toDouble();

    qDebug()<<"treatment_center_values"<<t_x_shift<<t_y_shift<<t_z_shift;
    qDebug()<<"center values::"<<center_x<<center_y<<center_z;
    double fin_x_shift;
    double fin_y_shift;
    double fin_z_shift;

    if(center_x>t_x_shift)
    {
       fin_x_shift = -(center_x-t_x_shift);   //verified.
    }
    else
    {
       fin_x_shift = (t_x_shift-center_x);
    }
    qDebug()<<"fin_x_shift value::"<<fin_x_shift;

    if(center_z>t_z_shift)
    {
       fin_z_shift  = (center_z-t_z_shift);   //verified
    }
    else
    {
       fin_z_shift = -(t_z_shift-center_z);
    }
    qDebug()<<"fin_z_value::"<<fin_z_shift;

    if(center_y>t_y_shift)
    {
        fin_y_shift = -(center_y-t_y_shift);
    }
    else
    {
        fin_y_shift = (t_y_shift-center_y);
    }
    qDebug()<<"fin_y_value::"<<fin_y_shift;
    fin_y_shift=fin_y_shift;


    qDebug()<<"x & y & z shifts::"<<fin_x_shift<<fin_y_shift<<fin_z_shift;

    ui->lineEdit_XShift_in->setText(QString::number(fin_x_shift));
    ui->lineEdit_YShift_in->setText(QString::number(-fin_y_shift));
    ui->lineEdit_ZShift_in->setText(QString::number(-fin_z_shift));
    ct_y_shift = fin_y_shift;



    //----------------------------Origin from text doc-------------------------------//


    //-----------------------------------written for testing-------------------------------------//


    try
    {
    float h_angle3D[3];
    h_angle3D[0]=ui->lineEdit_Pitch_in->text().toDouble();//in degree
    h_angle3D[2]=ui->lineEdit_Yaw_in->text().toDouble();//in degree
    h_angle3D[1]=ui->lineEdit_Roll_in->text().toDouble();//in degree

    float translation3D[3];
    translation3D[0]=ui->lineEdit_XShift_in->text().toDouble();//in mm
    translation3D[2]=ui->lineEdit_ZShift_in->text().toDouble();//in mm
    translation3D[1]=ui->lineEdit_YShift_in->text().toDouble();//in mm


    resampler3D = ResampleFilterType3D::New();


    TransformType3D::InputPointType centerFixed;
    centerFixed[0] = origin3D[0] + (size3D[0]*spacing3D[0])/2;
    centerFixed[1] = origin3D[1] + (size3D[1]*spacing3D[1])/2;
    centerFixed[2] = origin3D[2] + (size3D[2]*spacing3D[2])/2;

    qDebug()<<"centersss "<<centerFixed[0]<<centerFixed[1]<<centerFixed[2];
    qDebug()<<"origin "<<origin3D[0]<<origin3D[1]<<origin3D[2];
    qDebug()<<"size3D "<<size3D[0]<<size3D[1]<<size3D[2];
    qDebug()<<"spacing3D "<<spacing3D[0]<<spacing3D[1]<<spacing3D[2];

//    parameters3D.SetSize(6);
//    parameters3D[0] =  -h_angle3D[0]*PI/180; //theta
//    parameters3D[1] =  -h_angle3D[1]*PI/180; //X-shift
//    parameters3D[2] =  -h_angle3D[2]*PI/180; //Y-shift
//    parameters3D[3] =  -translation3D[0]; //theta
//    parameters3D[4] =  -translation3D[1]; //X-shift
//    parameters3D[5] =  -translation3D[2]; //Y-shift

    parameters3D.SetSize(6);
    parameters3D[0] =  h_angle3D[0]*PI/180; //Pitch
    parameters3D[2] =  -h_angle3D[1]*PI/180; //Roll
    parameters3D[1] =  -h_angle3D[2]*PI/180; //Yaw
    parameters3D[3] =  translation3D[0]; //X-Shift
    parameters3D[5] =  -translation3D[1]; //Y-shift
    parameters3D[4] =  -translation3D[2]; //Z-shift

    outputorigin3D[0] = translation3D[0];
    outputorigin3D[1] = -translation3D[1];
    outputorigin3D[2] = -translation3D[2];



    transform3D->SetParameters(parameters3D);
    transform3D->SetCenter(centerFixed);

//    TransformType3D::Pointer transformInverse=TransformType3D::New() ;
//    transform3D->GetInverse(transformInverse);

    resampler3D->SetTransform(/*transformInverse*/transform3D);

    resampler3D->SetInput(0,fixedImage3Df);

    resampler3D->SetSize(fixedImage3Df->GetLargestPossibleRegion().GetSize());

    resampler3D->SetInterpolator(interpolator3D);

    resampler3D->SetOutputOrigin(fixedImage3Df->GetOrigin()/*outputorigin3D*/);

    resampler3D->SetOutputSpacing(fixedImage3Df->GetSpacing());



    resampler3D->SetOutputDirection(fixedImage3Df->GetDirection());


    resampler3D->SetDefaultPixelValue(lowerThreshold);



    try{

         resampler3D->Update();

    }
    catch(itk::ExceptionObject &err)
    {
        std::cerr << "Exception caught Resampler !"<<err.GetDescription() << std::endl;
        return;
    }

    movingImage3Df=NULL;
    movingImage3Df=resampler3D->GetOutput();



    resampler3D=NULL;



    /*Display Moving image in Image co-ordinates*/

     for (int k=0;k<size3D[2];k++)
     {
         for (int j=0;j<size3D[1];j++)
         {
           for (int i=0;i<size3D[0];i++)
           {
             if((movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]]<upperThreshold)&&(movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]]>lowerThreshold))
                dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]] = (movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]]-lowerThreshold)*255/(upperThreshold-lowerThreshold) ;
             else if((movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]])>upperThreshold)
                dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]]=upperThreshold;
             else
                 dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]]=lowerThreshold;

           }
         }
     }


     qDebug()<<"j nhkkkkkkkkkkkkkkkk";



//    for(int i=0;i< (size3D[0]*size3D[1]*size3D[2]);i++){
//     if((movingImage3Df->GetBufferPointer()[i]<upperThreshold)&&(movingImage3Df->GetBufferPointer()[i]>lowerThreshold))
//        dispVolume[i]=(movingImage3Df->GetBufferPointer()[i]-lowerThreshold)*255/(upperThreshold-lowerThreshold);
//     else
//        dispVolume[i]=0;
//    }


    this->DisplayVolume(dispVolume);

//     qApp->processEvents();

//    this->DisplayVolume(movingImage3Df->GetBufferPointer());

    ui->label_Status->setText("Transform Applied");
    }
    catch(std::exception &e)
    {
        std::cout<<"Exception found"<<&e;
        return;
    }

}
void MainWindow::dicomWrite(QString filepath)
{
  try
    {
    /*Assumes the file filepath is a valid path.
     * Sets the patient matrix.
     * adds metadata read from xml file.
     * Writes Files to the given folder path.*/

    vtkSmartPointer <vtkDICOMCTGenerator> generator;
    generator =vtkSmartPointer <vtkDICOMCTGenerator>::New();
    // Create a meta data object with some desired attributes.
//    vtkSmartPointer <vtkDICOMMetaData> meta =
//            vtkSmartPointer <vtkDICOMMetaData>:: New ();
    //crashes here in debug mode !!

//    vtkDICOMTag DicomTag;
//    for (int i=0;i<tagList->length();i++){
//        DicomTag = vtkDICOMTag(tagList->at(i).Group,tagList->at(i).Element);
//        meta->SetAttributeValue(tagList->at(i).No,DicomTag,tagList->at(i).VRKey);
//        meta->SetAttributeValue(DicomTag,tagList->at(i).Data);
//    }
    //Set the patient orientation.Its a 4x4 matrix and fixed for the machine.
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

    QString mod="CT";

    CTReader->GetMetaData()->SetAttributeValue(vtkDICOMTag(0x0008,0x0060),mod.toStdString());

    writer -> SetInputData(converter3D->GetOutput());
    writer -> SetMetaData (CTReader->GetMetaData());
    writer->SetMemoryRowOrderToFileNative();
    writer -> SetGenerator (generator);
    // Set the output filename format as a printf-style string.
    writer -> SetFilePattern ("%s/slice -%04.4d.dcm");//pattern is fixed.
    // Set the directory to write the files into.
    writer -> SetFilePrefix (filepath.toStdString().c_str());
    //writer->SetPatientMatrix(m);
    // Write the file.
    writer ->Write ();
    writer->Update();

    qDebug()<<"rgreghhrthwe"<<CTReader->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0008,0x0060)).AsString().c_str();
    }
    catch(std::exception &e)
    {
        std::cout<<"exception found,,"<<&e;
        return;
    }
}



void MainWindow::on_Reset_clicked()
{



}



void MainWindow::on_generateVolume_clicked()
{

//    short *volShort;
//    volShort= new  short[size];
////    for(int i=0;i<size;i++)
////        volShort[i]= static_cast<short>(volume[i]);
////    qDebug()<<"kkkk";

//    for(int i=0;i<512;i++)
//    {

//        for(int j=0;j<512;j++)
//        {

//            for(int k=0;k<512;k++)
//            {
//                  volShort[k+512*j+(512*512*i)]= static_cast<float>(movingImage3Df->GetBufferPointer()[k+512*512*(i)+((512-1-j)*512)]);

//        }

//    }
//    }

//    vtkImageImport * vol = vtkImageImport::New();

////    float x=-(0.5*(volumeSize-1)*0.5);
//    float x1=-(0.5*(512-1)*0.5);
//    float x2=-(0.5*(512-1)*0.5);
//    float x3=-(0.5*(512-1)*0.5);

//    vol->CopyImportVoidPointer(volShort/*volume*/, sizeof(short)*512*512*512);


////    vol->CopyImportVoidPointer(volShort/*volume*/, sizeof(short)*volumeSize*volumeSize*volumeSize);
//    vol->SetDataScalarTypeToShort();
//    vol->SetNumberOfScalarComponents(1);
//    vol->SetWholeExtent(0, (512-1), 0, (512-1), 0, (512-1));

////    vol->SetWholeExtent(0, (volumeSize-1), 0, (volumeSize-1), 0, (volumeSize-1));
//    vol->SetDataExtentToWholeExtent();
//    //    vol->SetDataSpacing(0.5,0.5,0.5);
//    vol->SetDataSpacing(256.0/(float)512,256.0/(float)512,256.0/(float)512);
////    vol->SetDataOrigin(x,-x,x );//data origin is fixed.
//    qDebug()<<"check data origin"<<x1<<-x2<<x3;
//        vol->SetDataOrigin(x1,-x2,x3 );//data origin is fixed.


//    return;

       try
       {



        /*Rearranging the volume from machine coordinates to image coordinates*/

        qDebug()<<"size3D[0]: "<<size3D[0]<<", size3D[1]: "<<size3D[1]<<", size3D[2]: "<<size3D[2];
         for (int k=0;k<size3D[2];k++)
         {
             for (int j=0;j<size3D[1];j++)
             {
               for (int i=0;i<size3D[0];i++)
               {

//                   if((movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]])>upperThreshold)
//                      movingImage3Df2->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]]=upperThreshold;
//                   /*else */if((movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]])<lowerThreshold)
//                       movingImage3Df2->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]]=lowerThreshold;

//                   else
                    movingImage3Df2->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]] = movingImage3Df->GetBufferPointer()[i+(size3D[1]-1-j)*size3D[0]+k*size3D[0]*size3D[1]] ;

//                   movingImage3Df2->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]] = movingImage3Df->GetBufferPointer()[i+(size3D[1]-1-j)*size3D[0]+/*(size3D[2]-1-*/k/*)*/*size3D[0]*size3D[1]]  ;


//                   movingImage3Df2->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]] = movingImage3Df->GetBufferPointer()[(size3D[0]-1-i)+(size3D[2]-1-k)*size3D[0]+(size3D[1]-1-j)*size3D[0]*size3D[2]] ;

               }
             }
         }

         this->DisplayVolume(movingImage3Df2->GetBufferPointer());


        /*convert back to short*/


        revCaster3D=ReverseCastImageFilterType3D::New();
        revCaster3D->SetInput(movingImage3Df2);
        try
        {
        revCaster3D->Update();
        }
        catch(std::exception &e)
        {
            std::cout<<"exception found in revCaster3D pointer"<<&e;
            return;
        }



        /*convert to vtk*/


        converter3D=ConverterType3D::New();
        converter3D->SetInput(revCaster3D->GetOutput());
        try
        {
        converter3D->Update();
        }
        catch(std::exception &e)
        {
            std::cout<<"Exception found in converter3D"<<&e;
            return;
        }

        volumeCount++;

        QDir dir(ui->lineEdit_SavePAth->text());

        if (!dir.exists())
        {
            dir.mkdir(ui->lineEdit_SavePAth->text());
            dir.mkpath(ui->lineEdit_SavePAth->text()+"\\volume"+QString::number(volumeCount));
        }
        else
        {
            dir.mkpath(ui->lineEdit_SavePAth->text()+"\\volume"+QString::number(volumeCount));
        }


        this->dicomWrite(ui->lineEdit_SavePAth->text()+"\\volume"+QString::number(volumeCount));


        ui->label_Status->setText("Volume Generated");
        revCaster3D=NULL;
        converter3D=NULL;
    }
    catch(std::exception &e)
    {
        std::cout<<&e;
        return;
    }

    this->m_resampleCtData();





}
void MainWindow::loadVTKVolume()
{

     QString dicomFolder=ui->LineEdit_InputPath->text();

    /*Create Dicom dir and load files.*/
    vtkSmartPointer <vtkDICOMDirectory> dicomdir =
            vtkSmartPointer <vtkDICOMDirectory>:: New ();
    dicomdir -> SetDirectoryName (dicomFolder.toStdString().c_str());
    dicomdir ->Update ();

    vtkStringArray *sortedFiles = dicomdir -> GetFileNamesForSeries (0);

    CTReader->SetFileNames(sortedFiles);
    CTReader->SetDataScalarTypeToShort();
    CTReader->SetMemoryRowOrderToFileNative();

    qDebug()<<"Memory order = "<<CTReader->GetMemoryRowOrderAsString();/*FileNAtive*/

    qDebug()<<QString::fromStdString(CTReader->GetMetaData()->GetAttributeValue(
                                              vtkDICOMTag(0x0018,0x0060)).AsString());

    try{
        CTReader->Update();
        qDebug()<<"Reading Success..!!";
    }
    catch(...)
    {

        qDebug()<<"Exception caught...!!";
    }


    /*vtk to itk converter*/



    revConverter3D->SetInput(CTReader->GetOutput());
    qDebug()<<"before revConverter3D update::";
    try
    {
        revConverter3D->Update();
    }
    catch(...)
    {
        qDebug()<<"after revConverter3D update catch::";
    }

    caster3D->SetInput(revConverter3D->GetOutput());
    qDebug()<<"before caster update::";
    try
    {
        caster3D->Update();
    }
    catch(...)
    {
        qDebug()<<"after caster update catch";
    }
    fixedImage3Df2 = caster3D->GetOutput();


    // 3D Image size (float type)
    size3D[0]    =fixedImage3Df2->GetBufferedRegion().GetSize()[0];
    size3D[1]    =fixedImage3Df2->GetBufferedRegion().GetSize()[1];
    size3D[2]    =fixedImage3Df2->GetBufferedRegion().GetSize()[2];

    // 3D Image Spacing  (float type)
    spacing3D[0] =fixedImage3Df2->GetSpacing()[0];
    spacing3D[1] =fixedImage3Df2->GetSpacing()[1];
    spacing3D[2] =fixedImage3Df2->GetSpacing()[2];

    // 3D Image Origing   (float type)
    origin3D[0]  =fixedImage3Df2->GetOrigin()[0];
    origin3D[1]  =fixedImage3Df2->GetOrigin()[1];
    origin3D[2]  =fixedImage3Df2->GetOrigin()[2];

    /*Allocate fixed Image and movingImage*/

     ImageType3Df::SizeType size1;
     size1[0] =  size3D[0];
     size1[1] =  size3D[1];
     size1[2] =  size3D[2];

     ImageType3Df::IndexType index1;
     index1[0] = 0;
     index1[1] = 0;
     index1[2] = 0;

     ImageType3Df::RegionType region1;
     region1.SetIndex(index1);
     region1.SetSize(size1);

     qDebug()<<"above moving Image3Df::";

     movingImage3Df->SetRegions(region1);
     movingImage3Df->Allocate(true);
     movingImage3Df->SetSpacing(spacing3D);
     movingImage3Df->SetOrigin(origin3D);


     movingImage3Df2->SetRegions(region1);
     movingImage3Df2->Allocate(true);
     movingImage3Df2->SetSpacing(spacing3D);
     movingImage3Df2->SetOrigin(origin3D);

     ImageType3Df::SizeType size2;
     size2[0] =  size3D[0];
     size2[1] =  size3D[1];
     size2[2] =  size3D[2];

     ImageType3Df::IndexType index2;
     index2[0] = 0;
     index2[1] = 0;
     index2[2] = 0;


     ImageType3Df::RegionType region2;
     region2.SetIndex(index2);
     region2.SetSize(size2);

     fixedImage3Df->SetRegions(region2);
     fixedImage3Df->Allocate(true);
     fixedImage3Df->SetSpacing(spacing3D);
     fixedImage3Df->SetOrigin(origin3D);





     QString dicomFolder_1="D:\\cbct_images\\mallegowda\\CBCT(221-670)";

    /*Create Dicom dir and load files.*/
    vtkSmartPointer <vtkDICOMDirectory> dicomdir_1 =
            vtkSmartPointer <vtkDICOMDirectory>:: New ();
    dicomdir_1 -> SetDirectoryName (dicomFolder_1.toStdString().c_str());
    dicomdir_1 ->Update ();
    vtkStringArray *sortedFiles_1 = dicomdir_1 -> GetFileNamesForSeries (0);

    CTReader_1->SetFileNames(sortedFiles_1);

    CTReader_1->SetDataScalarTypeToShort();

    CTReader_1->SetMemoryRowOrderToFileNative();

    qDebug()<<"Memory order11 = "<<CTReader_1->GetMemoryRowOrderAsString();/*FileNAtive*/

    qDebug()<<QString::fromStdString(CTReader_1->GetMetaData()->GetAttributeValue(
                                              vtkDICOMTag(0x0018,0x0060)).AsString());

    try{
        CTReader_1->Update();
        qDebug()<<"Reading Success..!!";
    }
    catch(...)
    {

        qDebug()<<"Exception caught...!!";
    }


    /*vtk to itk converter*/



    revConverter3D_1->SetInput(CTReader_1->GetOutput());
    qDebug()<<"before revConverter3D update::";
    try
    {
        revConverter3D_1->Update();
    }
    catch(...)
    {
        qDebug()<<"after revConverter3D update catch::";
    }

    caster3D_1->SetInput(revConverter3D_1->GetOutput());
    qDebug()<<"before caster update::";
    try
    {
        caster3D_1->Update();
    }
    catch(...)
    {
        qDebug()<<"after caster update catch";
    }
    fixedImage3Df2_1 = caster3D_1->GetOutput();


    // 3D Image size (float type)
    size3D_1[0]    =fixedImage3Df2_1->GetBufferedRegion().GetSize()[0];
    size3D_1[1]    =fixedImage3Df2_1->GetBufferedRegion().GetSize()[1];
    size3D_1[2]    =fixedImage3Df2_1->GetBufferedRegion().GetSize()[2];

    // 3D Image Spacing  (float type)
    spacing3D_1[0] =fixedImage3Df2_1->GetSpacing()[0];
    spacing3D_1[1] =fixedImage3Df2_1->GetSpacing()[1];
    spacing3D_1[2] =fixedImage3Df2_1->GetSpacing()[2];

    // 3D Image Origing   (float type)
    origin3D_1[0]  =fixedImage3Df2_1->GetOrigin()[0];
    origin3D_1[1]  =fixedImage3Df2_1->GetOrigin()[1];
    origin3D_1[2]  =fixedImage3Df2_1->GetOrigin()[2];

    /*Allocate fixed Image and movingImage*/

     ImageType3Df::SizeType size1_1;
     size1_1[0] =  size3D_1[0];
     size1_1[1] =  size3D_1[1];
     size1_1[2] =  size3D_1[2];

     ImageType3Df::IndexType index1_1;
     index1_1[0] = 0;
     index1_1[1] = 0;
     index1_1[2] = 0;

     ImageType3Df::RegionType region1_1;
     region1_1.SetIndex(index1_1);
     region1_1.SetSize(size1_1);

     qDebug()<<"above moving Image3Df::";

     movingImage3Df_1->SetRegions(region1_1);
     movingImage3Df_1->Allocate(true);
     movingImage3Df_1->SetSpacing(spacing3D_1);
     movingImage3Df_1->SetOrigin(origin3D_1);


     movingImage3Df2_1->SetRegions(region1_1);
     movingImage3Df2_1->Allocate(true);
     movingImage3Df2_1->SetSpacing(spacing3D_1);
     movingImage3Df2_1->SetOrigin(origin3D_1);

     ImageType3Df::SizeType size2_1;
     size2_1[0] =  size3D_1[0];
     size2_1[1] =  size3D_1[1];
     size2_1[2] =  size3D_1[2];

     ImageType3Df::IndexType index2_1;
     index2_1[0] = 0;
     index2_1[1] = 0;
     index2_1[2] = 0;


     ImageType3Df::RegionType region2_1;
     region2_1.SetIndex(index2);
     region2_1.SetSize(size2);

     fixedImage3Df_1->SetRegions(region2_1);
     fixedImage3Df_1->Allocate(true);
     fixedImage3Df_1->SetSpacing(spacing3D_1);
     fixedImage3Df_1->SetOrigin(origin3D_1);







    /*Push loaded volume to display buffer*/
    if(dispVolume!=NULL)
        delete[] dispVolume;

    dispVolume = new float[ size3D[0]*size3D[1]*size3D[2]];
   qDebug()<<"write";

   /*Rearranging the volume from image coordinates to Image coordinates*/

    for (int k=0;k<size3D[2];k++)
    {
        for (int j=0;j<size3D[1];j++)
        {
          for (int i=0;i<size3D[0];i++)
          {
            fixedImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]] = fixedImage3Df2->GetBufferPointer()[i+(size3D[1]-1-j)*size3D[0]+(/*size3D[2]-1-*/k)*size3D[0]*size3D[1]] ;
          }
          if(j==1){

          }

        }
    }

/*
    lowerThreshold = 32768;
    upperThreshold =-32768;

    for(unsigned int i=0;i< (size3D[0]*size3D[1]*size3D[2]);i++){
     if(fixedImage3Df->GetBufferPointer()[i]>upperThreshold)
         upperThreshold=fixedImage3Df->GetBufferPointer()[i];
     if(fixedImage3Df->GetBufferPointer()[i]<lowerThreshold)
         lowerThreshold=fixedImage3Df->GetBufferPointer()[i];
    }

    qDebug()<<"lowerThreshold "<<lowerThreshold<<"upperThreshold "<<upperThreshold;
    for(unsigned int i=0;i< (size3D[0]*size3D[1]*size3D[2]);i++){
     dispVolume[i]=(fixedImage3Df->GetBufferPointer()[i]-lowerThreshold)*255/(upperThreshold-lowerThreshold);
    }

*/

    qDebug()<<"lowerThreshold "<<lowerThreshold<<"upperThreshold "<<upperThreshold;

    for(int i=0;i< (size3D[0]*size3D[1]*size3D[2]);i++){
     if((fixedImage3Df->GetBufferPointer()[i]<upperThreshold)&&(fixedImage3Df->GetBufferPointer()[i]>lowerThreshold))
        dispVolume[i]=(fixedImage3Df->GetBufferPointer()[i]-lowerThreshold)*255/(upperThreshold-lowerThreshold);
     else
        dispVolume[i]=lowerThreshold;
    }




    /*Push loaded volume to display buffer*/
    if(dispVolume_1!=NULL)
        delete[] dispVolume_1;

    dispVolume_1 = new float[ size3D_1[0]*size3D_1[1]*size3D_1[2]];
   qDebug()<<"write";

   /*Rearranging the volume from image coordinates to Image coordinates*/

    for (int k=0;k<size3D_1[2];k++)
    {
        for (int j=0;j<size3D_1[1];j++)
        {
          for (int i=0;i<size3D_1[0];i++)
          {
            fixedImage3Df_1->GetBufferPointer()[i+j*size3D_1[0]+k*size3D_1[0]*size3D_1[1]] = fixedImage3Df2_1->GetBufferPointer()[i+(size3D_1[1]-1-j)*size3D_1[0]+(/*size3D[2]-1-*/k)*size3D_1[0]*size3D_1[1]] ;
          }
          if(j==1){

          }

        }
    }


    qDebug()<<"lowerThreshold "<<lowerThreshold<<"upperThreshold "<<upperThreshold;

    for(int i=0;i< (size3D_1[0]*size3D_1[1]*size3D_1[2]);i++){
     if((fixedImage3Df_1->GetBufferPointer()[i]<upperThreshold)&&(fixedImage3Df_1->GetBufferPointer()[i]>lowerThreshold))
        dispVolume_1[i]=(fixedImage3Df_1->GetBufferPointer()[i]-lowerThreshold)*255/(upperThreshold-lowerThreshold);
     else
        dispVolume_1[i]=lowerThreshold;
    }





    float *mergedBufferVolume=NULL;
    mergedBufferVolume = new float[size3D[0]*size3D[1]*1024];


    for (int i=0;i<size3D[0]*size3D[1]*1024;i++)
    {

        mergedBufferVolume[i] = 0;

    }
    qDebug()<<"dispVolume size"<<mergedBufferVolume[134218736];
    int p=0;
    int q=0;

    for(int i=0; i<size3D[0]*size3D[1]*size3D[2];i++){
        mergedBufferVolume[i] = dispVolume[i];
        p++;
    }
    qDebug()<<"dispVolume size"<< p<<size3D[0]<<size3D[1]<<size3D[2];

    for(int i=134217728; i<268435456;i++){
        mergedBufferVolume[i] = dispVolume_1[q];
        q++;
//        qDebug()<<q;
    }
    qDebug()<<"dispVolume size"<< p<<q<<size3D[0]<<size3D[1];




//    for (int k = 0; k < 512;k++) {
//        for (int j=0;j<512;j++)
//        {
//            for (int i=0;i<512;i++)
//            {
//                //                   qDebug()<<"dispVolume 3";
//                mergedBufferVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]] = dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]];
//                if(k==208 && j==1){
//                    qDebug()<<"J&K"<<j<<k<<i<<dispVolume[i*j*k]<<dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]];
//                }
////                p++;

//            }

//        }
//    }


//     for (int x = 0; x < 1024; ++x) {
//            // Copy slices from bufferVolume1
//            for (int y = 0; y < size3D[1]; ++y) {
//                for (int z = 0; z < size3D[2]; ++z) {
//                    mergedBufferVolume[x * 1024 * size3D[2] + y * size3D[2] + z] = dispVolume[x * size3D[1] * size3D[2] + y * size3D[2] + z];
//                }
//            }
//            // Append slices from bufferVolume2
//            for (int y = 0; y < size3D[1]; ++y) {
//                for (int z = 0; z < size3D[2]; ++z) {
//                    mergedBufferVolume[x * 1024 * size3D[2] + (y + size3D[1]) * size3D[2] + z] = dispVolume1[x * size3D[1] * size3D[2] + y *size3D[2] + z];
//                }
//            }
//        }


    this->DisplayVolume(mergedBufferVolume);

}

void MainWindow::loadVolume(){

    seriesReader->SetImageIO( imgIO );

    QString dicomFolder=ui->LineEdit_InputPath->text();

    typedef itk::GDCMSeriesFileNames NamesGeneratorType;
    NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
    nameGenerator->SetUseSeriesDetails( true );
//    nameGenerator->AddSeriesRestriction("0008|0021" );
    nameGenerator->SetDirectory(dicomFolder.toStdString());


    try
    {
        //        std::cout << std::endl << "The directory: " << std::endl;
        //        std::cout << std::endl << dicomFolder.toStdString() << std::endl << std::endl;
        //        std::cout << "Contains the following DICOM Series: ";
        //        std::cout << std::endl << std::endl;

        typedef std::vector< std::string >    SeriesIdContainer;
        const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();

        SeriesIdContainer::const_iterator seriesItr = seriesUID.begin();

        while( seriesItr != seriesUID.end() )
        {
            std::cout << seriesItr->c_str() << std::endl;
            seriesItr++;
        }

        std::string seriesIdentifier = seriesUID.begin()->c_str();



        //        std::cout << "Now reading series: " << seriesIdentifier << std::endl;

        typedef std::vector< std::string >   FileNamesContainer;
        FileNamesContainer fileNames =nameGenerator->GetFileNames( seriesIdentifier );


        seriesReader->SetFileNames( fileNames );

        try
        {
            seriesReader->Update();
        }
        catch (itk::ExceptionObject &ex)
        {
            std::cout << ex << std::endl;
            //          return EXIT_FAILURE;
        }

    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
        //        return EXIT_FAILURE;
    }



    caster3D->SetInput(0,seriesReader->GetOutput());
    fixedImage3Df2 = caster3D->GetOutput();
    caster3D->Update();


    size3D[0]    =fixedImage3Df2->GetBufferedRegion().GetSize()[0];
    size3D[1]    =fixedImage3Df2->GetBufferedRegion().GetSize()[1];
    size3D[2]    =fixedImage3Df2->GetBufferedRegion().GetSize()[2];

    spacing3D[0] =fixedImage3Df2->GetSpacing()[0];
    spacing3D[1] =fixedImage3Df2->GetSpacing()[1];
    spacing3D[2] =fixedImage3Df2->GetSpacing()[2];

    origin3D[0]  =fixedImage3Df2->GetOrigin()[0];
    origin3D[1]  =fixedImage3Df2->GetOrigin()[1];
    origin3D[2]  =fixedImage3Df2->GetOrigin()[2];

    /*Allocate fixed Image and movingImage*/

     ImageType3Df::SizeType size1;
     size1[0] =  size3D[0];
     size1[1] =  size3D[1];
     size1[2] =  size3D[2];

     ImageType3Df::IndexType index1;
     index1[0] = 0;
     index1[1] = 0;
     index1[2] = 0;


     ImageType3Df::RegionType region1;
     region1.SetIndex(index1);
     region1.SetSize(size1);

     movingImage3Df->SetRegions(region1);
     movingImage3Df->Allocate(true);
     movingImage3Df->SetSpacing(spacing3D);
     movingImage3Df->SetOrigin(origin3D);


     movingImage3Df2->SetRegions(region1);
     movingImage3Df2->Allocate(true);
     movingImage3Df2->SetSpacing(spacing3D);
     movingImage3Df2->SetOrigin(origin3D);
     movingImage3Df2->Update();



     ImageType3Df::SizeType size2;
     size2[0] =  size3D[0];
     size2[1] =  size3D[1];
     size2[2] =  size3D[2];

     ImageType3Df::IndexType index2;
     index2[0] = 0;
     index2[1] = 0;
     index2[2] = 0;


     ImageType3Df::RegionType region2;
     region2.SetIndex(index2);
     region2.SetSize(size2);

     fixedImage3Df->SetRegions(region2);
     fixedImage3Df->Allocate(true);
     fixedImage3Df->SetSpacing(spacing3D);
     fixedImage3Df->SetOrigin(origin3D);

    /*Push loaded volume to display buffer*/
    if(dispVolume!=NULL)
        delete[] dispVolume;
    dispVolume = new float[ size3D[0]*size3D[1]*size3D[2]];


   /*Rearranging the volume from image coordinates to machine coordinates*/

    for (int k=0;k<size3D[2];k++)
    {
        for (int j=0;j<size3D[1];j++)
        {
          for (int i=0;i<size3D[0];i++)
          {
            fixedImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]] = fixedImage3Df2->GetBufferPointer()[(size3D[0]-1-i)+(size3D[2]-1-k)*size3D[0]+(size3D[1]-1-j)*size3D[0]*size3D[1]] ;

          }
        }
    }


/*
    lowerThreshold = 32768;
    upperThreshold =-32768;

    for(unsigned int i=0;i< (size3D[0]*size3D[1]*size3D[2]);i++){
     if(fixedImage3Df->GetBufferPointer()[i]>upperThreshold)
         upperThreshold=fixedImage3Df->GetBufferPointer()[i];
     if(fixedImage3Df->GetBufferPointer()[i]<lowerThreshold)
         lowerThreshold=fixedImage3Df->GetBufferPointer()[i];
    }

    qDebug()<<"lowerThreshold "<<lowerThreshold<<"upperThreshold "<<upperThreshold;
    for(unsigned int i=0;i< (size3D[0]*size3D[1]*size3D[2]);i++){
     dispVolume[i]=(fixedImage3Df->GetBufferPointer()[i]-lowerThreshold)*255/(upperThreshold-lowerThreshold);
    }

*/

    qDebug()<<"lowerThreshold "<<lowerThreshold<<"upperThreshold "<<upperThreshold;

    for(int i=0;i< (size3D[0]*size3D[1]*size3D[2]);i++){
     if((fixedImage3Df2->GetBufferPointer()[i]<upperThreshold)&&(fixedImage3Df2->GetBufferPointer()[i]>lowerThreshold))
        dispVolume[i]=(fixedImage3Df2->GetBufferPointer()[i]-lowerThreshold)*255/(upperThreshold-lowerThreshold);
     else
        dispVolume[i]=0;
    }

    this->DisplayVolume(dispVolume);

}

void MainWindow::m_resampleCtData()
{
    QString Dicomheader="D:\\TransformCT";
     QString xmlFile = Dicomheader+"\\Dicom_HeadersList.xml";//name of the file is fixed
//    QString xmlFile ="D:\\dummymotion\\kv1\\Dicom_HeadersList.xml";
    /////create a folder if don't exist.//////

    QString cbctwritepath=/*CT_DICOM_Path*/ui->lineEdit_SavePAth->text()+"\\volume1";

    //////////////MATLAB REPLACEMENT////////////////`

    qDebug()<<"11_______";
    vtkSmartPointer <vtkDICOMDirectory> dicomdir =
            vtkSmartPointer <vtkDICOMDirectory>:: New ();
    dicomdir -> SetDirectoryName (cbctwritepath.toStdString().c_str());

    ExtBuffer = new unsigned short[512*512*866];




    try
    {
        dicomdir ->Update ();
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
        //return;

    }


     QDir directory(cbctwritepath);
     int fileCount = 0;
     QFileInfoList fileInfoList = directory.entryInfoList(QDir::Files);
     foreach (QFileInfo fileInfo, fileInfoList) {
         fileCount++;
     }
     qDebug()<<"filecount::"<<fileCount;



    vtkSmartPointer<vtkDICOMReader> reader1 = vtkSmartPointer<vtkDICOMReader>::New();
    vtkSmartPointer<vtkDICOMReader> reader12=NULL;

    int  numSeries=dicomdir->GetNumberOfSeries();
    qDebug()<<"dicomseries::"<<dicomdir->GetNumberOfSeries()<<cbctwritepath;

    vtkStringArray *sortedFiles;

    qDebug()<<"Number of Series found :"<<numSeries;

    if(numSeries>1 || numSeries == 0)
        qDebug()<<"error";//QMessage Box to be added


    sortedFiles = dicomdir -> GetFileNamesForSeries (numSeries-1);




    for(int i=0;i<sortedFiles->GetNumberOfValues();i++){
//        qDebug()<<"entering for::"<<i;

        if(reader1->CanReadFile(sortedFiles->GetValue(i))){

            reader1->SetFileName(sortedFiles->GetValue(i));
            reader1->SetGlobalWarningDisplay(true);

            try
            {
                reader1->Update();
            }
            catch(...)
            {
                qDebug()<<"Exception  reading dicom files";
                 //return;
            }

            if(QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(
                                          vtkDICOMTag(0x0008,0x0060)).AsString()).compare("RTIMAGE")==0)
            {
                //return;
            }

            if(QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(
                                          vtkDICOMTag(0x0008,0x0060)).AsString()).compare("RTSTRUCT")==0){

                //qDebug()<<"RTSTRUCT available"<<rtStructFile;

            }

        }
    }
    qDebug()<<"for loop done";
    QString temp_row = QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0028,0x0010)).AsString());

    QString temp_col = QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0028,0x0011)).AsString());

    QString slicethickness = QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0018,0x0050)).AsString());
    qDebug()<<"slicethickness"<<slicethickness<<fileCount;


    double thickness = slicethickness.toDouble();
    double scan_length = (fileCount)*thickness;
    qDebug()<<"Thicness & scan length::"<<thickness<<scan_length;


    int ctDIM1=512;
    int ctDIM2=512;
    int ctDIM3 = (scan_length/0.5);

    if(ctDIM3%2==0)
    {
        ctDIM3=ctDIM3;
    }
    else
    {
        ctDIM3=ctDIM3+1;
    }

    qDebug()<<"ctDIM values::"<<ctDIM3;



    qDebug()<<"ctDIM values::"<<ctDIM1<<ctDIM2<<ctDIM3;


    QString temp = QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0018,0x1100)).AsString());
    int recondiameter = temp.toDouble();
    qDebug()<<"tag::"<<temp<<recondiameter;

    double x_resolution;
    double y_resolution;
    double min_dim_x;
    double min_dim_y;

    double max_dim_x;
    double max_dim_y;

    x_resolution = recondiameter/0.5;
    y_resolution = recondiameter/0.5;

    if(x_resolution>512)
    {
       min_dim_x = (x_resolution-512)/2;
       min_dim_y = (y_resolution-512)/2;

       max_dim_x=x_resolution;
       max_dim_y=y_resolution;

    }
    if(x_resolution==512)
    {
       max_dim_x = x_resolution;
       max_dim_y = y_resolution;

       min_dim_x=0;
       min_dim_y=0;
    }

    qDebug()<<"tag::"<<min_dim_y<<max_dim_y<<min_dim_x<<max_dim_x<<x_resolution<<y_resolution;



    reader1=NULL;
    reader12 =NULL;

    reader12 =vtkSmartPointer<vtkDICOMReader>::New();
    reader12->SetFileNames(sortedFiles);
    //    reader->SetDataScalarTypeToShort(); //Commented on 01-01-2022
    reader12->SetMemoryRowOrderToFileNative();

    try
    {
        reader12->Update();
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
        //return;

    }
    qDebug()<<"reader12 updated::";

    //----------------------------Origin from text doc-------------------------------//

    QString shiftfile = "D:\\CT_Slices.txt";

    QFile filename1(shiftfile);

    QString line;
    QString min_value;
    QString max_value;


    if(filename1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&filename1);
        bool posFind=false;
        int posCnt=0;

        while( !in.atEnd())
        {
            line = in.readLine();
            if (line.contains("Slice_values"))
            {
                posFind=true;
            }
            if(posFind && posCnt<3)
            {
                if(line.contains("min"))
                {
                   QStringList splitD = line.split("=");
                   min_value = splitD.at(1);
                }
                if(line.contains("max"))
                {
                   QStringList splitD = line.split("=");
                   max_value = splitD.at(1);
                }

                posCnt++;
                if(posCnt==3)
                    break;
            }

    }
    }
    qDebug()<<"shift_values"<<min_value<<max_value;

    //----------------------------Origin from text doc-------------------------------//

    qDebug()<<"14_______";
    vtkSmartPointer<vtkImageData> volume123 = vtkSmartPointer<vtkImageData>::New();
    volume123->DeepCopy(reader12->GetOutput());

//    qDebug()<<"1_______!!!!!!"<<ctDIM1<<ctDIM2<<ctDIM3<<slicePixelX<<slicePixelY<<sThickness<<m_recondia<<FanSelection;

//    ctDIM3= m_scanlengthCT/sThickness;
    vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
    reslice->SetInputData(volume123);
    reslice->SetInterpolationModeToLinear();
    //    double targetSpacing12[3]={slicePixelX,slicePixelY,sThickness};
    if(FanSelection==1)
    {
        reslice->SetOutputSpacing(0.5,0.5,0.5);
    }
    else
    {
        reslice->SetOutputSpacing(1,1,1);
    }
    //reslice->SetOutputDimensionality(m_recondia);
    reslice->SetOutputExtent(0,ctDIM1-1,0,ctDIM2-1,0,ctDIM3-1);
    reslice->Update();

    /////DETECTOR TEMP
    //bar->setValue(80);
    qDebug()<<"qqqqq";
    //  QProcess process;
    //  process.start("Resampling.exe");
    //  process.waitForFinished();


    //  QString program = qApp->applicationDirPath()+"\\Resampling.exe";



    //        QProcess* myProcess2 = new QProcess();
    //        myProcess2->start(program);
    //        myProcess2->waitForStarted();
    //        _sleep(20000);

    // Step 5: Save the resampled volume as a .nii file using vtkNIFTIImageWriter
    vtkSmartPointer<vtkNIFTIImageWriter> writer = vtkSmartPointer<vtkNIFTIImageWriter>::New();
    writer->SetFileName("D:\\output\\output_resampled12.nii"); // Output filename with .nii extension
    writer->SetInputData(reslice->GetOutput());
    qDebug()<<"1_______";
    writer->Write();

    //   WinExec("Resampling.exe", SW_HIDE);
    //  _sleep(20000);
    //  Call Matlab exe for creation Volume.ini

    //Temporarily Commenting CT Reconstruction because of diff GPU card
    qDebug()<<"after";

//    ctDIM1 = 512;
//    ctDIM2 = 512;
//    ctDIM3 = fileCount;

    short *volfloat;
    int size2=ctDIM1*ctDIM2*ctDIM3;
    volfloat= new  short[size2];
    int min = min_value.toInt();
    int max = max_value.toInt();

    using ImageType = itk::Image<float, 3>;
    using ReaderType = itk::ImageFileReader<ImageType>;

    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName("D:\\output\\output_resampled12.nii");
    try
    {
        reader->Update();
    }
    catch(itk::ExceptionObject &ex)
    {
        qDebug()<<"Exception  reading nifti files";
        std::cerr << ex << std::endl;
        return;

    }

    qDebug()<<"reader updated::";


    ImageType::Pointer image = reader->GetOutput();

    // Get the size of the image volume
    ImageType::SizeType size1 = image->GetLargestPossibleRegion().GetSize();

    // Access the image data as a 3D array
    float *data = image->GetBufferPointer();

    qDebug()<<"Size value"<<size1[0]<<size1[1]<<size1[2];



    for(int i=0;i<ctDIM3;i++)//z
    {

        for(int j=0;j<ctDIM2;j++)//y
        {

            for(int k=0;k<ctDIM1;k++)//x
            {
                volfloat[k+ctDIM1*j+(ctDIM1*ctDIM2*i)]= static_cast<float>(data[i*ctDIM1*ctDIM2+j*ctDIM1+k]);

            }

        }
    }
    if(FanSelection==2){
//        m_ctDIM1=400;m_ctDIM2=400;m_ctDIM3=454;
        ctDIM1=400;ctDIM2=400;ctDIM3=454;
    }

    vtkImageImport * vol1 = vtkImageImport::New();
//    cbctimgnumcount1=0;
    //    float x=-(0.5*(volumeSize-1)*0.5);
    float x12=-(0.5*(ctDIM1-1)*0.5);
    float x22=-(0.5*(ctDIM2-1)*0.5);
    float x32=-(0.5*(ctDIM3-1)*0.5);

//    m_recondia=ctDIM1*slicePixelX;

//    qDebug()<<"Reconstruction Diameter"<<m_recondia<<m_CTFOV;

    vol1->CopyImportVoidPointer(volfloat/*volume*/, sizeof(short)*ctDIM1*ctDIM2*ctDIM3);

    //    vol->CopyImportVoidPointer(volShort/*volume*/, sizeof(short)*volumeSize*volumeSize*volumeSize);
    vol1->SetDataScalarTypeToShort();
    vol1->SetNumberOfScalarComponents(1);
    qDebug()<<"ctDIM3 value::"<<ctDIM3;
    if(FanSelection==1)
    {
    vol1->SetWholeExtent(0,ctDIM1-1,0,ctDIM2-1,0,ctDIM3-1);
    }
    else
    {
        vol1->SetWholeExtent(0,ctDIM1-1,0,ctDIM2-1,27,ctDIM3);

    }

    //    vol->SetWholeExtent(0, (volumeSize-1), 0, (volumeSize-1), 0, (volumeSize-1));
    vol1->SetDataExtentToWholeExtent();
    if(FanSelection==1)
    {
    vol1->SetDataSpacing(0.5,0.5,0.5);
    }
    else
    {
        vol1->SetDataSpacing(1,1,1);
    }
//    vol1->SetDataSpacing(m_recondia/(float)ctDIM1,m_recondia/(float)ctDIM2,/*256.0/(float)ctDIM3*/sThickness);
    //    vol->SetDataOrigin(x,-x,x );//data origin is fixed.
    qDebug()<<"check data origin"<<x12<<-x22<<x32<<ctDIM1<<ctDIM2<<ctDIM3;
    //vol1->set
    vol1->SetDataOrigin(x12,-x22,x32 );//data origin is fixed.

qDebug()<<"data origin is fixed";

//vtkSmartPointer<vtkExtractVOI> extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
//extractVOI->SetInputData(vol1->GetOutput());
//qDebug()<<"Input done";


//// Set the region of interest (example: X: 10-50, Y: 20-80, Z: 5-30)
//extractVOI->SetVOI(0,ctDIM1-1,0,ctDIM2-1, min_value.toInt()-1, max_value.toInt()-1);
//qDebug()<<"VOI done"<<min_value<<max_value;


//// Update the filter
////try
////{
//    qDebug()<<"entering try::";
//    extractVOI->Update();
////}

//if (extractVOI->GetErrorCode() != 0) {
//    std::cerr << "Error executing vtkExtractVOI. Error code: "
//              << extractVOI->GetErrorCode() << std::endl;
//    // Handle the error as needed
//}
//else
//{
//    qDebug()<<"No errorcode";
//}




//qDebug()<<"VOI updated";


//// Access the cropped dataset
//vtkDataSet* croppedDataSet = extractVOI->GetOutput();

//vtkImageImport * vol2 = vtkImageImport::New();

//vol2->CopyImportVoidPointer(croppedDataSet/*volume*/, sizeof(short)*ctDIM1*ctDIM2*512);

//vol2->SetDataScalarTypeToShort();
//vol2->SetNumberOfScalarComponents(1);
//if(FanSelection==1)
//{
//vol2->SetWholeExtent(0,ctDIM1-1,0,ctDIM2-1,0,512);
//}
//else
//{
//    vol2->SetWholeExtent(0,ctDIM1-1,0,ctDIM2-1,27,ctDIM3);

//}

////    vol->SetWholeExtent(0, (volumeSize-1), 0, (volumeSize-1), 0, (volumeSize-1));
//vol2->SetDataExtentToWholeExtent();
//if(FanSelection==1)
//{
//vol2->SetDataSpacing(0.5,0.5,0.5);
//}
//else
//{
//    vol2->SetDataSpacing(1,1,1);
//}
////    vol1->SetDataSpacing(m_recondia/(float)ctDIM1,m_recondia/(float)ctDIM2,/*256.0/(float)ctDIM3*/sThickness);
////    vol->SetDataOrigin(x,-x,x );//data origin is fixed.
//qDebug()<<"check data origin"<<x12<<-x22<<x32<<ctDIM1<<ctDIM2<<ctDIM3;
////vol1->set
//vol2->SetDataOrigin(x12,-x22,x32 );//data origin is fixed.




//    DicomCbct dicom;
      bool readSucess1= dicom->readTags(xmlFile);
    qDebug()<<"readSuccess1::::::"<<readSucess1<<xmlFile;
    if(!readSucess1){
        //            QMessageBox::warning(this,"Status","Cannot read  .xml file");
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setWindowIcon(QIcon(":/theme/Themes/PANACEA.png"));
        msgBox->setWindowTitle("ERROR");
        msgBox->setText("Cannot read .xml file");
        msgBox->exec();
        delete msgBox;
        return;
    }
//    m_clearctdata();
//    dicom->setVtkVolume(vol1);

    dicom->dicomWrite(ui->lineEdit_SavePAth->text()+"\\volume2",vol1);
    qDebug()<<"Done::";

    QDir directory1(ui->lineEdit_SavePAth->text()+"\\volume2"); // Replace with your directory path
    QStringList fileList = directory1.entryList(QDir::Files);

    int shifted_fileCount = 0;
    QFileInfoList fileInfoList1 = directory1.entryInfoList(QDir::Files);
    foreach (QFileInfo fileInfo, fileInfoList1) {
        shifted_fileCount++;
    }
    qDebug()<<"shifted_filecount::"<<shifted_fileCount;
    qDebug()<<"Raw_ct filecount::"<<ct_count<<center_ct_y;

    double Half_shifted_filecnt = shifted_fileCount/2;
    double shifted_slices;
    double ct_filecount = center_ct_y*2;
    if(ct_filecount==ct_count)
    {
        shifted_slices = 0;
    }
    else if(ct_filecount==(ct_count+1) || ct_filecount==(ct_count-1))
    {
        shifted_slices = 0;
    }
    else
    {
        shifted_slices =ct_y_shift/0.5;
    }

    qDebug()<<"shifted_slices & raw Ct file count::"<<shifted_slices<<ct_filecount;


    double new_y_center = Half_shifted_filecnt+shifted_slices;

    qDebug()<<"new_y_center & sliceThickness"<<new_y_center<<slicethickness<<ct_y_shift;


    int min_1 = /*min_value.toInt()-1*/ new_y_center-256;
    int max_1 = /*max_value.toInt()-1*/new_y_center+256;
    qDebug()<<"min_1 & max_1::"<<min_1<<max_1;

    for (int i = 0; i < min_1 && i < fileList.size(); ++i) {
        QString filePath_strt = directory1.filePath(fileList[i]);
        QFile::remove(filePath_strt);
//        if (QFile::remove(filePath)) {
//            qDebug() << "Deleted file:" << filePath;
//        } else {
//            qDebug() << "Failed to delete file:" << filePath;
//        }
    }

    for (int i = fileList.size() - 1; i >= max_1 && i >= 0; --i) {
        QString filePath_end = directory1.filePath(fileList[i]);
        QFile::remove(filePath_end);
//        if (QFile::remove(filePath)) {
//            qDebug() << "Deleted file:" << filePath;
//        } else {
//            qDebug() << "Failed to delete file:" << filePath;
//        }
    }

    qDebug()<<"completed::";
    QMessageBox *msg = new QMessageBox();
    msg->setWindowTitle("Information");
    msg->setIcon(QMessageBox::Information);
    msg->setText("CT files removed");
    msg->exec();
    delete msg;



    /////////////////////////////---------------------------commented for testing----------------------------------///////////////////////////////

//    int ct_dimension=512;

//    QString dirPath= "D:\\TransformCT\\volume2";
//    QDir directory1(dirPath);

//    QStringList filters;
//    filters << "*.dcm";  // Add more extensions if needed

//    directory1.setNameFilters(filters);
//    directory1.setFilter(QDir::Files | QDir::NoSymLinks);

//    QStringList fileList = directory1.entryList();

//    unsigned short *temp_buffer1 = new unsigned short[ct_dimension*ct_dimension];
//    if (fileList.isEmpty()) {
//        qDebug() << "No DICOM files found in the directory.";
//    } else {
//        int x=0;
//        foreach (const QString &file1, fileList) {
////           qDebug() << directory1.absoluteFilePath(file1);
////           typedef itk::Image<signed short,2> ImageType2;
//           using ImageType2 = itk::Image<signed short,2>;
//           using ReaderType2 = itk::ImageFileReader<ImageType2>;
//           ReaderType2::Pointer reader2 = ReaderType2::New();
//           itk::GDCMImageIO::Pointer dicomIO = itk::GDCMImageIO::New(); // Use GDCMImageIO for DICOM files
//           reader2->SetImageIO(dicomIO);
//           reader2->SetFileName(directory1.absoluteFilePath(file1).toStdString()); // Input DICOM file
//           try
//           {
//               reader2->Update();

//           }
//           catch (itk::ExceptionObject & ex)
//           {
//               std::cerr << "Error reading the DICOM image: " << ex << std::endl;
//           }

//           ImageType2::Pointer dicomImage = reader2->GetOutput();
//           ImageType2::SizeType size= dicomImage->GetLargestPossibleRegion().GetSize();


//           unsigned short * input = new unsigned short[860*860];
////           qDebug()<<"size::"<<size[0]<<size[1];
//           size[0]=860;
//           size[1]=860;

//           itk::ImageRegionConstIterator<ImageType2> it(dicomImage,dicomImage->GetLargestPossibleRegion());
//           while(!it.IsAtEnd()){
//               input[it.GetIndex()[1]*size[0]+it.GetIndex()[0]]=it.Get();
//               ++it;
//           }

//           unsigned short **bckgnd_img = new unsigned short*[ct_dimension];
//           unsigned short **bckgnd_img_1_QARA = new unsigned short*[x_resolution];
//           for(int i=0;i<x_resolution;i++){
//              bckgnd_img_1_QARA[i] = new unsigned short[x_resolution];
//           }

//           for(int i=0;i<ct_dimension;i++){
//              bckgnd_img[i] = new unsigned short[ct_dimension];
//           }


//           int p=0;
//           for(int i=0;i<x_resolution;i++){
//               for(int j=0;j<x_resolution;j++){
//                   bckgnd_img_1_QARA[i][j]=input[p];
//                   p=p+1;
//               }
//           }

//           int origin_begin_x=(x_resolution-ct_dimension)/2;//the more u increase this the more left the image will shift.
//           int origin_end_x=x_resolution-((x_resolution-ct_dimension)/2);
//           int origin_begin_y=(y_resolution-ct_dimension)/2;
//           int origin_end_y =y_resolution-((y_resolution-ct_dimension)/2);int pi1=0,pj=0;

//           for(int i=origin_begin_y;i<origin_end_y;i++)//801
//           {
//               for(int j=origin_begin_x;j<origin_end_x;j++)//802 //668->768
//               {
//                   bckgnd_img[pi1][pj] = bckgnd_img_1_QARA[i][j];
//                   pj++;
//               }
//               pi1++;
//               pj=0;
//           }


//           int index =0;
//           for (int i = 0; i < ct_dimension; i++) {
//               for (int j = 0; j < ct_dimension; j++) {
//                   temp_buffer1[index] = bckgnd_img[i][j];
//                   index++;
//               }
//           }


//           QByteArray ba;
//           std::string outputDirectory = "D:\\output1\\";
//           // Construct the output file path
//           std::string outputFile = outputDirectory +"projD1_"+std::to_string(x)+".raw";


//           FILE* file11 = fopen(outputFile.c_str(), "wb");

//           if (file11) {
//              // Write the raw image data to the file
//              fwrite(temp_buffer1, 1, ct_dimension*ct_dimension*(sizeof(unsigned short)), file11);

//              // Close the file
//              fclose(file11);
//           }
//           x=x+1;
//        }




//    }
//    qDebug()<<"raw file written";

//    QString dirPath_raw= "D:\\output1\\";
//    QDir directory2(dirPath_raw);

//    QByteArray ba;
//    QStringList filters2;
//    filters2 << "*.raw";  // Add more extensions if needed

//    directory2.setNameFilters(filters2);
//    directory2.setFilter(QDir::Files | QDir::NoSymLinks);

//    QStringList fileList2 = directory2.entryList();

//     for (int i=3;i<fileList2.length()+1;++i){
//           ba =(dirPath_raw+"projD1_"+QString::number(i)+".raw").toLatin1();

//           const char *fileName = ba.data();
//           FILE    *fp;
//           fopen_s(&fp, fileName, "rb");

//           if(fp)
//           {
//               fread(ExtBuffer+(i-1)*(512*512), sizeof(unsigned short),512*512, fp);
//               fclose(fp);
//           }

//     }
//     qDebug()<<"raw file copied to pointer::";
//     vtkImageImport * vol3 = vtkImageImport::New();

//     float x112=-(0.5*(512-1)*0.5);
//     float x122=-(0.5*(512-1)*0.5);
//     float x132=-(0.5*(866-1)*0.5);

//     ctDIM1=512;
//     ctDIM2=512;
//     ctDIM3=866;


//     vol3->CopyImportVoidPointer(ExtBuffer/*volume*/, sizeof(short)*ctDIM1*ctDIM2*ctDIM3);

//     //    vol->CopyImportVoidPointer(volShort/*volume*/, sizeof(short)*volumeSize*volumeSize*volumeSize);
//     vol3->SetDataScalarTypeToShort();
//     vol3->SetNumberOfScalarComponents(1);
//     if(FanSelection==1)
//     {
//     vol3->SetWholeExtent(0,ctDIM1-1,0,ctDIM2-1,0,/*max_value.toInt()-1*/ctDIM3-1);
//     }
//     else
//     {
//         vol1->SetWholeExtent(0,ctDIM1-1,0,ctDIM2-1,27,ctDIM3);

//     }

//     //    vol->SetWholeExtent(0, (volumeSize-1), 0, (volumeSize-1), 0, (volumeSize-1));
//     vol3->SetDataExtentToWholeExtent();
//     if(FanSelection==1)
//     {
//     vol3->SetDataSpacing(0.5,0.5,0.5);
//     }
//     else
//     {
//         vol3->SetDataSpacing(1,1,1);
//     }
// //    vol1->SetDataSpacing(m_recondia/(float)ctDIM1,m_recondia/(float)ctDIM2,/*256.0/(float)ctDIM3*/sThickness);
//     //    vol->SetDataOrigin(x,-x,x );//data origin is fixed.
//     qDebug()<<"check data origin"<<x12<<-x22<<x32<<ctDIM1<<ctDIM2<<ctDIM3;
//     //vol1->set
//     vol3->SetDataOrigin(x112,-x122,x132 );//data origin is fixed.

//     bool readSucess3= dicom->readTags(xmlFile);
//   qDebug()<<"readSuccess1::::::"<<readSucess1<<xmlFile;
//   if(!readSucess3){
//       //            QMessageBox::warning(this,"Status","Cannot read  .xml file");
//       QMessageBox *msgBox = new QMessageBox(this);
//       msgBox->setWindowIcon(QIcon(":/theme/Themes/PANACEA.png"));
//       msgBox->setWindowTitle("ERROR");
//       msgBox->setText("Cannot read .xml file");
//       msgBox->exec();
//       delete msgBox;
//       return;
//   }

//   dicom->dicomWrite(ui->lineEdit_SavePAth->text()+"\\volume3",vol3);

    /////////////////////////////---------------------------commented for testing----------------------------------///////////////////////////////














//    QString program = qApp->applicationDirPath()+"\\writeadditionaltags"+"\\writeadditionaltags.exe";

//    //     qDebug()<<""<<program<<AP_DICOM_Path;
//    QStringList arguments;

//    QString m_CTFid= QString::number(m_fadct);
//    QString m_CTScan= QString::number(m_scanlengthCT);

////    QString path= "D:\\DicomSend";
//    arguments<<CT_DICOM_Path<<m_CTFid<<m_CTScan;

//    QProcess* myProcess = new QProcess();
//    myProcess->start(program, arguments);
//    myProcess->waitForStarted();


//    QString fPath = CT_DICOM_Path;
//    if(fPath == 0||fPath == "")
//    {
//        QMessageBox::warning(this,"Warning","No path found !!");
//        return;
//    }

//    QDir dir(fPath);
//    QStringList filters;
//    QStringList dcmList;

//    if(!dir.exists())
//    {
//        QMessageBox::warning(this,"Warning","Directory does not exists !!");
//    }

//    filters << "*.dcm" ;
//    dir.setNameFilters(filters);
//    dcmList = dir.entryList(filters);

//    qDebug()<<"No of CT dicom files : "<<dcmList.length();

//    if(dcmList.length()==0){
//        QMessageBox::warning(this,"Error","No images found..");
//        return;
//    }

}

void MainWindow::on_GPU_Transform3D_clicked()
{
    fanselect = ui->lineEdit_fanSelection->text();
    qDebug()<<"fanselect::"<<fanselect;
    FanSelection=fanselect.toInt();

    if(movingImage3Df.IsNull() || fixedImage3Df.IsNull())
        return;




    float h_angle3D[3];
    h_angle3D[0]=ui->lineEdit_Pitch_in->text().toDouble();//in degree
    h_angle3D[2]=ui->lineEdit_Yaw_in->text().toDouble();//in degree
    h_angle3D[1]=ui->lineEdit_Roll_in->text().toDouble();//in degree

    float translation3D[3];
    translation3D[0]=ui->lineEdit_XShift_in->text().toDouble();//in mm
    translation3D[2]=ui->lineEdit_ZShift_in->text().toDouble();//in mm
    translation3D[1]=ui->lineEdit_YShift_in->text().toDouble();//in mm

    float * buffer = new float[size3D[0]*size3D[1]*size3D[2]];

    qDebug()<<"test calling ";
   // findMutualInformation(float* h_input1, float* h_input2, unsigned int* size, float* MI);
//    findMutualInformation(fixedImage3Df->GetBufferPointer(), fixedImage3Df->GetBufferPointer(),(unsigned int *) size3D,buffer);

    qDebug()<<"rigidTransformation3D";



    //rigidTransformation3D(fixedImage3Df->GetBufferPointer(),(unsigned int *)size3D,spacing3D,h_angle3D,translation3D,movingImage3Df->GetBufferPointer());

//    rigidTransformation3D(/*fixedImage3Df->GetBufferPointer()*/ buffer,(unsigned int *)size3D, /*(float *)fixedImage3Df->GetSpacing()*/ spacing3D,h_angle3D,translation3D,buffer);
    qDebug()<<"rigidTransformation3D 2";

    for (int k=0;k<size3D[2];k++)
    {
        for (int j=0;j<size3D[1];j++)
        {
          for (int i=0;i<size3D[0];i++)
          {
            if((movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]]<upperThreshold)&&(movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]]>lowerThreshold))
               dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]] = (movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]]-lowerThreshold)*255/(upperThreshold-lowerThreshold) ;
            else if((movingImage3Df->GetBufferPointer()[i+j*size3D[0]+k*size3D[0]*size3D[1]])>upperThreshold)
               dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]]=upperThreshold;
            else
                dispVolume[i+j*size3D[0]+k*size3D[0]*size3D[1]]=lowerThreshold;

          }
        }
    }

    qDebug()<<"j nhkkkkkkkkkkkkkkkk";


//    for(int i=0;i< (size3D[0]*size3D[1]*size3D[2]);i++){
//     if((movingImage3Df->GetBufferPointer()[i]<upperThreshold)&&(movingImage3Df->GetBufferPointer()[i]>lowerThreshold))
//        dispVolume[i]=(movingImage3Df->GetBufferPointer()[i]-lowerThreshold)*255/(upperThreshold-lowerThreshold);
//     else
//        dispVolume[i]=0;
//    }


   this->DisplayVolume(dispVolume);

//     qApp->processEvents();

//    this->DisplayVolume(movingImage3Df->GetBufferPointer());

   ui->label_Status->setText("Transform Applied");

   }



