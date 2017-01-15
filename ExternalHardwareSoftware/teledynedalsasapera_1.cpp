//c includes
#include <cstring> // for strstr()
#include <stdio.h>

//stl includes
#include <iostream>
#include <string>

//local includes
#include "teledynedalsasapera_1.h"

#ifdef _WIN32

TeleDalsaSaperaLT::TeleDalsaSaperaLT(MachCamConfigFileXMLData& machCamData): macCamXML(machCamData)
{
    grabNo = this->macCamXML.CameraNumber.toInt();

    //get the camera configuration file by converting QString via std::string to c_string;
    QString text = macCamXML.filePathName;
    std::string str = text.toLatin1().constData();
    const char* configFile = str.c_str();

    // choose the camera
    char deviceName[CORPRM_GETSIZE(CORACQ_PRM_LABEL)];
    bool noMatchingString = true;
    for ( QVector<LocationStruct>::size_type i = 0; i < this->macCamXML.locs.size(); i++ )
    {
        //get serverName by converting QString via std::string to c_string;
        QString qs = macCamXML.locs[i].serverName;
        std::string str = qs.toLatin1().constData();
        const char* serverName = str.c_str();

        //of form : static BOOL GetResourceName(const char *serverName, SapManager::ResType resourceType,
        //int resourceIndex, char* resourceName);

        SapManager::GetResourceName(serverName, SapManager::ResourceAcqDevice, macCamXML.locs[i].deviceIndex, deviceName);

        if (deviceName == this->macCamXML.SerialNumber.toStdString())
        {
            SapLocation loc(serverName, macCamXML.locs[i].deviceIndex);
            camLoc = loc;

            // Create a SapAcqDevice object
            acqDevice = new SapAcqDevice(loc, configFile);
            if (!acqDevice->Create())
            {
                std::cout << "could not open Gige device.\n";
            }
            std::cout << "Detected TDalsa Camera has serial number " << deviceName << std::endl;

            this->serialNo = deviceName;
            noMatchingString = false;
        }

        if(!noMatchingString)
            break;

    }
    if (noMatchingString)
    {
        std::cout << "MachCamXML File : TeleDyne Dalsa - no matching serial number. Exit(0). " << std::endl;
        exit(0);
    }

}

TeleDalsaSaperaLT::~TeleDalsaSaperaLT()
{
 std::cout << "The TeleDalsaSaperaLT destructor has been invoked." << std::endl;
}

bool TeleDalsaSaperaLT::open(int grabberNumber)
{
    // Get the number of features provided by the camera
    int featureCount;
    status = acqDevice->GetFeatureCount(&featureCount);

    // Create an empty feature object (to receive information)
    SapFeature feature(camLoc);
    if (!(feature.Create()))
    {
        std::cout << "could not open Gige feature object.\n";
        return false;
    }

    // Get information from current feature
    // Get feature object
    char valueChar[64];
    int64 valueInt64;
    if (!acqDevice->GetFeatureValue("DeviceSerialNumber", valueChar, sizeof(valueChar)))
    {
        std::cout << "could not open Gige feature value:DeviceSerialNumber .\n";
        return false;
    }
    this->serialNo = valueChar;

    if (!acqDevice->GetFeatureValue("PixelSize", &valueInt64))
    {
        std::cout << "could not open Gige feature value:PixelSize .\n";
        return false;
    }
    this->pixelSize = valueInt64;

    if (!acqDevice->GetFeatureValue("Width", &valueInt64))
    {
        std::cout << "could not open Gige feature value:Width .\n";
        return false;
    }
    this->width = valueInt64;

    if (!acqDevice->GetFeatureValue("Height", &valueInt64))
    {
        std::cout << "could not open Gige feature value:Height .\n";
        return false;
    }
    this->height = valueInt64;

    // build the buffer
    buffers = new SapBuffer (this->nBuffers, (int) this->width, (int)this->height, SapFormatMono8, SapBuffer::TypeScatterGather);

    if (!buffers->Create())
    {
      std::cout << "could not create the buffer object.\n";
      return false;
    }

    //Pointer to buffer[0] data address
    if (!buffers->GetAddress((void**)&pData))
    {
        std::cout << "buffer pointer is NULL but should point to a valid memory loacation";
    }


    //The transfer object
    // SapAcqDeviceToBuf(SapAcqDevice *pAcqDevice, SapBuffer *pBuf, SapXferCallback pCallback = NULL, void *pContext = NULL);
    xfer = new SapAcqDeviceToBuf(acqDevice, buffers, NULL, NULL);
    acqDevice->RegisterCallback("FrameEnd", callBackFrameCounter,&FrameCount);


    if (!xfer->Create())
    {
        std::cout << "could not create the transfer object\n";
        return false;
    }
    // Start continous grab
    xfer->Grab();


    return true;

}

