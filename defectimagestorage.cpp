#include "defectimagestorage.h"

DefectImageStorage::DefectImageStorage(QWidget *parent, int numberOfImages) : QWidget(parent), queueLength(numberOfImages)
{
    p_layOut = new QHBoxLayout;
    addDefectCameraViewLabels(labels, p_layOut, numberOfImages);

}

DefectImageStorage::~DefectImageStorage()
{

}

// using a QList
void DefectImageStorage::addDefectCameraViewLabels(QList<DefectLabel*>& p_Labels, QHBoxLayout* layOut,int numberOfImages)
{
    for(int i = 0; i != numberOfImages ; ++i)
    {
        p_Labels.push_back(new DefectLabel);
        p_Labels[i]->setFixedSize(80,60);
        p_Labels[i]->setFrameStyle(QFrame::Box | QFrame::Raised);
        QSize size = p_Labels[i]->sizeHint();
        //qDebug() << "from CameraWidget::addDefectCameraViewLabels, label size (Width * Height)   " << size;

        layOut->addWidget(p_Labels[i]);
    }
}

// return the pointer to the layout holding the list of defect image labels
QHBoxLayout *DefectImageStorage::getDefectLabelLayout()
{
    return p_layOut;
}
