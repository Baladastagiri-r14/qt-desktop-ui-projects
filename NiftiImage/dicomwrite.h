#ifndef DICOMWRITE_H
#define DICOMWRITE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <vtkSmartPointer.h>
#include <vtkDICOMReader.h>

////#include <afxstr.h>
#include <vtkDICOMMRGenerator.h>

#include <vtkImageImport.h>
#include <vtkDICOMCTGenerator.h>
#include <vtkDICOMTag.h>
#include <vtkDICOMMetaData.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include<vtkDirectory.h>
#include<vtkMatrix4x4.h>
#include <vtkDICOMWriter.h>
#include<vtkDICOMSorter.h>
#include<vtkDICOMDirectory.h>
#include<vtkImageExport.h>
#include<vtkIntArray.h>
#include<vtkMedicalImageProperties.h>

#include <vtkDICOMImageReader.h>
#include <vtkImageReslice.h>
#include <QGraphicsColorizeEffect>
#include <vtkDICOMGenerator.h>
#include <vtkDICOMUIDGenerator.h>
#include <atlstr.h>
#include <vtkStringArray.h>
#include <vtkTransform.h>
#include <vtkDICOMVR.h>

//itk libraries
#include "itkImage.h"
#include "itkImageToVTKImageFilter.h"
#include <itkImageRegionIterator.h>

struct DicomTagElements
{
    int Group;
    int Element;
    int No;
    std::string VRKey;
    std::string Data;
};
class dicomwrite:public QObject
{
    Q_OBJECT
public:
        dicomwrite(QWidget* parent=0);
        bool readTags(const QString vFileName);
        void dicomWrite(QString filepath,vtkImageImport *v);
//        void CBCTDicomHeaderFile(CString patientPath);

        QList<DicomTagElements> tagList;
        float *vol;
        vtkImageImport *volume;
        int* dim;
        short *v;
        unsigned short *v1;
        QString opnm;//="Rakesh";
        QString versionNo;//="1234";
        QString RTID;
        QString patientName;
        QString patientAge;
        QString patientGender;
        QString StudyInstanceUID;
        QString SeriesInstanceUID;
        QString SOPinstanceUID;
        QString StudyDescription;
        QString SeriesDescription;
        QString FractionNumber;
        QString StudyID;
        QString siteno;
        QString phaseno;
        QString BeamCount;
        QStringList ImagingModes;



        QString ImageTypes;
        QString InstanceCreationDate;
        QString InstanceCreationTime;
        QString SOPClassUIDs;
        QString StudyDate;
        QString SeriesDate;
        QString AcquisitionDate;
        QString ContentDate;
        QString StudyTime;
        QString SeriesTime;
        QString AcquisitionTime;
        QString ContentTime;
        QString AccessionNumber;
        QString Modality;
        QString Manufacturer;
        QString InstitutionName;
        QString ReferringPhysiciansName;
        QString StationName;
        QString PerformingPhysiciansName;
        QString OperatorsName;
        QString ManufacturersModelName;
        QString PatientID;
        QString patientsBirthDate;
        QString PatientsSex;
        QString ScanOptions;
        QString SliceThickness2;
        QString KVP;
        QString DataCollectionDiameter;
        QString DeviceSerialNumber;
        QString SoftwareVersions;
        QString ProtocolName;
        QString ReconstructionDiameter;
        QString GantryDetectorTilt;
        QString TableHeight;
        QString RotationDirection;
        QString ExposureTime;
        QString XRayTubeCurrent;
        QString ExposureInuAs;
        QString FilterType;
        QString GeneratorPower;
        QString FocalSpots;
        QString DateofLastCalibration;
        QString TimeofLastCalibration;
        QString ConvolutionKernel;
        QString PatientPosition;
        QString SeriesNumber;
        QString AcquisitionNumber;
        QString InstanceNumber;

        QStringList ImagePositionPatients;
        QStringList ImageOrientationPatient;
        QString FrameofReferenceUID;
        QString PositionReferenceIndicator;
        QString SliceLocation;
        QString SamplesperPixel;
        QString PhotometricInterpretation;
        QString Rows;
        QString Columns;
        QStringList PixelSpacing;
        QString BitsAllocated;
        QString BitsStored;
        QString HighBit;
        QString PixelRepresentation;
        QString SmallestImagePixelValue;
        QString LargestImagePixelValue;
        QString SmallestPixelValueinSeries;
        QString LargestPixelValueinSeries;
        QString QualityControlImage;
        QString RescaleIntercept;
        QString RescaleSlope;
        QString PixelData;
        QString WindowWidth;
        QString WindowCenter;
         QString PatPos;
        vtkSmartPointer<vtkDICOMReader> reader=NULL;
        vtkSmartPointer<vtkDICOMWriter> writer1=NULL;

        char PID[16];
        char Pname[33];
        char Pat_pos[30];
        char site_name[33];
        char Pat_gender[16];
        char operatorName[30];
        //char versionNo[30];
        int Pat_age;
        int IIKv,IIma,IIms;

        void setVtkVolume(vtkImageImport *v);

};

#endif // DICOMWRITE_H
