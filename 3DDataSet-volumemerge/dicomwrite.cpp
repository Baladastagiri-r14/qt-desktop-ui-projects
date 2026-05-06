#include "dicomwrite.h"
#include <QDebug>
#include <QtXml/qdom.h>
#include <QFile>
#include "gdcmUIDGenerator.h"
#include <mutex>
#include <QMessageBox>


std::mutex writerMutex;

dicomwrite::dicomwrite(QWidget* parent)
{

}

bool dicomwrite::readTags(const QString vFileName)
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

void dicomwrite::dicomWrite(QString filepath,vtkImageImport *v)
{
    qDebug()<<"Entering writer::"<<filepath;
    /*vtkSmartPointer <vtkDICOMWriter>*/ writer1 =vtkSmartPointer <vtkDICOMWriter>:: New ();



//    vtkImageImport *volume = vtkImageImport::New();
    volume=v;
    filepath="D:\\TransformCT\\volume2";
    qDebug()<<"Volume copied:::"<<filepath;

    vtkSmartPointer <vtkDICOMCTGenerator> generator;
    generator =vtkSmartPointer <vtkDICOMCTGenerator>::New();
    // Create a meta data object with some desired attributes.
    vtkSmartPointer <vtkDICOMMetaData> meta =
            vtkSmartPointer <vtkDICOMMetaData>:: New ();
    //crashes here in debug mode !!

    vtkDICOMTag DicomTag;
    for (int i=0;i<tagList.length();i++){
        DicomTag = vtkDICOMTag(tagList.at(i).Group,tagList.at(i).Element);
        meta->SetAttributeValue(tagList.at(i).No,DicomTag,tagList.at(i).VRKey);
        meta->SetAttributeValue(DicomTag,tagList.at(i).Data);

    }
    qDebug()<<"Data Tag"<<tagList.length();

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
//    m->Identity();
    qDebug()<<"Pointer Orientation::";

    // Plug the generator and meta data into the writer.
    //    volume->SetDataScalarTypeToShort();
//    writer -> SetInputData(volume);
   // writer -> SetInputC;


    writer1->SetInputConnection(volume->GetOutputPort()/*v->GetOutputPort()*/);
    qDebug()<<"Input connection::";

    writer1 -> SetMetaData (meta);
    qDebug()<<"Meta data::";

    writer1->SetMemoryRowOrderToFileNative();

    qDebug()<<"SetMemoryRowOrderToFileNative";

    writer1 -> SetGenerator (generator);
    qDebug()<<"SetGenerator";

    // Set the output filename format as a printf-style string.
    //writer -> SetFilePattern ("%s/slice -%04.4d.dcm");//pattern is fixed.
    writer1 -> SetFilePattern ("%s/slice -%04.4d.dcm");//pattern is fixed.
    qDebug()<<"SetFilePattern";

    // Set the directory to write the files into.
    writer1 -> SetFilePrefix (filepath.toStdString().c_str());
    qDebug()<<"filepath::"<<filepath;
    writer1->SetPatientMatrix(m);
    qDebug()<<"SetPatientMatrix::";

    // Write the file.
     writerMutex.lock();
    try
    {
     writer1->Write();
    }catch(...)
    {
        qDebug()<<"Exception  writing dicom files";
              // Handle the error or exit the program gracefully
              return;


    }
     writerMutex.unlock();
    qDebug()<<" writer before update::";

    try
    {
     writer1->Update();

     QMessageBox *msg = new QMessageBox();
     msg->setWindowTitle("Information");
     msg->setIcon(QMessageBox::Information);
     msg->setText("CT files generated successfully");
     msg->exec();
     delete msg;
    }
    catch(...)
    {
        qDebug()<<"Exception updating writer dicom files";

        QMessageBox *msg = new QMessageBox();
        msg->setWindowTitle("Information");
        msg->setIcon(QMessageBox::Critical);
        msg->setText("CT files not generated");
        msg->exec();
        delete msg;
        return ;

    }

}

