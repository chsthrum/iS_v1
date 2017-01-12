#ifndef TELEDYNEDALSASAPERA_1
#define TELEDYNEDALSASAPERA_1

// Disable deprecated function warnings with Visual Studio 2005
#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(disable: 4995)
#endif

#define CAMERA_NUMBER  2

// Teledyne Dalsa includes
#include "sapclassbasic.h"

//c includes
#include "stdio.h"
#include "conio.h"

//stl includes
#include <iostream>
#include <string>
#include <vector>

//opencv includes
#include "opencv2/highgui/highgui.hpp"

//local includes
#include "../ImagingStuff/Structures.h"


#ifdef _WIN32
class TeleDalsaSaperaLT : public cv::VideoCapture
{
public:
    //explicit TeleDalsaSaperaLT(std::vector<SapLocation>& cameras, int grabberNumber, const char *configFile);
    explicit TeleDalsaSaperaLT(std::vector<SapLocation>& cameras, MachCamConfigFileXMLData& ); // for i4060 application
    virtual ~TeleDalsaSaperaLT();
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

    unsigned int nBuffers = 1; //using n sub buffers
    int grabNo;
    int portNo;
    std::string serialNo;
    std::vector<SapLocation>& camLocs;
    MachCamConfigFileXMLData& macCamXML;
    BOOL status = false;



    SapAcqDevice		*acqDevice = NULL;
    SapBuffer			*buffers = NULL;
    SapAcqDeviceToBuf   *xfer = NULL; // a non framegrabber device ie. a gige camera
    SapLocation         *loc = NULL;

    unsigned char* pData;// This smart pointer will receive the address of the grab result data.

    int grabbedImages;// Create an integer variable to count the number (if used) of grabbed images.

    int64 width;
    int64 height;
    int64 pixelSize; // number of bits

    int FrameCount = 0;
    int PreviousFrameCount = 0;

    int format; // for bytes per pixel
    unsigned int bytesPerPixel; // 1 for grayscale and 3 for RGB
    int boardType;
    size_t totalBuffersSizeInBytes;

    int timeout = 4000; //mSec
    bool isRunning; // the flag for whether the camera is running(true) or not(false)

    //private callback function
    static void callBackFrameCounter(SapAcqDeviceCallbackInfo *pInfo);


};

// for finding the TeleDyne Dalsa Gige Cameras
std::vector<SapLocation> findT_DalsaGigeCams(); // not a member of Class::TeleDalsaSaperaLT


#endif // _WIN32

#endif // TELEDYNEDALSASAPERA_1

