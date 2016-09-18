//opencv
#include "opencv2/imgproc/imgproc.hpp"

//qt
#include "QPixmap"

#include "defectimagestorage.h"
#include "defectlabelslayout.h"
#include "ImagingStuff/MatToQImage.h"

DefectImageStorage::DefectImageStorage(QWidget *parent, int numberOfImages) : QWidget(parent), queueLength(numberOfImages)
{
    p_layOut = new QHBoxLayout;
    //addDefectCameraViewLabels(defectImageLabels, p_layOut, numberOfImages);
    addCameraWidgetDefectLabels(defectLabels, p_layOut, numberOfImages);

    defectLabels[3]->setDefectFrameNumber("yippees");


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

