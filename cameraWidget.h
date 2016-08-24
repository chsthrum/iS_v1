#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

//qt includes
#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QList>
#include <QLayout>
#include <QMouseEvent>
//local includes
#include "defectLabel.h"
#include "ImagingStuff/SharedImageBuffer.h"
#include "ImagingStuff/CaptureThread.h"
#include "ImagingStuff/ProcessingThread.h"
#include "ImagingStuff/Config.h"

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    //CameraWidget(QWidget *parent = 0, int deviceNumber = 0);
    //CameraWidget(QWidget *parent, int deviceNumber);
    explicit CameraWidget(QWidget *parent, int deviceNumber, SharedImageBuffer *sharedImageBuffer);
    ~CameraWidget();
    bool connectToCamera(bool dropFrame, int capThreadPrio, int procThreadPrio, bool createProcThread, int width, int height);

    //void addDefectCameraViewLabels(QVector<QLabel*>& p_Labels, QHBoxLayout* & p_layOut,int i);
    //void addDefectCameraViewLabels(QList<QLabel*>& p_Labels, QHBoxLayout* p_layOut,int i);
    void addDefectCameraViewLabels(QList<DefectLabel*>& p_Labels, QHBoxLayout* p_layOut,int i);

    QSize getSize(); // gets the size of the QLabel

    void setText(QString); // puts some text in a QLabel

protected:
    //void mousePressEvent(QMouseEvent *ev);

private:

    SharedImageBuffer *sharedImageBuffer;
    int cameraNumber;
    bool isCameraConnected;

    ProcessingThread *processingThread;
    CaptureThread *captureThread;

    QLabel *cameraViewLabel;
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


    QList <DefectLabel*> labels;

private slots:
    void updateFrame(const QImage &frame);


};

#endif // CAMERAWIDGET_H
