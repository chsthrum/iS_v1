//local includes
#include "defectLabel.h"

DefectLabel::DefectLabel(QWidget *parent) : QLabel(parent)
{
    this->setText("No Defect.");
    this->setAlignment(Qt::AlignCenter);
}

DefectLabel::~DefectLabel()
{

}



void DefectLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        if (this->text().isNull())
            this->setText("WOW");
        else
            this->clear();

        this->setFixedSize(100,80);

    }
}
