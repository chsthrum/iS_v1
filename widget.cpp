//qt includes
#include <QDebug>
//local includes
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
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


    addCameras(cams,camLayout,5);

    layout->addLayout(logoLayout);
    layout->addLayout(camLayout);

    this->setLayout(layout);

    setWindowTitle(tr("Fibrescan's First Window with Qwidgets"));


/*********************************************************************************
end of the layout
***********************************************************************************/

    // Create SharedImageBuffer object
    sharedImageBuffer = new SharedImageBuffer();
    QSize size = camLayout->sizeHint();
    qDebug() << "from widget::widget(), label size (Width * Height)   " << size;
    size = cams[0]->getSize();
    qDebug() << "from CameraWidget::getSize(), label size (Width * Height)   " << size;

    //test
    cams[0]->setText("test");
 }

Widget::~Widget()
{

}

void Widget::addCameras(QList<CameraWidget*>& p_CamWidgets, QVBoxLayout* p_layOut,int limit)
{
    for(int i = 0; i != limit ; ++i)
    {
        p_CamWidgets.push_back(new CameraWidget(this, i));
       // p_CamWidgets[i]->setMinimumSize(1000,250);
        p_layOut->addWidget(p_CamWidgets[i]);
        p_layOut->addSpacing(1);
    }


}
