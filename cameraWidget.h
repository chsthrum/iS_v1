#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

//generates the view for each camera

//qt includes
#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QList>
#include <QLayout>
#include <QPushButton>
#include <QMouseEvent>
//local includes
#include "defectLabel.h"
#include "ImagingStuff/SharedImageBuffer.h"
#include "ImagingStuff/CaptureThread.h"
#include "ImagingStuff/ProcessingThread.h"
#include "ImagingStuff/Config.h"
#include "pic2label.h"
#include "ImagingStuff/Structures.h"
#include "defectimagestorage.h"

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    //CameraWidget(QWidget *parent = 0, int deviceNumber = 0);
    //CameraWidget(QWidget *parent, int deviceNumber);
    explicit CameraWidget(QWidget *parent, int deviceNumber, int nDefectImages, SharedImageBuffer *sharedImageBuffer);
    ~CameraWidget();

    bool connectToCamera(bool dropFrame, int capThreadPrio, int procThreadPrio, bool createProcThread, int width, int height);


    //set the camera status indicator label
    bool setCameraStatusLabel();
    //number of displayed defect images
   void setNumberOfDefectImages(int);
   int getNumberOfDefectImages() const;





    QSize getSize(); // gets the size of the QLabel

    void setText(QString); // puts some text in a QLabel

protected:
    //void mousePressEvent(QMouseEvent *ev);

private:

    DefectImageStorage *defectImages;
    SharedImageBuffer *sharedImageBuffer;
    int deviceNumber;
    bool isCameraConnected;
    int numberOfDefectImages;

    ProcessingThread *processingThread;
    CaptureThread *captureThread;

    //ScaledLabel *cameraViewLabel;
    QLabel* cameraViewLabel;
    //DefectLabel *cameraViewLabel;
    QLabel *scoreLabel;
    //QLabel *defectLabel;
    DefectLabel *defectLabel;
    QLabel *defectMapLongLabel;
    QLabel *defectMapShortLabel;
    QLabel *camNumberLabel;
    QLabel *machStatusLabel;
    QLabel *camStatusLabel;
    QLabel *detectLabel;
    QLabel* imageBufferLabel;
    QLabel *captureRateLabel;
    QLabel *nFramesCapturedLabel;
    QLabel *processingRateLabel;
    QLabel *nFramesProcessedLabel;
    QPushButton *stopMotionPB;



    QList <DefectLabel*> labels;
    void stopCaptureThread();
    void stopProcessingThread();

    int heightForWidth(const QImage&, int labelWidth );
    //int heightForWidth(int)const;

private slots:
    void updateFrame(const QImage &frame);
    void updateDefectStruct(const DefectStructToSave &);
    void updateProcessingThreadStats(struct ThreadStatisticsData statData);
    void updateCaptureThreadStats(struct ThreadStatisticsData statData);
    void diceTest_withString(QString) const;
    void diceTest_withCvmat (struct DefectStructToSave);
signals:
    void setROI(QRect roi);


};

#endif // CAMERAWIDGET_H
