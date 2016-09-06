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
//openCV
#include "opencv2/core/core.hpp"
//stl
#include <iostream>
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
    QHBoxLayout* getDefectLabelLayout();

private:
    //QLabel *defectLabel;
    QLabel *defectIndicator;
    QPushButton *defectStopmotion;
    QString filename;
    DefectStructToSave *ds;
    cv::Mat defectMat;
    long defectMatNumber;
    long rawTimeSecs;
    QQueue<DefectStructToSave>defectQueue;
    int queueLength;
    cv::FileStorage* storage; // for storing the defect file in xml.gz (zipped xml format)
    struct DefectStructToSave defectData;
    QList <DefectLabel*> labels;
    QHBoxLayout *p_layOut;


signals:

    void newDefectStruct(const DefectStructToSave &defectData);


};

#endif // DEFECTIMAGESTORAGE_H
