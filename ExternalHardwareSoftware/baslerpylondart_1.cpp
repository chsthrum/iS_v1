#include "baslerpylondart_1.h"

#ifdef _WIN32

//BaslerPylonDart::BaslerPylonDart(CTlFactory &tlFac, MachCamConfigFileXMLData machCamData):tlFactory(tlFac)
BaslerPylonDart::BaslerPylonDart(MachCamConfigFileXMLData& machCamData): macCamXML(machCamData)
{
    CTlFactory& tlFactory = CTlFactory::GetInstance();

    //variable initialisation
    grabbedImages = 0.;
    int cameraNumber = machCamData.CameraNumber.toInt();

    // Get all attached devices and exit application if no device is found.
    DeviceInfoList_t devices;

    tlFactory.EnumerateDevices(devices);

//    if ( tlFactory.EnumerateDevices(devices) == 0 )
//    {
//        throw RUNTIME_EXCEPTION( "No camera present.");
//    }
    cout << "number of cameras: " << devices.size() << endl;

    cam = new CInstantCamera;

    // choose the camera
    bool noMatchingString = true;
    for (int i = 0; i < devices.size(); i++ )
    {
        string sn = devices[i].GetSerialNumber();
        if (sn == macCamXML.SerialNumber.toStdString())
        {
            cam->Attach( tlFactory.CreateDevice( devices[i]));
            cout << "Detected Basler Camera has serial number " << sn << endl;
            this->serialNo = sn;
            noMatchingString = false;
        }
    }

    if (noMatchingString)
    {
        cout << "MachCamXML File : Basler Transport Layer - no matching serial number. Exit(0). " << endl;
        exit(0);
    }

    // Print the model name of the camera.
    cout << "Using Camera No " << cameraNumber << " Device type " << cam->GetDeviceInfo().GetModelName()
    << " Serial Number " << cam->GetDeviceInfo().GetSerialNumber()<< endl;
}

BaslerPylonDart::~BaslerPylonDart()
{
cout << "The SiliconSoftwareGrabber destructor has been invoked." << endl;
}

bool BaslerPylonDart::open(int device)
{
    device = 0; // purely for compatability - no effect

    QString text = macCamXML.filePathName;
    std::string s = text.toLatin1().constData();
    const char* configFile = s.c_str();


    //const char* test = config;
    //open the camer for loading the configuration file and interrogating the nodemap.
    cam->Open();

    //cout << "file: " << test << " loaded into camera number: " << device << endl;
    CFeaturePersistence::Load(configFile, &cam->GetNodeMap(), false); // config


    //    try
    //    {
    //     //read the content of the file back to the camera's node map with enabled validation.
    //     cout << "Reading file back to camera's node map..."<< endl;
    //     CFeaturePersistence::Load(config, &cam->GetNodeMap(), false);
    //     cout << "file: " << config << " loaded into camera number: " << device << endl;
    //    }
    //    catch (const GenericException & e)
    //    {
    //      cerr << "Failed to set the Load the configuration file to the nodemap. Reason: "
    //      << e.GetDescription() << endl;
    //    }

    INodeMap& nodemap = cam->GetNodeMap();


    CIntegerPtr width( nodemap.GetNode( "Width"));
    CIntegerPtr height( nodemap.GetNode( "Height"));
    this->width = (int) width->GetValue();
    this->height = (int) height->GetValue();
    //close the camera after loading the configuration file and interrogating the nodemap.

    cam->MaxNumBuffer = 16; //default = 10.

    //Specify the output pixel format.
    formatConverter.OutputPixelFormat = PixelType_BGR8packed;


    cam->Close();


    // According to their default configuration, the cameras are
    // set up for free-running continuous acquisition.
    cam->StartGrabbing();

    return true;
}

void BaslerPylonDart::release()
{
    //cam->DestroyDevice();
}

bool BaslerPylonDart::grab()
{
    //does nothing


    return true;
}

bool BaslerPylonDart::retrieve(cv::Mat &im, int i)
{
    i = 0; // for compatibility

    //cout << "entered retrieve x" <<endl; // test

    // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
        cam->RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);

        // Image grabbed successfully?
        if (ptrGrabResult->GrabSucceeded())
        {

            formatConverter.Convert(pylonImage, ptrGrabResult);
            // Access the image data.
            //cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
            //cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
            //const uint8_t *pImageBuffer = (uint8_t *) ptrGrabResult->GetBuffer();
            //cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[0] << endl << endl;

        }
        else
        {
            cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
        }

    im = cv::Mat(ptrGrabResult->GetHeight(),ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*)pylonImage.GetBuffer());

    if (!im.data)
    {
        printf (" error in retrieve() - no image data.\n");
        return false;
    }

    else return true;

}

bool BaslerPylonDart::retrieve(cv::Mat &im)
{
     //cout << "entered retrieve xx" <<endl; // test

    // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
        cam->RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);

        // Image grabbed successfully?
        if (ptrGrabResult->GrabSucceeded())
        {

            formatConverter.Convert(pylonImage, ptrGrabResult);
            // Access the image data.
            //cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
            //cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
            //const uint8_t *pImageBuffer = (uint8_t *) ptrGrabResult->GetBuffer();
            //cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[0] << endl << endl;

        }
        else
        {
            cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
        }

    im = cv::Mat(ptrGrabResult->GetHeight(),ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*)pylonImage.GetBuffer());

    if (!im.data)
    {
        printf (" error in retrieve() - no image data.\n");
        return false;
    }

    else return true;

}

double BaslerPylonDart::get(int propId)
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

bool BaslerPylonDart::set(int propId, double value)
{
    propId = 0; // both are purely for compatability
    value = 0;
    return true;
}

bool BaslerPylonDart::isOpened() const
{
   return true;
}

int BaslerPylonDart::ErrorMessage(int err)
{
    err = 1;
    return 1;
}

int BaslerPylonDart::ErrorMessageWait(int err)
{
    err = 1;
    return 1;
}

unsigned int BaslerPylonDart::getWidth() const
{
    return 1;
}

unsigned int BaslerPylonDart::getHeight() const
{
    return 1;
}

unsigned int BaslerPylonDart::getChannels() const
{
    return 1;
}

unsigned int BaslerPylonDart::getbytesPerChannel() const
{
    return 1;
}

#endif //_WIN32
