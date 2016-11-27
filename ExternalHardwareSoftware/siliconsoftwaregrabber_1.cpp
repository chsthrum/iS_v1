#include "siliconsoftwaregrabber_1.h"

#ifdef win32
SiliconSoftwareGrabber::SiliconSoftwareGrabber(unsigned int cameraNumber, unsigned int portNumber, const std::string &configFile)
    :camNo(cameraNumber),  portNo(portNumber), config(configFile) // directly initialize our member variables
{

}

SiliconSoftwareGrabber::~SiliconSoftwareGrabber()
{

}

#endif

