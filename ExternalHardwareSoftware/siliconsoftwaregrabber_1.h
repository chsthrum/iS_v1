#ifndef SILICONSOFTWAREGRABBER_1_H
#define SILICONSOFTWAREGRABBER_1_H

// a the class to operate the silicon software grabber api

//siso includes.
#ifdef win32
#include <fgrab_struct.h>
#include <fgrab_prototype.h>
#include <fgrab_define.h>
#include "board_and_dll_chooser" // is this really needed.
#endif

//opencv includes
#include "opencv2/highgui/highgui.hpp"

//stl includes
#include <iostream>
#include <string>

#ifdef _WIN32
class SiliconSoftwareGrabber : cv::VideoCapture
{
public:

    explicit SiliconSoftwareGrabber(unsigned int cameraNumber, unsigned int portNumber, const std::string& configFile);
    ~SiliconSoftwareGrabber();

    virtual bool open(const std::string &filename);
    virtual void release();
    virtual double get() const;
    virtual bool set();
    virtual bool isOpened() const;
    virtual bool grab();
    virtual bool retrieve ();     //grabbedFrame

private:
    int camNo;
    int portNo;
    std::string config;

    Fg_Struct *fg;
    dma_mem *mem;

};
#endif

#endif // SILICONSOFTWAREGRABBER_1_H
