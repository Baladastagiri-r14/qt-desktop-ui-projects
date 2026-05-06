#-------------------------------------------------
#
# Project created by QtCreator 2024-01-20T09:41:20
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_merge
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


win32: LIBS += "advapi32.lib"
win32: LIBS +="Shell32.lib"

INCLUDEPATH +="D:\\TKs\\LibsForGRAY\\ITK\\ITK_D\\include\\ITK-4.11"
LIBS +=-L"D:\\TKs\\LibsForGRAY\\ITK\\ITK_D\\lib"\
        -lITKBiasCorrection-4.11\
        -lITKBioCell-4.11\
        -lITKCommon-4.11\
        -lITKDICOMParser-4.11\
        -litkdouble-conversion-4.11\
        -lITKEXPAT-4.11\
        -lITKFEM-4.11\
        -litkgdcmcharls-4.11\
        -litkgdcmCommon-4.11\
        -litkgdcmDICT-4.11\
        -litkgdcmDSED-4.11\
        -litkgdcmIOD-4.11\
        -litkgdcmjpeg8-4.11\
        -litkgdcmjpeg12-4.11\
        -litkgdcmjpeg16-4.11\
        -litkgdcmMEXD-4.11\
        -litkgdcmMSFF-4.11\
        -litkgdcmopenjpeg-4.11\
        -litkgdcmsocketxx-4.11\
        -lITKgiftiio-4.11\
        -lITKIOBioRad-4.11\
        -lITKIOBMP-4.11\
        -lITKIOCSV-4.11\
        -lITKIOGDCM-4.11\
        -lITKIOGE-4.11\
        -lITKIOGIPL-4.11\
        -lITKIOHDF5-4.11\
        -lITKIOImageBase-4.11\
        -lITKIOIPL-4.11\
        -lITKIOJPEG-4.11\
        -lITKIOLSM-4.11\
        -lITKIOMesh-4.11\
        -lITKIOMeta-4.11\
        -lITKIOMRC-4.11\
        -lITKIONIFTI-4.11\
        -lITKIONRRD-4.11\
        -lITKIOPNG-4.11\
        -lITKIOSiemens-4.11\
        -lITKIOSpatialObjects-4.11\
        -lITKIOStimulate-4.11\
        -lITKIOTIFF-4.11\
        -lITKIOTransformBase-4.11\
        -lITKIOTransformHDF5-4.11\
        -lITKIOTransformInsightLegacy-4.11\
        -lITKIOTransformMatlab-4.11\
        -lITKIOVTK-4.11\
        -lITKIOXML-4.11\
        -litkjpeg-4.11\
        -lITKKLMRegionGrowing-4.11\
        -lITKLabelMap-4.11\
        -lITKMesh-4.11\
        -lITKMetaIO-4.11\
        -litknetlib-4.11\
        -litkNetlibSlatec-4.11\
        -lITKniftiio-4.11\
        -lITKNrrdIO-4.11\
        -lITKOptimizers-4.11\
        -lITKOptimizersv4-4.11\
        -lITKPath-4.11\
        -litkpng-4.11\
        -lITKPolynomials-4.11\
        -lITKQuadEdgeMesh-4.11\
        -lITKSpatialObjects-4.11\
        -lITKStatistics-4.11\
        -litksys-4.11\
        -litktestlib-4.11\
        -litktiff-4.11\
        -lITKTransform-4.11\
        -lITKTransformFactory-4.11\
        -litkv3p_netlib-4.11\
        -litkvcl-4.11\
        -lITKVideoCore-4.11\
        -lITKVideoIO-4.11\
        -litkvnl_algo-4.11\
        -litkvnl-4.11\
        -lITKVNLInstantiation-4.11\
        -lITKVTK-4.11\
        -lITKVtkGlue-4.11\
        -lITKWatersheds-4.11\
        -litkzlib-4.11\
        -lITKznz-4.11\
        -llibitkhdf5_D\
        -llibitkhdf5_cpp_D\
