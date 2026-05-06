#-------------------------------------------------
#
# Project created by QtCreator 2021-10-04T12:37:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dicom_tagwrite
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -lAdvapi32

LIBS += "Rpcrt4.lib"
LIBS += "WS2_32.lib"

INCLUDEPATH +="D:\\TKs\\LibsForGRAY\\VTK\\VTK_D\\include\\vtk-7.0"
LIBS    +=-L"D:\\TKs\\LibsForGRAY\\VTK\\VTK_D\\lib"\
            -lvtkalglib-7.0 \
            -lvtkChartsCore-7.0 \
            -lvtkCommonColor-7.0 \
            -lvtkCommonComputationalGeometry-7.0 \
            -lvtkCommonCore-7.0 \
            -lvtkCommonDataModel-7.0 \
            -lvtkCommonExecutionModel-7.0 \
            -lvtkCommonMath-7.0 \
            -lvtkCommonMisc-7.0 \
            -lvtkCommonSystem-7.0 \
            -lvtkCommonTransforms-7.0 \
            -lvtkDICOMParser-7.0 \
            -lvtkDomainsChemistry-7.0 \
            -lvtkDomainsChemistryOpenGL2-7.0 \
            -lvtkexoIIc-7.0 \
            -lvtkexpat-7.0 \
            -lvtkFiltersAMR-7.0 \
            -lvtkFiltersCore-7.0 \
            -lvtkFiltersExtraction-7.0 \
            -lvtkFiltersFlowPaths-7.0 \
            -lvtkFiltersGeneral-7.0 \
            -lvtkFiltersGeneric-7.0 \
            -lvtkFiltersGeometry-7.0 \
            -lvtkFiltersHybrid-7.0 \
            -lvtkFiltersHyperTree-7.0 \
            -lvtkFiltersImaging-7.0 \
            -lvtkFiltersModeling-7.0 \
            -lvtkFiltersParallel-7.0 \
            -lvtkFiltersParallelImaging-7.0 \
            -lvtkFiltersProgrammable-7.0 \
            -lvtkFiltersSelection-7.0 \
            -lvtkFiltersSMP-7.0 \
            -lvtkFiltersSources-7.0 \
            -lvtkFiltersStatistics-7.0 \
            -lvtkFiltersTexture-7.0 \
            -lvtkFiltersVerdict-7.0 \
            -lvtkfreetype-7.0 \
            -lvtkGeovisCore-7.0 \
            -lvtkglew-7.0 \
            -lvtkGUISupportQt-7.0 \
            -lvtkGUISupportQtSQL-7.0 \
            -lvtkhdf5-7.0 \
            -lvtkhdf5_hl-7.0 \
            -lvtkImagingColor-7.0 \
            -lvtkImagingCore-7.0 \
            -lvtkImagingFourier-7.0 \
            -lvtkImagingGeneral-7.0 \
            -lvtkImagingHybrid-7.0 \
            -lvtkImagingMath-7.0 \
            -lvtkImagingMorphological-7.0 \
            -lvtkImagingSources-7.0 \
            -lvtkImagingStatistics-7.0 \
            -lvtkImagingStencil-7.0 \
            -lvtkInfovisCore-7.0 \
            -lvtkInfovisLayout-7.0 \
            -lvtkInteractionImage-7.0 \
            -lvtkInteractionStyle-7.0 \
            -lvtkInteractionWidgets-7.0 \
            -lvtkIOAMR-7.0 \
            -lvtkIOCore-7.0 \
            -lvtkIOEnSight-7.0 \
            -lvtkIOExodus-7.0 \
            -lvtkIOExport-7.0 \
            -lvtkIOGeometry-7.0 \
            -lvtkIOImage-7.0 \
            -lvtkIOImport-7.0 \
            -lvtkIOInfovis-7.0 \
            -lvtkIOLegacy-7.0 \
            -lvtkIOLSDyna-7.0 \
            -lvtkIOMINC-7.0 \
            -lvtkIOMovie-7.0 \
            -lvtkIONetCDF-7.0 \
            -lvtkIOParallel-7.0 \
            -lvtkIOParallelXML-7.0 \
            -lvtkIOPLY-7.0 \
            -lvtkIOSQL-7.0 \
            -lvtkIOVideo-7.0 \
            -lvtkIOXML-7.0 \
            -lvtkIOXMLParser-7.0 \
            -lvtkjpeg-7.0 \
            -lvtkjsoncpp-7.0 \
            -lvtklibxml2-7.0 \
            -lvtkmetaio-7.0 \
            -lvtkNetCDF-7.0 \
            -lvtkNetCDF_cxx-7.0 \
            -lvtkoggtheora-7.0 \
            -lvtkParallelCore-7.0 \
            -lvtkpng-7.0 \
            -lvtkproj4-7.0 \
            -lvtkRenderingAnnotation-7.0 \
            -lvtkRenderingContext2D-7.0 \
            -lvtkRenderingContextOpenGL2-7.0 \
            -lvtkRenderingCore-7.0 \
            -lvtkRenderingFreeType-7.0 \
            -lvtkRenderingImage-7.0 \
            -lvtkRenderingLabel-7.0 \
            -lvtkRenderingLOD-7.0 \
            -lvtkRenderingOpenGL2-7.0 \
            -lvtkRenderingQt-7.0 \
            -lvtkRenderingVolume-7.0 \
            -lvtkRenderingVolumeOpenGL2-7.0 \
            -lvtksqlite-7.0 \
            -lvtksys-7.0 \
            -lvtktiff-7.0 \
            -lvtkverdict-7.0 \
            -lvtkViewsContext2D-7.0 \
            -lvtkViewsCore-7.0 \
            -lvtkViewsInfovis-7.0 \
            -lvtkViewsQt-7.0 \
            -lvtkzlib-7.0

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
       # -lITKOptimizers-4.11\
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

INCLUDEPATH +="D:\\TKs\\LibsForGRAY\\DicomLibrary\\DICOM_D\\include"
LIBS    += -L"D:\\TKs\\LibsForGRAY\\DicomLibrary\\DICOM_D\\lib"\
           -lvtkDICOM-7.0
