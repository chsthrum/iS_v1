//qt includes
#include <QDebug>
//local includes
#include "pic2label.h"

ScaledLabel::ScaledLabel(QWidget *parent) : QLabel(parent)
{
    //this->setFrameStyle(QFrame::Box | QFrame::Raised);
    //this->setFixedSize(100,100);


}

ScaledLabel::~ScaledLabel()
{

}

void ScaledLabel::setPix(const QPixmap & p)
{
    pix = p;
}


QPixmap ScaledLabel::scaledPixmap() const
{
    //qDebug() << "this->sizeHint = " << this->sizeHint();
    //qDebug() << "this->size() = " << this->size();

    return pix.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

}

int ScaledLabel::heightForWidth( int width ) const       //width comes from the resize instruction width component
{

    return pix.isNull() ? this->height() : ((qreal)pix.height()*width)/pix.width();
}

QSize ScaledLabel::sizeHint() const
{
    int w = this->width();
    return QSize( w, heightForWidth(w) );
}


