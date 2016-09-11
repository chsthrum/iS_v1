#ifndef DEFECTIMAGESTORAGE_H
#define DEFECTIMAGESTORAGE_H

//QT
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QQueue>
#include <QLayout>
#include <QTime> //for milliseconds
//openCV
#include "opencv2/core/core.hpp"
//stl
#include <iostream>
#include <ctime> //for seconds
//local
#include "ImagingStuff/Structures.h"
#include "defectLabel.h"




class DefectImageStorage : public QWidget
{
    Q_OBJECT

public:
    explicit DefectImageStorage(QWidget *parent, int numberOfImages);
    ~DefectImageStorage();
    void addDefectCameraViewLabels(QList<DefectLabel*>& p_Labels, QHBoxLayout* p_layOut,int numberOfImages);
    QHBoxLayout* DefectLabelLayout();

private:
    //QLabel *defectLabel;
    QLabel *defectIndicator;
    QLabel *defectFrameNumberLabel;
    long defectFrameNumber;
    //QLabel *defectClassLabel;
    //QLabel *productCodeLabel;
    //QLabel *dateTimeDefectLabel;
    QPushButton *defectStopmotion;
    QString filename;
    DefectStructToSave *ds;
    cv::Mat defectMat;
    long rawTimeSecs;
    QQueue<DefectStructToSave>defectQueue;
    int queueLength;
    cv::FileStorage* storage; // for storing the defect file in xml.gz (zipped xml format)
    struct DefectStructToSave defectData;
    QList <DefectLabel*> defectImageLabels;
    QHBoxLayout *p_layOut;





};

#endif // DEFECTIMAGESTORAGE_H
