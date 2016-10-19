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
    void addCameraWidgetDefectLabels(QList<DefectLabel*>& p_Labels, QHBoxLayout* p_layOut,int numberOfImages);
    void addCameraWidgetDefectLabels(QList<DefectLabelsLayout*>& p_Labels, QHBoxLayout* p_layOut,int numberOfImages); // adds the defect display widgets
    QHBoxLayout* DefectLabelLayout(); // returns a layout pointer to the CameraWidget objects layout mechanism
    void setDefectLabels(int, QString);
    void setDefectImages(int, cv::Mat&);
    DefectStructToSave setDefectStruct(const DefectStructToSave &);
    void incrementDefectLabels(const DefectStructToSave &);
    int getDefectLabelWidth() const;
    int getDefectLabelHeight() const;




private:
    //QLabel *defectLabel;
    //QLabel *defectIndicator;
    //QLabel *defectFrameNumberLabel;
    long defectFrameNumber;
    //QLabel *defectClassLabel;
    //QLabel *productCodeLabel;
    //QLabel *dateTimeDefectLabel;
    QPushButton *defectStopmotion;
    QString filename;
    DefectStructToSave *ds;
    cv::Mat defectMat;
    long rawTimeSecs;
    QQueue<DefectStructToSave>normalDefectStructQueue;
    QQueue<DefectStructToSave>minatureDefectStructQueue;
    int queueLength;
    cv::FileStorage* storage; // for storing the defect file in xml.gz (zipped xml format)
    struct DefectStructToSave defectData;
    //QList <DefectLabel*> defectImageLabels;
    QList <DefectLabelsLayout*> defectLabels;
    QVBoxLayout *p_vLayOut;
    QHBoxLayout *p_layOut;

    int *previousDefectFrameNumber;








};

#endif // DEFECTIMAGESTORAGE_H
