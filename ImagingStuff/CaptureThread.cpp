/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* CaptureThread.cpp                                                    */
/*                                                                      */
/* Nick D'Ademo <nickdademo@gmail.com>                                  */
/*                                                                      */
/* Copyright (c) 2012-2013 Nick D'Ademo                                 */
/*                                                                      */
/* Permission is hereby granted, free of charge, to any person          */
/* obtaining a copy of this software and associated documentation       */
/* files (the "Software"), to deal in the Software without restriction, */
/* including without limitation the rights to use, copy, modify, merge, */
/* publish, distribute, sublicense, and/or sell copies of the Software, */
/* and to permit persons to whom the Software is furnished to do so,    */
/* subject to the following conditions:                                 */
/*                                                                      */
/* The above copyright notice and this permission notice shall be       */
/* included in all copies or substantial portions of the Software.      */
/*                                                                      */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  */
/* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   */
/* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    */
/* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     */
/* SOFTWARE.                                                            */
/*                                                                      */
/************************************************************************/

#include "CaptureThread.h"
#include "ImagingStuff/Config.h"
#include "../ExternalHardwareSoftware/siliconsoftwaregrabber_1.h"
#include "../ExternalHardwareSoftware/baslerpylondart_1.h"

//CaptureThread::CaptureThread(SharedImageBuffer *sharedImageBuffer, int deviceNumber, bool dropFrameIfBufferFull, int width, int height): QThread(), sharedImageBuffer(sharedImageBuffer)
//{
//    cap = new VideoCapture;
//    // Save passed parameters
//    this->dropFrameIfBufferFull=dropFrameIfBufferFull;
//    this->deviceNumber=deviceNumber;
//    this->width = width;
//    this->height = height;
//    // Initialize variables(s)
//    doStop=false;
//    doGrab=false;
//    sampleNumber=0;
//    fpsSum=0;
//    fps.clear();
//    statsData.averageFPS=0;
//    statsData.nFramesProcessed=0;

//}

CaptureThread::CaptureThread(SharedImageBuffer *sharedImageBuffer, int deviceNumber, bool dropFrameIfBufferFull, int width, int height, MachCamConfigFileXMLData machCamData) : QThread(), sharedImageBuffer(sharedImageBuffer)
{
    switch(machCamData.ManufacturerType)
    {
    case FS_LOCAL_CAM:
        cap = new VideoCapture;
        break;
    case FS_SISO_CIS_GRAY:
        break;
    case FS_SISO_CIS_RGB:
        // this should be a refer to a centrally located setup file
        //cap = new SiliconSoftwareGrabber(0, 0, "C:/Program Files/SiliconSoftware/Runtime5.2.1/bin/MySisoMcf/YKK_BLUE_UNCUT_600DPI.mcf");
        cap = new SiliconSoftwareGrabber(0, 0, "C:/Program Files/SiliconSoftware/Runtime5.2.1/bin/MySisoMcf/YKK_BLUE_UNCUT_600DPI.mcf");
        break;
    case FS_BASLER_DART_PYLON_AREA:
        //cap = new BaslerPylonDart(CTlFactory::GetInstance(), 2, "C:/Users/Fibrescan/Documents/BaslerFeatureFiles/daA1280-54uc_21917870.pfs");
        cap = new BaslerPylonDart(CTlFactory::GetInstance(), machCamData.CameraNumber.toInt(), machCamData.filePathName);
        break;
    default:
        std::cout << " passed thru to default option CaptureThread Constructor switch statement)" << std::endl;
        break;
    }

    // Save passed parameters
    this->dropFrameIfBufferFull=dropFrameIfBufferFull;
    this->deviceNumber=deviceNumber;
    this->width = width;
    this->height = height;
    this->cameraType = machCamData.ManufacturerType;
    // Initialize variables(s)
    doStop=false;
    doGrab=false;
    sampleNumber=0;
    fpsSum=0;
    fps.clear();
    statsData.averageFPS=0;
    statsData.nFramesProcessed=0;
}


CaptureThread::~CaptureThread()
{

}


