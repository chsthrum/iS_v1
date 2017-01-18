//qt includes
#include <QDesktopWidget>
#include <QDebug>
//local includes
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //read the MachineCameraConfiguration file
    QVector<MachCamConfigFileXMLData> vecXMLData = readXMLDataFromFile("C:/Users/Fibrescan/Documents/iScanDev1/iS_v1/ConfigFilesXML/machineCameraConfig34BAS.xml");

    //set the scroll area
    scrollArea = new QScrollArea;
    //check for duplicate serial numbers which would cause camera setup problems.
    if (!checkForDuplicateSerialNumber(vecXMLData))
    {
        qDebug() << "serial number duplicated in the xml file.";
        exit(0);
    }
    else
        widget = new CameraContainer(this, vecXMLData);
    //make the widget a child of the scroll area
    scrollArea->setWidget(widget);
    //make the scroll area the central widget
    this->setCentralWidget(scrollArea);
    //set the centralWidget to the size here under
    resize(QDesktopWidget().availableGeometry(this).size() * 0.9);
}

MainWindow::~MainWindow()
{
qDebug() << "MainWindow destructor called.";
}
