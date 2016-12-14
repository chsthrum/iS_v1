/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* Structures.h                                                         */
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

#ifndef STRUCTURES_H
#define STRUCTURES_H

// Qt
#include <QtCore/QRect>
#include <QString>
#include <QPixmap>

//opencv
#include "opencv2/core/core.hpp"

struct ImageProcessingSettings{
    int smoothType;
    int smoothParam1;
    int smoothParam2;
    double smoothParam3;
    double smoothParam4;
    int dilateNumberOfIterations;
    int erodeNumberOfIterations;
    int flipCode;
    double cannyThreshold1;
    double cannyThreshold2;
    int cannyApertureSize;
    bool cannyL2gradient;
};

struct ImageProcessingFlags{
    bool grayscaleOn;
    bool smoothOn;
    bool dilateOn;
    bool erodeOn;
    bool flipOn;
    bool cannyOn;
};

struct MouseData{
    QRect selectionBox;
    bool leftButtonRelease;
    bool rightButtonRelease;
};

struct ThreadStatisticsData{
    int averageFPS;
    int nFramesProcessed;
};

//CHS

struct DefectStructToSave
{
    cv::Mat SdefectMat;
    QPixmap SpixMinature;
    QString SdefectMatNo;  // frame number of defect image
    QString SdistanceFromPreviousdefect; // the distance in frames from the previous image
    bool SwithinDefectFreeLength; // if the defect is within the defect free length as defined by its distance from the preveious defect this flag will go on.
    int SrawtimeS;
    int ScameraNumber;
    QString SfileName;
};

struct MachCamConfigFileXMLData
{
    QString NumberOfCameras = "";
    QString Mach_SerialNumber = "";
    QString Mach_YearOfManufacture = "";
    QString Mach_ModelNumber = "";
    QString CameraNumber = "";
    QString filePathName = "";
    int ManufacturerType = 0;
    QString SerialNumber = "";
    QString Model = "";
    QString CameraReferenceDistance_mm = "";
    QString FrameGrabberNumber = ""; // for Silicon Software Frame grabber
    QString FrameGrabberPortNumber = "";  // for Silicon Software Frame grabber
};

#endif // STRUCTURES_H
