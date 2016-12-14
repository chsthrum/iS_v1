#ifndef SILICONSOFTWAREGRABBER_1_H
#define SILICONSOFTWAREGRABBER_1_H

// a the class to operate the silicon software grabber api


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

//siso includes.
#ifdef _WIN32
#include <fgrab_struct.h>
#include <fgrab_prototyp.h>
#include <fgrab_define.h>

#endif

//opencv includes
#include "opencv2/highgui/highgui.hpp"

//stl includes
#include <iostream>
#include <string>

#include <QString>

#ifdef _WIN32
class SiliconSoftwareGrabber : public cv::VideoCapture
{
public:

    explicit SiliconSoftwareGrabber(int grabberNumber, unsigned int portNumber, QString configFile);
    virtual ~SiliconSoftwareGrabber();

    virtual bool open(int) override;
    virtual void release()override;
    virtual bool grab()override;
    virtual bool retrieve (cv::Mat& im, int) override;     //grabbedFrame - can be used via the overiding the base class with just the image reference call
    virtual bool retrieve (cv::Mat& im);     //grabbedFrame - this is not a base overiding method
    virtual double get(int propId) override;
    virtual bool set(int propId, double value) override;
    virtual bool isOpened() const override;


    int ErrorMessage(Fg_Struct *fg);
    int ErrorMessageWait(Fg_Struct *fg);

    unsigned int getWidth()const;
    unsigned int getHeight()const;
    unsigned int getChannels()const;
    unsigned int getbytesPerChannel()const;

    frameindex_t getCurrentPicNo() const;

private:
    int grabNo;
    int portNo;
    const char* config;

    Fg_Struct *fg;
    dma_mem *mem;
    int nBuffers = 32;
    const char *applet;
    unsigned int width;
    unsigned int height;
    int format; // for bytes per pixel
    unsigned int bytesPerPixel; // 1 for grayscale and 3 for RGB
    int boardType;
    size_t totalBuffersSizeInBytes;
    frameindex_t last_pic_nr;
    frameindex_t current_pic_nr;
    int timeout = 4;
    bool isRunning; // the flag for whether the camera is running(true) or not(false)





};
#endif // _WIN32

#endif // SILICONSOFTWAREGRABBER_1_H
