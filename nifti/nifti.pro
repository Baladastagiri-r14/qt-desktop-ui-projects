#-------------------------------------------------
#
# Project created by QtCreator 2023-10-11T10:16:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nifti
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -lAdvapi32

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
        -lITKznz-4.11

    INCLUDEPATH += "D:\\TKs\\LibsForGRAY\\VTK\VTK_D\\include\\vtk-7.0"
    LIBS    += -L"D:\\TKs\\LibsForGRAY\\VTK\\VTK_D\\lib"\
                -l\vtkalglib-7.0\
                -l\vtkChartsCore-7.0\
                -l\vtkCommonColor-7.0\
                -l\vtkCommonComputationalGeometry-7.0\
                -l\vtkCommonCore-7.0\
                -l\vtkCommonDataModel-7.0\
                -l\vtkCommonExecutionModel-7.0\
                -l\vtkCommonMath-7.0\
                -l\vtkCommonMisc-7.0\
                -l\vtkCommonSystem-7.0\
                -l\vtkCommonTransforms-7.0\
                -l\vtkDICOMParser-7.0\
                -l\vtkDomainsChemistry-7.0\
                -l\vtkDomainsChemistryOpenGL2-7.0\
                -l\vtkexoIIc-7.0\
                -l\vtkexpat-7.0\
                -l\vtkFiltersAMR-7.0\
                -l\vtkFiltersCore-7.0\
                -l\vtkFiltersExtraction-7.0\
                -l\vtkFiltersFlowPaths-7.0\
                -l\vtkFiltersGeneral-7.0\
                -l\vtkFiltersGeneric-7.0\
                -l\vtkFiltersGeometry-7.0\
                -l\vtkFiltersHybrid-7.0\
                -l\vtkFiltersHyperTree-7.0\
                -l\vtkFiltersImaging-7.0\
                -l\vtkFiltersModeling-7.0\
                -l\vtkFiltersParallel-7.0\
                -l\vtkFiltersParallelImaging-7.0\
                -l\vtkFiltersProgrammable-7.0\
                -l\vtkFiltersSelection-7.0\
                -l\vtkFiltersSMP-7.0\
                -l\vtkFiltersSources-7.0\
                -l\vtkFiltersStatistics-7.0\
                -l\vtkFiltersTexture-7.0\
                -l\vtkFiltersVerdict-7.0\
                -l\vtkfreetype-7.0\
                -l\vtkGeovisCore-7.0\
                -l\vtkglew-7.0\
                -l\vtkGUISupportQt-7.0\
                -l\vtkGUISupportQtSQL-7.0\
                -l\vtkhdf5_hl-7.0\
                -l\vtkhdf5-7.0\
                -l\vtkImagingColor-7.0\
                -l\vtkImagingCore-7.0\
                -l\vtkImagingFourier-7.0\
                -l\vtkImagingGeneral-7.0\
                -l\vtkImagingHybrid-7.0\
                -l\vtkImagingMath-7.0\
                -l\vtkImagingMorphological-7.0\
                -l\vtkImagingSources-7.0\
                -l\vtkImagingStatistics-7.0\
                -l\vtkImagingStencil-7.0\
                -l\vtkInfovisCore-7.0\
                -l\vtkInfovisLayout-7.0\
                -l\vtkInteractionImage-7.0\
                -l\vtkInteractionStyle-7.0\
                -l\vtkInteractionWidgets-7.0\
                -l\vtkIOAMR-7.0\
                -l\vtkIOCore-7.0\
                -l\vtkIOEnSight-7.0\
                -l\vtkIOExodus-7.0\
                -l\vtkIOExport-7.0\
                -l\vtkIOGeometry-7.0\
                -l\vtkIOImage-7.0\
                -l\vtkIOImport-7.0\
                -l\vtkIOInfovis-7.0\
                -l\vtkIOLegacy-7.0\
                -l\vtkIOLSDyna-7.0\
                -l\vtkIOMINC-7.0\
                -l\vtkIOMovie-7.0\
                -l\vtkIONetCDF-7.0\
                -l\vtkIOParallel-7.0\
                -l\vtkIOParallelXML-7.0\
                -l\vtkIOPLY-7.0\
                -l\vtkIOSQL-7.0\
                -l\vtkIOVideo-7.0\
                -l\vtkIOXML-7.0\
                -l\vtkIOXMLParser-7.0\
                -l\vtkjpeg-7.0\
                -l\vtkjsoncpp-7.0\
                -l\vtklibxml2-7.0\
                -l\vtkmetaio-7.0\
                -l\vtkNetCDF_cxx-7.0\
                -l\vtkNetCDF-7.0\
                -l\vtkoggtheora-7.0\
                -l\vtkParallelCore-7.0\
                -l\vtkpng-7.0\
                -l\vtkproj4-7.0\
                -l\vtkRenderingAnnotation-7.0\
                -l\vtkRenderingContext2D-7.0\
                -l\vtkRenderingContextOpenGL2-7.0\
                -l\vtkRenderingCore-7.0\
                -l\vtkRenderingFreeType-7.0\
                -l\vtkRenderingImage-7.0\
                -l\vtkRenderingLabel-7.0\
                -l\vtkRenderingLOD-7.0\
                -l\vtkRenderingOpenGL2-7.0\
                -l\vtkRenderingQt-7.0\
                -l\vtkRenderingVolume-7.0\
                -l\vtkRenderingVolumeOpenGL2-7.0\
                -l\vtksqlite-7.0\
                -l\vtksys-7.0\
                -l\vtktiff-7.0\
                -l\vtkverdict-7.0\
                -l\vtkViewsContext2D-7.0\
                -l\vtkViewsCore-7.0\
                -l\vtkViewsInfovis-7.0\
                -l\vtkViewsQt-7.0\
                -l\vtkzlib-7.0

INCLUDEPATH +="D:\\TKs\\LibsForGRAY\\DicomLibrary\\DICOM_D\\include"
LIBS    += -L"D:\\TKs\LibsForGRAY\\DicomLibrary\\DICOM_D\\lib"\
           -lvtkDICOM-7.0
