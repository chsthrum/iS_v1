//opencv
#include "opencv2/imgproc/imgproc.hpp"

//qt
#include <QPixmap>
#include <QThread>
#include <QString>

#include "defectimagestorage.h"
#include "defectlabelslayout.h"
#include "ImagingStuff/MatToQImage.h"



DefectImageStorage::DefectImageStorage(QWidget *parent, int numberOfImages) : QWidget(parent), queueLength(numberOfImages)
{
    p_layOut = new QHBoxLayout;
    previousDefectFrameNumber = new int(0);
    //addDefectCameraViewLabels(defectImageLabels, p_layOut, numberOfImages);
    addCameraWidgetDefectLabels(defectLabels, p_layOut, queueLength);
    defectLabels[3]->setDefectFrameNumber("yippees");

    //clear the queues
    normalDefectStructQueue.clear();
    minatureDefectStructQueue.clear();




}

DefectImageStorage::~DefectImageStorage()
{

}

// for the defect labels only
void DefectImageStorage::addCameraWidgetDefectLabels(QList<DefectLabel*>& p_DefectImageLabels, QHBoxLayout* layOut,int numberOfImages)
{
    for(int i = 0; i != numberOfImages ; ++i)
    {
        p_DefectImageLabels.push_back(new DefectLabel());
        p_DefectImageLabels[i]->setFixedSize(80,60);
        p_DefectImageLabels[i]->setFrameStyle(QFrame::Box | QFrame::Raised);
        p_DefectImageLabels[i]->setText("No defect");

        layOut->addWidget(p_DefectImageLabels[i]);
    }
}

// for the DefectLabelsLayout
void DefectImageStorage::addCameraWidgetDefectLabels(QList<DefectLabelsLayout*>& p_DefectImageLabels, QHBoxLayout* layOut,int numberOfImages)
{
    for(int i = 0; i != numberOfImages ; ++i)
    {
        p_DefectImageLabels.push_back(new DefectLabelsLayout(this));
        layOut->addWidget(p_DefectImageLabels[i]);
    }
}

// return the pointer to the layout holding the list of defect image labels
QHBoxLayout *DefectImageStorage::DefectLabelLayout()
{
    return p_layOut;

}

void DefectImageStorage::setDefectLabels(int i, QString s)
{
    defectLabels[i]->setDefectFrameNumber(s);
}

void DefectImageStorage::setDefectStruct(DefectStructToSave& ds)
{

    //resize the image but retain the original - put these into two different containers
    cv::Mat temp;
    QImage qI;
    cv::Size size(getDefectLabelWidth(), getDefectLabelHeight());
    // C++: void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR )
    cv::resize(ds.SdefectMat, temp, size, 0, 0, cv::INTER_LINEAR);
    //QImage MatToQImage(const Mat& mat)
    qI = MatToQImage(temp);

    DefectStructToSave minature_Im;
    minature_Im.SpixMinature = QPixmap::fromImage(qI);
    minature_Im.SdefectMat.data = 0;
    minature_Im.SdefectMatNo = ds.SdefectMatNo;
    minature_Im.SrawtimeS = ds.SrawtimeS;

    DefectStructToSave normal_Im;
    normal_Im.SpixMinature.isNull();
    normal_Im.SdefectMat = ds.SdefectMat; // retain the original
    normal_Im.SdefectMatNo = ds.SdefectMatNo;
    normal_Im.SrawtimeS = ds.SrawtimeS;

    //get the distance in frames from the previous defect frame

    minature_Im.SdistanceFromPreviousdefect = QString::number((minature_Im.SdefectMatNo.toInt()) - *previousDefectFrameNumber);
    *previousDefectFrameNumber = minature_Im.SdefectMatNo.toInt();


    //Add images to the queue, when the queue is full remove the last image from the end before adding another to the front.

    if ((minatureDefectStructQueue.size() < queueLength) && (normalDefectStructQueue.size() < queueLength))
    {
        minatureDefectStructQueue.prepend(minature_Im);
        normalDefectStructQueue.prepend(normal_Im);
    }

    else if ((minatureDefectStructQueue.size() == queueLength) && (normalDefectStructQueue.size() == queueLength) &&
             (!minatureDefectStructQueue.isEmpty()) && (!normalDefectStructQueue.isEmpty()))
    {
        minatureDefectStructQueue.pop_back();
        normalDefectStructQueue.pop_back();
        minatureDefectStructQueue.prepend(minature_Im);
        normalDefectStructQueue.prepend(normal_Im);

    }


    //load images into the defect labels
    QQueue<DefectStructToSave>::const_iterator minIter = minatureDefectStructQueue.constBegin();
    //int j = 0;
    int j = defectLabels.size()-1; // from end to beginning


    while (minIter != minatureDefectStructQueue.constEnd())
    {
        DefectStructToSave tempStruct;
        tempStruct = *minIter;
        defectLabels[j]->setDefectImage(tempStruct.SpixMinature);
        defectLabels[j]->setDefectFrameNumber(tempStruct.SdefectMatNo);
        defectLabels[j]->setFramesFromPreviousDefectFrame(tempStruct.SdistanceFromPreviousdefect);
        minIter++;
        //j++;
        j--; // from end to beginning
    }
    qDebug() << "Hello from thread" << QThread::currentThread();

}

void DefectImageStorage::setDefectImages(int i, cv::Mat& im)
{
    cv::Mat temp;
    QImage qI;
    cv::Size size(getDefectLabelWidth(), getDefectLabelHeight());
    // C++: void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR )
    cv::resize(im, temp, size, 0, 0, cv::INTER_LINEAR);
    //QImage MatToQImage(const Mat& mat)
    qI = MatToQImage(temp);
    QPixmap pix = QPixmap::fromImage(qI);
    defectLabels[i]->setDefectImage(pix);
}

int DefectImageStorage::getDefectLabelWidth() const
{
    return defectLabels[0]->getDefectLabelWidth();
}

int DefectImageStorage::getDefectLabelHeight() const
{
    return defectLabels[0]->getDefectLabelHeight();
}

