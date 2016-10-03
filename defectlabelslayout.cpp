#include "defectlabelslayout.h"


DefectLabelsLayout::DefectLabelsLayout(QWidget *parent): QWidget(parent)
{

    verticalBox = new QVBoxLayout;
    defectImageLabel = new DefectLabel;
    defectFrameNumber = new QLabel;
    framesFromPreviousDefectFrame = new QLabel;

    defectImageLabel->setFixedSize(80,60);
    defectImageLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    defectImageLabel->setText("No image");

    defectFrameNumber->setFrameStyle(QFrame::Box | QFrame::Raised);
    defectFrameNumber->setAlignment(Qt::AlignCenter);
    defectFrameNumber->setText("No Info");

    framesFromPreviousDefectFrame->setFrameStyle(QFrame::Box | QFrame::Raised);
    framesFromPreviousDefectFrame->setAlignment(Qt::AlignCenter);
    framesFromPreviousDefectFrame->setText("No Info");

    verticalBox->addWidget(defectImageLabel);
    verticalBox->addWidget(defectFrameNumber);
    verticalBox->addWidget(framesFromPreviousDefectFrame);

    setLayout(verticalBox);



}

DefectLabelsLayout::~DefectLabelsLayout()
{

}

void DefectLabelsLayout::setDefectFrameNumber(QString frameNo)
{
    defectFrameNumber->setText(frameNo);
}


void DefectLabelsLayout::setFramesFromPreviousDefectFrame(QString previousFrame)
{
    framesFromPreviousDefectFrame->setText(previousFrame);
}

void DefectLabelsLayout::setBackGroundColourOfLabel_framesFromPreviousDefectFrame(bool setBackgroundcolour)
{
    if(setBackgroundcolour)
        framesFromPreviousDefectFrame->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    else
        framesFromPreviousDefectFrame->setStyleSheet("QLabel { background-color : none; color : black; }");
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

