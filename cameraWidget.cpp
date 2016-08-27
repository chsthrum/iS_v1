//qt includes
#include <QLayout>
#include <QDebug>
//local includes
#include "cameraWidget.h"

//CameraWidget::CameraWidget(QWidget *parent, int deviceNumber, SharedImageBuffer* sharedImageBuffer) : QWidget(parent), cameraNumber(deviceNumber), sharedImageBuffer(sharedImageBuffer)
CameraWidget::CameraWidget(QWidget *parent, int deviceNumber, SharedImageBuffer* sharedImageBuffer) : QWidget(parent), sharedImageBuffer(sharedImageBuffer)

{

    // Save Device Number
    this->deviceNumber=deviceNumber;
    // Initialize internal flag
    isCameraConnected=false;

    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);

    //cameraViewLabel = new ScaledLabel;
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
    cameraViewLabel->setMinimumSize(250,250);
    /* do not set the height less than the size it can expand to, else the image will be cropped.
    The reason is that each cameraViewLabel maximum size is basically determined by the CamaeraContainer layout. */
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
    if(isCameraConnected)
    {
        // Stop processing thread
        if(processingThread->isRunning())
            stopProcessingThread();
        // Stop capture thread
        if(captureThread->isRunning())
            stopCaptureThread();

        // Automatically start frame processing (for other streams)
        if(sharedImageBuffer->isSyncEnabledForDeviceNumber(deviceNumber))
            sharedImageBuffer->setSyncEnabled(true);

        // Remove from shared buffer
        sharedImageBuffer->removeByDeviceNumber(deviceNumber);
        // Disconnect camera
        if(captureThread->disconnectCamera())
            qDebug() << "[" << deviceNumber << "] Camera successfully disconnected.";
        else
            qDebug() << "[" << deviceNumber << "] WARNING: Camera already disconnected.";
    }
    // Delete UI
   // delete ui;

}

bool CameraWidget::connectToCamera(bool dropFrameIfBufferFull, int capThreadPrio, int procThreadPrio, bool enableFrameProcessing, int width, int height)
{
    // Set frame label text
    //if(sharedImageBuffer->isSyncEnabledForDeviceNumber(deviceNumber))
    //    ui->frameLabel->setText("Camera connected. Waiting...");
    //else
    //    ui->frameLabel->setText("Connecting to camera...");

    // Create capture thread
    captureThread = new CaptureThread(sharedImageBuffer, deviceNumber, dropFrameIfBufferFull, width, height);
    // Attempt to connect to camera
    if(captureThread->connectToCamera())
    {
        // Create processing thread
        processingThread = new ProcessingThread(sharedImageBuffer, deviceNumber);
        // Create image processing settings dialog
        //imageProcessingSettingsDialog = new ImageProcessingSettingsDialog(this);
        // Setup signal/slot connections
        connect(processingThread, SIGNAL(newFrame(QImage)), this, SLOT(updateFrame(QImage)));
        //connect(captureThread, SIGNAL(newFrame(QImage)), this, SLOT(updateFrame(QImage)));
        //connect(processingThread, SIGNAL(updateStatisticsInGUI(struct ThreadStatisticsData)), this, SLOT(updateProcessingThreadStats(struct ThreadStatisticsData)));
        //connect(captureThread, SIGNAL(updateStatisticsInGUI(struct ThreadStatisticsData)), this, SLOT(updateCaptureThreadStats(struct ThreadStatisticsData)));
        //connect(imageProcessingSettingsDialog, SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)), processingThread, SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));
        //connect(this, SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)), processingThread, SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
        connect(this, SIGNAL(setROI(QRect)), processingThread, SLOT(setROI(QRect)));
        // Only enable ROI setting/resetting if frame processing is enabled
        //if(enableFrameProcessing)
        //    connect(ui->frameLabel, SIGNAL(newMouseData(struct MouseData)), this, SLOT(newMouseData(struct MouseData)));
        // Set initial data in processing thread
        emit setROI(QRect(0, 0, captureThread->getInputSourceWidth(), captureThread->getInputSourceHeight()));
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
    //set the size of the label holding the image to the scaled image. NOTE THIS FUNCTION MIGHT PROVE TOO EXPENSIVE
    cameraViewLabel->setFixedSize(cameraViewLabel->width(), heightForWidth(frame, cameraViewLabel->width()));
    qDebug() << cameraViewLabel->size();
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

void CameraWidget::stopCaptureThread()
{
    qDebug() << "[" << deviceNumber << "] About to stop capture thread...";
    captureThread->stop();
    sharedImageBuffer->wakeAll(); // This allows the thread to be stopped if it is in a wait-state
    // Take one frame off a FULL queue to allow the capture thread to finish
    if(sharedImageBuffer->getByDeviceNumber(deviceNumber)->isFull())
        sharedImageBuffer->getByDeviceNumber(deviceNumber)->get();
    captureThread->wait();
    qDebug() << "[" << deviceNumber << "] Capture thread successfully stopped.";
}

void CameraWidget::stopProcessingThread()
{
    qDebug() << "[" << deviceNumber << "] About to stop processing thread...";
    processingThread->stop();
    sharedImageBuffer->wakeAll(); // This allows the thread to be stopped if it is in a wait-state
    processingThread->wait();
    qDebug() << "[" << deviceNumber << "] Processing thread successfully stopped.";
}

QSize CameraWidget::getSize()
{
    return labels[0]->size();
}

void CameraWidget::setText(QString text)
{
    labels[0]->setText(text);
}


int CameraWidget::heightForWidth(const QImage&  pix, int labelWidth)      //width comes from the resize instruction width component
{
    return pix.isNull() ? this->height() : ((qreal)pix.height()*labelWidth)/pix.width();
}

//int CameraWidget::heightForWidth(int labelWidth)const
//{
//    return pix.isNull() ? this->height() : ((qreal)pix.height()*labelWidth)/pix.width();
//}


