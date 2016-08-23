//qt includes
#include <QLayout>
#include <QDebug>
//local includes
#include "CameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent, int deviceNumber) : QWidget(parent), cameraNumber(deviceNumber)
{
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);

    cameraViewLabel = new QLabel;

    scoreLabel = new QLabel;
    scoreLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    scoreLabel->setFixedSize(1000,50);
    defectMapLongLabel = new QLabel;
    defectMapLongLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    defectMapShortLabel = new QLabel;
    defectMapShortLabel->setFrameStyle(QFrame::Box | QFrame::Raised);

    //indicator labels like old fashioned indicator lamps
    camNumberLabel = new QLabel;
    camNumberLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    camNumberLabel->setFixedSize(20,20);
    //camNumberLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    camNumberLabel->setText(QString::number(deviceNumber));
    camNumberLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    detectLabel = new QLabel;
    detectLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    detectLabel->setFixedSize(20,20);
    camStatusLabel = new QLabel;
    camStatusLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    camStatusLabel->setFixedSize(20,20);
    machStatusLabel = new QLabel;
    machStatusLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    machStatusLabel->setFixedSize(20,20);

    // Set up the camera view label
    cameraViewLabel->setMinimumSize(250,100);
    cameraViewLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    cameraViewLabel->setText("No camera connected.");
    cameraViewLabel->setAlignment(Qt::AlignCenter);


    QVBoxLayout* indicatorLampsLayout = new QVBoxLayout;
    QHBoxLayout* defectImagesLayoutBox = new QHBoxLayout;
    QHBoxLayout* cameraView = new QHBoxLayout;
    QVBoxLayout* chartsAndViews = new QVBoxLayout;
    QVBoxLayout* charts = new QVBoxLayout;

    setWindowTitle(tr("CameraView"));

    addDefectCameraViewLabels(labels, defectImagesLayoutBox, 8);

    indicatorLampsLayout->addWidget(detectLabel);
    indicatorLampsLayout->addWidget(machStatusLabel);
    indicatorLampsLayout->addWidget(camStatusLabel);
    indicatorLampsLayout->addWidget(camNumberLabel);

    charts->addWidget(defectMapLongLabel);
    charts->addWidget(defectMapShortLabel);
    charts->addWidget(scoreLabel);

    chartsAndViews->addLayout(defectImagesLayoutBox);
    chartsAndViews->addLayout(charts);

    cameraView->addWidget(cameraViewLabel);
    cameraView->addLayout(indicatorLampsLayout);
    cameraView->addLayout(chartsAndViews);


    setLayout(cameraView);

/*********************************************************************
 camera stuff
*********************************************************************/



}

CameraWidget::~CameraWidget()
{

}

// using a QList
void CameraWidget::addDefectCameraViewLabels(QList<DefectLabel*>& p_Labels, QHBoxLayout* p_layOut,int limit)
{
    for(int i = 0; i != limit ; ++i)
    {
        p_Labels.push_back(new DefectLabel);
        p_Labels[i]->setFixedSize(80,60);
        p_Labels[i]->setFrameStyle(QFrame::Box | QFrame::Raised);
        QSize size = p_Labels[i]->sizeHint();
        qDebug() << "from CameraWidget::addDefectCameraViewLabels, label size (Width * Height)   " << size;

        p_layOut->addWidget(p_Labels[i]);
    }
}

QSize CameraWidget::getSize()
{
    return labels[0]->size();
}

void CameraWidget::setText(QString text)
{
    labels[0]->setText(text);
}




