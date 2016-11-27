//qt includes
#include <QLayout>
#include <QDebug>
//local includes
#include "cameraWidget.h"
#include "ImagingStuff/Structures.h"
#include "defectimagestorage.h"
#include "defectlabelslayout.h"


CameraWidget::CameraWidget(QWidget *parent, int deviceNumber, int nDefectImages, SharedImageBuffer* sharedImageBuffer) : QWidget(parent), sharedImageBuffer(sharedImageBuffer), numberOfDefectImages(nDefectImages)

{
    //pool = new QThreadPool; // does not seem to make any difference
    //Pointer to object to hold all the local defect images
    defectImages = new DefectImageStorage(this, nDefectImages);
    // Save Device Number
    this->deviceNumber=deviceNumber;
    // Initialize internal flag
    isCameraConnected=false;

    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);

    cameraViewLabel = new QLabel;

    stopMotionPB = new QPushButton;
    stopMotionPB->setFixedSize(100,20);
    stopMotionPB->setText("Stop Enabled");

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

    captureRateLabel = new QLabel;
    captureRateLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    captureRateLabel->setFixedSize(100,20);

    nFramesCapturedLabel = new QLabel;
    nFramesCapturedLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nFramesCapturedLabel->setFixedSize(100,20);

    processingRateLabel = new QLabel;
    processingRateLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    processingRateLabel->setFixedSize(100,20);

    nFramesProcessedLabel = new QLabel;
    nFramesProcessedLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nFramesProcessedLabel->setFixedSize(100,20);

    imageBufferLabel = new QLabel;
    imageBufferLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    imageBufferLabel->setFixedSize(100,20);

    // Set up the camera view label
    cameraViewLabel->setMinimumSize(250,250);
    /* do not set the height less than the size it can expand to, else the image will be cropped.
    The reason is that each cameraViewLabel maximum size is basically determined by the CameraContainer layout. */
    cameraViewLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    cameraViewLabel->setText("No camera connected.");
    cameraViewLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* labelsAndLamps = new QVBoxLayout;
    QVBoxLayout* labelsAndButtonsLayout = new QVBoxLayout;
    QHBoxLayout* indicatorLamps = new QHBoxLayout;
    // Set up the layout of the defect images
    QHBoxLayout* defectImagesLayoutBox = defectImages->DefectLabelLayout();
    QHBoxLayout* cameraView = new QHBoxLayout;
    QVBoxLayout* chartsAndViews = new QVBoxLayout;
    QVBoxLayout* charts = new QVBoxLayout;

    setWindowTitle(tr("CameraView"));

    labelsAndButtonsLayout->addWidget(stopMotionPB);

    labelsAndButtonsLayout->addWidget(captureRateLabel);
    labelsAndButtonsLayout->addWidget(nFramesCapturedLabel);
    labelsAndButtonsLayout->addWidget(processingRateLabel);
    labelsAndButtonsLayout->addWidget(nFramesProcessedLabel);
    labelsAndButtonsLayout->addWidget(imageBufferLabel);

    indicatorLamps->addWidget(detectLabel);
    indicatorLamps->addWidget(machStatusLabel);
    indicatorLamps->addWidget(camStatusLabel);
    indicatorLamps->addWidget(camNumberLabel);

    labelsAndLamps->addLayout(indicatorLamps);
    labelsAndLamps->addLayout(labelsAndButtonsLayout);


    charts->addWidget(defectMapLongLabel);
    charts->addWidget(defectMapShortLabel);
    charts->addWidget(scoreLabel);

    chartsAndViews->addLayout(defectImagesLayoutBox);
    chartsAndViews->addLayout(charts);

    cameraView->addWidget(cameraViewLabel);
    cameraView->addLayout(labelsAndLamps);
    cameraView->addLayout(chartsAndViews);


    setLayout(cameraView);

    // Register type
    qRegisterMetaType<struct ThreadStatisticsData>("ThreadStatisticsData");
    qRegisterMetaType<struct DefectStructToSave>("DefectStructToSave");

