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

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    //CameraWidget(QWidget *parent = 0, int deviceNumber = 0);
    CameraWidget(QWidget *parent, int deviceNumber);
    ~CameraWidget();

    //void addDefectCameraViewLabels(QVector<QLabel*>& p_Labels, QHBoxLayout* & p_layOut,int i);
    //void addDefectCameraViewLabels(QList<QLabel*>& p_Labels, QHBoxLayout* p_layOut,int i);
    void addDefectCameraViewLabels(QList<DefectLabel*>& p_Labels, QHBoxLayout* p_layOut,int i);

    QSize getSize(); // gets the size of the QLabel

    void setText(QString); // puts some text in a QLabel

protected:
    //void mousePressEvent(QMouseEvent *ev);

private:

    int cameraNumber;

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


};

#endif // CAMERAWIDGET_H