void TeleDalsaSaperaLT::release()
{

}

bool TeleDalsaSaperaLT::grab()
{
    //does nothing

    return true;
}

bool TeleDalsaSaperaLT::retrieve(cv::Mat &image, int n)
{
    n = 0; // does nothing for compatability only
    //cout << "entered retrieve x,x" <<endl; // test

    cv::Mat im = cv::Mat((int)this->height,(int)this->width, CV_8UC1, this->pData);

    if (!im.data)
    {
        printf (" error in retrieve() - no image data xx.\n");
        return false;
    }

    while(PreviousFrameCount == FrameCount) {}

        PreviousFrameCount = FrameCount;
        image = im;
        return true;
}

bool TeleDalsaSaperaLT::retrieve(cv::Mat &image)
{

    //cout << "entered retrieve x" <<endl; // test

    cv::Mat im = cv::Mat((int)this->height,(int)this->width, CV_8UC1, this->pData);

    if (!im.data)
    {
        printf (" error in retrieve() - no image data x.\n");
        return false;
    }

    while(PreviousFrameCount == FrameCount) {}

        PreviousFrameCount = FrameCount;
        image = im;
        return true;
}

double TeleDalsaSaperaLT::get(int propId)
{
    switch (propId)
    {
    case CV_CAP_PROP_FRAME_WIDTH:
        return (double) width;
        break;

    case CV_CAP_PROP_FRAME_HEIGHT:
        return (double)height;
        break;

    default:
        std::cout << "error in switch of get(int)" << std::endl;
        break;
    }

    return -1.0;
}

bool TeleDalsaSaperaLT::set(int propId, double value)
{
    propId = 0; // both are purely for compatability
    value = 0;
    return true;
}

bool TeleDalsaSaperaLT::isOpened() const
{
    if (!acqDevice)
        return false;
    else
        return true;
}

int TeleDalsaSaperaLT::ErrorMessage(int err)
{
    err = 1;
    return 1;
}

int TeleDalsaSaperaLT::ErrorMessageWait(int err)
{
    err = 1;
    return 1;
}

unsigned int TeleDalsaSaperaLT::getWidth() const
{
    return 1;

}

unsigned int TeleDalsaSaperaLT::getHeight() const
{
    return 1;
}

unsigned int TeleDalsaSaperaLT::getChannels() const
{
    return 1;
}


unsigned int TeleDalsaSaperaLT::getbytesPerChannel() const
{
    return 1;

}



void TeleDalsaSaperaLT::callBackFrameCounter(SapAcqDeviceCallbackInfo *pInfo)
{
        int* frameCount = (int*)pInfo->GetContext();
        (*frameCount)++;

}

QVector<LocationStruct> findT_DalsaGigeCams() // not a member of Class::TeleDalsaSaperaLT
{
    std::cout << "Finding Gige Cameras...." << std::endl;

    char    serverName [FS_SERVER_NAME_LENGTH];
    int GenieIndex = 0;
    int deviceIndex = 0;
    QVector<LocationStruct> camLocs; //to hold the Gige cam locations (server/device pairs)
    bool showGigEOnly = true;
    bool serverFound = false;


    //interrogate the full system to see what TeleDyne Dalsa Cameras are connected
    int serverCount = SapManager::GetServerCount(); // remember the first server [0] = the host server (this pc)

    //With Gige cameras - Cameras are the servers and camera resources are the devices.
    for (int serverIndex = 0; serverIndex < serverCount; serverIndex++)
    {
         if (SapManager::GetResourceCount(serverIndex, SapManager::ResourceAcqDevice) != 0)
       {
             SapManager::GetServerName(serverIndex, serverName, sizeof(serverName));
          if (showGigEOnly && strstr(serverName,"CameraLink_") > 0)
             continue;
             printf("%d: %s\n", GenieIndex+1, serverName);
             GenieIndex++;
             serverFound = TRUE;
             //deviceCount = GenieIndex;

             char deviceName[CORPRM_GETSIZE(CORACQ_PRM_LABEL)];

             deviceIndex=0;
             SapManager::GetResourceName(serverName, SapManager::ResourceAcqDevice, deviceIndex, deviceName, sizeof(deviceName));
             printf("    %s%s\n", "User defined Name : ", deviceName);
             printf("........................................\n");

             LocationStruct loc;
             loc.serverName = serverName;
             loc.deviceIndex = deviceIndex;
             camLocs.push_back(loc);
         }
    }
    return camLocs;
}


#endif //_WIN32
