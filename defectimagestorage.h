#ifndef DEFECTIMAGESTORAGE_H
#define DEFECTIMAGESTORAGE_H

// responsible for handling the control, display and storage of defect image and defect data

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
#include "defectlabelslayout.h"




class DefectImageStorage : public QWidget
{
    Q_OBJECT

public:
    explicit DefectImageStorage(QWidget *parent, int numberOfImages);
    ~DefectImageStorage();
    void addDefectCameraViewLabels(QList<DefectLabel*>& p_Labels, QHBoxLayout* p_layOut,int numberOfImages);
    void addDefectCameraViewLabels(QList<DefectLabelsLayout*>& p_Labels, QHBoxLayout* p_layOut,int numberOfImages); // adds the defect display widgets
    QHBoxLayout* DefectLabelLayout(); // returns a layout pointer to the CameraWidget objects layout mechanism
    void setDefectLabels(int, QString);


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
    QList <DefectLabelsLayout*> defectLabels;
    QVBoxLayout *p_vLayOut;
    QHBoxLayout *p_layOut;





};

#endif // DEFECTIMAGESTORAGE_H