void dicomwrite::CBCTDicomHeaderFile(CString patientPath)
{
    // get current date n time
        SYSTEMTIME systime;
        GetLocalTime(&systime);
        CString Date, Time, UID;
        Date.Format(_T("%02d%02d%02d"),systime.wYear,systime.wMonth,systime.wDay);
        Time.Format(_T("%02d%02d%02d"),systime.wHour,systime.wMinute,systime.wSecond);
        UID.Format(_T("1.2.528.1.1007.235.5.3.%s.%s.132444"),Date,Time);
    //    QString RTID="RT202204A02 ";
    //    QString Pname="Sundaran";
    //    QString Pat_gender="Male";
    //    QString Pat_pos="";
    //    QString Pat_age="21";
    //    QString patientAge="";
        // Patient name, RTID,gender,age from motion manager
        sprintf(PID,"%s",(const char *)RTID.toStdString().c_str());
        sprintf(Pname,"%s",(const char *)patientName.toStdString().c_str());
        sprintf(Pat_gender,"%s",(const char *)patientGender.toStdString().c_str());

        //patient position from offline R&V database
        sprintf(Pat_pos,"%s",(const char *)PatPos.toLatin1().data());

        Pat_age = (QString(patientAge)).toInt();
        // operator name and software version from UI

        /*sprintf(operatorName,"%s",(const char *)opnm.toStdString().c_str());
        sprintf(versionNo,"%s",(const char *)versionNo.toStdString().c_str());*/

        // machine details from motion manager
        IIKv = 80;//VP;
        IIma = 100;//mA;
        IIms = 32;//ms;

        CString DICOM_Header_File = patientPath + _T("\\Dicom_HeadersList.xml");

        gdcm::UIDGenerator suid;

        // write into xml file
        CStringA strtextconchar1(DICOM_Header_File);
        FILE *fp1 = fopen(strtextconchar1,"w");
        if(fp1 != NULL)
        {
            fprintf(fp1,"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
            fprintf(fp1,"<!--DOCTYPE extraHeaders-->\n");
            fprintf(fp1,"<!-- site : http://medical.nema.org/standard.html -->\n");
            fprintf(fp1,"<extraHeaders>\n");
            fprintf(fp1,"	<Syntax>ExplicitVR</Syntax>\n");
            fprintf(fp1,"	<Dicom>\n");
            fprintf(fp1,"		<!--DICOM META INFORMATION MODULE MODULE-->\n");
            fprintf(fp1,"		<!-- VRKEY value : -->\n");
            fprintf(fp1,"		<!-- Name 	Description 			Length -->\n");
            fprintf(fp1,"		<!-- AE 	Application Entity 		16 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- AS 	Age String 				4 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- AT 	Attribute Tag 			4 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- CS 	Code String 			16 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- DA		Date			 		8 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- DS 	Decimal String 			16 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- DT 	Date Time 				26 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- FL 	Floating Point Single 	4 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- FD 	Floating Point Double 	8 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- IS 	Integer String 			12 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- LO 	Long String 			64 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- LT 	Long Text 				10240 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- OB 	Other Byte String 		Unlimited -->\n");
            fprintf(fp1,"		<!-- OF 	Other Float String 		Unlimited -->\n");
            fprintf(fp1,"		<!-- OW 	Other Word String 		Unlimited -->\n");
            fprintf(fp1,"		<!-- PN 	Person Name 			64 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- SH 	Short String 			16 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- SL 	Signed Long 			4 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- SQ 	Sequence of Items 		Unlimited -->\n");
            fprintf(fp1,"		<!-- SS 	Signed Short 			2 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- ST 	Short Text 				1024 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- TM 	Time 					16 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- UI 	Unique Identifier 		64 Bytes Maximum -->\n");
            fprintf(fp1,"		<!-- UL 	Unsigned Long 			4 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- UN 	Unknown 				Unlimited -->\n");
            fprintf(fp1,"		<!-- US 	Unsigned Short 			2 Bytes Fixed -->\n");
            fprintf(fp1,"		<!-- UT 	Unlimited Text 			Unlimited -->\n");
            fprintf(fp1,"		<!--MEDIA STORAGE SOP CLASS UID (UNPROTECTED)-->\n");
            fprintf(fp1,"		<header No=\"1\" Elem=\"0x0002\" Group=\"0x0002\" VRKey=\"UI\">1.2.840.10008.5.1.4.1.1.2</header> <!-- CT Image Storage -->\n");
            fprintf(fp1,"		<!--MEDIA STORAGE SOP CLASS INSTANCE UID-->\n");
            fprintf(fp1,"		<header No=\"2\" Elem=\"0x0003\" Group=\"0x0002\" VRKey=\"UI\">1.76.380.42.70023.0.%02d%02d%02d%02d%02d%02d</header>\n",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);
            fprintf(fp1,"		<!--PATIENT MODULE-->\n");
            fprintf(fp1,"		<!--Patient's Name-->\n");
            fprintf(fp1,"		<header No=\"3\" Elem=\"0x0010\" Group=\"0x0010\" VRKey=\"PN\">%s</header>\n", Pname);
            fprintf(fp1,"		<!--Patient ID-->\n");
            fprintf(fp1,"		<header No=\"4\" Elem=\"0x0020\" Group=\"0x0010\" VRKey=\"LO\">%s</header>\n", PID);

            QStringList strDOB = patientAge.split("-");
            QString dob;
            if(strDOB.length()>=2)
               dob  = QString(strDOB[2]).mid(0,4)+strDOB[1]+strDOB[0];
            else
               dob = "";

            fprintf(fp1,"		<!--Patient's Birth Date-->\n");
            fprintf(fp1,"		<header No=\"5\" Elem=\"0x0030\" Group=\"0x0010\" VRKey=\"DA\">%s</header>\n",dob.toStdString().c_str());
            fprintf(fp1,"		<!--Patient's Sex-->\n");
            fprintf(fp1,"		<header No=\"6\" Elem=\"0x0040\" Group=\"0x0010\" VRKey=\"CS\">%s</header>\n", Pat_gender);
            fprintf(fp1,"		<!--GENERAL STUDY MODULE-->\n");
            fprintf(fp1,"		<!--Study Instance UID-->\n");
            //1.76.380.42.70023.0.129.1
            fprintf(fp1,"		<header No=\"7\" Elem=\"0x000D\" Group=\"0x0020\" VRKey=\"UI\">%s</header>\n",StudyInstanceUID.toStdString().c_str());
            fprintf(fp1,"		<!--Study Date-->\n");
            fprintf(fp1,"		<header No=\"8\" Elem=\"0x0020\" Group=\"0x0008\" VRKey=\"DA\">%02d%02d%02d</header>\n",systime.wYear,systime.wMonth,systime.wDay);
            fprintf(fp1,"		<!--Study Time-->\n");
            fprintf(fp1,"		<header No=\"9\" Elem=\"0x0030\" Group=\"0x0008\" VRKey=\"TM\">%02d%02d%02d</header>\n",systime.wHour,systime.wMinute,systime.wSecond);
            fprintf(fp1,"		<!--Referring Physician's Name-->\n");
            fprintf(fp1,"		<header No=\"10\" Elem=\"0x0090\" Group=\"0x0008\" VRKey=\"PN\"></header>\n");
            fprintf(fp1,"		<!--Study ID-->\n");
            fprintf(fp1,"		<header No=\"\" Elem=\"0x0010\" Group=\"0x0020\" VRKey=\"SH\">1</header>\n");
            fprintf(fp1,"		<!--Accession Number-->\n");
            fprintf(fp1,"		<header No=\"12\" Elem=\"0x0050\" Group=\"0x0008\" VRKey=\"SH\"></header>\n");
            fprintf(fp1,"		<!--Study Description-->\n");
            fprintf(fp1,"		<header No=\"13\" Elem=\"0x1030\" Group=\"0x0008\" VRKey=\"LO\">%s</header>\n",StudyDescription.toStdString().c_str());
            fprintf(fp1,"		<!--GENERAL SERIES MODULE-->\n");
            fprintf(fp1,"		<!--Modality-->\n");
            fprintf(fp1,"		<header No=\"14\" Elem=\"0x0060\" Group=\"0x0008\" VRKey=\"CS\">CT</header>\n");
            fprintf(fp1,"		<!--Series Instance UID-->\n");
            //1.76.380.42.70023.0.129.1.1
            fprintf(fp1,"		<header No=\"15\" Elem=\"0x000E\" Group=\"0x0020\" VRKey=\"UI\">%s</header>\n",suid.Generate());
            fprintf(fp1,"		<!--Series Number-->\n");
            fprintf(fp1,"		<header No=\"16\" Elem=\"0x0011\" Group=\"0x0020\" VRKey=\"IS\">1</header>\n");
            fprintf(fp1,"		<!--Series Date-->\n");
            fprintf(fp1,"		<header No=\"17\" Elem=\"0x0021\" Group=\"0x0008\" VRKey=\"DA\">%02d%02d%02d</header>\n",systime.wYear,systime.wMonth,systime.wDay);
            fprintf(fp1,"		<!--Series Time-->\n");
            fprintf(fp1,"		<header No=\"18\" Elem=\"0x0031\" Group=\"0x0008\" VRKey=\"TM\">%02d%02d%02d</header>\n",systime.wHour,systime.wMinute,systime.wSecond);
            fprintf(fp1,"		<!--Performing Physician's Name-->\n");
            fprintf(fp1,"		<header No=\"19\" Elem=\"0x1050\" Group=\"0x0008\" VRKey=\"PN\"></header>\n");
            fprintf(fp1,"		<!--Protocol Name-->\n");
            fprintf(fp1,"		<header No=\"20\" Elem=\"0x1030\" Group=\"0x0018\" VRKey=\"LO\"></header>\n");
            fprintf(fp1,"		<!--Series Description-->\n");
            fprintf(fp1,"		<header No=\"21\" Elem=\"0x103E\" Group=\"0x0008\" VRKey=\"LO\"></header>\n");
            fprintf(fp1,"		<!--Operator's Name-->\n");
            fprintf(fp1,"		<header No=\"22\" Elem=\"0x1070\" Group=\"0x0008\" VRKey=\"PN\">%s</header>\n",operatorName);
            fprintf(fp1,"		<!--Patient Position-->\n");
            //        fprintf(fp1,"		<header No=\"23\" Elem=\"0x5100\" Group=\"0x0018\" VRKey=\"CS\">HFS</header>\n");
            fprintf(fp1,"		<header No=\"23\" Elem=\"0x5100\" Group=\"0x0018\" VRKey=\"CS\">%s</header>\n", Pat_pos);
            fprintf(fp1,"		<!--FRAME OF REFERENCE MODULE-->\n");
            fprintf(fp1,"		<!--Frame of Reference UID-->\n");
            fprintf(fp1,"		<header No=\"24\" Elem=\"0x0052\" Group=\"0x0020\" VRKey=\"UI\">1.76.380.42.1</header>\n");
            fprintf(fp1,"		<!--Position Reference Indicator-->\n");
            fprintf(fp1,"		<header No=\"25\" Elem=\"0x1040\" Group=\"0x0020\" VRKey=\"LO\"></header>\n");
            fprintf(fp1,"		<!--GENERAL EQUIPMENT MODULE-->\n");
            fprintf(fp1,"		<!--Manufacturer-->\n");
            fprintf(fp1,"		<header No=\"26\" Elem=\"0x0070\" Group=\"0x0008\" VRKey=\"LO\">%s</header>\n",Manufacturer.toStdString().c_str());
            fprintf(fp1,"		<!--Institution Name-->\n");
            fprintf(fp1,"		<header No=\"27\" Elem=\"0x0080\" Group=\"0x0008\" VRKey=\"LO\">Panacea Medical Technologies</header>\n");
            fprintf(fp1,"		<!--Station Name-->\n");
            fprintf(fp1,"		<header No=\"28\" Elem=\"0x1010\" Group=\"0x0008\" VRKey=\"SH\"></header>\n");
            fprintf(fp1,"		<!--Manufacture's Model Name-->\n");
            fprintf(fp1,"		<header No=\"29\" Elem=\"0x1090\" Group=\"0x0008\" VRKey=\"LO\">%s</header>\n",ManufacturersModelName.toStdString().c_str());
            fprintf(fp1,"		<!--Device Serial Number-->\n");
            fprintf(fp1,"		<header No=\"30\" Elem=\"0x1000\" Group=\"0x0018\" VRKey=\"LO\">%s</header>\n",DeviceSerialNumber.toStdString().c_str());
            fprintf(fp1,"		<!--Software Version-->\n");
            fprintf(fp1,"		<header No=\"31\" Elem=\"0x1020\" Group=\"0x0018\" VRKey=\"LO\">%s</header>\n",versionNo);
            fprintf(fp1,"		<!--Date of Last Calibration-->\n");
            fprintf(fp1,"		<header No=\"32\" Elem=\"0x1200\" Group=\"0x0018\" VRKey=\"DA\"></header>\n");
            fprintf(fp1,"		<!--Time of Last Calibration-->\n");
            fprintf(fp1,"		<header No=\"33\" Elem=\"0x1201\" Group=\"0x0018\" VRKey=\"TM\"></header>\n");
            fprintf(fp1,"		<!--Content Date-->\n");
            fprintf(fp1,"		<header No=\"34\" Elem=\"0x0023\" Group=\"0x0008\" VRKey=\"DA\"></header>\n");
            fprintf(fp1,"		<!--Content Time-->\n");
            fprintf(fp1,"		<header No=\"35\" Elem=\"0x0033\" Group=\"0x0008\" VRKey=\"TM\"></header>\n");
            fprintf(fp1,"		<!--Acquisition Number-->\n");
            fprintf(fp1,"		<header No=\"36\" Elem=\"0x0012\" Group=\"0x0020\" VRKey=\"IS\">933</header>\n");
            fprintf(fp1,"		<!--Acquisition Date-->\n");
            fprintf(fp1,"		<header No=\"37\" Elem=\"0x0022\" Group=\"0x0008\" VRKey=\"DA\">%02d%02d%02d</header>\n",systime.wYear,systime.wMonth,systime.wDay);
            fprintf(fp1,"		<!--Acquisition Time-->\n");
            fprintf(fp1,"		<header No=\"38\" Elem=\"0x0032\" Group=\"0x0008\" VRKey=\"TM\">%02d%02d%02d</header>\n",systime.wHour,systime.wMinute,systime.wSecond);
            fprintf(fp1,"		<!--Quality Control Image-->\n");
            fprintf(fp1,"		<header No=\"39\" Elem=\"0x0300\" Group=\"0x0028\" VRKey=\"CS\">NO</header>\n");
            fprintf(fp1,"		<!--CT IMAGE MODULE-->\n");
            fprintf(fp1,"		<!--Image Type-->\n");
            fprintf(fp1,"		<header No=\"40\" Elem=\"0x0008\" Group=\"0x0008\" VRKey=\"CS\">ORIGINAL\PRIMARY</header>\n");
            fprintf(fp1,"		<!--KVP-->\n");
            fprintf(fp1,"		<header No=\"41\" Elem=\"0x0060\" Group=\"0x0018\" VRKey=\"DS\">%d</header>\n",IIKv);
            fprintf(fp1,"		<!--Scan Options-->\n");
            fprintf(fp1,"		<header No=\"42\" Elem=\"0x0022\" Group=\"0x0018\" VRKey=\"CS\"></header>\n");
            fprintf(fp1,"		<!--Data Collection Diameter-->\n");
            fprintf(fp1,"		<header No=\"43\" Elem=\"0x0090\" Group=\"0x0018\" VRKey=\"DS\">0.00</header>\n");
            fprintf(fp1,"		<!--Reconstruction Diameter-->\n");
            fprintf(fp1,"		<header No=\"44\" Elem=\"0x1100\" Group=\"0x0018\" VRKey=\"DS\">256.00</header>\n");
            fprintf(fp1,"		<!--Gantry/Detector Tilt-->\n");
            fprintf(fp1,"		<header No=\"45\" Elem=\"0x1120\" Group=\"0x0018\" VRKey=\"DS\"></header>\n");
            fprintf(fp1,"		<!--Table Heigh-->\n");
            fprintf(fp1,"		<header No=\"46\" Elem=\"0x1130\" Group=\"0x0018\" VRKey=\"DS\"></header>\n");
            fprintf(fp1,"		<!--Rotation Direction-->\n");
            fprintf(fp1,"		<header No=\"47\" Elem=\"0x1140\" Group=\"0x0018\" VRKey=\"CS\">CW</header>\n");
            fprintf(fp1,"		<!--Exposure Time-->\n");
            fprintf(fp1,"		<header No=\"48\" Elem=\"0x1150\" Group=\"0x0018\" VRKey=\"IS\">%d</header>\n",IIms);
            fprintf(fp1,"		<!--X-Ray Tube Current-->\n");
            fprintf(fp1,"		<header No=\"49\" Elem=\"0x1151\" Group=\"0x0018\" VRKey=\"IS\">%d</header>\n",IIma);
            fprintf(fp1,"		<!--Exposure uAs-->\n");
            fprintf(fp1,"		<header No=\"50\" Elem=\"0x1153\" Group=\"0x0018\" VRKey=\"IS\">%d</header>\n",IIms*IIma);
            fprintf(fp1,"		<!--Filter Type-->\n");
            fprintf(fp1,"		<header No=\"51\" Elem=\"0x1160\" Group=\"0x0018\" VRKey=\"SH\"></header>\n");
            fprintf(fp1,"		<!--Generator Power-->\n");
            fprintf(fp1,"		<header No=\"52\" Elem=\"0x1170\" Group=\"0x0018\" VRKey=\"IS\"></header>\n");
            fprintf(fp1,"		<!--Focal Spot-->\n");
            fprintf(fp1,"		<header No=\"53\" Elem=\"0x1190\" Group=\"0x0018\" VRKey=\"DS\"></header>\n");
            fprintf(fp1,"		<!--Convolution Kernel-->\n");
            fprintf(fp1,"		<header No=\"54\" Elem=\"0x1210\" Group=\"0x0018\" VRKey=\"SH\"></header>\n");
            fprintf(fp1,"		<!--SOP COMMON MODULE-->\n");
            fprintf(fp1,"		<!--SOP CLASS UID (UNPROTECTED)-->\n");
            fprintf(fp1,"		<header No=\"55\" Elem=\"0x0016\" Group=\"0x0008\" VRKey=\"UI\">1.2.840.10008.5.1.4.1.1.2</header>\n");
            fprintf(fp1,"		<!--SOP INSTANCE UID-->\n");
            fprintf(fp1,"		<header No=\"56\" Elem=\"0x0018\" Group=\"0x0008\" VRKey=\"UI\">1.76.380.42.70023.0.%02d%02d%02d%02d%02d%02d</header>\n",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);
            fprintf(fp1,"	</Dicom>\n");
            fprintf(fp1,"</extraHeaders>\n");
            fclose(fp1);
        }
}

void dicomwrite::setVtkVolume(vtkImageImport *v)
{
    volume=v;
}