/*********************************************************************
 camera stuff........
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
        {
            qDebug() << "[" << deviceNumber << "] Camera successfully disconnected.";
            delete captureThread;
            captureThread = NULL;
            delete processingThread;
            processingThread = NULL;

        }
        else
            qDebug() << "[" << deviceNumber << "] WARNING: Camera already disconnected.";
    }

}

bool CameraWidget::connectToCamera(bool dropFrameIfBufferFull, int capThreadPrio, int procThreadPrio, bool enableFrameProcessing, int width, int height)
{
    // Set frame label text
    if(sharedImageBuffer->isSyncEnabledForDeviceNumber(deviceNumber))
        this->cameraViewLabel->setText("Camera connected. Waiting...");
    else
        this->cameraViewLabel->setText("Connecting to camera...");

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
        connect(processingThread, SIGNAL(updateDefectStruct(struct DefectStructToSave)), this, SLOT(diceTest_withCvmat (struct DefectStructToSave)));
        connect(processingThread, SIGNAL(updateStatisticsInGUI(struct ThreadStatisticsData)), this, SLOT(updateProcessingThreadStats(struct ThreadStatisticsData)));
        connect(captureThread, SIGNAL(updateStatisticsInGUI(struct ThreadStatisticsData)), this, SLOT(updateCaptureThreadStats(struct ThreadStatisticsData)));

        connect(processingThread, SIGNAL(dice_is_6(QString)), this, SLOT (diceTest_withString(QString)));//defectLabels

        //connect(imageProcessingSettingsDialog, SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)), processingThread, SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));
        //connect(this, SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)), processingThread, SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
        connect(this, SIGNAL(setROI(QRect)), processingThread, SLOT(setROI(QRect)));
        // Only enable ROI setting/resetting if frame processing is enabled
        //if(enableFrameProcessing)
        //    connect(ui->frameLabel, SIGNAL(nDefectImageStorage::ewMouseData(struct MouseData)), this, SLOT(newMouseData(struct MouseData)));
        // Set initial data in processing thread
        emit setROI(QRect(0, 0, captureThread->getInputSourceWidth(), captureThread->getInputSourceHeight()));
        //emit newImageProcessingFlags(imageProcessingFlags);
        //imageProcessingSettingsDialog->updateStoredSettingsFromDialog();

        // Start capturing frames from camera
        captureThread->start((QThread::Priority)capThreadPrio); //TODO GRAB BUTTON CONTROLS THIS POINT
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
        setCameraStatusLabel();
        return true;
    }
    // Failed to connect to camera
    else
        return false;


}
void CameraWidget::updateCaptureThreadStats(struct ThreadStatisticsData statData)
{
    // Show [number of images in buffer / image buffer size] in imageBufferLabel
    imageBufferLabel->setText(QString("[")+QString::number(sharedImageBuffer->getByDeviceNumber(deviceNumber)->size())+
                                  QString("/")+QString::number(sharedImageBuffer->getByDeviceNumber(deviceNumber)->maxSize())+QString("]"));
    // Show percentage of image bufffer full in imageBufferBar
    //ui->imageBufferBar->setValue(sharedImageBuffer->getByDeviceNumber(deviceNumber)->size());

    // Show processing rate in captureRateLabel
    captureRateLabel->setText(QString::number(statData.averageFPS)+" fps");
    // Show number of frames captured in nFramesCapturedLabel
    nFramesCapturedLabel->setText(QString("[") + QString::number(statData.nFramesProcessed) + QString("]  frames"));
}

void CameraWidget::diceTest_withString(QString message) const
{
   defectImages->setDefectLabels(3, message);

}


void CameraWidget::diceTest_withCvmat(DefectStructToSave dsts)
{
    //run this function in a separate thread

    QFuture<DefectStructToSave> f1 = QtConcurrent::run(this->defectImages, &DefectImageStorage::setDefectStruct, dsts);
    DefectStructToSave result = f1.result();
    //f1.waitForFinished();
    defectImages->incrementDefectLabels(result);
    /*"Hello from thread QThread(0x14ab590, name = "Thread (pooled)")" is output from the debug statemnt in setDefectStruct
    when two of the objects have invoked this function at the same time. ie. the run function of 1 object has not returned before it
    needs to be called again by the second object.
    If however "Hello from thread QThread(0x13d5320)" is output then the run function is returning in good time and the same thread
    can be used again.*/

    //defectImages->setDefectStruct(dsts); // this works but only in the main thread
    ;

}
void CameraWidget::updateProcessingThreadStats(struct ThreadStatisticsData statData)
{
    // Show processing rate in processingRateLabel
    processingRateLabel->setText(QString::number(statData.averageFPS)+" fps");
    // Show ROI information in roiLabel
//    roiLabel->setText(QString("(")+QString::number(processingThread->getCurrentROI().x())+QString(",")+
//                          QString::number(processingThread->getCurrentROI().y())+QString(") ")+
//                          QString::number(processingThread->getCurrentROI().width())+
//                          QString("x")+QString::number(processingThread->getCurrentROI().height()));
    // Show number of frames processed in nFramesProcessedLabel
    nFramesProcessedLabel->setText(QString("[") + QString::number(statData.nFramesProcessed) + QString("]  frames"));
}

void CameraWidget::updateFrame(const QImage &frame)
{
    //set the size of the label holding the image to the scaled image. NOTE THIS FUNCTION MIGHT PROVE TOO EXPENSIVE
    cameraViewLabel->setFixedSize(cameraViewLabel->width(), heightForWidth(frame, cameraViewLabel->width()));
    //qDebug() << cameraViewLabel->size();
    this->cameraViewLabel->setPixmap(QPixmap::fromImage(frame).scaled(this->cameraViewLabel->width(), this->cameraViewLabel->height(),Qt::KeepAspectRatio));
    //TEST//this->labels[3]->setPixmap(QPixmap::fromImage(frame).scaled(this->cameraViewLabel->width(), this->cameraViewLabel->height(),Qt::KeepAspectRatio));
    //TEST//this->camStatusLabel->setStyleSheet("QLabel { background-color : green; color : blue; }");
}

bool CameraWidget::setCameraStatusLabel()
{
    if(isCameraConnected)
    {
        camStatusLabel->setStyleSheet("QLabel { background-color : green; color : blue; }");
        return true;
    }
    else
        return false;
}

void CameraWidget::setNumberOfDefectImages(int n)
{
    numberOfDefectImages = n;

}

int CameraWidget::getNumberOfDefectImages() const
{
    return numberOfDefectImages;

}

void CameraWidget::setGrab(bool sG)
{
    captureThread->setGrab(sG);
    processingThread->setGrab(sG);
}

void CameraWidget::stopCaptureThread()
{
    qDebug() << "[" << deviceNumber << "] About to stop capture thread...";
    captureThread->stop();
    sharedImageBuffer->wakeAll(); // This allows the thread to be stopped even if it is in a wait-state
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
    sharedImageBuffer->wakeAll(); // This allows the thread to be stopped even if it is in a wait-state
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


