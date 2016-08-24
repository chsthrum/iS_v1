#-------------------------------------------------
#
# Project created by QtCreator 2016-08-13T09:27:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

TARGET = iScanLayoutOnMainWindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    defectLabel.cpp \
    pic2label.cpp \
    ImagingStuff/MatToQImage.cpp \
    ImagingStuff/SharedImageBuffer.cpp \
    cameraWidget.cpp \
    cameraContainer.cpp \
    ImagingStuff/CaptureThread.cpp \
    ImagingStuff/ProcessingThread.cpp

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
    ImagingStuff/Config.h

DISTFILES += \
    notes.txt
