#-------------------------------------------------
#
# Project created by QtCreator 2016-08-13T09:27:07
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += concurrent

QT       += concurrent widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = iScanLayoutOnMainWindow
TEMPLATE = app


#FOR UNIX OS
unix{

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

INCLUDEPATH += /usr/local/boost_1_61_0


SOURCES += main.cpp\
        mainwindow.cpp \
    defectLabel.cpp \
    pic2label.cpp \
    ImagingStuff/MatToQImage.cpp \
    ImagingStuff/SharedImageBuffer.cpp \
    cameraWidget.cpp \
    cameraContainer.cpp \
    ImagingStuff/CaptureThread.cpp \
    ImagingStuff/ProcessingThread.cpp \
    defectimagestorage.cpp \
    defectlabelslayout.cpp \
    cstopmotion.cpp \
    csimpledefectmapLabel.cpp

HEADERS  += mainwindow.h \
    defectLabel.h \
    pic2label.h \
    ImagingStuff/Buffer.h \
    ImagingStuff/MatToQImage.h \
    ImagingStuff/SharedImageBuffer.h \
    cameraContainer.h \
    cameraWidget.h \
    ImagingStuff/CaptureThread.h \
    ImagingStuff/ProcessingThread.h \
    ImagingStuff/Config.h \
    defectimagestorage.h \
    weighteddie.h \
    ImagingStuff/Structures.h \
    defectlabelslayout.h \
    cstopmotion.h \
    csimpledefectmapLabel.h

DISTFILES += \
    notes.txt

}
# end unix

#FOR WIN32 OS
win32{

INCLUDEPATH += "C:\local\boost_1_55_0"


#vidi


INCLUDEPATH += "C:\Program Files\ViDi Systems\ViDi Suite 13\develop\include"

#always include the quote makes for white space file names


#siso

INCLUDEPATH += "C:\Program Files\SiliconSoftware\Runtime5.2.1\include"


#opencv

INCLUDEPATH += C:\Opencv2410\opencv\build\include


LIBS +=$$quote(-LC:\Program Files\ViDi Systems\ViDi Suite 13\bin)\ -lvidi_runtime_library_13


#siso


LIBS +=$$quote(-LC:\Program Files\SiliconSoftware\Runtime5.2.1\lib\visualc)\ -lfglib5

LIBS +=$$quote(-LC:\Program Files\SiliconSoftware\Runtime5.2.1\lib\visualc)\ -lclsersis

LIBS +=$$quote(-LC:\Program Files\SiliconSoftware\Runtime5.2.1\lib\visualc)\ -ldisplay_lib

LIBS +=$$quote(-LC:\Program Files\SiliconSoftware\Runtime5.2.1\lib\visualc)\ -lgbelib

LIBS +=$$quote(-LC:\Program Files\SiliconSoftware\Runtime5.2.1\lib\visualc)\ -liolibrt



SOURCES += main.cpp\
    mainwindow.cpp \
    defectLabel.cpp \
    pic2label.cpp \
    ImagingStuff/MatToQImage.cpp \
    ImagingStuff/SharedImageBuffer.cpp \
    cameraWidget.cpp \
    cameraContainer.cpp \
    ImagingStuff/CaptureThread.cpp \
    ImagingStuff/ProcessingThread.cpp \
    defectimagestorage.cpp \
    defectlabelslayout.cpp \
    cstopmotion.cpp \
    csimpledefectmapLabel.cpp



HEADERS  += mainwindow.h \
    defectLabel.h \
    pic2label.h \
    #ImagingStuff/Buffer.h \
    #ImagingStuff/MatToQImage.h \
    #ImagingStuff/SharedImageBuffer.h \
    cameraContainer.h \
    cameraWidget.h \
    #ImagingStuff/CaptureThread.h \
    #ImagingStuff/ProcessingThread.h \
    #ImagingStuff/Config.h \
    defectimagestorage.h \
    weighteddie.h \
    #ImagingStuff/Structures.h \
    defectlabelslayout.h \
    cstopmotion.h \
    csimpledefectmapLabel.h

HEADERS += \
    ImagingStuff/Buffer.h \
    ImagingStuff/MatToQImage.h \
    ImagingStuff/SharedImageBuffer.h \
    ImagingStuff/CaptureThread.h \
    ImagingStuff/ProcessingThread.h \
    ImagingStuff/Config.h \
    ImagingStuff/Structures.h



DISTFILES += \

    notes.txt


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../opencv2410/opencv/build/x64/vc12/lib/ -lopencv_core2410

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../opencv2410/opencv/build/x64/vc12/lib/ -lopencv_core2410d



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../opencv2410/opencv/build/x64/vc12/lib/ -lopencv_highgui2410

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../opencv2410/opencv/build/x64/vc12/lib/ -lopencv_highgui2410d




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../opencv2410/opencv/build/x64/vc12/lib/ -lopencv_imgproc2410

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../opencv2410/opencv/build/x64/vc12/lib/ -lopencv_imgproc2410d



#pylon
INCLUDEPATH +=$$quote(C:/Program Files/Basler/pylon 5/Development/include)
#Note: PYLON_DEV_DIR = C:\Program Files\Basler\pylon 5\Development
LIBS +=$$quote(-LC:\Program Files\Basler\pylon 5\Development\lib\x64)\
#LIBS +=-L$(PYLON_DEV_DIR)\lib\x64\
              -lGCBase_MD_VC120_v3_0_Basler_pylon_v5_0\
              -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0\
              -lPylonBase_MD_VC120_v5_0\
              -lPylonC_MD_VC120\
              -lPylonGUI_MD_VC120_v5_0\
              -lPylonUtility_MD_VC120_v5_0

#TDalsa
INCLUDEPATH += $$quote(C:\Program Files\Teledyne DALSA\Sapera\Classes\Basic)
INCLUDEPATH += $$quote(C:\Program Files\Teledyne DALSA\Sapera\Include)

LIBS +=$$quote(-LC:\Program Files\Teledyne DALSA\Sapera\Lib\Win64)\
                -lSapClassBasic \
                -lcorapi

DISTFILES += \
    Operational_Notes.txt

HEADERS += \
    CameraDrivers/fs_cameraconfig.h \
    ExternalHardwareSoftware/siliconsoftwaregrabber_1.h \
    ExternalHardwareSoftware/baslerpylondart_1.h

SOURCES += \
    ExternalHardwareSoftware/siliconsoftwaregrabber_1.cpp \
    ExternalHardwareSoftware/baslerpylondart_1.cpp

SOURCES += \
    xmlStuff/writemachcamconfigfilexml.cpp \
    xmlStuff/readxmldatafromfile.cpp \
    xmlStuff/listxml_elements.cpp \
    ExternalHardwareSoftware/teledynedalsasapera_1.cpp

HEADERS += \
    xmlStuff/writemachcamconfigfilexml.h \
    xmlStuff/readxmldatafromfile.h \
    xmlStuff/listxml_elements.h \
    ExternalHardwareSoftware/teledynedalsasapera_1.h

}
# end win32

HEADERS += \
    UtilityStuff/fs_utilities_various.h

SOURCES += \
    UtilityStuff/fs_utilities_various.cpp

DISTFILES += \
    changesTravellingJan2017



