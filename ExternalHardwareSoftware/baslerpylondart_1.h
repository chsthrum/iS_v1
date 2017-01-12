#ifndef BASLERPYLONDART_1
#define BASLERPYLONDART_1


// a the class to operate the basler pylon api

//#include "C:\Program Files (x86)\Microsoft SDKs\Cpp REST SDK for Visual Studio 2013\SDK\include\asyncrt_utils.h"


// Include files to use the PYLON API.
#include <pylon/PylonIncludes.h>

// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using cout.
using namespace std;

// Allow all the names in the namespace GenApi to be used without qualification.
using namespace GenApi;


//opencv includes
#include "opencv2/highgui/highgui.hpp"

//stl includes
//stl includes
#include <iostream>
#include <string>
//QT includes
#include <QString>
//Local includes
#include "../ImagingStuff/Structures.h"

#ifdef _WIN32
class BaslerPylonDart : public cv::VideoCapture
{
public:

    //explicit BaslerPylonDart(CTlFactory& tlFac, int grabberNumber, const char *configFile);
    //explicit BaslerPylonDart(CTlFactory& tlFac, int grabberNumber, QString configFile);
    //explicit BaslerPylonDart(CTlFactory& tlFac, MachCamConfigFileXMLData);
    explicit BaslerPylonDart(MachCamConfigFileXMLData &);

    virtual ~BaslerPylonDart();

    virtual bool open(int) override;
    virtual void release()override;
    virtual bool grab()override;
    virtual bool retrieve (cv::Mat& im, int) override;     //grabbedFrame - can be used via the overiding the base class with just the image reference call
    virtual bool retrieve (cv::Mat& im);     //grabbedFrame - this is not a base overiding method
    virtual double get(int propId) override;
    virtual bool set(int propId, double value) override;
    virtual bool isOpened() const override;


    int ErrorMessage(int err);
    int ErrorMessageWait(int err);

    unsigned int getWidth()const;
    unsigned int getHeight()const;
    unsigned int getChannels()const;
    unsigned int getbytesPerChannel()const;

private:
    int grabNo;
    int portNo;
    string serialNo;

    MachCamConfigFileXMLData& macCamXML;

    //const char* config;
    //const char* filename;




    //CTlFactory& tlFactory;
    CInstantCamera* cam;
    CGrabResultPtr ptrGrabResult;// This smart pointer will receive the grab result data.
    CImageFormatConverter formatConverter; // Create a pylon image converter object
    CPylonImage pylonImage;// Create a PylonImage that will be used to create OpenCV images later.
    int grabbedImages;// Create an integer variable to count the number (if used) of grabbed images.

    unsigned int width;
    unsigned int height;
    int format; // for bytes per pixel
    unsigned int bytesPerPixel; // 1 for grayscale and 3 for RGB
    int boardType;
    size_t totalBuffersSizeInBytes;

    int timeout = 4000; //mSec
    bool isRunning; // the flag for whether the camera is running(true) or not(false)





};
#endif // _WIN32

#endif // BASLERPYLONDART_1

