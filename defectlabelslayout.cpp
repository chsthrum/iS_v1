#include "defectlabelslayout.h"

DefectLabelsLayout::DefectLabelsLayout(QWidget *parent): QWidget(parent)
{

    verticalBox = new QVBoxLayout;
    defectImageLabel = new DefectLabel;
    defectFrameNumberandLength = new QLabel;

    defectImageLabel->setFixedSize(80,60);
    defectImageLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    defectImageLabel->setText("No image");

    defectFrameNumberandLength->setFrameStyle(QFrame::Box | QFrame::Raised);
    defectFrameNumberandLength->setAlignment(Qt::AlignCenter);
    defectFrameNumberandLength->setText("No Info");

    verticalBox->addWidget(defectImageLabel);
    verticalBox->addWidget(defectFrameNumberandLength);

    setLayout(verticalBox);



}

DefectLabelsLayout::~DefectLabelsLayout()
{

}

void DefectLabelsLayout::setDefectFrameNumber(QString frameNo)
{
    defectFrameNumberandLength->setText(frameNo);

}

