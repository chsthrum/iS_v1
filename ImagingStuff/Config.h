/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* Config.h                                                             */
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

#ifndef CONFIG_H
#define CONFIG_H

// Camera Display instancies and labels
#define NUMBER_OF_CAMERAS                   1// when using in synced mode this number must match the number connected cameras
#define NUMBEROFDEFECTIMAGESTODISPLAY       5

//Defect free length  - 2 or more defects most not occurr within this distance (in frames)
#define DEFECT_FREE_LENGTH                  20

// Machine Reversing after defect stop in distance in Frames
#define REVERSE_LENGTH_N_FRAMES             13

//Offsets
//set the end position of set from the further most camera (ie. the first camera to encounter the defect)
#define OFFSET_CAMERA_0_TO_END_IN_FRAMES           100
//set the offset from camera0 to camera1
#define OFFSET_CAMERA_0_TO_CAMERA1_IN_FRAMES       20
//set the offset from camera0 to camera2
#define OFFSET_CAMERA_0_TO_CAMERA2_IN_FRAMES       40


// FPS statistics queue lengths
#define PROCESSING_FPS_STAT_QUEUE_LENGTH    32
#define CAPTURE_FPS_STAT_QUEUE_LENGTH       32

// Image buffer size
#define DEFAULT_IMAGE_BUFFER_SIZE           32

// Drop frame if image/frame buffer is full
#define DEFAULT_DROP_FRAMES                 false
// Thread priorities
#define DEFAULT_CAP_THREAD_PRIO             QThread::NormalPriority
#define DEFAULT_PROC_THREAD_PRIO            QThread::HighPriority

// IMAGE PROCESSING
// Smooth
#define DEFAULT_SMOOTH_TYPE                 0 // Options: [BLUR=0,GAUSSIAN=1,MEDIAN=2]
#define DEFAULT_SMOOTH_PARAM_1              3
#define DEFAULT_SMOOTH_PARAM_2              3
#define DEFAULT_SMOOTH_PARAM_3              0
#define DEFAULT_SMOOTH_PARAM_4              0
// Dilate
#define DEFAULT_DILATE_ITERATIONS           1
// Erode
#define DEFAULT_ERODE_ITERATIONS            1
// Flip
#define DEFAULT_FLIP_CODE                   0 // Options: [x-axis=0,y-axis=1,both axes=-1]
// Canny
#define DEFAULT_CANNY_THRESHOLD_1           10
#define DEFAULT_CANNY_THRESHOLD_2           00
#define DEFAULT_CANNY_APERTURE_SIZE         3
#define DEFAULT_CANNY_L2GRADIENT            false

#endif // CONFIG_H
