#ifndef WIDGET_H
#define WIDGET_H

//generates the entire view for all the cameras

//qt includes
#include <QWidget>
#include <QLayout>
#include <QScrollArea>
//local includes
#include "cameraWidget.h"
#include "pic2label.h"
#include "ImagingStuff/Buffer.h"
#include "ImagingStuff/SharedImageBuffer.h"
#include "csimpledefectmapLabel.h"




class CameraContainer : public QWidget
{
    Q_OBJECT

public:
    CameraContainer(QWidget *parent = 0);
    ~CameraContainer();
    void addCameras(QList<CameraWidget *> &p_CamWidgets, QVBoxLayout* p_layOut, SharedImageBuffer*, int nCameras);
    void addSimpleMapLabels(QList<CsimpleDefectMapLabel*>, QHBoxLayout* p_simple, int nLabels);


private:
    CameraWidget* cam;
    QList <CameraWidget*> cams; // for the different cameras
    QList <CsimpleDefectMapLabel*> list_simpledMapLabels; // the list of the simple defect map labels
    QVBoxLayout* camLayout;
    QHBoxLayout* logoLayout;
    QVBoxLayout* layout;
    QHBoxLayout* mapTopBannerLayout;
    QHBoxLayout* simpleDefectMapLayout;
    ScaledLabel* logoLabel;
    QMap<int, int> deviceNumberMap;
    SharedImageBuffer *sharedImageBuffer;

};

#endif // WIDGET_H
