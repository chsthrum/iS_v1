#ifndef WIDGET_H
#define WIDGET_H
//qt includes
#include <QWidget>
#include <QLayout>
#include <QScrollArea>
//local includes
#include "cameraWidget.h"
#include "pic2label.h"
#include "ImagingStuff/Buffer.h"
#include "ImagingStuff/SharedImageBuffer.h"

const int NumberOfDevices = 100;

class CameraContainer : public QWidget
{
    Q_OBJECT

public:
    CameraContainer(QWidget *parent = 0);
    ~CameraContainer();
    void addCameras(QList<CameraWidget *> &p_CamWidgets, QVBoxLayout* p_layOut, SharedImageBuffer*, int limit);


private:
    CameraWidget* cam;
    QList <CameraWidget*> cams; // for the different cameras
    QVBoxLayout* camLayout;
    QHBoxLayout* logoLayout;
    QVBoxLayout* layout;
    ScaledLabel* logoLabel;

    QMap<int, int> deviceNumberMap;
    SharedImageBuffer *sharedImageBuffer;

};

#endif // WIDGET_H
