#-------------------------------------------------
#
# Project created by QtCreator 2016-08-13T09:27:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iScanLayoutOnMainWindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CameraWidget.cpp \
    defectLabel.cpp \
    pic2label.cpp \
    widget.cpp

HEADERS  += mainwindow.h \
    CameraWidget.h \
    defectLabel.h \
    pic2label.h \
    widget.h

DISTFILES += \
    notes.txt
