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

    logoLayout->addStretch();
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch();


    addCameras(cams,camLayout,sharedImageBuffer,NUMBER_OF_CAMERAS);

    layout->addLayout(logoLayout);
    layout->addLayout(camLayout);

    this->setLayout(layout);

    setWindowTitle(tr("Fibrescan's First Window with Qwidgets"));


/*********************************************************************************
end of the layout
***********************************************************************************/


   //QSize size = camLayout->sizeHint();
   //qDebug() << "from widget::widget(), label size (Width * Height)   " << size;
   // size = cams[0]->getSize();
   // qDebug() << "from CameraWidget::getSize(), label size (Width * Height)   " << size;

    //test
   // cams[0]->setText("test");

}

CameraContainer::~CameraContainer()
{

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

    // Start processing

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
