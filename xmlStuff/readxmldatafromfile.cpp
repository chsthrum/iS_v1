#include "readxmldatafromfile.h"
#include "listxml_elements.h"
#include "../ImagingStuff/Config.h" //for the Machine Camera config file

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


/* Structure elements of MachCamConfigFileXMLData

    QString NumberOfCameras = "";
    QString Mach_SerialNumber = "";
    QString Mach_YearOfManufacture = "";
    QString Mach_ModelNumber = "";
    QString CameraNumber = "";
    QString filePathName = "";
    int ManufacturerType = 0;
    QString SerialNumber = "";
    QString Model = "";
    QString CameraReferenceDistance_mm = "";
    QString FrameGrabberNumber = ""; // for Silicon Software Frame grabber
    QString FrameGrabberPortNumber = "";  // for Silicon Software Frame grabber
*/


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
           if (sL[i]== "FS_LOCAL_CAM")
           retVec[i].ManufacturerType = "FS_LOCAL_CAM";
           if (sL[i]== "FS_SISO_CIS_GRAY")
           retVec[i].ManufacturerType = "FS_SISO_CIS_GRAY";
           if (sL[i]== "FS_SISO_CIS_RGB")
           retVec[i].ManufacturerType = "FS_SISO_CIS_RGB";
           if (sL[i]== "FS_BASLER_DART_PYLON_AREA")
           retVec[i].ManufacturerType = "FS_BASLER_DART_PYLON_AREA";
           if (sL[i]== "FS_TDALSA_GIGE_LINE_GRAY")
           retVec[i].ManufacturerType = "FS_TDALSA_GIGE_LINE_GRAY";
           //and more when available

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

        sL = ListXmlElements(document, "Camera", "FrameGrabberNumber");
        for(int i = 0; i < sL.size(); i++)
        {
            //fill the vector
            retVec[i].FrameGrabberNumber = sL[i];
        }

        sL = ListXmlElements(document, "Camera", "FrameGrabberPortNumber");
        for(int i = 0; i < sL.size(); i++)
        {
            //fill the vector
            retVec[i].FrameGrabberPortNumber = sL[i];
        }


        for (int i = 0; i!=sL.count(); i++)
            qDebug()  << sL[i];

        qDebug()  << "Finished";


    return retVec;
}

//check for a dupicate string
bool checkForDuplicateSerialNumber(QVector<MachCamConfigFileXMLData>& vec)
{
    int nOccur = 0; //number of identical string occurancies
    for (QVector<MachCamConfigFileXMLData>::size_type i = 0; i < vec.size(); i++)
    {
        for (QVector<MachCamConfigFileXMLData>::size_type j = 0; j < vec.size(); j++)
        {
            //check for a dupicate string
            if (vec[i].SerialNumber == vec[j].SerialNumber)
            {
                if((++nOccur) > 1)
                {
                    // other words we have found a duplicated string
                    //std::cout << "duplicate serial number found in the Machine Camera Configuration file or vector at element " << i << '\n';
                    qDebug() << "duplicate serial number found in the Machine Camera Configuration file or vector at element " << i << '\n';
                    return false;
                }
            }
        }
         nOccur = 0; // reset the number of occurancies in the outer loop.
    }
    return true;
}

