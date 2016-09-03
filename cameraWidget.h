#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

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

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    //CameraWidget(QWidget *parent = 0, int deviceNumber = 0);
    //CameraWidget(QWidget *parent, int deviceNumber);
    explicit CameraWidget(QWidget *parent, int deviceNumber, int nDefectImages, SharedImageBuffer *sharedImageBuffer);
    ~CameraWidget();

    bool connectToCamera(bool dropFrame, int capThreadPrio, int procThreadPrio, bool createProcThread, int width, int height);

    //void addDefectCameraViewLabels(QVector<QLabel*>& p_Labels, QHBoxLayout* & p_layOut,int i);
    //void addDefectCameraViewLabels(QList<QLabel*>& p_Labels, QHBoxLayout* p_layOut,int i);
    void addDefectCameraViewLabels(QList<DefectLabel*>& p_Labels, QHBoxLayout* p_layOut,int i);

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
    QPushButton *stopMotionPB;


    QList <DefectLabel*> labels;
    void stopCaptureThread();
    void stopProcessingThread();

    int heightForWidth(const QImage&, int labelWidth );
    //int heightForWidth(int)const;

private slots:
    void updateFrame(const QImage &frame);
    void updateDefectStruct(const DefectStructToSave &);

signals:
    void setROI(QRect roi);


};

#endif // CAMERAWIDGET_H
