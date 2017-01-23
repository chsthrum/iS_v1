//qt includes
#include <QDebug>
#include <QString>

//local includes
#include "cameraContainer.h"
#include "ImagingStuff/Config.h"
#include "ImagingStuff/Structures.h"
#include "ExternalHardwareSoftware/baslerpylondart_1.h"
#include "ExternalHardwareSoftware/teledynedalsasapera_1.h"
#include "xmlStuff/readxmldatafromfile.h"


CameraContainer::CameraContainer(QWidget *parent, QVector<MachCamConfigFileXMLData>& vecXMLData): QWidget(parent)
{
    allCameraWidgetsActive = false; //NO cameras connected yet

    //read the MachineCameraConfiguration file
    //vecXMLData = readXMLDataFromFile("C:/Users/Fibrescan/Documents/iScanDev1/iS_v1/ConfigFilesXML/machineCameraConfig34BAS.xml");
    typedef QVector<MachCamConfigFileXMLData>::size_type vec_sz;


// are we using Basler Cameras?
    for (vec_sz i = 0; i < vecXMLData.size(); i++)
    {
        if(vecXMLData[i].ManufacturerType == "FS_BASLER_DART_PYLON_AREA")
            PylonInitialize();
            break;  // we just need to call PylonInitialize() once.
    }


// are we using TDalsa Cameras?
    bool foundCam = false;
    for (vec_sz i = 0; i < vecXMLData.size(); i++)
    {
        if(vecXMLData[i].ManufacturerType == "FS_TDALSA_GIGE_LINE_GRAY")
        {
            while (!foundCam) // we only want to find all the TDalsa cameras once
            {
            cameraLocations = findT_DalsaGigeCams(); //to hold the Gige cam locations (server/device pairs)
            foundCam = true;
            }
            vecXMLData[i].locs = cameraLocations; // add in the vector of Tdalsa camera servers and devices
        }
    }



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
    addCameras(cams,camLayout,sharedImageBuffer,vecXMLData);//, cameraLocs);

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


    allCameraWidgetsActive = true; // All cameras now connected

    qDebug() << "All Camera Widgets connected.\n";

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
    if (allCameraWidgetsActive)
    {
        typedef QList <CameraWidget*>::size_type list_size;
        for (list_size i = 0; i < cams.size(); i++)
        {
            delete cams[i]; //calls the cameraWidget destructor.
            cams[i] = NULL;
        }
        // Releases all pylon resources.
        Pylon::PylonTerminate(); // for the Basler cameras this line needs an if() qualification TODO
        //Continuity notes will probably have to include a copy or reference machCamXML struct; CHS 21JAN2017
    }

    qDebug() << "CameraContainer Destructor called.";
}

//add the Camera Widget and the buffers containing the mats which are all held in a hash table in the SharedImageBuffer class.

void CameraContainer::addCameras(QList<CameraWidget*>& p_CamWidgets, QVBoxLayout* p_layOut, SharedImageBuffer* sharedImBuf, QVector<MachCamConfigFileXMLData> vec_MachCamXMLData)//, QVector<LocationStruct> locs )
{
    int nCameras = vec_MachCamXMLData[0].NumberOfCameras.toInt();

    for(int i = 0; i != nCameras ; ++i)
    {
        p_CamWidgets.push_back(new CameraWidget(this, NUMBEROFDEFECTIMAGESTODISPLAY, sharedImBuf, vec_MachCamXMLData[i]));

        // p_CamWidgets[i]->setMinimumSize(1000,250);
        p_layOut->addWidget(p_CamWidgets[i]);
        p_layOut->addSpacing(1);
        // Create ImageBuffer with user-defined size
        Buffer<cv::Mat> *imageBuffer = new Buffer<cv::Mat>(DEFAULT_IMAGE_BUFFER_SIZE);
        bool syncEnabled = false; // setting up the cameras so they have the same frame
        //rate as the slowest. Set to "true" to enable. For free running cameras set to false
        // Add created ImageBuffer to SharedImageBuffer object
        sharedImBuf->add(i, imageBuffer, syncEnabled);


    }
    //TODO make this syncing command more elegent

    // Start processingaddSimpleMapLabels

    sharedImageBuffer->setSyncEnabled(false);
    // setting up the cameras so they have the same frame
    //rate as the slowest. Set to "true" to enable. For free running cameras set to false
    // Add created ImageBuffer to SharedImageBuffer object

    //if one of the cameras is a Basler Pylon series than allow pylon initilaisation
    // remember the destructor goes in the cameraContainer destructor
//    if (FS_BASLER_DART_PYLON_AREA)
//    {
//        //PylonAutoInitTerm autoInitTerm;
//        PylonInitialize();
//        // Note PylonTerminate() which releases all pylon resources is in the CameraContainer destructor.
//        // Get the transport layer factory. (Singleton so Global scope, so get by reference)
//        CTlFactory& tlFactory = CTlFactory::GetInstance();
//    }




    // connect to all the cameras after setting up the layout
    for(int i = 0; i != nCameras ; ++i)
    {
        p_CamWidgets[i]->connectToCamera(false, 3, 4, true, -1, -1, vec_MachCamXMLData[i]);
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
