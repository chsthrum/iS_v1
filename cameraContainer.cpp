//qt includes
#include <QDebug>
//local includes
#include "cameraContainer.h"
#include"ImagingStuff/Config.h"




CameraContainer::CameraContainer(QWidget *parent)
    : QWidget(parent)
{

    // Create SharedImageBuffer object
    sharedImageBuffer = new SharedImageBuffer();

    //load the logo and check that it has loaded
    QPixmap p("../images/fsSVG.png");
    if (p.isNull())
       qDebug() << "No image loaded";

    // Create a label and place it in the widget
    logoLabel = new ScaledLabel(this);

    /* Sets the intial size of the label width, that will be used in sizeHint() to set the height of the
    label to suit the images aspect ratio.*/
    logoLabel->setFixedSize(200,200);
    logoLabel->setPix(p);

    //Sets the label size to suit the images aspect ratio.
    logoLabel->setFixedSize(logoLabel->sizeHint());
    // put the pixMap into the resized label
    logoLabel->setPixmap(logoLabel->scaledPixmap());



    //setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);

    camLayout = new QVBoxLayout;
    logoLayout = new QHBoxLayout;
    layout = new QVBoxLayout;
    simpleDefectMapLayout = new QHBoxLayout;
    mapTopBannerLayout = new QHBoxLayout;
    globalGrabButton = new QPushButton;

    globalGrabButton->setText("Start Camera(s)");
    globalGrabButton->setFocus();
    globalGrabButton->setFixedSize(200,50);
    globalGrabButton->setStyleSheet("QPushButton { background-color : lime; color : black; }");
    isGrabbing = false; //set to true for grabbing as soon as the camera opens or false for start grabbing on button press

    logoLayout->addWidget(globalGrabButton);
    logoLayout->addStretch();
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch();


    // add in all the camera widgets
    addCameras(cams,camLayout,sharedImageBuffer,NUMBER_OF_CAMERAS);

    addSimpleMapLabels(list_simpledMapLabels, simpleDefectMapLayout, OFFSET_CAMERA_0_TO_END_IN_FRAMES);
    
    mapTopBannerLayout->addStretch();
    mapTopBannerLayout->addLayout(simpleDefectMapLayout);

    layout->addLayout(logoLayout);
    layout->addLayout(mapTopBannerLayout);
    layout->addLayout(camLayout);

    this->setLayout(layout);

    setWindowTitle(tr("Fibrescan's First Window with Qwidgets"));


/*********************************************************************************
end of the layout
***********************************************************************************/

    // Connect button signal to appropriate slot
    connect(globalGrabButton, SIGNAL (clicked()), this, SLOT (handleGrabButton()));


   //QSize size = camLayout->sizeHint();
   //qDebug() << "from widget::widget(), label size (Width * Height)   " << size;
   // size = cams[0]->getSize();
   // qDebug() << "from CameraWidget::getSize(), label size (Width * Height)   " << size;

    //test
   // cams[0]->setText("test");

}

CameraContainer::~CameraContainer()
{
    //delete sharedImageBuffer;
    //sharedImageBuffer = NULL;
}

//add the Camera Widget and the buffers containing the mats which are all held in a hash table in the SharedImageBuffer class.

void CameraContainer::addCameras(QList<CameraWidget*>& p_CamWidgets, QVBoxLayout* p_layOut, SharedImageBuffer* sharedImBuf, int nCameras)
{
    for(int i = 0; i != nCameras ; ++i)
    {
        p_CamWidgets.push_back(new CameraWidget(this, i, NUMBEROFDEFECTIMAGESTODISPLAY, sharedImBuf));
        // p_CamWidgets[i]->setMinimumSize(1000,250);
        p_layOut->addWidget(p_CamWidgets[i]);
        p_layOut->addSpacing(1);

        // Create ImageBuffer with user-defined size
        Buffer<Mat> *imageBuffer = new Buffer<Mat>(DEFAULT_IMAGE_BUFFER_SIZE);
        bool syncEnabled = true; // setting up the cameras so they have the same frame
        //rate as the slowest. Set to "true" to enable. For free running cameras set to false
        // Add created ImageBuffer to SharedImageBuffer object
        sharedImBuf->add(i, imageBuffer, syncEnabled);



    }
    //TODO make this syncing command more elegent

    // Start processingaddSimpleMapLabels

    sharedImageBuffer->setSyncEnabled(true);
    // setting up the cameras so they have the same frame
    //rate as the slowest. Set to "true" to enable. For free running cameras set to false
    // Add created ImageBuffer to SharedImageBuffer object


    // connect to all the cameras after setting up the layout
    for(int i = 0; i != nCameras ; ++i)
    {
        p_CamWidgets[i]->connectToCamera(false, 3, 4, true, -1, -1);
    }


}

void CameraContainer::addSimpleMapLabels(QList<CsimpleDefectMapLabel *> pSimpleLabels, QHBoxLayout *p_simpleLayout, int nLabels)
{
    for(int i = 0; i != nLabels; ++i)
    {
    pSimpleLabels.push_back(new CsimpleDefectMapLabel());
    pSimpleLabels[i]->setFixedSize(5,20);
    pSimpleLabels[i]->setFrameStyle(QFrame::Box | QFrame::Raised);
    // p_CamWidgets[i]->setMinimumSize(1000,250);
    p_simpleLayout->addWidget(pSimpleLabels[i]);
    p_simpleLayout->addSpacing(1);
    }

}

SharedImageBuffer *CameraContainer::getSharedImageBuffer() const
{
    return sharedImageBuffer;
}

void CameraContainer::handleGrabButton()
{
   if (!isGrabbing)
   {
    isGrabbing = true;
    globalGrabButton->setStyleSheet("QPushButton { background-color : pink; color : black; }");
    globalGrabButton->setText("Freeze Camera(s)");
   }
   else
   {
       isGrabbing = false;
       globalGrabButton->setStyleSheet("QPushButton { background-color : lime; color : black; }");
       globalGrabButton->setText("Start Camera(s)");

   }

   for (int i = 0; i < cams.size(); i++)
   {
       cams[i]->setGrab(isGrabbing);
       cams[i]->setGrab(isGrabbing);
   }

}
