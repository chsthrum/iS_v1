#ifndef DEFECTIMAGESTORAGE_H
#define DEFECTIMAGESTORAGE_H

//QT
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QQueue>
//openCV
#include "opencv2/core/core.hpp"
//stl
#include <iostream>

struct DefectStructToSave
{
    cv::Mat defectMat;
    long defectMatNo;
    long rawtimeS;
    std::string fileName;
};



class DefectImageStorage : public QWidget
{
    Q_OBJECT

public:
    explicit DefectImageStorage(QWidget *parent, int numberOfImages);
    ~DefectImageStorage();

private:
    QLabel *defectLabel;
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





};

#endif // DEFECTIMAGESTORAGE_H
