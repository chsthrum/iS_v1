#include <stdio.h>
#include "siliconsoftwaregrabber_1.h"

#ifdef _WIN32
SiliconSoftwareGrabber::SiliconSoftwareGrabber(int grabberNumber, unsigned int portNumber, QString configFile)
    :grabNo(grabberNumber),  portNo(portNumber)// config(configFile) // directly initialize our member variables
{
    config = "C:/Program Files/SiliconSoftware/Runtime5.2.1/bin/MySisoMcf/YKK_BLUE_UNCUT_600DPI.mcf";
    boardType = 0;
    fg = NULL;
    applet = NULL;
    printf ("starting the grabber board\n");
    boardType = (Fg_getBoardType(grabberNumber));
    last_pic_nr = 0;
    current_pic_nr = 0;

    // initialise the board.

    if (boardType == PN_MICROENABLE4AD4CL)
        applet = "DualLineRGB30";

    if ((fg = Fg_InitConfig(config, grabNo))== NULL) //initilise the grabber board using a cammera configuration file
    {
        ErrorMessageWait(fg);
        Fg_FreeGrabber(fg);
    }

    if (Fg_getParameter(fg,FG_WIDTH,&width,portNo) < 0) // Get the image width parameter
    {
        ErrorMessageWait(fg);
        Fg_FreeGrabber(fg);

    }

    if (Fg_getParameter(fg,FG_HEIGHT,&height,portNo) < 0)  // Get the image height parameter
    {
        ErrorMessageWait(fg);
        Fg_FreeGrabber(fg);

    }

    if (Fg_getParameter(fg,FG_FORMAT,&format,portNo) < 0)  // Get the image format
    {
        ErrorMessageWait(fg);
        Fg_FreeGrabber(fg);

    }

    switch (format)   //// Get the image bytes per pixel ie RGB=3
    {
    case FG_GRAY:
        bytesPerPixel = 1;
        break;
    case FG_COL24:
        bytesPerPixel = 3;
        break;
    default:
        bytesPerPixel = 3;
        break;
    }

}

SiliconSoftwareGrabber::~SiliconSoftwareGrabber()
{
    printf ("\nThe SiliconSoftwareGrabber destructor has been invoked\n\n");
}

bool SiliconSoftwareGrabber::open(int grabber)
{
    grabber = 0; // purely for compatability has no effect

    // total buffer memory size for grabber board
    totalBuffersSizeInBytes = width * height * bytesPerPixel* nBuffers;

    // alloccate the storage

    mem = Fg_AllocMemEx(fg, totalBuffersSizeInBytes, nBuffers);
    if (mem == NULL)  //
    {
        ErrorMessageWait(fg);
        Fg_FreeMemEx(fg, mem);
        Fg_FreeGrabber(fg);
        return false;
    }

    // Start Acquiring images from the camera into the Circular Buffers, non blocking. ie overwriting the buffers each time around.

    if ((Fg_AcquireEx(fg, portNo, GRAB_INFINITE, ACQ_STANDARD, mem)) < 0)
    {
        ErrorMessageWait(fg);
        Fg_FreeMemEx(fg, mem);
        Fg_FreeGrabber(fg);
        return false;
    }

    return true;  // FG_OK = 0
}

void SiliconSoftwareGrabber::release()
{
    Fg_FreeMemEx(fg, mem);
    Fg_FreeGrabber(fg);
}

double SiliconSoftwareGrabber::get(int propId)
{

    switch (propId)
    {
    case CV_CAP_PROP_FRAME_WIDTH:
        if (Fg_getParameter(fg,FG_WIDTH,&width,portNo) < 0) // Get the image width parameter
        {
            ErrorMessageWait(fg);
            Fg_FreeGrabber(fg);
            return -1.0;
        }
        return (double) width;
        break;

    case CV_CAP_PROP_FRAME_HEIGHT:
        if (Fg_getParameter(fg,FG_HEIGHT,&height,portNo) < 0)  // Get the image height parameter
        {
            ErrorMessageWait(fg);
            Fg_FreeGrabber(fg);
            return -1.0;
        }
        return (double)height;
        break;

    default:
        std::cout << "error in switch of get(int)" << std::endl;
        break;
    }

    return -1.0;
}

bool SiliconSoftwareGrabber::set(int propId, double value)
{
    propId = 0; // both are purely for compatability have no effect
    value = 0;
    return true;
}


bool SiliconSoftwareGrabber::isOpened() const
{
return 0;
}

bool SiliconSoftwareGrabber::grab()
{
    //NONE BLOCKING - every call to grab()returns the last image number transferred - even if is the same image number
    //current_pic_nr = Fg_getLastPicNumberEx(fg, portNo, mem);
    //BLOCKS until the image is transfered into the buffer. grab() will not return until the image is transferred
    current_pic_nr = Fg_getLastPicNumberBlockingEx(fg, last_pic_nr+1, portNo, timeout, mem);
    last_pic_nr = current_pic_nr;
    std::cout << "currentPicNumber = " << current_pic_nr << std::endl;

    if (current_pic_nr < 0) // error
    {
        ErrorMessageWait(fg);
        Fg_FreeMemEx(fg, mem);
        Fg_FreeGrabber(fg);
        return false;
    }
    else if (current_pic_nr == 0 ) // not finished transfering image to buffer
    {
        return false;
    }

    else return true;  // valid picture number returned indicating the iamge is now in the buffer.

}

bool SiliconSoftwareGrabber::retrieve(cv::Mat &im, int i) // retrieve image from buffer
{
    i = 0; // for compatibility
    im = cv::Mat(height, width, CV_8UC3, Fg_getImagePtrEx(fg, last_pic_nr, portNo, mem));

    if (!im.data)
    {
        printf (" error in retrieve() - no image data.\n");
        return false;
    }

    else return true;
}

bool SiliconSoftwareGrabber::retrieve(cv::Mat &im)
{
    im = cv::Mat(height, width, CV_8UC3, Fg_getImagePtrEx(fg, last_pic_nr, portNo, mem));

    if (!im.data)
    {
        printf (" error in retrieve() - no image data.\n");
        return false;
    }

    else return true;
}


int SiliconSoftwareGrabber::ErrorMessage(Fg_Struct *fg)
{
    int	error	= Fg_getLastErrorNumber(fg);
    const char*	err_str = Fg_getLastErrorDescription(fg);
    fprintf(stderr,"Error: %d : %s\n",error,err_str);
    return error;
}

int SiliconSoftwareGrabber::ErrorMessageWait(Fg_Struct *fg)
{
    int	error	= ErrorMessage(fg);
    printf (" ... press ENTER to continue\n");
    getchar();
    return error;
}

unsigned int SiliconSoftwareGrabber::getWidth() const
{
return 0;
}

unsigned int SiliconSoftwareGrabber::getHeight() const
{
return 0;
}

unsigned int SiliconSoftwareGrabber::getChannels() const
{
return 0;
}

unsigned int SiliconSoftwareGrabber::getbytesPerChannel() const
{
    return 0;
}

frameindex_t SiliconSoftwareGrabber::getCurrentPicNo() const
{
    return current_pic_nr;
}

#endif //_WIN32

