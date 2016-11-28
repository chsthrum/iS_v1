/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* CaptureThread.h                                                      */
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

#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

// Qt
#include <QtCore/QTime>
#include <QtCore/QThread>
// OpenCV
#include <opencv2/highgui/highgui.hpp>
// Local
#include "SharedImageBuffer.h"
#include "Config.h"
#include "MatToQImage.h"
#include "Structures.h"

using namespace cv;

class ImageBuffer;

class CaptureThread : public QThread
{
    Q_OBJECT

    public:
        //for local Camera
        CaptureThread(SharedImageBuffer *sharedImageBuffer, int deviceNumber, bool dropFrameIfBufferFull, int width, int height);
        //for machine vision camera
        CaptureThread(SharedImageBuffer *sharedImageBuffer, int deviceNumber, bool dropFrameIfBufferFull, int width, int height, int camType);
        ~CaptureThread();
        void stop();
        void setGrab(bool);
        bool connectToCamera();
        bool disconnectCamera();
        bool isCameraConnected();
        int getInputSourceWidth();
        int getInputSourceHeight();

    private:
        void updateFPS(int);
        SharedImageBuffer *sharedImageBuffer;
        VideoCapture *cap;
        Mat grabbedFrame;
        QImage frame;
        QTime t;
        QMutex doStopMutex;
        QMutex doGrabMutex;
        QQueue<int> fps;
        struct ThreadStatisticsData statsData;
        volatile bool doStop;
        volatile bool doGrab;
        int captureTime;
        int sampleNumber;
        int fpsSum;
        bool dropFrameIfBufferFull;
        int deviceNumber;
        int width;
        int height;
        int cameraType;

    protected:
        void run();

    signals:
        void updateStatisticsInGUI(struct ThreadStatisticsData);

};

#endif // CAPTURETHREAD_H
