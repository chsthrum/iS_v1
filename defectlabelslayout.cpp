#include "defectlabelslayout.h"


DefectLabelsLayout::DefectLabelsLayout(QWidget *parent): QWidget(parent)
{

    verticalBox = new QVBoxLayout;
    defectImageLabel = new DefectLabel;
    defectFrameNumber = new QLabel;
    defectFramePositionInWeb = new QLabel;

    defectImageLabel->setFixedSize(80,60);
    defectImageLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    defectImageLabel->setText("No image");

    defectFrameNumber->setFrameStyle(QFrame::Box | QFrame::Raised);
    defectFrameNumber->setAlignment(Qt::AlignCenter);
    defectFrameNumber->setText("No Info");

    defectFramePositionInWeb->setFrameStyle(QFrame::Box | QFrame::Raised);
    defectFramePositionInWeb->setAlignment(Qt::AlignCenter);
    defectFramePositionInWeb->setText("No Info");

    verticalBox->addWidget(defectImageLabel);
    verticalBox->addWidget(defectFrameNumber);
    verticalBox->addWidget(defectFramePositionInWeb);

    setLayout(verticalBox);



}

DefectLabelsLayout::~DefectLabelsLayout()
{

}

void DefectLabelsLayout::setDefectFrameNumber(QString frameNo)
{
    defectFrameNumber->setText(frameNo);
}

void DefectLabelsLayout::setDefectImage(QPixmap& defPix)
{
    defectImageLabel->setPixmap(defPix);
}

void DefectLabelsLayout::setDefectPositionInWeb(QString)
{

}

int DefectLabelsLayout::getDefectLabelWidth() const
{
    return defectImageLabel->width();
}

int DefectLabelsLayout::getDefectLabelHeight() const
{
    return defectImageLabel->height();
}

