#include "defectimagestorage.h"
#include "defectlabelslayout.h"

DefectImageStorage::DefectImageStorage(QWidget *parent, int numberOfImages) : QWidget(parent), queueLength(numberOfImages)
{
    p_layOut = new QHBoxLayout;
    //addDefectCameraViewLabels(defectImageLabels, p_layOut, numberOfImages);
    addDefectCameraViewLabels(defectLabels, p_layOut, numberOfImages);

    defectLabels[3]->setDefectFrameNumber("yippees");


}

DefectImageStorage::~DefectImageStorage()
{

}

// for the defect labels only
void DefectImageStorage::addDefectCameraViewLabels(QList<DefectLabel*>& p_DefectImageLabels, QHBoxLayout* layOut,int numberOfImages)
{
    for(int i = 0; i != numberOfImages ; ++i)
    {
        //p_vLayOut = new QVBoxLayout;
        //defectFrameNumberLabel = new QLabel;
        p_DefectImageLabels.push_back(new DefectLabel());
        p_DefectImageLabels[i]->setFixedSize(80,60);
        p_DefectImageLabels[i]->setFrameStyle(QFrame::Box | QFrame::Raised);
        p_DefectImageLabels[i]->setText("No defect");


        //QSize size = p_Labels[i]->sizeHint();
        //qDebug() << "from CameraWidget::addDefectCameraViewLabels, label size (Width * Height)   " << size;

        layOut->addWidget(p_DefectImageLabels[i]);
    }
}

// for the DefectLabelsLayout
void DefectImageStorage::addDefectCameraViewLabels(QList<DefectLabelsLayout*>& p_DefectImageLabels, QHBoxLayout* layOut,int numberOfImages)
{
    for(int i = 0; i != numberOfImages ; ++i)
    {

        p_DefectImageLabels.push_back(new DefectLabelsLayout(this));
        //p_DefectImageLabels[i]->setText("No defect");


        //QSize size = p_Labels[i]->sizeHint();
        //qDebug() << "from CameraWidget::addDefectCameraViewLabels, label size (Width * Height)   " << size;

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
