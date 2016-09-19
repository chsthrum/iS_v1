#-------------------------------------------------
#
# Project created by QtCreator 2016-08-13T09:27:07
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent

QT       += concurrent widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

TARGET = iScanLayoutOnMainWindow
TEMPLATE = app

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
    defectlabelslayout.cpp

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
    defectlabelslayout.h

DISTFILES += \
    notes.txt
