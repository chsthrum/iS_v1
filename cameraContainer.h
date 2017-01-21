#ifndef WIDGET_H
#define WIDGET_H

//generates the entire view for all the cameras

//qt includes
#include <QWidget>
#include <QLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QVector>
#include <QList>
#include <QDebug>

//local includes
#include "cameraWidget.h"
#include "pic2label.h"
#include "ImagingStuff/Buffer.h"
#include "ImagingStuff/SharedImageBuffer.h"
#include "ImagingStuff/CaptureThread.h"
#include "ImagingStuff/ProcessingThread.h"
#include "csimpledefectmapLabel.h"



#include "ExternalHardwareSoftware/baslerpylondart_1.h"



class CameraContainer : public QWidget
{
    Q_OBJECT

public:
    //CameraContainer(QWidget *parent = 0);
    CameraContainer(QWidget *parent, QVector<MachCamConfigFileXMLData>& vecXMLData);
    ~CameraContainer();
    void addCameras(QList<CameraWidget*>& p_CamWidgets, QVBoxLayout* p_layOut, SharedImageBuffer*, QVector <MachCamConfigFileXMLData>);//, QVector< LocationStruct>);
    void addSimpleMapLabels(QList<CsimpleDefectMapLabel*>, QHBoxLayout* p_simple, int nLabels);
    SharedImageBuffer* getSharedImageBuffer() const;


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
    QPushButton* globalGrabButton;
    bool isGrabbing;
    bool allCameraWidgetsActive;

    QVector<LocationStruct> cameraLocations; //these TDalsa Specific Locations

    //CTlFactory& tlFactory;

private slots:

    void handleGrabButton();



};

#endif // WIDGET_H
