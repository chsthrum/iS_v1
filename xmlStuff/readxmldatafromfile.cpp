#include "readxmldatafromfile.h"
#include "listxml_elements.h"

#include <QDebug>


QVector<MachCamConfigFileXMLData> readXMLDataFromFile(QString filename)
{
    QVector<MachCamConfigFileXMLData>retVec;
    MachCamConfigFileXMLData cFig;

    QDomDocument document;

    //load the file
    QFile file (filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))

    {
        qDebug() << "Failed to open the file";
        //return -1;
    }

    else
    {
        if(!document.setContent(&file))
        {
            qDebug() << "Failed to load the document";
           // return -1;
        }

        file.close();
     }
    //get the element by name

        QDomNodeList camerasList = document.elementsByTagName("Camera");

        qDebug() << "Number of Cameras in this system = " << camerasList.size();

        for(int i = 0; i < camerasList.size(); i++)
            retVec.push_back(cFig);


        /* Structure elements
        QString NumberOfCameras;
        QString Mach_SerialNumber;
        QString Mach_YearOfManufacture;
        QString Mach_ModelNumber;
        QString CameraNumber;
        QString filePathName;
        QString ManufacturerType;
        QString SerialNumber;
        QString Model;
        QString CameraReferenceDistance_mm;*/


        QStringList sL;

        //DO ALL THE MACHINE ELEMENTS

        //via function call
        // for the looping function I need the 1. Document 2. " tagname for the element " 3. "attribute name"
        sL = ListXmlElements(document, "Machine", "NumberOfCameras");
        for(int i = 0; i < camerasList.size(); i++)
        {
            //fill the vector
            retVec[i].NumberOfCameras=sL[0];
        }

        sL = ListXmlElements(document, "Machine", "Mach_SerialNumber");
        for(int i = 0; i < camerasList.size(); i++)
        {
            //fill the vector
            retVec[i].Mach_SerialNumber=sL[0];
        }

        sL = ListXmlElements(document, "Machine", "Mach_YearOfManufacture");
        for(int i = 0; i < camerasList.size(); i++)
        {
            //fill the vector
            retVec[i].Mach_YearOfManufacture=sL[0];
        }

        sL = ListXmlElements(document, "Machine", "Mach_ModelNumber");
        for(int i = 0; i < camerasList.size(); i++)
        {
            //fill the vector
            retVec[i].Mach_ModelNumber=sL[0];
        }

        //DO ALL THE CAMERA ELEMENTS

        sL = ListXmlElements(document, "Camera", "CameraNumber");
        for(int i = 0; i < sL.size(); i++)
        {
            //fill the vector
            retVec[i].CameraNumber = sL[i];
        }

        sL = ListXmlElements(document, "Camera", "filePathName");
        for(int i = 0; i < sL.size(); i++)
        {
            //fill the vector
            retVec[i].filePathName = sL[i];
        }

        sL = ListXmlElements(document, "Camera", "ManufacturerType");
        for(int i = 0; i < sL.size(); i++)
        {
            //fill the vector
            retVec[i].ManufacturerType = sL[i];
        }

        sL = ListXmlElements(document, "Camera", "SerialNumber");
        for(int i = 0; i < sL.size(); i++)
        {
            //fill the vector
            retVec[i].SerialNumber = sL[i];
        }

        sL = ListXmlElements(document, "Camera", "Model");
        for(int i = 0; i < sL.size(); i++)
        {
            //fill the vector
            retVec[i].Model = sL[i];
        }

        sL = ListXmlElements(document, "Camera", "CameraReferenceDistance_mm");
        for(int i = 0; i < sL.size(); i++)
        {
            //fill the vector
            retVec[i].CameraReferenceDistance_mm = sL[i];
        }


        //sL = ListXmlElements(document, "region", "contour_points");
        //sL = ListXmlElements(document, "map", "threshold");
        //sL = ListXmlElements(document, "region", "area");

        for (int i = 0; i!=sL.count(); i++)
            qDebug()  << sL[i];

        qDebug()  << "Finished";


    return retVec;
}
