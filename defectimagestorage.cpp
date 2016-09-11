#include "defectimagestorage.h"

DefectImageStorage::DefectImageStorage(QWidget *parent, int numberOfImages) : QWidget(parent), queueLength(numberOfImages)
{
    p_layOut = new QHBoxLayout;
    addDefectCameraViewLabels(defectImageLabels, p_layOut, numberOfImages);

}

DefectImageStorage::~DefectImageStorage()
{

}

// using a QList
void DefectImageStorage::addDefectCameraViewLabels(QList<DefectLabel*>& p_DefectImageLabels, QHBoxLayout* layOut,int numberOfImages)
{
    for(int i = 0; i != numberOfImages ; ++i)
    {
        p_DefectImageLabels.push_back(new DefectLabel());
        p_DefectImageLabels[i]->setFixedSize(80,60);
        p_DefectImageLabels[i]->setFrameStyle(QFrame::Box | QFrame::Raised);
        //p_Labels[i]->setWordWrap(true);
        p_DefectImageLabels[i]->setText("No Defect");
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