void CaptureThread::run()
{
    while(1) // This outer loop controls the camera state active or stopped
    {
        ////////////////////////////////
        // Stop thread if doStop=TRUE //
        ////////////////////////////////
        doStopMutex.lock();
        if(doStop)
        {
            doStop=false;
            doStopMutex.unlock();
            break; // break from the outer loop
        }
        doStopMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        while(1)    //this inner while loop does all the work, - we also need to include doStop detection.
        {
            ////////////////////////////////
            // Stop thread if doStop=TRUE //
            ////////////////////////////////
            doStopMutex.lock();
            if(doStop)
            {
                //doStop=false;
                doStopMutex.unlock();
                break; // break from the outer loop
            }
            doStopMutex.unlock();
            /////////////////////////////////
            /////////////////////////////////


            /////////////////////////////////
            //grab images if doGrab = TRUE
            /////////////////////////////////
            doGrabMutex.lock();
            if(!doGrab)
            {
                doGrabMutex.unlock();
                break; // break from the inner loop
            }
            doGrabMutex.unlock();
            /////////////////////////////////
            /////////////////////////////////

            // Save capture time
            captureTime=t.elapsed();
            // Start timer (used to calculate capture rate)
            t.start();

            // Synchronize with other streams (if enabled for this stream)
            sharedImageBuffer->sync(deviceNumber);

            // Capture frame (if available)
            if (!cap->grab())
                continue;   //go to the very end of the while loop, to avoid the next statements


            // Retrieve frame
            cap->retrieve(grabbedFrame);
            // Add frame to buffer
            sharedImageBuffer->getByDeviceNumber(deviceNumber)->add(grabbedFrame, dropFrameIfBufferFull);

            // Update statistics
            updateFPS(captureTime); //temp note bugs here
            statsData.nFramesProcessed++;
            // Inform GUI of updated statistics
            emit updateStatisticsInGUI(statsData);
        }
    //qDebug() << "Hello from captureThread";
    }
    qDebug() << "Stopping capture thread...";
}

bool CaptureThread::connectToCamera()
{
    // Open camera
    bool camOpenResult = cap->open(deviceNumber);

    // Set resolution
    if(width != -1)
        cap->set(CV_CAP_PROP_FRAME_WIDTH, width);

    if(height != -1)
        cap->set(CV_CAP_PROP_FRAME_HEIGHT, height);
    // Return result
    return camOpenResult;
}

bool CaptureThread::disconnectCamera()
{
    // Camera is connected
    if(cap->isOpened())
    {
        // Disconnect camera
        cap->release();
        return true;
    }
    // Camera is NOT connected
    else
        return false;
}

void CaptureThread::updateFPS(int timeElapsed)
{
    // Add instantaneous FPS value to queue
    if(timeElapsed>0)
    {
        fps.enqueue((int)1000/timeElapsed);
        // Increment sample number
        sampleNumber++;
    }
    // Maximum size of queue is DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH
    if(fps.size()>CAPTURE_FPS_STAT_QUEUE_LENGTH)
        fps.dequeue();
    // Update FPS value every DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH samples
    if((fps.size()==CAPTURE_FPS_STAT_QUEUE_LENGTH)&&(sampleNumber==CAPTURE_FPS_STAT_QUEUE_LENGTH))
    {
        // Empty queue in the while loop and store sum
        while(!fps.empty())
            fpsSum+=fps.dequeue();
        // Calculate average FPS
        statsData.averageFPS=fpsSum/CAPTURE_FPS_STAT_QUEUE_LENGTH;
        // Reset sum
        fpsSum=0;
        // Reset sample number
        sampleNumber=0;
    }
}

void CaptureThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    doStop=true;
}

void CaptureThread::setGrab(bool dG)
{
    QMutexLocker locker(&doGrabMutex);
    doGrab = dG;

}

bool CaptureThread::isCameraConnected()
{
    return cap->isOpened();
}

int CaptureThread::getInputSourceWidth()
{
        return cap->get(CV_CAP_PROP_FRAME_WIDTH);
}

int CaptureThread::getInputSourceHeight()
{
    return cap->get(CV_CAP_PROP_FRAME_HEIGHT);
}
