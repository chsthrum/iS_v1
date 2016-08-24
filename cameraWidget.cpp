//qt includes
#include <QLayout>
#include <QDebug>
//local includes
#include "cameraWidget.h"

//CameraWidget::CameraWidget(QWidget *parent, int deviceNumber, SharedImageBuffer* sharedImageBuffer) : QWidget(parent), cameraNumber(deviceNumber), sharedImageBuffer(sharedImageBuffer)
CameraWidget::CameraWidget(QWidget *parent, int deviceNumber, SharedImageBuffer* sharedImageBuffer) : QWidget(parent), sharedImageBuffer(sharedImageBuffer)

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

    // Save Device Number
    this->cameraNumber=deviceNumber;
    // Initialize internal flag
    isCameraConnected=false;
    //connect to the camera
    bool isCam;
    //bool connectToCamera(bool dropFrame, int capThreadPrio, int procThreadPrio, bool createProcThread, int width, int height);
    isCam = connectToCamera(false,DEFAULT_CAP_THREAD_PRIO, DEFAULT_PROC_THREAD_PRIO, true, -1, -1);


}

CameraWidget::~CameraWidget()
{

}

bool CameraWidget::connectToCamera(bool dropFrameIfBufferFull, int capThreadPrio, int procThreadPrio, bool enableFrameProcessing, int width, int height)
{
    // Set frame label text
    //if(sharedImageBuffer->isSyncEnabledForDeviceNumber(deviceNumber))
    //    ui->frameLabel->setText("Camera connected. Waiting...");
    //else
    //    ui->frameLabel->setText("Connecting to camera...");

    // Create capture thread
    captureThread = new CaptureThread(sharedImageBuffer, cameraNumber, dropFrameIfBufferFull, width, height);
    // Attempt to connect to camera
    if(captureThread->connectToCamera())
    {
        // Create processing thread
        processingThread = new ProcessingThread(sharedImageBuffer, cameraNumber);
        // Create image processing settings dialog
        //imageProcessingSettingsDialog = new ImageProcessingSettingsDialog(this);
        // Setup signal/slot connections
        //connect(processingThread, SIGNAL(newFrame(QImage)), this, SLOT(updateFrame(QImage)));
        connect(captureThread, SIGNAL(newFrame(QImage)), this, SLOT(updateFrame(QImage)));
        //connect(processingThread, SIGNAL(updateStatisticsInGUI(struct ThreadStatisticsData)), this, SLOT(updateProcessingThreadStats(struct ThreadStatisticsData)));
        //connect(captureThread, SIGNAL(updateStatisticsInGUI(struct ThreadStatisticsData)), this, SLOT(updateCaptureThreadStats(struct ThreadStatisticsData)));
        //connect(imageProcessingSettingsDialog, SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)), processingThread, SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));
        //connect(this, SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)), processingThread, SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
        //connect(this, SIGNAL(setROI(QRect)), processingThread, SLOT(setROI(QRect)));
        // Only enable ROI setting/resetting if frame processing is enabled
        //if(enableFrameProcessing)
        //    connect(ui->frameLabel, SIGNAL(newMouseData(struct MouseData)), this, SLOT(newMouseData(struct MouseData)));
        // Set initial data in processing thread
        //emit setROI(QRect(0, 0, captureThread->getInputSourceWidth(), captureThread->getInputSourceHeight()));
        //emit newImageProcessingFlags(imageProcessingFlags);
        //imageProcessingSettingsDialog->updateStoredSettingsFromDialog();

        // Start capturing frames from camera
        captureThread->start((QThread::Priority)capThreadPrio);
        // Start processing captured frames (if enabled)
        if(enableFrameProcessing)
            processingThread->start((QThread::Priority)procThreadPrio);

        // Setup imageBufferBar with minimum and maximum values
       //ui->imageBufferBar->setMinimum(0);
        //ui->imageBufferBar->setMaximum(sharedImageBuffer->getByDeviceNumber(deviceNumber)->maxSize());
        // Enable "Clear Image Buffer" push button
        //ui->clearImageBufferButton->setEnabled(true);
        // Set text in labels
        //ui->deviceNumberLabel->setNum(deviceNumber);
        //ui->cameraResolutionLabel->setText(QString::number(captureThread->getInputSourceWidth())+QString("x")+QString::number(captureThread->getInputSourceHeight()));
        // Set internal flag and return
        isCameraConnected=true;
        // Set frame label text
        //if(!enableFrameProcessing)
         //   ui->frameLabel->setText("Frame processing disabled.");
        qDebug() << "Camera is connected";
    }
    // Failed to connect to camera
    else
        return false;

    return -1;

}

void CameraWidget::updateFrame(const QImage &frame)
{
    // Display frame
    //int x = frame.width();
    //qDebug() << "got this far " ;//<< this->cameraViewLabel->width();
    this->cameraViewLabel->setPixmap(QPixmap::fromImage(frame).scaled(this->cameraViewLabel->width(), this->cameraViewLabel->height(),Qt::KeepAspectRatio));

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
        //qDebug() << "from CameraWidget::addDefectCameraViewLabels, label size (Width * Height)   " << size;

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




