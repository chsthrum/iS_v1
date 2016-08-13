#ifndef WIDGET_H
#define WIDGET_H
//qt includes
#include <QWidget>
#include <QLayout>
#include <QScrollArea>
//local includes
#include "CameraWidget.h"
#include "pic2label.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void addCameras(QList<CameraWidget *> &p_CamWidgets, QVBoxLayout* p_layOut, int limit);


private:
    CameraWidget* cam;
    QList <CameraWidget*> cams; // for the different cameras
    QVBoxLayout* camLayout;
    QHBoxLayout* logoLayout;
    QVBoxLayout* layout;
    ScaledLabel* logoLabel;

};

#endif // WIDGET_H
